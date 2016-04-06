library ieee;

-- STD_LOGIC and STD_LOGIC_VECTOR types, and relevant functions
use ieee.std_logic_1164.all;

-- SIGNED and UNSIGNED types, and relevant functions
use ieee.numeric_std.all;

-- Basic sequential functions and concurrent procedures
use ieee.VITAL_Primitives.all;

entity midiOut is

	port
	(
		-- clock interface
		clk		:	in std_logic;
		
		-- reset interface
		reset_n		:	in std_logic;
		
		-- clock for midiOut
		
		clk_midi : in std_logic;
		
		-- conduit interface for midi out jack
		coe_midiOut			:	out std_logic;
		
		-- avalon slave interface
		-- mininum interface possible
		avs_s0_write_n	: in std_logic ;
		avs_s0_writedata : in std_logic_vector (31 downto 0)
	);
	
end midiOut;


architecture avalon of midiOut is

signal midiDataInput : std_logic_vector (29 downto 0) :="111111111111111111111111111111";
signal counter : integer range 0 to 29 := 29;
signal localMidiData : std_logic_vector (29 downto 0):="111111111111111111111111111111";

begin

	midiReceiver : process(avs_s0_write_n) is
	begin
		if falling_edge(avs_s0_write_n) then
			--save the midi data
			--midi data is only 30bits ignore the first two bits.
			midiDataInput(29 downto 0) <= avs_s0_writedata(29 downto 0);	
		
			midiDataInput(28) <= avs_s0_writedata(21);
			midiDataInput(27) <= avs_s0_writedata(22);
			midiDataInput(26) <= avs_s0_writedata(23);
			midiDataInput(25) <= avs_s0_writedata(24);
			midiDataInput(24) <= avs_s0_writedata(25);
			midiDataInput(23) <= avs_s0_writedata(26);
			midiDataInput(22) <= avs_s0_writedata(27);
			midiDataInput(21) <= avs_s0_writedata(28);

			midiDataInput(18) <= avs_s0_writedata(11);
			midiDataInput(17) <= avs_s0_writedata(12);
			midiDataInput(16) <= avs_s0_writedata(13);
			midiDataInput(15) <= avs_s0_writedata(14);
			midiDataInput(14) <= avs_s0_writedata(15);
			midiDataInput(13) <= avs_s0_writedata(16);
			midiDataInput(12) <= avs_s0_writedata(17);
			midiDataInput(11) <= avs_s0_writedata(18);

			midiDataInput(8) <= avs_s0_writedata(1);
			midiDataInput(7) <= avs_s0_writedata(2);
			midiDataInput(6) <= avs_s0_writedata(3);
			midiDataInput(5) <= avs_s0_writedata(4);
			midiDataInput(4) <= avs_s0_writedata(5);
			midiDataInput(3) <= avs_s0_writedata(6);
			midiDataInput(2) <= avs_s0_writedata(7);
			midiDataInput(1) <= avs_s0_writedata(8);
			
		end if;
	end process;
	
	midiSender: process(clk_midi,midiDataInput) is
	begin
		if rising_edge(clk_midi)then
		
			if (localMidiData /= midiDataInput) then 
				counter <=29;
				localMidiData <= midiDataInput;
			end if;
			
			if (counter = 0) then
				coe_midiOut <= '1';
				--For MIDI protocol 
				--'1' is the value of the last bit of every 30 bits midi signal
				--'1' is also the default value when there is no on the wire.
			else
				coe_midiOut <= localMidiData(counter);
				counter <= counter -1;					
			end if;
			
		end if;		
	end process;
	
end avalon;




