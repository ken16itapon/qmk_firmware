# ENCODER_MAP_ENABLE = yes

SRC +=  naginata_v15.c
SRC +=  twpair_on_jis.c

# RAW_ENABLE = yes

# # Unicode機能の有効化
# UNICODE_ENABLE = yes
# CONSOLE_ENABLE = yes

# RGB_MATRIX_ENABLE = yes

EXTRAFLAGS += -flto

EXTRAKEY_ENABLE = no
ENCODER_ENABLE = no
MOUSEKEY_ENABLE = no

SERIAL_DRIVER = vendor
SPLIT_KEYBOARD = yes

RGBLIGHT_ENABLE = yes

MCU = RP2040
BOOTLOADER = rp2040

# Debug機能の有効化
CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes

