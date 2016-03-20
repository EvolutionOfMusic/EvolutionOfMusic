clear
clc

S = 8192/2;
note = @(f,d) 0.9*cos(2*pi*f*[0:1/S:d]);
tempo = @(bbm) bbm/16;
time = @(hold, pause, bbm) (hold - pause)/tempo(bbm);
FS = [];fs = [];ds = [];

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
        fs = [];
        ds = [];
        num_notes = sscanf(fgetl(file), '%d'); 
        [volume, track_id] = sscanf(fgetl(file), '%d %d');
        clear volume track_id;
        for k = 1:num_notes
            temp = sscanf(fgetl(file), '%d %d %d');
            fs = [fs, tone_freq(temp(2))];
            ds = [ds, time(temp(3), temp(1), 40)];
        end
        
        new_fs = [];
        for index=1:length(ds)
            new_fs = [new_fs note(fs(index), ds(index))];
        end
        %noteReturn = note(fs(1), ds(1));
        [rowsFS columnsFS] = size(FS);
        [rowsfs columnsfs] = size(fs);
        delta = abs(columnsfs - columnsFS);
        
        %Preparation
        if (columnsfs > columnsFS)
            insert = zeros(rowsFS, columnsfs - columnsFS);
            FS = [FS insert];
        elseif (columnsFS > columnsfs)
            new_fs = [new_fs zeros(1, columnsFS - columnsfs)];
        end
        % Polymerzation!
        FS = [FS;new_fs];
    end 
    out_file = sprintf('sample_%d.wav', song_id);
    audiowrite(out_file, FS, S) 
end
fclose(file) 