library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
    use IEEE.std_logic_arith.all;
    use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
    use IEEE.std_logic_signed.all;
    use IEEE.std_logic_unsigned.all;
	
use work.SynthesizerPackage.all;

entity AudioSynthesis is
  port (
    -- DE2 required signals
    clk      			: in  std_logic;

	--Address input
	freq_address  		: in std_logic_vector(11 downto 0);
	instrument_address  : in std_logic_vector(4 downto 0);
	
	--Audio output
	audioData 			: out WAVE_ARRAY
  )
end entity;

architecture instrumentSynthesis of AudioSynthesis is
	type instrument_function is envelope
		audioData		:	WAVE_ARRAY;
		function_length	:	std_logic_vector;
	end envelope;
	
	signal 	sineData, brassData, windData, percussiveData : WAVE_ARRAY;
begin
	sinLut: SinLut
		port map(
			clk 		=> clk,
			address 	=> freq_addr,
			audioData 	=> sineData
		);
	
	brassLut: BrassLut
		port map(
			clk 		=> clk,
			address 	=> freq_addr,
			audioData 	=> brassData
		);
	
	windLut: WindLut
		port map(
			clk 		=> clk,
			address 	=> freq_addr,
			audioData 	=> windData
		);
	
	percussiveLut: PercussiveLut
		port map(
			clk 		=> clk,
			address 	=> freq_addr,
			audioData 	=> percussiveData
		);
		
	rom_select: process (clk)
		variable i : integer := 0;
	begin
		if clk'event and clk = '1' then
			with instrument_address select audioData(i) <=
			--	audioData(i)	|	Instrument Address
				sineData 		when "00000" else 
				brassData 		when "00001" else
				windData 		when "00010" else
				percussiveData 	when "00011";
		end if;
	end process rom_select;
	
end instrumentSynthesis;
