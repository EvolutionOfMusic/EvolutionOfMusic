/*************************************************************************
* Description:                                                           *
* The following is the microC code demonstrating use of the Altera       *
* University IP Cores                                                    *
**************************************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "includes.h"
#include "altera_up_avalon_audio.h"
#include "altera_up_avalon_audio_regs.h"
#include "altera_up_avalon_audio_and_video_config.h"
#include "system.h"


/* Definition of Task Stacks and priorities */
#define     AUDIO_DATA_TASK_STACKSIZE   2048
#define     AUDIO_DATA_TASK_PRIORITY    1
OS_STK      audio_data_task_stk[AUDIO_DATA_TASK_STACKSIZE];

/* Other defines */
#define     BUFFER_SIZE    1


/* Handle audio data movement */
void audio_data_task(void* pdata)
{
	printf("Beginning\n");

    alt_up_audio_dev * audio_dev;
    alt_up_av_config_dev * audio_config_dev;
    unsigned int *SynthesizerBase = (unsigned int *) 0x1109074;

    unsigned int l_buf[BUFFER_SIZE];
    int testTone = 56;
    int i = 0, j = 0, returnValue[2];
    int writeSizeL = BUFFER_SIZE;

    /* Open Devices */
    /*audio_dev = alt_up_audio_open_dev ("/dev/synthesizer_0");
    if ( audio_dev == NULL)
        printf("Error: could not open audio device \n");
    else
        printf("Opened audio device \n");

    audio_config_dev = alt_up_av_config_open_dev("/dev/audio_and_video_config_0");
    if ( audio_config_dev == NULL)
        printf("Error: could not open audio config device \n");
    else
        printf("Opened audio config device \n");*/

    /* Configure WM8731 */
    audio_config_dev = alt_up_av_config_open_dev(AUDIO_AND_VIDEO_CONFIG_0_NAME);
    //alt_up_audio_reset_audio_core(audio_dev);
    returnValue[0] = alt_up_av_config_reset(audio_config_dev);

    /* Write to configuration registers in the audio codec; see datasheet for what these values mean */
    /*
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x0, 0x17);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x1, 0x17);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x2, 0x68);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x3, 0x68);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x4, 0x1A);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x5, 0x06);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x6, 0x00);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x7, 0x3E);
    alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x9, 0x01);*/

    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x0, 0x17);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x1, 0x17);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x2, 0x70);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x3, 0x70);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x4, 0x1A);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x5, 0x0C);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x6, 0x00);
    returnValue[0] = alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x7, 0x0D);
    //alt_up_av_config_write_audio_cfg_register(audio_config_dev, 0x9, 0x01);

    printf("Starting\n");

    //main loop
    while(1)
    {
            //read the data from the left buffer
            //writeSizeL = alt_up_audio_read_fifo(audio_dev, l_buf, BUFFER_SIZE, ALT_UP_AUDIO_LEFT);

            //shift values to a proper base value
            for (i = 0; i < writeSizeL; i = i+1)
            {
            	l_buf[i]= (2000000 + 100000*j++%2000000);
            }

            //write data to the L and R buffers; R buffer will receive a copy of L buffer data
            SynthesizerBase = l_buf[i];

            //if(j%(32768/2) == 0)
            	//printf("data written:%i\n buffer[0]:%i\n", l_buf[0], writeSizeL);

    }

}


/* main task */
int main(void)
{

    OSTaskCreateExt(audio_data_task,
                  NULL,
                  (void *)&audio_data_task_stk[AUDIO_DATA_TASK_STACKSIZE-1],
                  AUDIO_DATA_TASK_PRIORITY,
                  AUDIO_DATA_TASK_PRIORITY,
                  audio_data_task_stk,
                  AUDIO_DATA_TASK_STACKSIZE,
                  NULL,
                  0);

    OSStart();
    return 0;
}
