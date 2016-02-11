/* 
 * File:   main.cpp
 * Author: leeingram
 *
 * Created on February 8, 2016, 10:20 AM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>


using namespace std;

/*
 * 
 */
enum status {EOT, EOS, EOSF};

status parse_track(struct Track &track_ptr, ifstream &file){
    char file_line[20];
    char flow_control; 
    static int i = 0, j = 0;   
    status function_status;
    long int pause_time, hold_time, tone;
    
    
    if(file.is_open()){ 
        while(1) { 
            file.getline(file_line, 20);
            
            flow_control = file_line[0];
            if(flow_control == '%'){
                function_status = EOT;
                break;
            }
            
            if(flow_control == '*'){
                function_status = EOS;
                break;
            }
            cout << "line 43" << endl;
            if(flow_control == '#'){
                function_status = EOSF;
                break;
            }
            
            if(i == 0){
                track_ptr.instrument_id = atol(file_line);
            } else if (i == 1) {
                track_ptr.volume = atol(file_line);
            } else {
                sscanf(file_line, "%d %d %d", &pause_time, &tone, &hold_time);
                track_ptr.channel[j].hold_time = hold_time;
                track_ptr.channel[j].pause_time = pause_time;
                track_ptr.channel[j].tone = tone;
                j++;
            } 
            
            i++;
            
        } 
    }
    
    i = 0;
    j = 0;
    
    return function_status;
}


status get_song(){
    status function_status;
    streampos last_line;
    ifstream file;
    
    if(function_status == EOT){
        last_line = file.tellg();
    } else if(function_status == EOS){
        last_line = file.tellg();
    } else {
        last_line = NULL;
    }
    return EOT;
}

int main(int argc, char** argv) {  
    struct Track test_track;
    status read_status;
    char songid[5];
    
    
    ifstream file("main_py_output");
    
    file.getline(songid, 5);
    
    read_status = parse_track(test_track, file);
    
    cout << test_track.instrument_id << endl;
    cout << test_track.volume << endl;
    
    return 0;
}

