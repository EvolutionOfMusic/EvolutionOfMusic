S = 8192;
note = @(f,d) 0.9*cos(2*pi*f*[0:1/S:d]);
tempo = @(bbm) bbm/16;
time = @(hold, pause, bbm) (hold - pause)/tempo(bbm);
fs = [];
ds = [];
file = fopen('song_file', 'r');

file_line = fgetl(file);
while ischar(file_line)
    temp = sscanf(file_line, '%d %d %d');
    fs = [fs, tone_freq(temp(2))];
    ds = [ds, time(temp(3), temp(1), 100)];
    file_line = fgetl(file);
end 
fclose(file);

for index=1:numel(fs)
    fs = [fs note(fs(index), ds(index))];
end
audiowrite('sample2.wav', fs, S)