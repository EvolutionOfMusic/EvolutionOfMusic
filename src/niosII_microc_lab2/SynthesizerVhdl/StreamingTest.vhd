-- Author: Peter Crinklaw

--Top Level file for Sythesizer component. Hides avalon interface specs
--from the main Synthesizer component.
     library IEEE;
        use IEEE.std_logic_1164.all;
        use IEEE.std_logic_textio.all;
        use IEEE.std_logic_arith.all;
        use IEEE.numeric_bit.all;
        use IEEE.numeric_std.all;
        use IEEE.std_logic_signed.all;
        --use IEEE.std_logic_unsigned.all;


entity StreamingTest is

port (

	csi_clk12		: in  std_logic;
	reset_n			: in  std_logic;
	
	gpio			: out std_logic;
  
	aso_data_waveform		: out std_logic_vector(31 downto 0);
	aso_valid_waveform		: out std_logic
  );
end entity;


architecture rtl of StreamingTest is
signal counter		: std_logic_vector(31 downto 0) := x"00000000";
signal data		: std_logic_vector(31 downto 0) := x"00000000";
begin
	

HM: process(csi_clk12, reset_n) is
begin
	if reset_n = '0' then
		aso_valid_waveform <= '0';
		data <= x"00000000";
	elsif rising_edge(csi_clk12) then
		aso_valid_waveform <= '1';
		aso_data_waveform <= data;
		data <= data + 1;
	end if;
end process HM;


end rtl;