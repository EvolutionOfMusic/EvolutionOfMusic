
# (C) 2001-2016 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ACDS 12.1sp1 243 linux 2016.03.23.15:56:04

# ----------------------------------------
# vcsmx - auto-generated simulation script

# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="niosII_system"
QSYS_SIMDIR="./../../"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="+vcs+finish+100"

# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_ELAB=1 SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/up_clocks_0/
mkdir -p ./libraries/audio_and_video_config_0/
mkdir -p ./libraries/audio_0/
mkdir -p ./libraries/gate_timer/
mkdir -p ./libraries/sram_0/
mkdir -p ./libraries/sdram_0/
mkdir -p ./libraries/jtag_uart_0/
mkdir -p ./libraries/timer_0/
mkdir -p ./libraries/sysid_qsys_0/
mkdir -p ./libraries/onchip_memory2_0/
mkdir -p ./libraries/nios2_qsys_0/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cycloneii_ver/
mkdir -p ./libraries/altera/
mkdir -p ./libraries/lpm/
mkdir -p ./libraries/sgate/
mkdir -p ./libraries/altera_mf/
mkdir -p ./libraries/altera_lnsim/
mkdir -p ./libraries/cycloneii/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/submodules/niosII_system_onchip_memory2_0.hex ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.mif ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.hex ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  vlogan +v2k           "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives.v"              -work altera_ver      
  vlogan +v2k           "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220model.v"                       -work lpm_ver         
  vlogan +v2k           "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate.v"                          -work sgate_ver       
  vlogan +v2k           "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf.v"                      -work altera_mf_ver   
  vlogan +v2k -sverilog "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_lnsim.sv"                  -work altera_lnsim_ver
  vlogan +v2k           "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_atoms.v"                -work cycloneii_ver   
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_syn_attributes.vhd"        -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_standard_functions.vhd"    -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/alt_dspbuilder_package.vhd"       -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_europa_support_lib.vhd"    -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives_components.vhd" -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives.vhd"            -work altera          
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220pack.vhd"                      -work lpm             
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220model.vhd"                     -work lpm             
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate_pack.vhd"                   -work sgate           
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate.vhd"                        -work sgate           
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf_components.vhd"         -work altera_mf       
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf.vhd"                    -work altera_mf       
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_lnsim_components.vhd"      -work altera_lnsim    
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_atoms.vhd"              -work cycloneii       
  vhdlan                "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_components.vhd"         -work cycloneii       
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_up_clocks_0.vhd"                                     -work up_clocks_0             
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_serial_bus_controller.v"                       -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_slow_clock_generator.v"                                  -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init.v"                                   -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_dc2.v"                               -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_d5m.v"                               -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_lcm.v"                               -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ltm.v"                               -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_35.v"                         -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_adv7181.v"                        -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_70.v"                         -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_115.v"                        -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_audio.v"                          -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_adv7180.v"                        -work audio_and_video_config_0
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_audio_and_video_config_0.vhd"                        -work audio_and_video_config_0
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_audio_bit_counter.v"                                     -work audio_0                 
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_audio_in_deserializer.v"                                 -work audio_0                 
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_audio_out_serializer.v"                                  -work audio_0                 
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_clock_edge.v"                                            -work audio_0                 
  vlogan +v2k  "$QSYS_SIMDIR/submodules/altera_up_sync_fifo.v"                                             -work audio_0                 
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_audio_0.vhd"                                         -work audio_0                 
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_gate_timer.vhd"                                      -work gate_timer              
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_sram_0.vhd"                                          -work sram_0                  
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_sdram_0.vhd"                                         -work sdram_0                 
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_jtag_uart_0.vhd"                                     -work jtag_uart_0             
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_timer_0.vhd"                                         -work timer_0                 
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_sysid_qsys_0.vho"                                    -work sysid_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_onchip_memory2_0.vhd"                                -work onchip_memory2_0        
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_tck.vhd"              -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_wrapper.vhd"          -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_sysclk.vhd"           -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_oci_test_bench.vhd"                     -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0.vhd"                                    -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_test_bench.vhd"                         -work nios2_qsys_0            
  vhdlan -xlrm "$QSYS_SIMDIR/niosII_system.vhd"                                                                                          
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_nios2_qsys_0_jtag_debug_module_translator.vhd"                                                
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_onchip_memory2_0_s1_translator.vhd"                                                           
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_sdram_0_s1_translator.vhd"                                                                    
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_sram_0_avalon_sram_slave_translator.vhd"                                                      
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_audio_and_video_config_0_avalon_av_config_slave_translator.vhd"                               
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_synthesizer_0_voice_select_translator.vhd"                                                    
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_spi_0_spi_control_port_translator.vhd"                                                        
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_timer_0_s1_translator.vhd"                                                                    
  vhdlan -xlrm "$QSYS_SIMDIR/niosii_system_jtag_uart_0_avalon_jtag_slave_translator.vhd"                                                 
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  vcs -lca -t ps $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  ./simv $USER_DEFINED_SIM_OPTIONS
fi
