#include <stdio.h>
#include "includes.h"
#include "altera_avalon_fifo_util.h"
#include "altera_avalon_fifo_regs.h"
#include "altera_avalon_fifo.h"
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "altera_up_avalon_character_lcd.h"

#define   BUFFER_SIZE    	128

/* Definition of Task Stacks */
#define   AUDIO_TASK_STACKSIZE 	100000
#define   LASER_INPUT_TASK_STACKSIZE	5000
#define   UI_TASK_STACKSIZE	5000

/* Definition of Task Priorities */
#define LASER_INPUT_TASK_PRIORITY  	1
#define UI_TASK_PRIORITY			2
#define AUDIO_TASK_PRIORITY      	3

OS_STK    audioTaskStack[AUDIO_TASK_STACKSIZE];
OS_STK    laserInputTaskStack[LASER_INPUT_TASK_STACKSIZE];
OS_STK    uiTaskStack[UI_TASK_STACKSIZE];

OS_EVENT * laserStatusChanged;
OS_EVENT * settingChanged;

int scaleIndex = 0;
int baseTranspose = 0;
/* Prints "Hello World" and sleeps for three seconds */
void audioTask(void* pdata){
	INT8U err;
    alt_up_audio_dev * audio_dev;
    alt_up_av_config_dev * audio_config_dev;
    volatile unsigned int level;
    unsigned int buffer[BUFFER_SIZE];
    int i = 0;

    audio_config_dev = alt_up_av_config_open_dev("/dev/audio_and_video_config_0");
    if ( audio_config_dev == NULL)
        printf("Error: could not open audio config device \n");
    else
        printf("Opened audio config device \n");

    /* Open Devices */
    audio_dev = alt_up_audio_open_dev ("/dev/audio_0");
    if ( audio_dev == NULL)
        printf("Error: could not open audio device \n");
    else
        printf("Opened audio device \n");

    /* Configure WM8731 */
    alt_up_av_config_reset(audio_config_dev);
    alt_up_audio_reset_audio_core(audio_dev);

    /* Write to configuration registers in the audio codec; see datasheet for what these values mean */
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x0, 0x17);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x1, 0x17);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x2, 0x68);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x3, 0x68);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x4, 0x15);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x5, 0x06);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x6, 0x00);
	altera_avalon_fifo_init(FIFO_0_OUT_CSR_BASE, 0x0, 10, FIFO_0_OUT_CSR_FIFO_DEPTH-10);
	altera_avalon_fifo_read_fifo(FIFO_0_OUT_BASE, FIFO_0_OUT_CSR_BASE);

	while (1){
		level =  altera_avalon_fifo_read_level(FIFO_0_OUT_CSR_BASE);
		if (level>0){
			for (i=0;i<level;i++){
				buffer[i]= ((altera_avalon_fifo_read_fifo(FIFO_0_OUT_BASE, FIFO_0_OUT_CSR_BASE)>>16) + 0x7fff)/2;
			}
		}
        alt_up_audio_write_fifo (audio_dev, buffer, level, ALT_UP_AUDIO_RIGHT);
        alt_up_audio_write_fifo (audio_dev, buffer, level, ALT_UP_AUDIO_LEFT);
		OSTimeDlyHMSM(0, 0, 0, 1);
	}

}

/* Prints "Hello World" and sleeps for three seconds */
void laserInputTask(void* pdata){
	INT8U err;
	alt_u32* laserStatusPointer =(alt_u32* )SWITCH_BASE;
	alt_u32* midiOutPointer = (alt_u32*) MIDIOUT_0_BASE;
	alt_u32* voiceAddr =SYNTHESIZER_0_BASE;

	alt_u32 laserStatus = 0;
	alt_u32 previousLaserStatus = 0;
	alt_u32 differentBits = 0;
	int noteType;
	int laserIndex=0;

	while (1){
		OSSemPend(laserStatusChanged, 0, &err);
		previousLaserStatus = laserStatus;						// save previous laserstatus
		laserStatus = 255 - *laserStatusPointer; 				// inverse 8bits input
		differentBits = previousLaserStatus^laserStatus;		// XOR: 100 ^ 110 = 010

		for (laserIndex=0;laserIndex<8;laserIndex++){
			//if laser i is changed
			if( ((1 << laserIndex) & (differentBits)) == (1 << laserIndex) ){
				//get notetype 1 on   0 off
				noteType = ((laserStatus &  (1 << laserIndex)) ==  (1 << laserIndex)) ?  1: 0;
				//write to midi out
				*midiOutPointer = generateMidiData(getPitch(scaleIndex,laserIndex)+baseTranspose,noteType);
				//write to on board synth
				sendNoteSynthesizer(getPitch(scaleIndex,laserIndex)+baseTranspose,noteType);
				OSTimeDlyHMSM(0, 0, 0, 2);

			}
		}
	}
}

void uiTask(void* pdata){
	INT8U err;
	alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");
	if ( char_lcd_dev == NULL){
		alt_printf ("Error: could not open character LCD device\n");
	}
	else{
		alt_printf ("Opened character LCD device\n");
	}
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_cursor_off(char_lcd_dev);

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 0);
	alt_up_character_lcd_string(char_lcd_dev, "Laser Harp");

	while(1){
		OSSemPend(settingChanged, 0, &err);
		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
        switch(baseTranspose){
        	case -5:
    			alt_up_character_lcd_string(char_lcd_dev, "G  ");
    			break;
        	case -4:
    			alt_up_character_lcd_string(char_lcd_dev, "Ab ");
    			break;
        	case -3:
    			alt_up_character_lcd_string(char_lcd_dev, "A  ");
    			break;
        	case -2:
    			alt_up_character_lcd_string(char_lcd_dev, "Bb ");
    			break;
        	case -1:
    			alt_up_character_lcd_string(char_lcd_dev, "B  ");
    			break;
        	case 0:
    			alt_up_character_lcd_string(char_lcd_dev, "C  ");
    			break;
        	case 1:
    			alt_up_character_lcd_string(char_lcd_dev, "C# ");
    			break;
        	case 2:
    			alt_up_character_lcd_string(char_lcd_dev, "D  ");
    			break;
        	case 3:
    			alt_up_character_lcd_string(char_lcd_dev, "Eb ");
    			break;
        	case 4:
    			alt_up_character_lcd_string(char_lcd_dev, "E  ");
    			break;
        	case 5:
    			alt_up_character_lcd_string(char_lcd_dev, "F  ");
    			break;
        	case 6:
    			alt_up_character_lcd_string(char_lcd_dev, "F# ");
    			break;
        }


        switch(scaleIndex){
        	case 0:
    			alt_up_character_lcd_string(char_lcd_dev, "Major Scale ");
    			break;
        	case 1:
    			alt_up_character_lcd_string(char_lcd_dev, "Minor Scale ");
    			break;
        	case 2:
    			alt_up_character_lcd_string(char_lcd_dev, "Blue Scale  ");
    			break;
        	case 3:
    			alt_up_character_lcd_string(char_lcd_dev, "Doran Scale ");
    			break;
        }

	}
}

static void laserChangeHandler( void * context){
	OSSemPost(laserStatusChanged);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE, 0xff);
}

static void button1Handler(void * context){
	scaleIndex ++;
	if (scaleIndex>3){
		scaleIndex = 0;
	}
	OSSemPost(settingChanged);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_1_BASE, 0x1);
}
static void button2Handler(void * context){
	baseTranspose ++;
	if (baseTranspose>6){
		baseTranspose = -5;
	}
	OSSemPost(settingChanged);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_2_BASE, 0x1);
}

/* The main function creates two task and starts multi-tasking */
int main(void){
	laserStatusChanged = OSSemCreate(0);
	settingChanged = OSSemCreate(1);
	alt_ic_isr_register(SWITCH_IRQ_INTERRUPT_CONTROLLER_ID, //alt_u32 ic_id
						SWITCH_IRQ, //alt_u32 irq
						laserChangeHandler, //alt_isr_func isr
						NULL,
						NULL);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCH_BASE,0xff);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH_BASE, 0xff);

	alt_ic_isr_register(BUTTON_1_IRQ_INTERRUPT_CONTROLLER_ID, //alt_u32 ic_id
						BUTTON_1_IRQ, //alt_u32 irq
						button1Handler, //alt_isr_func isr
						NULL,
						NULL);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_1_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_1_BASE, 0x1);

	alt_ic_isr_register(BUTTON_2_IRQ_INTERRUPT_CONTROLLER_ID, //alt_u32 ic_id
						BUTTON_2_IRQ, //alt_u32 irq
						button2Handler, //alt_isr_func isr
						NULL,
						NULL);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_2_BASE,0x1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_2_BASE, 0x1);

	OSTaskCreateExt(audioTask,
				  NULL,
				  (void *)&audioTaskStack[AUDIO_TASK_STACKSIZE-1],
				  AUDIO_TASK_PRIORITY,
				  AUDIO_TASK_PRIORITY,
				  audioTaskStack,
				  AUDIO_TASK_STACKSIZE,
				  NULL,
				  0);

	OSTaskCreateExt(laserInputTask,
				  NULL,
				  (void *)&laserInputTaskStack[LASER_INPUT_TASK_STACKSIZE-1],
				  LASER_INPUT_TASK_PRIORITY,
				  LASER_INPUT_TASK_PRIORITY,
				  laserInputTaskStack,
				  LASER_INPUT_TASK_STACKSIZE,
				  NULL,
				  0);

	OSTaskCreateExt(uiTask,
				  NULL,
				  (void *)&uiTaskStack[UI_TASK_STACKSIZE-1],
				  UI_TASK_PRIORITY,
				  UI_TASK_PRIORITY,
				  uiTaskStack,
				  UI_TASK_STACKSIZE,
				  NULL,
				  0);

	OSStart();
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");
	printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");printf(".");

	return 0;
}
