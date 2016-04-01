function [ note ] = freq_2_amp( a, f, T )
% http://www.mathworks.com/matlabcentral/newsreader/view_thread/136160
% T is the duration of the note
% f is the frequency in Hertz
% a is the amplitude or Volume
note = a*sin(2*pi*f*[0:1/(2*S):T]);

end

