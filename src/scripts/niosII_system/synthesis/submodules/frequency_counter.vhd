library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity frequency_counter_0 is
    Port ( clock: IN STD_LOGIC;
	 clock_reset: IN STD_LOGIC;
	 conduit_end_0: IN STD_LOGIC;
	 readdata: OUT STD_LOGIC_VECTOR(31 downto 0));
end frequency_counter_0;


architecture behavioural of frequency_counter_0 is
	signal count: STD_LOGIC_VECTOR(31 downto 0);
	begin
	
	c0: process(conduit_end_0) is
	begin
		if rising_edge(conduit_end_0) then
			count <= STD_LOGIC_VECTOR(unsigned(count) + 1);
		end if;
	end process c0;
	
	seq: process(clock) is
	begin
		if rising_edge(clock) then
			readdata <= count;
		end if;
	end process seq;

end behavioural;

