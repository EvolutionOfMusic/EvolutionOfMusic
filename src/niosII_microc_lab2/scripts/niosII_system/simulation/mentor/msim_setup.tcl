
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

# ACDS 12.1sp1 243 linux 2016.03.23.15:56:00

# ----------------------------------------
# Auto-generated simulation script

# ----------------------------------------
# Initialize the variable
if ![info exists SYSTEM_INSTANCE_NAME] { 
  set SYSTEM_INSTANCE_NAME ""
} elseif { ![ string match "" $SYSTEM_INSTANCE_NAME ] } { 
  set SYSTEM_INSTANCE_NAME "/$SYSTEM_INSTANCE_NAME"
} 

if ![info exists TOP_LEVEL_NAME] { 
  set TOP_LEVEL_NAME "niosII_system"
} elseif { ![ string match "" $TOP_LEVEL_NAME ] } { 
  set TOP_LEVEL_NAME "$TOP_LEVEL_NAME"
} 

if ![info exists QSYS_SIMDIR] { 
  set QSYS_SIMDIR "./../"
} elseif { ![ string match "" $QSYS_SIMDIR ] } { 
  set QSYS_SIMDIR "$QSYS_SIMDIR"
} 


# ----------------------------------------
# Copy ROM/RAM files to simulation directory
file copy -force $QSYS_SIMDIR/submodules/niosII_system_onchip_memory2_0.hex ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.dat ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.mif ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.hex ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_b.dat ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.hex ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.dat ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_ociram_default_contents.mif ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.mif ./
file copy -force $QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_rf_ram_a.hex ./

# ----------------------------------------
# Create compilation libraries
proc ensure_lib { lib } { if ![file isdirectory $lib] { vlib $lib } }
ensure_lib          ./libraries/     
ensure_lib          ./libraries/work/
vmap       work     ./libraries/work/
vmap       work_lib ./libraries/work/
if { ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] } {
  ensure_lib                  ./libraries/altera_ver/      
  vmap       altera_ver       ./libraries/altera_ver/      
  ensure_lib                  ./libraries/lpm_ver/         
  vmap       lpm_ver          ./libraries/lpm_ver/         
  ensure_lib                  ./libraries/sgate_ver/       
  vmap       sgate_ver        ./libraries/sgate_ver/       
  ensure_lib                  ./libraries/altera_mf_ver/   
  vmap       altera_mf_ver    ./libraries/altera_mf_ver/   
  ensure_lib                  ./libraries/altera_lnsim_ver/
  vmap       altera_lnsim_ver ./libraries/altera_lnsim_ver/
  ensure_lib                  ./libraries/cycloneii_ver/   
  vmap       cycloneii_ver    ./libraries/cycloneii_ver/   
  ensure_lib                  ./libraries/altera/          
  vmap       altera           ./libraries/altera/          
  ensure_lib                  ./libraries/lpm/             
  vmap       lpm              ./libraries/lpm/             
  ensure_lib                  ./libraries/sgate/           
  vmap       sgate            ./libraries/sgate/           
  ensure_lib                  ./libraries/altera_mf/       
  vmap       altera_mf        ./libraries/altera_mf/       
  ensure_lib                  ./libraries/altera_lnsim/    
  vmap       altera_lnsim     ./libraries/altera_lnsim/    
  ensure_lib                  ./libraries/cycloneii/       
  vmap       cycloneii        ./libraries/cycloneii/       
}
ensure_lib                          ./libraries/up_clocks_0/             
vmap       up_clocks_0              ./libraries/up_clocks_0/             
ensure_lib                          ./libraries/audio_and_video_config_0/
vmap       audio_and_video_config_0 ./libraries/audio_and_video_config_0/
ensure_lib                          ./libraries/audio_0/                 
vmap       audio_0                  ./libraries/audio_0/                 
ensure_lib                          ./libraries/gate_timer/              
vmap       gate_timer               ./libraries/gate_timer/              
ensure_lib                          ./libraries/sram_0/                  
vmap       sram_0                   ./libraries/sram_0/                  
ensure_lib                          ./libraries/sdram_0/                 
vmap       sdram_0                  ./libraries/sdram_0/                 
ensure_lib                          ./libraries/jtag_uart_0/             
vmap       jtag_uart_0              ./libraries/jtag_uart_0/             
ensure_lib                          ./libraries/timer_0/                 
vmap       timer_0                  ./libraries/timer_0/                 
ensure_lib                          ./libraries/sysid_qsys_0/            
vmap       sysid_qsys_0             ./libraries/sysid_qsys_0/            
ensure_lib                          ./libraries/onchip_memory2_0/        
vmap       onchip_memory2_0         ./libraries/onchip_memory2_0/        
ensure_lib                          ./libraries/nios2_qsys_0/            
vmap       nios2_qsys_0             ./libraries/nios2_qsys_0/            

# ----------------------------------------
# Compile device library files
alias dev_com {
  echo "\[exec\] dev_com"
  if { ![ string match "*ModelSim ALTERA*" [ vsim -version ] ] } {
    vlog     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives.v"              -work altera_ver      
    vlog     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220model.v"                       -work lpm_ver         
    vlog     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate.v"                          -work sgate_ver       
    vlog     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf.v"                      -work altera_mf_ver   
    vlog -sv "/OPT/altera/12.1/tools/quartus/eda/sim_lib/mentor/altera_lnsim_for_vhdl.sv"  -work altera_lnsim_ver
    vlog     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_atoms.v"                -work cycloneii_ver   
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_syn_attributes.vhd"        -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_standard_functions.vhd"    -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/alt_dspbuilder_package.vhd"       -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_europa_support_lib.vhd"    -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives_components.vhd" -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_primitives.vhd"            -work altera          
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220pack.vhd"                      -work lpm             
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/220model.vhd"                     -work lpm             
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate_pack.vhd"                   -work sgate           
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/sgate.vhd"                        -work sgate           
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf_components.vhd"         -work altera_mf       
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_mf.vhd"                    -work altera_mf       
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/altera_lnsim_components.vhd"      -work altera_lnsim    
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_atoms.vhd"              -work cycloneii       
    vcom     "/OPT/altera/12.1/tools/quartus/eda/sim_lib/cycloneii_components.vhd"         -work cycloneii       
  }
}

# ----------------------------------------
# Compile the design files in correct order
alias com {
  echo "\[exec\] com"
  vcom "$QSYS_SIMDIR/submodules/niosII_system_up_clocks_0.vhd"                                     -work up_clocks_0             
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_serial_bus_controller.v"                       -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_slow_clock_generator.v"                                  -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init.v"                                   -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_dc2.v"                               -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_d5m.v"                               -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_lcm.v"                               -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ltm.v"                               -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_35.v"                         -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_adv7181.v"                        -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_70.v"                         -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_de2_115.v"                        -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_audio.v"                          -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_av_config_auto_init_ob_adv7180.v"                        -work audio_and_video_config_0
  vcom "$QSYS_SIMDIR/submodules/niosII_system_audio_and_video_config_0.vhd"                        -work audio_and_video_config_0
  vlog "$QSYS_SIMDIR/submodules/altera_up_audio_bit_counter.v"                                     -work audio_0                 
  vlog "$QSYS_SIMDIR/submodules/altera_up_audio_in_deserializer.v"                                 -work audio_0                 
  vlog "$QSYS_SIMDIR/submodules/altera_up_audio_out_serializer.v"                                  -work audio_0                 
  vlog "$QSYS_SIMDIR/submodules/altera_up_clock_edge.v"                                            -work audio_0                 
  vlog "$QSYS_SIMDIR/submodules/altera_up_sync_fifo.v"                                             -work audio_0                 
  vcom "$QSYS_SIMDIR/submodules/niosII_system_audio_0.vhd"                                         -work audio_0                 
  vcom "$QSYS_SIMDIR/submodules/niosII_system_gate_timer.vhd"                                      -work gate_timer              
  vcom "$QSYS_SIMDIR/submodules/niosII_system_sram_0.vhd"                                          -work sram_0                  
  vcom "$QSYS_SIMDIR/submodules/niosII_system_sdram_0.vhd"                                         -work sdram_0                 
  vcom "$QSYS_SIMDIR/submodules/niosII_system_jtag_uart_0.vhd"                                     -work jtag_uart_0             
  vcom "$QSYS_SIMDIR/submodules/niosII_system_timer_0.vhd"                                         -work timer_0                 
  vcom "$QSYS_SIMDIR/submodules/niosII_system_sysid_qsys_0.vho"                                    -work sysid_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_onchip_memory2_0.vhd"                                -work onchip_memory2_0        
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_tck.vhd"              -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_wrapper.vhd"          -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_jtag_debug_module_sysclk.vhd"           -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_oci_test_bench.vhd"                     -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0.vhd"                                    -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/submodules/niosII_system_nios2_qsys_0_test_bench.vhd"                         -work nios2_qsys_0            
  vcom "$QSYS_SIMDIR/niosII_system.vhd"                                                                                          
  vcom "$QSYS_SIMDIR/niosii_system_nios2_qsys_0_jtag_debug_module_translator.vhd"                                                
  vcom "$QSYS_SIMDIR/niosii_system_onchip_memory2_0_s1_translator.vhd"                                                           
  vcom "$QSYS_SIMDIR/niosii_system_sdram_0_s1_translator.vhd"                                                                    
  vcom "$QSYS_SIMDIR/niosii_system_sram_0_avalon_sram_slave_translator.vhd"                                                      
  vcom "$QSYS_SIMDIR/niosii_system_audio_and_video_config_0_avalon_av_config_slave_translator.vhd"                               
  vcom "$QSYS_SIMDIR/niosii_system_synthesizer_0_voice_select_translator.vhd"                                                    
  vcom "$QSYS_SIMDIR/niosii_system_spi_0_spi_control_port_translator.vhd"                                                        
  vcom "$QSYS_SIMDIR/niosii_system_timer_0_s1_translator.vhd"                                                                    
  vcom "$QSYS_SIMDIR/niosii_system_jtag_uart_0_avalon_jtag_slave_translator.vhd"                                                 
}

# ----------------------------------------
# Elaborate top level design
alias elab {
  echo "\[exec\] elab"
  vsim -t ps -L work -L work_lib -L up_clocks_0 -L audio_and_video_config_0 -L audio_0 -L gate_timer -L sram_0 -L sdram_0 -L jtag_uart_0 -L timer_0 -L sysid_qsys_0 -L onchip_memory2_0 -L nios2_qsys_0 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneii_ver -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L cycloneii $TOP_LEVEL_NAME
}

# ----------------------------------------
# Elaborate the top level design with novopt option
alias elab_debug {
  echo "\[exec\] elab_debug"
  vsim -novopt -t ps -L work -L work_lib -L up_clocks_0 -L audio_and_video_config_0 -L audio_0 -L gate_timer -L sram_0 -L sdram_0 -L jtag_uart_0 -L timer_0 -L sysid_qsys_0 -L onchip_memory2_0 -L nios2_qsys_0 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneii_ver -L altera -L lpm -L sgate -L altera_mf -L altera_lnsim -L cycloneii $TOP_LEVEL_NAME
}

# ----------------------------------------
# Compile all the design files and elaborate the top level design
alias ld "
  dev_com
  com
  elab
"

# ----------------------------------------
# Compile all the design files and elaborate the top level design with -novopt
alias ld_debug "
  dev_com
  com
  elab_debug
"

# ----------------------------------------
# Print out user commmand line aliases
alias h {
  echo "List Of Command Line Aliases"
  echo
  echo "dev_com                       -- Compile device library files"
  echo
  echo "com                           -- Compile the design files in correct order"
  echo
  echo "elab                          -- Elaborate top level design"
  echo
  echo "elab_debug                    -- Elaborate the top level design with novopt option"
  echo
  echo "ld                            -- Compile all the design files and elaborate the top level design"
  echo
  echo "ld_debug                      -- Compile all the design files and elaborate the top level design with -novopt"
  echo
  echo 
  echo
  echo "List Of Variables"
  echo
  echo "TOP_LEVEL_NAME                -- Top level module name."
  echo
  echo "SYSTEM_INSTANCE_NAME          -- Instantiated system module name inside top level module."
  echo
  echo "QSYS_SIMDIR                   -- Qsys base simulation directory."
}
h
