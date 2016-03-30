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

--synthesis_resources = lut 1 mux21 4 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  niosII_system_nios2_qsys_0_instruction_master_translator IS 
	 PORT 
	 ( 
		 av_address	:	IN  STD_LOGIC_VECTOR (24 DOWNTO 0);
		 av_read	:	IN  STD_LOGIC;
		 av_readdata	:	OUT  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 av_waitrequest	:	OUT  STD_LOGIC;
		 clk	:	IN  STD_LOGIC;
		 reset	:	IN  STD_LOGIC;
		 uav_address	:	OUT  STD_LOGIC_VECTOR (24 DOWNTO 0);
		 uav_burstcount	:	OUT  STD_LOGIC_VECTOR (2 DOWNTO 0);
		 uav_byteenable	:	OUT  STD_LOGIC_VECTOR (3 DOWNTO 0);
		 uav_debugaccess	:	OUT  STD_LOGIC;
		 uav_lock	:	OUT  STD_LOGIC;
		 uav_read	:	OUT  STD_LOGIC;
		 uav_readdata	:	IN  STD_LOGIC_VECTOR (31 DOWNTO 0);
		 uav_readdatavalid	:	IN  STD_LOGIC;
		 uav_waitrequest	:	IN  STD_LOGIC;
		 uav_write	:	OUT  STD_LOGIC;
		 uav_writedata	:	OUT  STD_LOGIC_VECTOR (31 DOWNTO 0)
	 ); 
 END niosII_system_nios2_qsys_0_instruction_master_translator;

 ARCHITECTURE RTL OF niosII_system_nios2_qsys_0_instruction_master_translator IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q	:	STD_LOGIC := '0';
	 SIGNAL  wire_nO_w83w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_av_waitrequest_172m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_166m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_169m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_170m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_w_lg_reset259w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_uav_readdatavalid258w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_uav_waitrequest256w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_vcc :	STD_LOGIC;
 BEGIN

	wire_w_lg_reset259w(0) <= NOT reset;
	wire_w_lg_uav_readdatavalid258w(0) <= NOT uav_readdatavalid;
	wire_w_lg_uav_waitrequest256w(0) <= NOT uav_waitrequest;
	av_readdata <= ( uav_readdata(31 DOWNTO 0));
	av_waitrequest <= wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_av_waitrequest_172m_dataout;
	s_wire_vcc <= '1';
	uav_address <= ( av_address(24 DOWNTO 0));
	uav_burstcount <= ( "1" & "0" & "0");
	uav_byteenable <= ( "1" & "1" & "1" & "1");
	uav_debugaccess <= '0';
	uav_lock <= '0';
	uav_read <= (av_read AND wire_nO_w83w(0));
	uav_write <= '0';
	uav_writedata <= ( "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0" & "0");
	PROCESS (clk, reset)
	BEGIN
		IF (reset = '1') THEN
				niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q <= '0';
		ELSIF (clk = '1' AND clk'event) THEN
				niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q <= wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_170m_dataout;
		END IF;
	END PROCESS;
	wire_nO_w83w(0) <= NOT niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q;
	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_av_waitrequest_172m_dataout <= wire_w_lg_uav_readdatavalid258w(0) WHEN av_read = '1'  ELSE uav_waitrequest;
	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_166m_dataout <= niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q AND NOT((uav_readdatavalid AND niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q));
	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_169m_dataout <= (wire_w_lg_uav_waitrequest256w(0) AND av_read) AND wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_av_waitrequest_172m_dataout;
	wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_170m_dataout <= wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_166m_dataout WHEN niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_175q = '1'  ELSE wire_niosii_system_nios2_qsys_0_instruction_master_translator_altera_merlin_master_translator_nios2_qsys_0_instruction_master_translator_read_accepted_169m_dataout;

 END RTL; --niosII_system_nios2_qsys_0_instruction_master_translator
--synopsys translate_on
--VALID FILE
