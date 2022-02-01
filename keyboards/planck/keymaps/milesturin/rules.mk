MCU = STM32F303

BOOTLOADER = stm32-dfu

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = yes        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no 	    # Enable keyboard RGB underglow
AUDIO_ENABLE = yes          # Audio output
WS2812_DRIVER = pwm
CUSTOM_MATRIX = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
ENCODER_ENABLE = yes
DIP_SWITCH_ENABLE = no

SRC += matrix.c
SRC += muse.c

LAYOUTS = ortho_4x12 planck_mit
LAYOUTS_HAS_RGB = no
