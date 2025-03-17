# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
WPM_ENABLE = no             # WPM calculation
RGB_MATRIX_ENABLE = yes     # Enable RGB matrix effects
UNICODE_ENABLE = yes         # Unicode
OS_DETECTION_ENABLE = yes

# 薙刀式配列用の定義
NAGINATA_ENABLE = yes

# タップダンス機能を有効化
TAP_DANCE_ENABLE = yes

# デバッグ用
CONSOLE_ENABLE = yes

# 分割ファイルを追加
SRC += key_handlers.c state_manager.c os_specific.c naginata_v15.c twpair_on_jis.c

