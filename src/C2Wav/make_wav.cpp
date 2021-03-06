/* make_wav.c
 * Creates a WAV file from an array of ints.
 * Output is monophonic, signed 16-bit samples
 * copyright
 * Fri Jun 18 16:36:23 PDT 2010 Kevin Karplus
 * Creative Commons license Attribution-NonCommercial
 *  http://creativecommons.org/licenses/by-nc/3.0/
 */
/* modified by Stephen based on www-mmsp.ece.mcgill.ca/documents/audioformats/wave/wave.html and https://blogs.msdn.microsoft.com/dawate/2009/06/23/intro-to-audio-programming-part-2-demystifying-the-wav-format/ */

#include "make_wav.h"
 
void write_little_endian(unsigned int word, int num_bytes, FILE *wav_file){
    unsigned buf;
    while(num_bytes>0){
	buf = word & 0xff;/* write a byte at a time */
        fwrite(&buf, 1,1, wav_file);
        num_bytes--;
	word >>= 8;
    }
}
 
/* information about the WAV file format from
    http://ccrma.stanford.edu/courses/422/projects/WaveFormat/
 */
 
void write_wav(char * filename, unsigned long num_samples, double * data, int s_rate) {
    FILE* wav_file;
    unsigned int sample_rate;
    unsigned int num_channels;
    unsigned int bytes_per_sample;
    unsigned int byte_rate;
    unsigned long i;    /* counter for samples */
 
    num_channels = 1;   /* monoaural */
    bytes_per_sample = 2;
 
    if (s_rate <= 0) sample_rate = 44100;
    else sample_rate = (unsigned int) s_rate;
 
    byte_rate = sample_rate*num_channels*bytes_per_sample;
 
    wav_file = fopen(filename, "wb");
    assert(wav_file);   /* make sure it opened */
 
    /* write RIFF header */
    fwrite("RIFF", 1, 4, wav_file);
    write_little_endian(36 + bytes_per_sample* num_samples*num_channels, 4, wav_file); /* Tells the wav how many bytes there are */
    fwrite("WAVE", 1, 4, wav_file);
 
    /* write fmt  subchunk */
    fwrite("fmt ", 1, 4, wav_file);
    write_little_endian(16, 4, wav_file);   /* SubChunk1Size is 16 */
    write_little_endian(1, 2, wav_file);    /* PCM is format 1 */
    write_little_endian(num_channels, 2, wav_file);
    write_little_endian(sample_rate, 4, wav_file);
    write_little_endian(byte_rate, 4, wav_file);
    write_little_endian(num_channels*bytes_per_sample, 2, wav_file);  /* block align */
    write_little_endian(8*bytes_per_sample, 2, wav_file);  /* bits/sample */
 
    /* write data subchunk */
    fwrite("data", 1, 4, wav_file);
    write_little_endian(bytes_per_sample*num_samples, 4, wav_file);/* data chunk size */
    for (i = 0;i < num_samples;i++)//
	write_little_endian(((unsigned int)data[i]),bytes_per_sample, wav_file); /* translates float to 32-bit */
	/* writes the Song into the WAV */
 
    fclose(wav_file);
}

/*Example usage:
/* test_make_wav.c
 * Fri Jun 18 17:13:19 PDT 2010 Kevin Karplus
 * Test program for the write_wav function in make_wav.c
 */
/* 
#include <math.h>
#include "make_wav.h"
 
#define S_RATE  (44100)
#define BUF_SIZE (S_RATE*2) /* 2 second buffer /
 
int buffer[BUF_SIZE];
 
int main(int argc, char ** argv)
{
    int i;
    float t;
    float amplitude = 32000;
    float freq_Hz = 440;
    float phase=0;
 
    float freq_radians_per_sample = freq_Hz*2*M_PI/S_RATE;
 
    /* fill buffer with a sine wave /
    for (i=0; i<BUF_SIZE; i++)
    {
        phase += freq_radians_per_sample;
    buffer[i] = (int)(amplitude * sin(phase));
    }
 
    write_wav("test.wav", BUF_SIZE, buffer, S_RATE);
 
    return 0;
}
*/
