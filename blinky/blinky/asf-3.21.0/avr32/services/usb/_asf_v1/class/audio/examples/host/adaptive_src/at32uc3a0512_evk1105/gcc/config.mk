#
# Copyright (c) 2009-2010 Atmel Corporation. All rights reserved.
#
# \asf_license_start
#
# \page License
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. The name of Atmel may not be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# 4. This software may only be redistributed and used in connection with an
#    Atmel microcontroller product.
#
# THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# \asf_license_stop
#

# Path to top level ASF directory relative to this project directory.
PRJ_PATH = ../../../../../../../../../../..

# Target CPU architecture: ap, ucr1, ucr2 or ucr3
ARCH = ucr2

# Target part: none, ap7xxx or uc3xxxxx
PART = uc3a0512

# Target device flash memory details (used by the avr32program programming
# tool: [cfi|internal]@address
FLASH = internal@0x80000000

# Clock source to use when programming; xtal, extclk or int
PROG_CLOCK = int

# Application target name. Given with suffix .a for library and .elf for a
# standalone application.
TARGET = adaptif_src_example.elf

# List of C source files.
CSRCS = \
       avr32/boards/evk1105/led.c                         \
       avr32/components/audio/amp/tpa6130a2/tpa6130.c     \
       avr32/components/audio/codec/tlv320aic23b/tlv320aic23b.c \
       avr32/components/audio/dac/pwm_dac/pwm_dac.c       \
       avr32/components/display/et024006dhu/et024006dhu.c \
       avr32/drivers/abdac/abdac.c                        \
       avr32/drivers/ebi/smc/smc.c                        \
       avr32/drivers/flashc/flashc.c                      \
       avr32/drivers/gpio/gpio.c                          \
       avr32/drivers/intc/intc.c                          \
       avr32/drivers/pdca/pdca.c                          \
       avr32/drivers/pm/pm.c                              \
       avr32/drivers/pm/pm_conf_clocks.c                  \
       avr32/drivers/pm/power_clocks_lib.c                \
       avr32/drivers/ssc/i2s/ssc_i2s.c                    \
       avr32/drivers/twi/twi.c                            \
       avr32/drivers/usart/usart.c                        \
       avr32/drivers/usbb/_asf_v1/enum/host/usb_host_enum.c \
       avr32/drivers/usbb/_asf_v1/enum/host/usb_host_task.c \
       avr32/drivers/usbb/_asf_v1/enum/usb_task.c         \
       avr32/drivers/usbb/_asf_v1/usb_drv.c               \
       avr32/services/audio/audio_mixer/audio_mixer.c     \
       avr32/services/audio/audio_player/players/usb/usb_stream_player_with_resampling.c \
       avr32/services/usb/_asf_v1/class/audio/examples/host/audio_example.c \
       avr32/services/usb/_asf_v1/class/audio/examples/host/avr32_logo.c \
       avr32/services/usb/_asf_v1/class/audio/examples/host/enum/host/usb_host_user.c \
       avr32/services/usb/_asf_v1/class/audio/examples/host/host_audio_task.c \
       avr32/services/usb/_asf_v1/class/audio/examples/host/user_interface/controller/qt1081_controller.c \
       avr32/utils/debug/debug.c                          \
       avr32/utils/debug/print_funcs.c

# List of assembler source files.
ASSRCS = \
       avr32/drivers/intc/exception.S                     \
       avr32/utils/startup/trampoline_uc3.S

# List of include paths.
INC_PATH = \
       avr32/boards                                       \
       avr32/boards/evk1105                               \
       avr32/components/audio                             \
       avr32/components/audio/amp/tpa6130a2               \
       avr32/components/audio/codec/tlv320aic23b          \
       avr32/components/audio/dac/pwm_dac                 \
       avr32/components/display/et024006dhu               \
       avr32/components/touch/qt1081                      \
       avr32/drivers/abdac                                \
       avr32/drivers/cpu/cycle_counter                    \
       avr32/drivers/ebi/smc                              \
       avr32/drivers/flashc                               \
       avr32/drivers/gpio                                 \
       avr32/drivers/intc                                 \
       avr32/drivers/pdca                                 \
       avr32/drivers/pm                                   \
       avr32/drivers/ssc/i2s                              \
       avr32/drivers/twi                                  \
       avr32/drivers/usart                                \
       avr32/drivers/usbb/_asf_v1                         \
       avr32/drivers/usbb/_asf_v1/enum                    \
       avr32/drivers/usbb/_asf_v1/enum/host               \
       avr32/services/audio/audio_mixer                   \
       avr32/services/audio/audio_player/players/usb      \
       avr32/services/usb/_asf_v1                         \
       avr32/services/usb/_asf_v1/class/audio             \
       avr32/services/usb/_asf_v1/class/audio/examples/host \
       avr32/services/usb/_asf_v1/class/audio/examples/host/adaptive_src \
       avr32/services/usb/_asf_v1/class/audio/examples/host/adaptive_src/at32uc3a0512_evk1105 \
       avr32/services/usb/_asf_v1/class/audio/examples/host/conf \
       avr32/services/usb/_asf_v1/class/audio/examples/host/enum \
       avr32/services/usb/_asf_v1/class/audio/examples/host/enum/host \
       avr32/services/usb/_asf_v1/class/audio/examples/host/user_interface/controller \
       avr32/services/usb/_asf_v1/class/hid               \
       avr32/utils                                        \
       avr32/utils/debug                                  \
       avr32/utils/libs/dsplib/include                    \
       avr32/utils/preprocessor                           \
       common/boards                                      \
       common/utils                                       \
       thirdparty/newlib_addons/libs/include \
       avr32/services/usb/_asf_v1/class/audio/examples/host/adaptive_src/at32uc3a0512_evk1105/gcc

# Additional search paths for libraries.
LIB_PATH =  \
       avr32/utils/libs/dsplib/at32ucr2/gcc               \
       thirdparty/newlib_addons/libs/at32ucr2            

# List of libraries to use during linking.
LIBS =  \
       dsp-at32ucr2-dspspeed_opt                          \
       newlib_addons-at32ucr2-speed_opt                  

# Path relative to top level directory pointing to a linker script.
LINKER_SCRIPT = avr32/utils/linker_scripts/at32uc3a/0512/gcc/link_uc3a0512.lds

# Additional options for debugging. By default the common Makefile.in will
# add -g3.
DBGFLAGS = 

# Application optimization used during compilation and linking:
# -O0, -O1, -O2, -O3 or -Os
OPTIMIZATION = -O3

# Extra flags to use when archiving.
ARFLAGS = 

# Extra flags to use when assembling.
ASFLAGS = 

# Extra flags to use when compiling.
CFLAGS = 

# Extra flags to use when preprocessing.
#
# Preprocessor symbol definitions
#   To add a definition use the format "-D name[=definition]".
#   To cancel a definition use the format "-U name".
#
# The most relevant symbols to define for the preprocessor are:
#   BOARD      Target board in use, see boards/board.h for a list.
#   EXT_BOARD  Optional extension board in use, see boards/board.h for a list.
CPPFLAGS = \
       -D BOARD=EVK1105                                   \
       -D CONFIG_INTERRUPT_FORCE_INTC

# Extra flags to use when linking
LDFLAGS = \
        -Wl,-e,_trampoline

# Pre- and post-build commands
PREBUILD_CMD = 
POSTBUILD_CMD = 