#include "python3_to_cpp_converter.h"
// All EFSL files are in a source folder "efsl" in the Eclipse project
// with no further directory nesting underneath.
#include <efsl/efs.h>
#include <efsl/ls.h>

Song read_sd(void){
    // Create EFSL containers
    EmbeddedFileSystem efsl;
    
    char fileName[LIST_MAXLENFILENAME] = {"music"}; // reading the file "music"
    File readFile;
    
    // Initialises the filesystem on the SD card, if the filesystem does not
    // init properly then it displays an error message.
    printf("Attempting to init filesystem");
    int ret = efs_init(&efsl, SD_CARD_SPI_MASTER_NAME);
    
    // Initialize efsl
    if(ret != 0){
        printf("...could not initialize filesystem.\n");
        return 1;
    } else {
        printf("...success!\n");
    }
    
    // You could do some scanning of the file system here using the UNIX-like
    // API functions such as "ls_openDir(...)" and "ls_getNext(...). Reference
    // the included PDF for the documentation to do such a thing. This example
    // simply shows reading a file with a known filename.
    
    // Open the test file
    printf("\nAttempting to open file: \"%s\"\n", fileName);
    
    if (file_fopen(&readFile, &efsl.myFs, fileName, 'r') != 0) {
        printf("Error:\tCould not open file\n");
        return 1;
    } else {
        printf("Reading file...\n");   
    }
    
    // Create a memory buffer to read the file into
    euint8 *fileBuffer = malloc(readFile.FileSize * sizeof(euint8));
    if (!fileBuffer){
        printf("malloc failed!\n");
        return 1;
    }
    
    // Read all the file's contents into the buffer. See the file_fread(...) function
    // for the ability to read chunks of the file at a time, which is desirable for
    // larger files.
    unsigned int bytesRead = file_read(&readFile, readFile.FileSize, fileBuffer);
    
    printf("%u bytes read from the file\n", bytesRead); 
    
    // Close the file
    if (file_fclose(&readFile) != 0){
        printf("Error:\tCould not close file properly\n");
        return 1;   
    }
    
    /*// Print out the contents
    printf("\nFile contents (in hex):\n");
    int j;
    for (j = 0; j < bytesRead; ++j)
        printf(" 0x%02X", fileBuffer[j]);*/
    
    Song song = get_song_N(fileBuffer);
    
    // Free the file buffer memory
    free(fileBuffer);
    
    // Unmount the file system
    fs_umount(&efsl.myFs);
    
    return song;
}

Song get_song_N(euint8 file) {
    static int N = -1, NUM_SONGS;
    int NUM_TRACKS, NUM_NOTES;
    char file_line[20];
	
	if (N == -1) {
		// Number of Songs
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &NUM_SONGS);
		
		N++;
	}
	
	// Make a new song
	Song song;
	for (int i = 0;i < N && N < NUM_SONGS;i++) {
		// Number of Tracks
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &NUM_TRACKS);
		
		// Tempo
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &song.tempo);
		
		// SongID
		file.getline(file_line, 20);
		sscanf(file_line, "%d", &song.song_id);
		
		for (int j = 0;j < NUM_TRACKS;j++) {
			// Number of Notes
			file.getline(file_line, 20);
			sscanf(file_line, "%d", &NUM_NOTES);
		
			// Instrument ID, Volume
			file.getline(file_line, 20);
			sscanf(file_line, "%d %d", 
				&song.tunes[j].instrument_id, 
				&song.tunes[j].volume);
			
			for (int k = 0;k < NUM_NOTES;k++) {
				// Pause Time, Tone, Hold Time
				int a, b, c;
				file.getline(file_line, 20);
				sscanf(file_line, "%d %d %d", &a, &b, &c);
				song.tunes[j].channel[k].pause_time = a; 
				song.tunes[j].channel[k].tone = b;
				song.tunes[j].channel[k].hold_time = c;
			}
		}
	}
	N++;
}
