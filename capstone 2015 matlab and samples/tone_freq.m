function [ freq ] = tone_freq( tone ) 
    freqs = [523 554 587 622 659 698 740 784 831 880 932];
    if tone == 0 
        freq = 0;
    elseif mod(tone, 12) > 0 
        freq = freqs(mod(tone, 12)); 
    else 
        freq = 988;
    end
end

