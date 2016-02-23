# TCL File Generated by Component Editor 12.1sp1
# Tue Feb 23 16:25:47 MST 2016
# DO NOT MODIFY


# 
# synthesizer "synthesizer" v1.0
# null 2016.02.23.16:25:47
# 
# 

# 
# request TCL package from ACDS 12.1
# 
package require -exact qsys 12.1


# 
# module synthesizer
# 
set_module_property NAME synthesizer
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property DISPLAY_NAME synthesizer
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL SynthesizerTopLevel
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file SynthesizerTopLevel.vhd VHDL PATH SynthesizerVhdl/SynthesizerTopLevel.vhd
add_fileset_file Synthesizer.vhd VHDL PATH SynthesizerVhdl/Synthesizer.vhd
add_fileset_file SynthesizerPackage.vhd VHDL PATH SynthesizerVhdl/SynthesizerPackage.vhd


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock_reset
# 
add_interface clock_reset reset end
set_interface_property clock_reset associatedClock clock_32k
set_interface_property clock_reset synchronousEdges DEASSERT
set_interface_property clock_reset ENABLED true


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock_32k
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true

add_interface_port reset reset_n reset_n Input 1


# 
# connection point voice_select
# 
add_interface voice_select avalon end
set_interface_property voice_select addressUnits WORDS
set_interface_property voice_select associatedClock clock_32k
set_interface_property voice_select associatedReset reset
set_interface_property voice_select bitsPerSymbol 8
set_interface_property voice_select burstOnBurstBoundariesOnly false
set_interface_property voice_select burstcountUnits WORDS
set_interface_property voice_select explicitAddressSpan 0
set_interface_property voice_select holdTime 0
set_interface_property voice_select linewrapBursts false
set_interface_property voice_select maximumPendingReadTransactions 0
set_interface_property voice_select readLatency 0
set_interface_property voice_select readWaitTime 1
set_interface_property voice_select setupTime 0
set_interface_property voice_select timingUnits Cycles
set_interface_property voice_select writeWaitTime 0
set_interface_property voice_select ENABLED true

add_interface_port voice_select avs_writedata_voice_select writedata Input 32
add_interface_port voice_select avs_write_n_voice_select write_n Input 1
set_interface_assignment voice_select embeddedsw.configuration.isFlash 0
set_interface_assignment voice_select embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment voice_select embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment voice_select embeddedsw.configuration.isPrintableDevice 0


# 
# connection point audio
# 
add_interface audio avalon_streaming start
set_interface_property audio associatedClock clock_32k
set_interface_property audio associatedReset reset
set_interface_property audio dataBitsPerSymbol 8
set_interface_property audio errorDescriptor ""
set_interface_property audio firstSymbolInHighOrderBits true
set_interface_property audio maxChannel 0
set_interface_property audio readyLatency 0
set_interface_property audio ENABLED true

add_interface_port audio aso_data_audio_out data Output 32
add_interface_port audio aso_valid_audio_out valid Output 1


# 
# connection point clock_50M
# 
add_interface clock_50M clock end
set_interface_property clock_50M clockRate 0
set_interface_property clock_50M ENABLED true

add_interface_port clock_50M csi_clk50M clk Input 1


# 
# connection point clock_32k
# 
add_interface clock_32k clock end
set_interface_property clock_32k clockRate 0
set_interface_property clock_32k ENABLED true

add_interface_port clock_32k csi_clk32k clk Input 1

