# スプリット設定
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = vendor
SPLIT_TRANSPORT_SYNC = yes

# デバッグ機能
CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes

# RGB機能
RGBLIGHT_ENABLE = yes

# 無効化する機能
EXTRAKEY_ENABLE = no
ENCODER_ENABLE = no
MOUSEKEY_ENABLE = no

# 最適化
EXTRAFLAGS += -flto

# ソースファイル
SRC += naginata_v15.c
SRC += twpair_on_jis.c
SRC += split_debug.c
