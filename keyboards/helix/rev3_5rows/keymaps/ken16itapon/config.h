// ...existing code...

// Unicode設定の追加
// #define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX, UNICODE_MODE_MACOS
// #define UNICODE_KEY_WINCOMPOSE KC_RALT  // Windows Composeキー

#define NG_NO_HENSHU
#define NG_NO_KOYUMEISHI
#define SHINGETA

#ifdef RGB_MATRIX_ENABLE
    #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10
    #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#endif

#define TAPPING_TERM 150 // デフォルトは200ms

