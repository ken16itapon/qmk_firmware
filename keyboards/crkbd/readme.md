# Corne Keyboard (CRKBD)

![Crkbd](https://user-images.githubusercontent.com/736191/40575636-6fba63a4-6123-11e8-9ca0-3f990f1f9f4c.jpg)

![Crkbd](https://user-images.githubusercontent.com/736191/40887871-0eead5dc-678a-11e8-9518-e3ad9e5d2bac.png)

3x6�̏c�ɕ��񂾃L�[��3�̐e�w�L�[���������L�[�{�[�h�ł��B
�܂��A�g���L�[�⃍�[�^���[�G���R�[�_�[���g�p����I�v�V����������܂��B

�L�[�{�[�h�����e�i�[: [foostan](https://github.com/foostan/) [@foostan](https://twitter.com/foostan)  
�T�|�[�g����Ă���n�[�h�E�F�A: Corne PCB
�n�[�h�E�F�A�̓����: [PCB & �P�[�X�f�[�^](https://github.com/foostan/crkbd)

v1 - v3�̃L�[�{�[�h�̃t���b�V����:

```sh
qmk flash -kb crkbd/rev1 -km default
```

v4�̃L�[�{�[�h�̃t���b�V����:

```sh
qmk flash -kb crkbd/rev4 -km default
```

�ڍׂɂ��ẮA[�r���h���̃Z�b�g�A�b�v](https://docs.qmk.fm/#/getting_started_build_tools)�����[make�̎w��](https://docs.qmk.fm/#/getting_started_make_guide)���Q�Ƃ��Ă��������BQMK�����߂Ďg�����́A[���S���S�҃K�C�h](https://docs.qmk.fm/#/newbs)����n�߂Ă��������B

## �u�[�g���[�_�[

Corne PCB�ɂ́ATRRS�W���b�N�ׂ̗Ƀ��Z�b�g�{�^���ƃu�[�g�{�^��������A�u�[�g���[�_�[�ɓ��邱�Ƃ��ł��܂��B

����ɁA�L�[�{�[�h�̂��̔�����ڑ�����ۂɁuQ�v�܂��́uP�v�{�^��������������Ɓi�f�t�H���g��QWERTY���C�A�E�g�ɏ]���āj�A�u�[�g���[�_�[�ɃW�����v���AEEPROM�i�i���X�g���[�W�j�����Z�b�g���܂��B�ʏ�͍ŏ㕔�̃R�[�i�[�̈ʒu�ł����A�����\�ȗ�̂��߁A�݊����̂��߂�Q��P�Ɏc����Ă��܂��B

## RGB�}�g���b�N�X
Corne�L�[�{�[�h�́ARGB���C�g�̑����RGB�}�g���b�N�X�@�\���g�p���邱�Ƃ��T�|�[�g���Ă��܂��B����ɂ��A�L�[�{�[�h�̎g�p���ɂ��ǂ��̌����񋟂���܂��B�L�[���Ƃ̃G�t�F�N�g��K�؂ɃT�|�[�g���邽�߂ł��B�X�C�b�`����LED���g�p���Ă��Ȃ��ꍇ�́A������s��Ȃ������ǂ���������܂���B

�L�[�}�b�v��`rules.mk`�t�@�C���Ɉȉ���ǉ����܂�:

```make
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
```

�����āA`config.h`�t�@�C���Ɉȉ���ǉ����܂�:

```c
#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // �L�[�v���X�ɔ���
// #   define RGB_MATRIX_KEYRELEASES // �L�[�����[�X�ɔ����i�L�[�v���X�̑���Ɂj
#   define RGB_MATRIX_SLEEP // �T�X�y���h���ɃG�t�F�N�g���I�t�ɂ���
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // �^�X�N���s���ƂɃA�j���[�V�����ŏ�������LED�̐��𐧌��i�L�[�{�[�h�̉�����������j
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // �A�j���[�V������LED���X�V����p�x���~���b�P�ʂŐ����B16�i16ms�j��60fps�ɑ����i�L�[�{�[�h�̉�����������j
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // LED�̍ő�P�x��255�̂���150�ɐ����B��������ƃR���g���[���[���N���b�V������\������
#   define RGB_MATRIX_HUE_STEP 8
#   define RGB_MATRIX_SAT_STEP 8
#   define RGB_MATRIX_VAL_STEP 8
#   define RGB_MATRIX_SPD_STEP 10

/* �K�v�ȃA�j���[�V������L���ɂ��܂��B�����͑����̃X�y�[�X���L���邽�߁A�����݂̂�L���ɂ���K�v������܂��B *
 * �L���ɂ��āA�t�@�[���E�F�A������ɃR���p�C���ł��邱�Ƃ��m�F���Ă��������B */
// RGB�}�g���b�N�X�A�j���[�V�������[�h�B�����I�ɗL����
// �G�t�F�N�g�̊��S�ȃ��X�g�ɂ��ẮA�ȉ����Q�Ƃ��Ă�������:
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
// RGB_MATRIX_FRAMEBUFFER_EFFECTS����`����Ă���ꍇ�̂ݗL��
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// RGB_MATRIX_KEYPRESSES�܂���RGB_MATRIX_KEYRELEASES����`����Ă���ꍇ�̂ݗL��
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

���ꂪ��������ƁA�ʏ��RGB�L�[�}�b�v���g�p�ł��܂����ARGB�}�g���b�N�X�G�t�F�N�g���g�p����A���ǂ��̌��������܂��B
