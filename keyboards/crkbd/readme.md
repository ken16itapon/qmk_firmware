# Corne Keyboard (CRKBD)

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

![Crkbd](https://user-images.githubusercontent.com/736191/40887871-0eead5dc-678a-11e8-9518-e3ad9e5d2bac.png)

3x6の縦に並んだキーと3つの親指キーを持つ分割キーボードです。
また、拡張キーやロータリーエンコーダーを使用するオプションもあります。

キーボードメンテナー: [foostan](https://github.com/foostan/) [@foostan](https://twitter.com/foostan)  
サポートされているハードウェア: Corne PCB
ハードウェアの入手先: [PCB & ケースデータ](https://github.com/foostan/crkbd)

v1 - v3のキーボードのフラッシュ例:

```sh
qmk flash -kb crkbd/rev1 -km default
```

v4のキーボードのフラッシュ例:

```sh
qmk flash -kb crkbd/rev4 -km default
```

詳細については、[ビルド環境のセットアップ](https://docs.qmk.fm/#/getting_started_build_tools)および[makeの指示](https://docs.qmk.fm/#/getting_started_make_guide)を参照してください。QMKを初めて使う方は、[完全初心者ガイド](https://docs.qmk.fm/#/newbs)から始めてください。

## ブートローダー

Corne PCBには、TRRSジャックの隣にリセットボタンとブートボタンがあり、ブートローダーに入ることができます。

さらに、キーボードのその半分を接続する際に「Q」または「P」ボタンを押し続けると（デフォルトのQWERTYレイアウトに従って）、ブートローダーにジャンプし、EEPROM（永続ストレージ）をリセットします。通常は最上部のコーナーの位置ですが、分離可能な列のため、互換性のためにQとPに残されています。

## RGBマトリックス
Corneキーボードは、RGBライトの代わりにRGBマトリックス機能を使用することもサポートしています。これにより、キーボードの使用時により良い体験が提供されます。キーごとのエフェクトを適切にサポートするためです。スイッチ内のLEDを使用していない場合は、これを行わない方が良いかもしれません。

キーマップの`rules.mk`ファイルに以下を追加します:

```make
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
```

そして、`config.h`ファイルに以下を追加します:

```c
#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // キープレスに反応
// #   define RGB_MATRIX_KEYRELEASES // キーリリースに反応（キープレスの代わりに）
#   define RGB_MATRIX_SLEEP // サスペンド時にエフェクトをオフにする
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // タスク実行ごとにアニメーションで処理するLEDの数を制限（キーボードの応答性を向上）
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // アニメーションがLEDを更新する頻度をミリ秒単位で制限。16（16ms）は60fpsに相当（キーボードの応答性を向上）
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // LEDの最大輝度を255のうち150に制限。高すぎるとコントローラーがクラッシュする可能性あり
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 8
#   define RGB_MATRIX_SPD_STEP 10

/* 必要なアニメーションを有効にします。これらは多くのスペースを占有するため、少数のみを有効にする必要があります。 *
 * 有効にして、ファームウェアが正常にコンパイルできることを確認してください。 */
// RGBマトリックスアニメーションモード。明示的に有効化
// エフェクトの完全なリストについては、以下を参照してください:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
#   define ENABLE_RGB_MATRIX_PIXEL_FLOW
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// RGB_MATRIX_FRAMEBUFFER_EFFECTSが定義されている場合のみ有効
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// RGB_MATRIX_KEYPRESSESまたはRGB_MATRIX_KEYRELEASESが定義されている場合のみ有効
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
```

これが完了すると、通常のRGBキーマップを使用できますが、RGBマトリックスエフェクトが使用され、より良い体験が得られます。
