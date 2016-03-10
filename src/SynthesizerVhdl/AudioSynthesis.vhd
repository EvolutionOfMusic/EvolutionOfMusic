library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
--    use IEEE.std_logic_arith.all;
--    use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
--    use IEEE.std_logic_signed.all;
--    use IEEE.std_logic_unsigned.all;
	
use work.SynthesizerPackage.all;

package instr_class is
--	type audioData is (WAVE_ARRAY);
--	type function_length is (INTEGER);
	
	function get_audio return WAVE_ARRAY;
	function get_size return INTEGER;
	
	procedure sample(audioOut : out WAVE_ARRAY);
end instr_class;

package body instr_class is
	procedure sample(audioOut : out WAVE_ARRAY; freq_address : in std_logic_vector(11 downto 0)) is
		variable i : integer := 0;
	begin
		for i in 0 to 0 loop
			--what is freq_address supposed to be? I'm assuming its supposed to be freq_address
			audioOut(i) := freq_address & "0000";	
		end loop;
	end procedure;
end instr_class;

library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
--  use IEEE.std_logic_arith.all;
--  use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
	
library work;
	use work.all;
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
  );
end entity;

architecture instrumentSynthesis of AudioSynthesis is
	
begin

	--sinLut: SinLut
	--	port map(
	--		clk 		=> clk,
	--		address 	=> freq_addr,
	--		audioData 	=> sineData
	--	);
	--	
	--rom_select: process (clk)
	--	variable i : integer := 0;
	--begin
	--	if clk'event and clk = '1' then
	--		with instrument_address select audioData(i) <=
	--		--	audioData(i)	|	Instrument Address
	--			sineData 		when "00000" else 
	--			brassData 		when "00001" else
	--			windData 		when "00010" else
	--			percussiveData 	when "00011";
	--	end if;
	--end process rom_select;
	
	
	rom_select: process (clk)
		variable i : integer := 0;
	begin
		if clk'event and clk = '1' then
			--does not work, its a procedure so I don't what it wants
			--instrument.sample(audioOut => audioData; freq_address => freq_address);
		end if;
	end process rom_select;
	
end instrumentSynthesis;
