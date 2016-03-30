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

--synthesis_resources = mux21 22 
 LIBRARY ieee;
 USE ieee.std_logic_1164.all;

 ENTITY  niosII_system_addr_router IS 
	 PORT 
	 ( 
		 clk	:	IN  STD_LOGIC;
		 reset	:	IN  STD_LOGIC;
		 sink_data	:	IN  STD_LOGIC_VECTOR (99 DOWNTO 0);
		 sink_endofpacket	:	IN  STD_LOGIC;
		 sink_ready	:	OUT  STD_LOGIC;
		 sink_startofpacket	:	IN  STD_LOGIC;
		 sink_valid	:	IN  STD_LOGIC;
		 src_channel	:	OUT  STD_LOGIC_VECTOR (9 DOWNTO 0);
		 src_data	:	OUT  STD_LOGIC_VECTOR (99 DOWNTO 0);
		 src_endofpacket	:	OUT  STD_LOGIC;
		 src_ready	:	IN  STD_LOGIC;
		 src_startofpacket	:	OUT  STD_LOGIC;
		 src_valid	:	OUT  STD_LOGIC
	 ); 
 END niosII_system_addr_router;

 ARCHITECTURE RTL OF niosII_system_addr_router IS

	 ATTRIBUTE synthesis_clearbox : natural;
	 ATTRIBUTE synthesis_clearbox OF RTL : ARCHITECTURE IS 1;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_39m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_40m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_54m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_55m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_56m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_69m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_70m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_71m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_72m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_83m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_84m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_85m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_86m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_channel_87m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_46m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_60m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_61m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_75m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_76m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_89m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_90m_dataout	:	STD_LOGIC;
	 SIGNAL	wire_niosii_system_addr_router_src_data_91m_dataout	:	STD_LOGIC;
	 SIGNAL  wire_w_lg_w_sink_data_range117w377w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range123w351w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range144w335w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range153w320w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range168w311w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w1w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w2w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range120w376w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range126w350w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range147w334w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range156w319w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_lg_w_sink_data_range171w310w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  s_wire_niosii_system_addr_router_src_channel_1_377_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_niosii_system_addr_router_src_channel_2_403_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_niosii_system_addr_router_src_channel_3_429_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_niosii_system_addr_router_src_channel_4_455_dataout :	STD_LOGIC;
	 SIGNAL  s_wire_niosii_system_addr_router_src_channel_5_481_dataout :	STD_LOGIC;
	 SIGNAL  wire_w_sink_data_range117w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range120w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range123w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range126w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range144w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range147w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range153w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range156w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range168w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
	 SIGNAL  wire_w_sink_data_range171w	:	STD_LOGIC_VECTOR (0 DOWNTO 0);
 BEGIN

	wire_w_lg_w_sink_data_range117w377w(0) <= wire_w_sink_data_range117w(0) AND wire_w_lg_w_sink_data_range120w376w(0);
	wire_w_lg_w_sink_data_range123w351w(0) <= wire_w_sink_data_range123w(0) AND wire_w_lg_w_sink_data_range126w350w(0);
	wire_w_lg_w_sink_data_range144w335w(0) <= wire_w_sink_data_range144w(0) AND wire_w_lg_w_sink_data_range147w334w(0);
	wire_w_lg_w_sink_data_range153w320w(0) <= wire_w_sink_data_range153w(0) AND wire_w_lg_w_sink_data_range156w319w(0);
	wire_w_lg_w_sink_data_range168w311w(0) <= wire_w_sink_data_range168w(0) AND wire_w_lg_w_sink_data_range171w310w(0);
	wire_w1w(0) <= NOT s_wire_niosii_system_addr_router_src_channel_1_377_dataout;
	wire_w2w(0) <= NOT s_wire_niosii_system_addr_router_src_channel_2_403_dataout;
	wire_w_lg_w_sink_data_range120w376w(0) <= NOT wire_w_sink_data_range120w(0);
	wire_w_lg_w_sink_data_range126w350w(0) <= NOT wire_w_sink_data_range126w(0);
	wire_w_lg_w_sink_data_range147w334w(0) <= NOT wire_w_sink_data_range147w(0);
	wire_w_lg_w_sink_data_range156w319w(0) <= NOT wire_w_sink_data_range156w(0);
	wire_w_lg_w_sink_data_range171w310w(0) <= NOT wire_w_sink_data_range171w(0);
	s_wire_niosii_system_addr_router_src_channel_1_377_dataout <= ((((wire_w_lg_w_sink_data_range168w311w(0) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND sink_data(60));
	s_wire_niosii_system_addr_router_src_channel_2_403_dataout <= (((((((((wire_w_lg_w_sink_data_range153w320w(0) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND sink_data(56)) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND sink_data(60));
	s_wire_niosii_system_addr_router_src_channel_3_429_dataout <= ((((((((((((wire_w_lg_w_sink_data_range144w335w(0) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND sink_data(51)) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND sink_data(56)) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND sink_data(60));
	s_wire_niosii_system_addr_router_src_channel_4_455_dataout <= (((((((((((((((((((wire_w_lg_w_sink_data_range123w351w(0) AND sink_data(42)) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND sink_data(51)) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND sink_data(56)) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND sink_data(60));
	s_wire_niosii_system_addr_router_src_channel_5_481_dataout <= (((((((((((((((((((((wire_w_lg_w_sink_data_range117w377w(0) AND sink_data(40)) AND sink_data(41)) AND sink_data(42)) AND (NOT sink_data(43))) AND (NOT sink_data(44))) AND (NOT sink_data(45))) AND (NOT sink_data(46))) AND (NOT sink_data(47))) AND sink_data(48)) AND (NOT sink_data(49))) AND (NOT sink_data(50))) AND sink_data(51)) AND (NOT sink_data(52))) AND (NOT sink_data(53))) AND (NOT sink_data(54))) AND (NOT sink_data(55))) AND sink_data(56)) AND (NOT sink_data(57))) AND (NOT sink_data(58))) AND (NOT sink_data(59))) AND sink_data(60));
	sink_ready <= src_ready;
	src_channel <= ( "0" & "0" & "0" & "0" & s_wire_niosii_system_addr_router_src_channel_5_481_dataout & wire_niosii_system_addr_router_src_channel_83m_dataout & wire_niosii_system_addr_router_src_channel_84m_dataout & wire_niosii_system_addr_router_src_channel_85m_dataout & wire_niosii_system_addr_router_src_channel_86m_dataout & wire_niosii_system_addr_router_src_channel_87m_dataout);
	src_data <= ( sink_data(99 DOWNTO 90) & "0" & wire_niosii_system_addr_router_src_data_89m_dataout & wire_niosii_system_addr_router_src_data_90m_dataout & wire_niosii_system_addr_router_src_data_91m_dataout & sink_data(85 DOWNTO 0));
	src_endofpacket <= sink_endofpacket;
	src_startofpacket <= sink_startofpacket;
	src_valid <= sink_valid;
	wire_w_sink_data_range117w(0) <= sink_data(38);
	wire_w_sink_data_range120w(0) <= sink_data(39);
	wire_w_sink_data_range123w(0) <= sink_data(40);
	wire_w_sink_data_range126w(0) <= sink_data(41);
	wire_w_sink_data_range144w(0) <= sink_data(47);
	wire_w_sink_data_range147w(0) <= sink_data(48);
	wire_w_sink_data_range153w(0) <= sink_data(50);
	wire_w_sink_data_range156w(0) <= sink_data(51);
	wire_w_sink_data_range168w(0) <= sink_data(55);
	wire_w_sink_data_range171w(0) <= sink_data(56);
	wire_niosii_system_addr_router_src_channel_39m_dataout <= s_wire_niosii_system_addr_router_src_channel_1_377_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_2_403_dataout);
	wire_niosii_system_addr_router_src_channel_40m_dataout <= wire_w1w(0) AND NOT(s_wire_niosii_system_addr_router_src_channel_2_403_dataout);
	wire_niosii_system_addr_router_src_channel_54m_dataout <= wire_niosii_system_addr_router_src_channel_39m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_3_429_dataout);
	wire_niosii_system_addr_router_src_channel_55m_dataout <= wire_niosii_system_addr_router_src_channel_40m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_3_429_dataout);
	wire_niosii_system_addr_router_src_channel_56m_dataout <= s_wire_niosii_system_addr_router_src_channel_2_403_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_3_429_dataout);
	wire_niosii_system_addr_router_src_channel_69m_dataout <= wire_niosii_system_addr_router_src_channel_54m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_channel_70m_dataout <= wire_niosii_system_addr_router_src_channel_55m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_channel_71m_dataout <= wire_niosii_system_addr_router_src_channel_56m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_channel_72m_dataout <= s_wire_niosii_system_addr_router_src_channel_3_429_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_channel_83m_dataout <= s_wire_niosii_system_addr_router_src_channel_4_455_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_channel_84m_dataout <= wire_niosii_system_addr_router_src_channel_69m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_channel_85m_dataout <= wire_niosii_system_addr_router_src_channel_70m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_channel_86m_dataout <= wire_niosii_system_addr_router_src_channel_71m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_channel_87m_dataout <= wire_niosii_system_addr_router_src_channel_72m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_data_46m_dataout <= s_wire_niosii_system_addr_router_src_channel_1_377_dataout OR s_wire_niosii_system_addr_router_src_channel_2_403_dataout;
	wire_niosii_system_addr_router_src_data_60m_dataout <= wire_w2w(0) AND NOT(s_wire_niosii_system_addr_router_src_channel_3_429_dataout);
	wire_niosii_system_addr_router_src_data_61m_dataout <= wire_niosii_system_addr_router_src_data_46m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_3_429_dataout);
	wire_niosii_system_addr_router_src_data_75m_dataout <= wire_niosii_system_addr_router_src_data_60m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_data_76m_dataout <= wire_niosii_system_addr_router_src_data_61m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_4_455_dataout);
	wire_niosii_system_addr_router_src_data_89m_dataout <= s_wire_niosii_system_addr_router_src_channel_4_455_dataout OR s_wire_niosii_system_addr_router_src_channel_5_481_dataout;
	wire_niosii_system_addr_router_src_data_90m_dataout <= wire_niosii_system_addr_router_src_data_75m_dataout AND NOT(s_wire_niosii_system_addr_router_src_channel_5_481_dataout);
	wire_niosii_system_addr_router_src_data_91m_dataout <= wire_niosii_system_addr_router_src_data_76m_dataout OR s_wire_niosii_system_addr_router_src_channel_5_481_dataout;

 END RTL; --niosII_system_addr_router
--synopsys translate_on
--VALID FILE
