clear
clc

FS = 8912;
% http://www.mathworks.com/matlabcentral/newsreader/view_thread/136160
% T is the duration of the note
% f is the frequency in Hertz
% a is the amplitude or Volume
note = @(a,f,T) a*cos(2*pi*f*[0:1/FS:T]);
tempo = @(bpm) 16*bpm/60; 
% 16 (1/16 beats) = 1 beat
% 1 bpm = 16 (1/16 beats)/min  
% 60 sec = 1 min  
% 1 bpm = 60*16 (1/16th beats) / sec
time = @(hold, pause, bpm) (hold - (pause/2))/tempo(bpm);

song_file = input('Enter file name: ');

file = fopen(song_file, 'r');
clear song_file;

num_songs = sscanf(fgetl(file), '%d');
for i = 1:num_songs
    num_tracks = sscanf(fgetl(file), '%d');
    tempo = sscanf(fgetl(file), '%d');
    song_id = sscanf(fgetl(file), '%d');
    SONG = [];
    
    for j = 1:num_tracks
        CHANNEL = zeros(1, 160); TIMES = zeros(1, 160);
        num_notes = sscanf(fgetl(file), '%d'); 
        tuple = sscanf(fgetl(file), '%d %d');
        volume = tuple(1, 1); track_id = tuple(2, 1);
        clear track_id;
        for k = 1:num_notes
            temp = sscanf(fgetl(file), '%d %d %d');
            CHANNEL(k) = tone_freq(temp(2));%
            %CHANNEL = [CHANNEL, tone_freq(temp(2))];
            TIMES(k) = time(temp(3), temp(1), tempo);%
            %TIMES = [TIMES, time(temp(3), temp(1), 40)];
        end
        
        SCALED_FREQUENCIES = [];
        for index=1:length(TIMES)
            SCALED_FREQUENCIES = [SCALED_FREQUENCIES note(0.8, CHANNEL(index), TIMES(index))];
        end
        
        [rowsSONG, columnsSONG] = size(SONG);
        [rowsFREQUENCIES, columnsFREQUENCIES] = size(SCALED_FREQUENCIES);
        
        %Preparation
        if (columnsFREQUENCIES > columnsSONG)
            SONG = [SONG zeros(1, columnsFREQUENCIES - columnsSONG)];
        end
        SONG(1:columnsFREQUENCIES) = (SONG(1:columnsFREQUENCIES)) + (SCALED_FREQUENCIES(1:columnsFREQUENCIES)./(num_tracks));
    end
    SONG = SONG';
    out_file = sprintf('sample_%d.wav', song_id);
    audiowrite(out_file, SONG, FS);
end
fclose(file);
