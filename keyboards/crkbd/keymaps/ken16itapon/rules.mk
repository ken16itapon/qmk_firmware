UNICODE_ENABLE = yes

TAP_DANCE_ENABLE = yes

# If you want to change the display of OLED, you need to change here
SRC +=  naginata_v15.c
SRC +=  twpair_on_jis.c

RAW_ENABLE = yes
RGB_MATRIX_ENABLE = yes      # LEDマトリックスを有効化
RGB_MATRIX_DRIVER = WS2812   # または IS31FL3731（使用しているLEDドライバによる）

# WS2812の場合
WS2812_DRIVER = spi          # または bitbang（使用されているドライバーによる）

# これらも確認してください
RGBLIGHT_ENABLE = no         # RGB_MATRIXと競合するためnoに

OS_DETECTION_ENABLE = yes

