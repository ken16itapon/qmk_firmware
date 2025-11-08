# Keychron V2 ANSI キーボードのソース構成と機能分担

## 概要

Keychron V2は階層的なディレクトリ構造で、共通機能と各バリアント固有の機能を分離しています。
この設計により、DIPスイッチやCapsLock LEDなどの共通機能は一箇所で管理され、各バリアント（ANSI/ISO/JIS）は物理的な違い（LED配置、キー配列）のみを定義します。

## ディレクトリ構造

```
keyboards/keychron/v2/
├── config.h              # 共通設定（全バリアント共通）
├── info.json             # 共通情報（EEPROM、RGB、DIPスイッチ）
├── v2.c                  # 共通機能実装
├── mcuconf.h / halconf.h # MCU/HAL設定
├── readme.md             # ドキュメント
│
├── ansi/                 # ANSIバリアント（67キー標準）
│   ├── config.h          # ANSI固有設定
│   ├── keyboard.json     # ANSI固有のハードウェア定義
│   ├── ansi.c            # ANSI固有のRGB LED配置
│   └── keymaps/
│       └── default/
│           └── keymap.c  # デフォルトキーマップ
│
├── ansi_encoder/         # エンコーダー付きANSI
├── iso/                  # ISOバリアント
├── iso_encoder/          # エンコーダー付きISO
├── jis/                  # JISバリアント
└── jis_encoder/          # エンコーダー付きJIS
```

---

## 各ファイルの機能分担

### 1. 親ディレクトリ (keyboards/keychron/v2/)

共通機能を実装する層。全バリアントで共有されます。

#### v2.c - 共通機能実装

**役割**: 全バリアント共通の動作ロジック

```c
// DIPスイッチ処理（Mac/Winレイヤー切替）
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false;}
    if (index == 0) {
        default_layer_set(1UL << (active ? 1 : 0));
    }
    return true;
}

// RGBマトリックス制御
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // RGB全消灯機能の実装
    ...
}

// CapsLock LED表示
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    }
    ...
}
```

**実装されている機能**:
- **DIPスイッチ処理**: スイッチのON/OFFでMac（レイヤー0）/Windows（レイヤー1）を切り替え
- **RGB全消灯機能**: `QK_RGB_MATRIX_TOGGLE`で全LED消灯モード切替
- **CapsLock LED**: CapsLock状態に応じて指定LEDを白色点灯

---

#### config.h - 共通ハードウェア設定

**役割**: RGB LEDドライバーとI2C通信の設定

```c
/* RGB Matrix Driver Configuration */
#define SNLED27351_I2C_ADDRESS_1 SNLED27351_I2C_ADDRESS_VDDIO
#define SNLED27351_I2C_ADDRESS_2 SNLED27351_I2C_ADDRESS_GND

/* Increase I2C speed to 1000 KHz */
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 15U
#define I2C1_TIMINGR_SCLL 51U

#define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL

// 動的キーマップのレイヤー数
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
```

**設定項目**:
- **SNLED27351ドライバー**: 2つのI2Cアドレス（VDDIO、GND）
- **I2C高速化**: 1000 KHzに設定（デフォルトより高速）
- **スキャンフェーズ**: 9チャンネルスキャン設定
- **レイヤー数**: VIAで使用可能なレイヤー数を5に設定

---

#### info.json - 共通機能定義

**役割**: 共通機能の宣言（RGB、EEPROM、DIPスイッチ）

```json
{
    "eeprom": {
        "wear_leveling": {
            "backing_size": 4096
        }
    },
    "dip_switch": {
        "matrix_grid": [ [4, 4] ]
    },
    "rgb_matrix": {
        "animations": {
            "breathing": true,
            "cycle_all": true,
            "rainbow_moving_chevron": true,
            ...
        },
        "driver": "snled27351",
        "sleep": true
    }
}
```

**定義内容**:
- **EEPROM**: Wear Leveling機能で4096バイト確保
- **DIPスイッチ**: マトリックス位置[4, 4]に配置
- **RGB Matrix**: 
  - 有効化されたアニメーション21種類
  - ドライバー指定（SNLED27351）
  - スリープモード有効

---

### 2. ANSIバリアント (keyboards/keychron/v2/ansi/)

ANSI配列固有のハードウェア仕様とLED配置を定義します。

#### keyboard.json - ハードウェア定義

**役割**: ANSI固有のハードウェア仕様

```json
{
    "keyboard_name": "Keychron V2",
    "manufacturer": "Keychron",
    "usb": {
        "vid": "0x3434",
        "pid": "0x0320",
        "device_version": "1.0.0"
    },
    "features": {
        "bootmagic": true,
        "dip_switch": true,
        "extrakey": true,
        "mousekey": true,
        "nkro": true,
        "rgb_matrix": true
    },
    "matrix_pins": {
        "cols": ["C14", "C15", "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "B0", "B1", "A8", "A9", "H3"],
        "rows": ["B4", "B3", "A15", "A14", "A13"]
    },
    "diode_direction": "ROW2COL",
    "processor": "STM32L432",
    "bootloader": "stm32-dfu",
    "layouts": {
        "LAYOUT_ansi_67": {
            "layout": [ ... ]
        }
    }
}
```

**定義内容**:
- **USB識別子**: VID=0x3434 (Keychron), PID=0x0320 (V2 ANSI)
- **有効機能**: Bootmagic、DIPスイッチ、メディアキー、マウスキー、NKRO、RGB Matrix
- **マトリックス**: 5行×15列、ROW2COL方式
- **MCU**: STM32L432（ARM Cortex-M4）
- **ブートローダー**: STM32-DFU
- **レイアウト**: 67キー ANSI配列（物理座標とマトリックス位置のマッピング）

---

#### ansi.c - RGB LED物理配置

**役割**: RGB LEDのハードウェア接続と物理配置

```c
#ifdef RGB_MATRIX_ENABLE

// SNLED27351ドライバーのLED配線マッピング（67個のLED）
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, CB3_CA1,    CB1_CA1,    CB2_CA1},  // LED 0
    {0, CB3_CA2,    CB1_CA2,    CB2_CA2},  // LED 1
    ...
    {1, CB6_CA16,   CB4_CA16,   CB5_CA16}  // LED 66
};

// LED設定（マトリックス、物理座標、フラグ）
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index（5x15マトリックス → LED番号）
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14 },
        { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 },
        { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 65, 42, 43 },
        { 44, __, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, __, 55, 56 },
        { 57, 58, 59, __, __, __, 60, __, __, __, 61, 62, 63, 64, 66 }
    },
    {
        // LED Index to Physical Position（x, y座標 0-224）
        {0,0}, {15,0}, {29,0}, ..., {224,64}
    },
    {
        // RGB LED Index to Flag
        // 1=修飾キー, 4=通常キー, 8=特殊キー（CapsLock等）
        1, 4, 4, 4, 4, 4, 4, 4, ..., 1, 1, 1
    }
};

#endif // RGB_MATRIX_ENABLE
```

**定義内容**:
- **LED配線情報**: 67個のLEDがドライバー0/1のどのチャンネル（CB3_CA1等）に接続されているか
- **マトリックスマッピング**: キーマトリックス位置 → LED番号の対応
- **物理座標**: 各LEDのX/Y座標（RGBアニメーション用）
- **LEDフラグ**: 
  - `1` = 修飾キー（ESC、Tab、Caps、Shift、Ctrl等）
  - `4` = 通常キー
  - `8` = CapsLock LED

---

#### config.h - ANSI固有設定

**役割**: RGB輝度調整とCapsLock LED位置

```c
// LEDドライバーの電流調整（RGB各色の輝度バランス）
#define SNLED27351_CURRENT_TUNE \
    { 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60, 0xCA, 0xCA, 0x60 }

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 30
```

**設定項目**:
- **電流調整**: RGB各チャンネルの電流値（色バランス調整）
- **CapsLock LED**: LED番号30（Caps Lockキー）を指定

---

### 3. デフォルトキーマップ (keymaps/default/)

#### keymap.c - キー配列定義

**役割**: ユーザーが触る唯一のファイル - 実際のキー配列を定義

```c
enum layers{
    MAC_BASE,   // Mac用ベースレイヤー（レイヤー0）
    WIN_BASE,   // Windows用ベースレイヤー（レイヤー1）
    _FN1,       // Mac Fnレイヤー（RGB制御、メディアキー）
    _FN2,       // Win Fnレイヤー（RGB制御、メディアキー、タスクビュー）
    _FN3        // 共通Fnレイヤー（Fキー、RGB制御）
};

#define KC_TASK LGUI(KC_TAB)        // Windowsタスクビュー
#define KC_FLXP LGUI(KC_E)          // Windowsエクスプローラー

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_67(
        KC_ESC,  KC_1,    KC_2,    KC_3,    ...,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    ...,
        KC_CAPS, KC_A,    KC_S,    KC_D,    ...,
        KC_LSFT,          KC_Z,    KC_X,    ...,
        KC_LCTL, KC_LOPT, KC_LCMD,          KC_SPC, ..., MO(_FN1), ...
    ),

    [WIN_BASE] = LAYOUT_ansi_67(
        // Macとほぼ同じだが、修飾キーが異なる
        // KC_LOPT → KC_LWIN, KC_LCMD → KC_LALT
        ...
    ),

    [_FN1] = LAYOUT_ansi_67(
        // Mac Fnレイヤー
        KC_GRV,  KC_BRID, KC_BRIU, KC_NO,   KC_NO,   RM_VALD, RM_VALU, ...,
        RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, ...,
        ...
    ),

    [_FN2] = LAYOUT_ansi_67(
        // Win Fnレイヤー（Mac FN1に加えてKC_TASK、KC_FLXP追加）
        KC_GRV,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, RM_VALD, RM_VALU, ...,
        ...
    ),

    [_FN3] = LAYOUT_ansi_67(
        // 共通Fnレイヤー（Fキー）
        KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, ...,
        RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, ...,
        ...
    )
};
```

**レイヤー構成**:
- **MAC_BASE**: Mac用標準配列（Cmd、Optionキー）
- **WIN_BASE**: Windows用標準配列（Win、Altキー）
- **_FN1**: Mac Fnレイヤー
  - 輝度調整（KC_BRID/BRIU）
  - RGB制御（RM_TOGG、RM_NEXT、RM_VALU等）
  - メディアキー（KC_MPRV、KC_MPLY、KC_MNXT、KC_VOLU等）
- **_FN2**: Windows Fnレイヤー（_FN1 + Windows固有機能）
  - タスクビュー（Win+Tab）
  - エクスプローラー（Win+E）
- **_FN3**: 共通Fnレイヤー
  - Fキー（F1～F12）
  - RGB制御

---

## 機能の流れ

### 起動時の初期化シーケンス

```
1. keyboard.json 読み込み
   ↓
   - USB ID設定（VID/PID）
   - マトリックスピン設定（15列×5行）
   - プロセッサ/ブートローダー設定
   
2. config.h (親) 読み込み
   ↓
   - I2C通信設定（1000 KHz）
   - RGB LEDドライバー初期化（SNLED27351）
   
3. ansi.c 実行
   ↓
   - LED配線情報読み込み（67個のLED）
   - LED物理座標設定
   
4. v2.c 実行
   ↓
   - DIPスイッチ状態確認
   - 初期レイヤー設定（Mac=0 / Win=1）
```

---

### キー押下時の処理フロー

```
1. ハードウェアスキャン（keyboard.json）
   ↓
   マトリックス位置 [row, col] 検出
   
2. キーマップ参照（keymap.c）
   ↓
   現在のレイヤーから keycode 取得
   
3. 特殊処理判定（v2.c: process_record_kb）
   ↓
   - RGB制御キー → 全消灯処理
   - その他 → QMKコアへ
   
4. キーコード送信（QMKコア）
   ↓
   USB経由でホストPCへ送信
```

---

### RGB制御時の処理フロー

```
1. RGBキーコード押下（keymap.c）
   ↓
   例: RM_TOGG（RGB ON/OFF）
   
2. 特殊処理（v2.c: process_record_kb）
   ↓
   QK_RGB_MATRIX_TOGGLE時:
   - LED_FLAG_ALL → LED_FLAG_NONE（全消灯）
   - LED_FLAG_NONE → LED_FLAG_ALL（全点灯）
   
3. インジケーター処理（v2.c: rgb_matrix_indicators_advanced_kb）
   ↓
   CapsLock状態確認:
   - ON  → LED 30番を白色(255,255,255)
   - OFF → LED 30番を消灯(0,0,0)
   
4. LED制御（ansi.c: g_led_config）
   ↓
   - LED番号 → 物理座標マッピング
   - LED番号 → ドライバーチャンネルマッピング
   
5. ハードウェア出力（SNLED27351ドライバー）
   ↓
   I2C経由でLEDドライバーへ送信
```

---

## 他のバリアントとの関係

同じ親ディレクトリに複数のバリアントが存在し、共通機能を共有します：

| バリアント | ファイル | 特徴 |
|-----------|---------|------|
| **ansi/** | ansi.c, keyboard.json | 標準67キー、エンコーダーなし |
| **ansi_encoder/** | ansi_encoder.c, keyboard.json | エンコーダー付き67キー |
| **iso/** | iso.c, keyboard.json | ISO配列（Enterキー縦長） |
| **iso_encoder/** | iso_encoder.c, keyboard.json | エンコーダー付きISO |
| **jis/** | jis.c, keyboard.json | JIS配列 |
| **jis_encoder/** | jis_encoder.c, keyboard.json | エンコーダー付きJIS |

**共有される機能**（親ディレクトリ）:
- DIPスイッチによるMac/Win切替（v2.c）
- CapsLock LED制御（v2.c）
- RGB全消灯機能（v2.c）
- I2C/RGBドライバー設定（config.h）
- RGBアニメーション定義（info.json）

**バリアント固有の定義**:
- LED物理配置（*.c）
- マトリックスピン配置（keyboard.json）
- USB PID（keyboard.json）
- キー物理座標（keyboard.json）

---

## カスタマイズガイド

### 1. キー配列を変更したい

→ **keymaps/default/keymap.c** を編集
- レイヤー定義を変更
- キーコードを置き換え
- カスタムレイヤーを追加

### 2. CapsLock LED位置を変更したい

→ **ansi/config.h** を編集
```c
#define CAPS_LOCK_LED_INDEX 30  // ← LED番号を変更
```

### 3. RGB輝度/色バランスを調整したい

→ **ansi/config.h** を編集
```c
#define SNLED27351_CURRENT_TUNE \
    { 0xCA, 0xCA, 0x60, ... }  // ← 各色の電流値を調整
```

### 4. 独自のRGB制御を追加したい

→ **v2.c** の `process_record_kb()` に追加
```c
case MY_CUSTOM_RGB:
    if (record->event.pressed) {
        // カスタムRGB処理
    }
    return false;
```

### 5. DIPスイッチの動作を変更したい

→ **v2.c** の `dip_switch_update_kb()` を編集
```c
if (index == 0) {
    default_layer_set(1UL << (active ? 1 : 0));  // ← レイヤー番号変更
}
```

---

## まとめ

Keychron V2の設計哲学：
- **階層構造**: 共通機能と固有機能を明確に分離
- **再利用性**: 複数バリアントで共通コードを共有
- **保守性**: 機能ごとにファイルが分かれており、変更箇所が明確
- **拡張性**: 新しいバリアント追加時は最小限のファイル作成で対応可能

**ユーザーが触るファイル**: `keymaps/default/keymap.c` のみ
**開発者が触るファイル**: バリアント固有の定義（keyboard.json、*.c、config.h）
**フレームワークファイル**: 親ディレクトリの共通機能（通常は変更不要）
