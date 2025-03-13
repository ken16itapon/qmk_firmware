/*
 * QMK Firmware用: 直接カナ入力キー定義（例）
 * （濁点・半濁点・読点・句点を含む）
 *
 *  - 「あ」= '3'キー           → KN_A  = KC_3
 *  - 「い」= 'E'キー           → KN_I  = KC_E
 *  - 「け」= Shift + ';'キー   → KN_KE = S(KC_SCLN)
 *  - 「が」= 「か」入力後に    → KN_DAKU = S(KC_2)
 *  - 「ぱ」= 「は」入力後に    → KN_HANDAKU = S(KC_3)
 *  - 読点(、)= Shift + ','     → KN_TOUTEN = S(KC_COMM)
 *  - 句点(。)= Shift + '.'     → KN_KUTEN  = S(KC_DOT)
 *
 * 注意:
 *  - 実際の文字入力結果は、OS/IMEやキーボード配列設定(かな入力モード)によって決まります。
 *  - ここでは「JIS配列 + かな入力」でよく見られる割り当てを例示しています。
 *  - 実機の配列や設定次第では KC_INT系など別のキーコードが必要になる場合があります。
 */

/* あ行 (a, i, u, e, o) */
#define KN_A    KC_3      // あ
#define KN_I    KC_E      // い
#define KN_U    KC_4      // う
#define KN_E    KC_5      // え
#define KN_O    KC_6      // お

/* か行 (ka, ki, ku, ke, ko) */
#define KN_KA   KC_T              // か
#define KN_KI   KC_G              // き
#define KN_KU   KC_H              // く
#define KN_KE   S(KC_SCLN)        // け = Shift + ';'
#define KN_KO   KC_B              // こ

/* さ行 (sa, shi, su, se, so) */
#define KN_SA   KC_X      // さ
#define KN_SHI  KC_D      // し
#define KN_SU   KC_R      // す
#define KN_SE   KC_P      // せ
#define KN_SO   KC_C      // そ

/* た行 (ta, chi, tsu, te, to) */
#define KN_TA   KC_Q      // た
#define KN_CHI  KC_A      // ち
#define KN_TSU  KC_Z      // つ
#define KN_TE   KC_W      // て
#define KN_TO   KC_S      // と

/* な行 (na, ni, nu, ne, no) */
#define KN_NA   KC_U      // な
#define KN_NI   KC_I      // に
#define KN_NU   KC_1      // ぬ
#define KN_NE   KC_COMM   // ね = ','キー
#define KN_NO   KC_K      // の

/* は行 (ha, hi, fu, he, ho) */
#define KN_HA   KC_F      // は
#define KN_HI   KC_V      // ひ
#define KN_FU   KC_2      // ふ
/* へ = '^' 相当 → 通常は JIS 物理キーだが
 * US配列の場合は Shift + '6' だったり、環境に応じて変化します。 */
#define KN_HE   S(KC_6)   // へ(例: Shift + '6')
#define KN_HO   KC_MINS   // ほ = '-'キー

/* ま行 (ma, mi, mu, me, mo) */
#define KN_MA   KC_J      // ま
#define KN_MI   KC_N      // み
/* む(US配列だと ']' に相当)は環境次第で KC_RBRACKET や KC_INT系になる場合も */
#define KN_MU   KC_RBRACKET  // む(例)
#define KN_ME   KC_SLSH   // め = '/'キー
#define KN_MO   KC_M      // も

/* や行 (ya, yu, yo) */
#define KN_YA   KC_7      // や
#define KN_YU   KC_8      // ゆ
#define KN_YO   KC_9      // よ

/* ら行 (ra, ri, ru, re, ro) */
#define KN_RA   KC_O      // ら
#define KN_RI   KC_L      // り
#define KN_RU   KC_DOT    // る = '.'キー
#define KN_RE   KC_SCLN   // れ = ';'キー
/* ろ = '\'キー(物理刻印が\のJISキー)
 * US配列ベースなら KC_BSLS, 物理JISなら KC_INT1 ~ 5 の可能性も */
#define KN_RO   KC_BSLS   // ろ(例)

/* わ行 (wa, wo, n) */
#define KN_WA       KC_0      // わ
#define KN_WO       S(KC_0)   // を = Shift + '0'
#define KN_NN       KC_Y      // ん

/* === 追加: 濁点(゛), 半濁点(゜), 読点(、), 句点(。) === */

/* 濁点(゛) - 一般的には Shift + '2' キーに割り当てられがち */
#define KN_DAKUTEN     S(KC_2)   // ゛

/* 半濁点(゜) - 一般的には 濁点キーの隣(Shift + '3') など */
#define KN_HANDAKUTEN  S(KC_3)   // ゜

/* 読点(、) - 一般的には Shift + ',' */
#define KN_TOUTEN      S(KC_COMM) // 、

/* 句点(。) - 一般的には Shift + '.' */
#define KN_KUTEN       S(KC_DOT)  // 。
