
# MCU and Bootloader config
# RP2040 configuration (removed, using keyboard.json instead)

# Build Options
ENCODER_MAP_ENABLE = no     # Disable encoder map to save space
MOUSEKEY_ENABLE = no        # Mouse keys (disabled to save space)
EXTRAKEY_ENABLE = yes       # Audio control and System control
UNICODE_ENABLE = yes        # Unicode support (required for Naginata)
LTO_ENABLE = yes            # Link Time Optimization to reduce size
SPACE_CADET_ENABLE = no     # Disable Space Cadet to save space
GRAVE_ESC_ENABLE = no       # Disable Grave Escape to save space
MAGIC_ENABLE = no           # Disable Magic keycodes to save space
OLED_ENABLE = no            # Disable OLED to save space
RGBLIGHT_ENABLE = yes       # Enable RGB lighting for mode indication

# 薙刀式配列用の定義
NAGINATA_ENABLE = yes
OPT_DEFS += -DNAGINATA_ENABLE

# OS選択（デフォルトはMac）
# Windows用にコンパイルする場合: make helix/rev3_5rows:ken16itapon TARGET_OS=WIN
TARGET_OS ?= MAC

ifeq ($(TARGET_OS),WIN)
    OPT_DEFS += -DTARGET_OS_WINDOWS
    # Windows用にtwpair_on_jisを有効化
    SRC += key_handlers.c state_manager.c naginata_v15.c os_specific.c twpair_on_jis.c
else
    OPT_DEFS += -DTARGET_OS_MACOS
    # Mac用（twpair_on_jisは不要）
    SRC += key_handlers.c state_manager.c naginata_v15.c os_specific.c
endif
