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
	
--use work.SynthesizerPackage.all;	

	
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
	begin
		aso_data_audio_out <= avs_writedata_voice_select;
		aso_valid_audio_out <= aso_ready_audio_in ;
	
end additionalSynthesizer;
