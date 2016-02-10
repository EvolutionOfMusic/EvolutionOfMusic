library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
    use IEEE.std_logic_arith.all;
    use IEEE.numeric_bit.all;
    use IEEE.numeric_std.all;
    use IEEE.std_logic_signed.all;
    use IEEE.std_logic_unsigned.all;
	
use work.SynthesizerPackage.all;

entity Synthesizer is
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
end Synthesizer;

architecture synthesizer of Synthesizer is

  signal lut_addresses                  : MUX_INPUTS;
	signal target_lut_addresses 	: LUT_ADDRESSES;
	signal audioData		: WAVE_ARRAY;
  signal full_addr                      : std_logic_vector(16 downto 0);

	component AddressIncrementor is
	port (
	  -- system signals
	  clk         	: in  std_logic;
	  reset_n       : in  std_logic;
	  
	  -- NCO frequency control
	  phase_inc   	: in  std_logic_vector(15 downto 0);

	  -- Output waveforms
	  lut_address	: out std_logic_vector(11 downto 0)
	  );
	end component;
  
  component FrequencyMUX is
  port (
    -- DE2 required signals
    clk         : in std_logic;

    -- Inputs to make selection
    sel_sig     : in std_logic_vector(6 downto 0);
    
    -- Inputs to be selected
    freq_counts : in MUX_INPUTS;

    -- Frequency to be outputted
    ROM_step    : out LUT_ADDRESSES
    )end component;
	
	component SinLut is
		port (
			clk      : in  std_logic;
			
			--Address input
			address  : in std_logic_vector(16 downto 0);
			
			--Sine output
			audioData : out WAVE_ARRAY
		);
	end component;

	begin

          -- Add a frequency for the Incrementors
        Gen_INC:
          for I in 0 to 95 generate
	anAddressIncrementor: AddressIncrementor
		port map(
			clk => clk,
			reset_n => reset_n,
			phase_inc => ,
			lut_address => lut_addresses(I)
		);
        end generate Gen_INC;

  aFrequencyMUX: FrequencyMUX 
    port map(
      clk => clk,
      sel_sig => tone_addr,
      freq_counts => lut_addresses,
      ROM_step => target_lut_addresses
      );

  full_addr(16 downto 12) <= instrument_addr;
  full_addr(11 downto 0) <= target_lut_addresses;
	aSinLut: SinLut
		port map(
			clk => clk,
			address => full_addr,
			audioData => audioData
		);	

	send_output: process(clk, reset_n)
	begin
		if rising_edge(clk) then
			audio_output <= audioData(0);
		end if;
	end process send_output;

	audio_output_valid <= '1';	

end synthesizer;
