LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY SynthesizerTopLevel_tb IS
END SynthesizerTopLevel_tb

ARCHITECTURE behaviour OF SynthesizerTopLevel_tb IS

	COMPONENT SynthesizerTopLevel_tb
	PORT(
		-- system signals
		csi_clk50M		: in  std_logic;
		reset_n			: in  std_logic;
		csi_clk32k		: in  std_logic;
		
	-- Frequency control
		avs_writedata_voice_select   : in  std_logic_vector(31 downto 0);
		avs_write_n_voice_select   	: in  std_logic;
		
		aso_data_audio_out		: out std_logic_vector(31 downto 0);
		aso_valid_audio_out		: out std_logic
	); END COMPONENT;
	
	signal csi_clk32k : std_logic;
	signal avs_writedata_voice_select : std_logic_vector(31 downto 0);
	signal avs_write_n_voice_select : std_logic;
	
	signal aso_data_audio_out : out std_logic_vector(31 downto 0);
	signal aso_valid_audio_out : out std_logic;
	
	constant <clock>_process : process
	
BEGIN

	uut: SynthesizerTopLevel PORT MAP(
		csi_clk32k => csi_clk32k,
		avs_writedata_voice_select => avs_writedata_voice_select,
		avs_write_n_voice_select => avs_write_n_voice_select,
		aso_data_audio_out => aso_data_audio_out,
		aso_valid_audio_out => aso_valid_audio_out
	);
	
		
		
	begin
		<clock> <= '0';
		wait for <clock>_period/2;
		<clock> <= '1';
		wait for <clock>_period/2;
	end process;
	
	stim_proc: process
	begin
	wait for <clock>_period*10;
		avs_writedata_voice_select <= "0000 0000  0000 0000  0000 0000  0000 0000";
		avs_write_n_voice_select <= "0";
		Wait for 5 ns;
		
		avs_writedata_voice_select <= "0000 0000  0000 0000  0000 0000  0000 0000";
		avs_write_n_voice_select <= "1";
		Wait for 5 ns;
		
		avs_writedata_voice_select <= "0000 0000  0000 0000  0000 0100  0000 0000";
		avs_write_n_voice_select <= "0";
		Wait for 5 ns;
		
		avs_writedata_voice_select <= "0000 0000  0000 0000  0000 0100  0000 0000";
		avs_write_n_voice_select <= "1";
		Wait for 5 ns;
		
		wait;
	end process;
END;
	
	