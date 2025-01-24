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
# ENCODER_ENABLE = no
MOUSEKEY_ENABLE = no
CONSOLE_ENABLE = no

RGBLIGHT_ENABLE = yes

