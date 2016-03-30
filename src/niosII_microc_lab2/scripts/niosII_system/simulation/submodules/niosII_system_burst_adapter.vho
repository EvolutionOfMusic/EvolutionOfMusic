--IP Functional Simulation Model
--VERSION_BEGIN 12.1SP1 cbx_mgl 2013:01:31:18:08:38:SJ cbx_simgen 2013:01:31:18:04:55:SJ  VERSION_END


-- Copyright (C) 1991-2012 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- You may only use these simulation model output files for simulation
-- purposes and expressly not for synthesis or any other purposes (in which
-- event Altera disclaims all warranties of any kind).


--synopsys translate_off

--synthesis_resources = 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  niosII_system_burst_adapter IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 reset	:	IN  STD_LOGIC;
		 sink0_channel	:	IN  STD_LOGIC_VECTOR (9 DOWNTO 0);
		 sink0_data	:	IN  STD_LOGIC_VECTOR (81 DOWNTO 0);
		 sink0_endofpacket	:	IN  STD_LOGIC;
		 sink0_ready	:	OUT  STD_LOGIC;
		 sink0_startofpacket	:	IN  STD_LOGIC;
		 sink0_valid	:	IN  STD_LOGIC;
		 source0_channel	:	OUT  STD_LOGIC_VECTOR (9 DOWNTO 0);
		 source0_data	:	OUT  STD_LOGIC_VECTOR (81 DOWNTO 0);
		 source0_endofpacket	:	OUT  STD_LOGIC;
		 source0_ready	:	IN  STD_LOGIC;
		 source0_startofpacket	:	OUT  STD_LOGIC;
		 source0_valid	:	OUT  STD_LOGIC
	 ); 
 END niosII_system_burst_adapter;

 ARCHITECTURE RTL OF niosII_system_burst_adapter IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
 BEGIN

	sink0_ready <= source0_ready;
	source0_channel <= ( sink0_channel(9 DOWNTO 0));
	source0_data <= ( sink0_data(81 DOWNTO 52) & "0" & "1" & "0" & sink0_data(48 DOWNTO 0));
	source0_endofpacket <= sink0_endofpacket;
	source0_startofpacket <= sink0_startofpacket;
	source0_valid <= sink0_valid;

 END RTL; --niosII_system_burst_adapter
--synopsys translate_on
--VALID FILE
