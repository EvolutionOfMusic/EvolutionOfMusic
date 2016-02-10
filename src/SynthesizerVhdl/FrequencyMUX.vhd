library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
    use IEEE.std_logic_arith.all;
    use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
    use IEEE.std_logic_signed.all;
    use IEEE.std_logic_unsigned.all;
	
use work.SynthesizerPackage.all;

entity FrequencyMUX is
  port (
    -- DE2 required signals
    clk         : in std_logic;

    -- Inputs to make selection
    sel_sig     : in std_logic_vector(6 downto 0);
    
    -- Inputs to be selected
    freq_counts : in MUX_INPUTS;

    -- Frequency to be outputted
    ROM_step    : out LUT_ADDRESSES
)end entity;

architecture frequencySelect of FrequencyMUX is
  variable select       : integer;

  begin
    
  select <= to_integer(unsigned(sel_sig));

  ROM_step <= freq_counts(select);

  end frequencySelect;
