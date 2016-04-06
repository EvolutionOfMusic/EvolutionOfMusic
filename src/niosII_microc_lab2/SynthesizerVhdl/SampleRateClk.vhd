library ieee;
-- Commonly imported packages:
-- STD_LOGIC and STD_LOGIC_VECTOR types, and relevant functions
use ieee.std_logic_1164.all;
-- SIGNED and UNSIGNED types, and relevant functions
use ieee.numeric_std.all;
-- Basic sequential functions and concurrent procedures
use ieee.VITAL_Primitives.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity SampleRateClk is
    Port ( clk50MHz : in  std_logic;
           clk32000Hz : out  std_logic);
end SampleRateClk;

architecture avalon of SampleRateClk is
signal counter: std_logic_vector(31 downto 0);
signal local_clk: std_logic;
begin
    --clock divider
    process(clk50MHz)
    begin  
		if rising_edge(clk50MHz) then
			--flip clk32000Hz every half a clock cycle (hence
			--the division by two below)
			if (counter = 50000000/32000/2) then
				counter <= x"00000000";
				
				if local_clk = '0' then local_clk <= '1';
				else local_clk <= '0';
				end if;
			else
				counter <= counter + 1;
			end if;
        end if;
    end process;
	clk32000Hz <= local_clk;
end avalon;