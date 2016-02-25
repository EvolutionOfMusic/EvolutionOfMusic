library IEEE;
    use IEEE.std_logic_1164.all;
    use IEEE.std_logic_textio.all;
    use IEEE.numeric_std.all;
    use IEEE.std_logic_signed.all;
    use IEEE.std_logic_unsigned.all;

library work;	
	use work.SynthesizerPackage.ALL;

entity Synthesizer is
	port (
	-- system signals
	clk         		: in  std_logic;
	reset_n     		: in  std_logic;
	audio_input_valid	: in  std_logic;
	
	-- Frequency control
	--Bottom 16 bits are for first oscillator, next 16 are for second, next 16 are for third
	instrument_addr		  	: in  std_logic_vector(4 downto 0); -- There are actually 24 possible instruments
	tone_addr               : in  std_logic_vector(6 downto 0);
	audio_output			: out std_logic_vector(15 downto 0);
	audio_output_valid		: out std_logic
	);
end Synthesizer;

architecture synthesizer of Synthesizer is
  signal lut_addresses2         : MUX_INPUTS;
  signal target_lut_addresses 	: LUT_ADDRESSES;
  signal audioData		        : WAVE_ARRAY;
  signal full_addr                      : std_logic_vector(16 downto 0);
  signal temp_us : unsigned(15 downto 0);

  type freq_array is array (0 to 95) of Integer;
  type step_array is array (0 to 95) of std_logic_vector(15 downto 0);

  signal steps : step_array;
  constant freqs : freq_array :=
    ( -- 12 Notes per octave; All octaves start at C# and end in B#
		33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 						-- Octave1
		65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 					-- Octave2
		131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 			-- Octave3
		262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 			-- Octave4
		523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 			-- Octave5
		1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, -- Octave6
		2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, -- Octave7
		4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902  -- Octave8
	);    -- the frequencies for the frequency counters
	
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
	);
	end component;

	component AudioSynthesis is
			port(
				-- system signal
				clk 				: in std_logic;
				-- Input to select tone
				freq_address 		: in std_logic_vector (11 downto 0);
				-- Input to select the instrument to be used
				instrument_address 	: in std_logic_vector(4 downto 0);
				-- Audio data to be outputted
				audioData 			: out WAVE_ARRAY
			);
	end component;

	begin
        --step_array and freq_array are types not variables
        loop1: for i in 0 to 95 generate
			--the magic number represents: 2^32/50000000
			temp_us <= to_unsigned(freqs(i)*(33554432/390625),16);
            steps(i) <= std_logic_vector(temp_us);   -- Hard Coded 
                                                             -- clock frequency
                                                             -- 50 MHz
		end generate loop1;  

        -- Add a frequency for the Incrementors
        Gen_INC:
		for I in 0 to 95 generate
			anAddressIncrementor: AddressIncrementor
			port map(
				clk => clk,
				reset_n => reset_n,
				phase_inc => steps(I),
				lut_address => lut_addresses2(I)(0)
			);
        end generate Gen_INC;
	
		aFrequencyMUX: FrequencyMUX 
			port map(
			  clk => clk,
			  sel_sig => tone_addr,
			  freq_counts => lut_addresses2,
			  ROM_step => target_lut_addresses
			);
			
		aAudioSynthesis: AudioSynthesis
			port map(
				clk 				=> clk,
				freq_address 		=> target_lut_addresses(0),
				instrument_address 	=> instrument_addr,
				audioData 			=> audioData
			);

		send_output: process(clk, reset_n)
		begin
			if rising_edge(clk) then
				audio_output <= audioData(0);
			end if;
		end process send_output;

		audio_output_valid <= '1';
end synthesizer;
