EXTRAKEY_ENABLE = yes    # Audio control and System control
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no
OLED_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
DIP_SWITCH_ENABLE = no
MOUSEKEY_ENABLE = yes
LTO_ENABLE = yes

# MCU Configuration
MCU = RP2040
BOOTLOADER = rp2040
PLATFORM = CHIBIOS

# Core Features
SPLIT_KEYBOARD = yes
RGBLIGHT_ENABLE = yes
OLED_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# Additional Features
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes

# Drivers
SERIAL_DRIVER = vendor

# Optimization
LTO_ENABLE = yes
ALLOW_WARNINGS = yes

# Source Files
SRC += oled_display.c
