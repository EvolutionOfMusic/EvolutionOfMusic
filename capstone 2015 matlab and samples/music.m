clear
clc

S = 8192;
% http://www.mathworks.com/matlabcentral/newsreader/view_thread/136160
% T is the duration of the note
% f is the frequency in Hertz
% a is the amplitude or Volume
note = @(a,f,T) a*sin(2*pi*f*[0:1/S:T]);
tempo = @(bpm) bpm; 
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
    FS = [];
    
    for j = 1:num_tracks
        fs = []; ds = [];
        num_notes = sscanf(fgetl(file), '%d'); 
        tuple = sscanf(fgetl(file), '%d %d');
        volume = tuple(1, 1); track_id = tuple(2, 1);
        clear track_id;
        for k = 1:num_notes
            temp = sscanf(fgetl(file), '%d %d %d');
            fs = [fs, tone_freq(temp(2))];
            ds = [ds, time(temp(3), temp(1), 40)];
        end
        
        new_fs = [];
        for index=1:length(ds)
            new_fs = [new_fs note(0.9, fs(index), ds(index))];
        end
        
        [rowsFS columnsFS] = size(FS);
        [rowsfs columnsfs] = size(new_fs);
        
        %Preparation
        if (num_tracks == 1)
            FS = new_fs;
        elseif (j < num_tracks/2)
            if (j == 1)
                FS = new_fs./(num_tracks);
            elseif (columnsfs > columnsFS)
                FS = [FS zeros(rowsFS, columnsfs - columnsFS)];
                FS(1:columnsfs) = (FS(1:columnsfs)) + (new_fs./(num_tracks));
            else
                FS(1:columnsfs) = (FS(1:columnsfs)) + (new_fs./(num_tracks));
            end
        else
            if ((mod(num_tracks, 2) == 0 && j == floor(num_tracks/2)) || (mod(num_tracks, 2) == 1 && j == floor(num_tracks/2)+1))
                if (columnsfs > columnsFS)
                    FS = [FS zeros(rowsFS, columnsfs - columnsFS)];
                elseif (columnsFS > columnsfs)
                    new_fs = [new_fs zeros(1, columnsFS - columnsfs)];
                end
                FS = [FS;new_fs./(num_tracks/2)];
            elseif (columnsfs > columnsFS)
                FS = [FS zeros(rowsFS, columnsfs - columnsFS)];
                FS(2, 1:columnsfs) = FS(2, 1:columnsfs) + (new_fs./(num_tracks));
            else
                FS(2, 1:columnsfs) = FS(2, 1:columnsfs) + (new_fs./(num_tracks));
            end
        end
    end
    FS = FS';
    out_file = sprintf('sample_%d.wav', song_id);
    audiowrite(out_file, FS, S);
end
fclose(file);
