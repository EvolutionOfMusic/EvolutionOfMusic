-- Author: Peter Crinklaw

--Top Level file for Sythesizer component. Hides avalon interface specs
--from the main Synthesizer component.
library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
    use IEEE.std_logic_arith.all;
    --use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
    use IEEE.std_logic_signed.all;
    use IEEE.std_logic_unsigned.all;
	
use work.SynthesizerPackage.all;	

	
entity SynthesizerTopLevel is
port (
	-- system signals
	csi_clk50M			: in  std_logic;
	reset_n				: in  std_logic;
	csi_clk32k			: in  std_logic;
	
	-- Frequency control
	avs_writedata_voice_select   	: in  std_logic_vector(31 downto 0);
	avs_write_n_voice_select   	: in  std_logic;

aso_ready_audio_in			: in std_logic;
	
	aso_data_audio_out		: out std_logic_vector(31 downto 0);
	aso_valid_audio_out		: out std_logic
	);
end SynthesizerTopLevel;

architecture additionalSynthesizer of SynthesizerTopLevel is

	signal tone_s                   : std_logic_vector(6 downto 0);
	signal instrument_s             : std_logic_vector(4 downto 0);

	component Synthesizer is
		port (
		-- system signals
		clk         : in  std_logic;
		reset_n       : in  std_logic;
	  
		-- Frequency control
		--Bottom 16 bits are for first oscillator, next 16 are for second, next 16 are for third
	        instrument_addr   		: in  std_logic_vector(4 downto 0);
                tone_addr                      : in  std_logic_vector(6 downto 0);	
		audio_output			: out std_logic_vector(15 downto 0);
		audio_output_valid		: out std_logic
		);
	end component;
		
begin

	--avs_write_n_phase_increments_voice0 doesn't exist anywhere.
	read_phase_increment0: process(avs_write_n_voice_select)
	begin
		if falling_edge(avs_write_n_voice_select) then
				tone_s <=   avs_writedata_voice_select(6 downto 0);
                                instrument_s <=   avs_writedata_voice_select(11 downto 7);
		end if;
	end process read_phase_increment0;
	
	
	
	laserHarpSynthesizer: Synthesizer
	port map(
		clk => csi_clk32k,
		reset_n => reset_n,
	    instrument_addr => instrument_s,
        tone_addr => tone_s,
		audio_output => aso_data_audio_out(31 downto 16),
		audio_output_valid => aso_valid_audio_out
	);
	
end additionalSynthesizer;
