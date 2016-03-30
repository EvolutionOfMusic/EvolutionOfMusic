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

--synthesis_resources = lut 3 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  niosII_system_rst_controller IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 reset_in0	:	IN  STD_LOGIC;
		 reset_in1	:	IN  STD_LOGIC;
		 reset_out	:	OUT  STD_LOGIC
	 ); 
 END niosII_system_rst_controller;

 ARCHITECTURE RTL OF niosII_system_rst_controller IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_0_47q	:	STD_LOGIC := '0';
	 SIGNAL	niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_1_46q	:	STD_LOGIC := '0';
	 SIGNAL	niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_out_48q	:	STD_LOGIC := '0';
	 SIGNAL  wire_w2w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_gnd :	STD_LOGIC;
	 SIGNAL  s_wire_niosii_system_rst_controller_altera_reset_controller_rst_controller_merged_reset_6_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
 BEGIN

	wire_w2w(0) <= NOT s_wire_niosii_system_rst_controller_altera_reset_controller_rst_controller_merged_reset_6_dataout;
	reset_out <= niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_out_48q;
	s_wire_gnd <= '0';
	s_wire_niosii_system_rst_controller_altera_reset_controller_rst_controller_merged_reset_6_dataout <= (reset_in0 OR reset_in1);
	s_wire_vcc <= '1';
	PROCESS (clk, s_wire_niosii_system_rst_controller_altera_reset_controller_rst_controller_merged_reset_6_dataout)
	BEGIN
		IF (s_wire_niosii_system_rst_controller_altera_reset_controller_rst_controller_merged_reset_6_dataout = '1') THEN
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_0_47q <= '1';
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_1_46q <= '1';
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_out_48q <= '1';
		ELSIF (clk = '1' AND clk'event) THEN
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_0_47q <= niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_1_46q;
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_1_46q <= s_wire_gnd;
				niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_out_48q <= niosii_system_rst_controller_altera_reset_controller_rst_controller_altera_reset_synchronizer_alt_rst_sync_uq1_altera_reset_synchronizer_int_chain_0_47q;
		END IF;
	END PROCESS;

 END RTL; --niosII_system_rst_controller
--synopsys translate_on
--VALID FILE
