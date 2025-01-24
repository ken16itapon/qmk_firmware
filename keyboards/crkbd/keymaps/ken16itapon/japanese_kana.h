/*
 * かな入力用キー定義サンプル（小文字/大文字区別版）
 * - アルファベットキーは原則「小文字」を使う
 * - Shift が必要な文字（:, ^, [, など）は記号としてそのまま表記
 * - 連続入力が必要な濁音・拗音などは文字列を連結
 *
 * 例)
 *   - KN_MA "j"        // ま
 *   - KN_GA "t["       // が （「か」=t + 「濁点」=[）
 *   - KN_PYA "v#&"     // ぴゃ（「ぴ」=v# + 「ゃ」=&）
 */

/* --- あ行 (あ/い/う/え/お) --- */
#define KN_A    "3"   // あ
#define KN_I    "e"   // い
#define KN_U    "4"   // う
#define KN_E    "5"   // え
#define KN_O    "6"   // お

/* --- か行 (か/き/く/け/こ) --- */
#define KN_KA   "t"   // か
#define KN_KI   "g"   // き
#define KN_KU   "h"   // く
/* 「け」= Shift + ';' → ':' (記号なのでコロンそのまま記述) */
#define KN_KE   ":"   // け
#define KN_KO   "b"   // こ

/* --- さ行 (さ/し/す/せ/そ) --- */
#define KN_SA   "x"   // さ
#define KN_SHI  "d"   // し
#define KN_SU   "r"   // す
#define KN_SE   "p"   // せ
#define KN_SO   "c"   // そ

/* --- た行 (た/ち/つ/て/と) --- */
#define KN_TA   "q"   // た
#define KN_CHI  "a"   // ち
#define KN_TSU  "z"   // つ
#define KN_TE   "w"   // て
#define KN_TO   "s"   // と

/* --- な行 (な/に/ぬ/ね/の) --- */
#define KN_NA   "u"   // な
#define KN_NI   "i"   // に
#define KN_NU   "1"   // ぬ
#define KN_NE   ","   // ね
#define KN_NO   "k"   // の

/* --- は行 (は/ひ/ふ/へ/ほ) --- */
#define KN_HA   "f"   // は
#define KN_HI   "v"   // ひ
#define KN_FU   "2"   // ふ
/*
 * 「へ」= SHIFT + '6' → '^' (US配列例)
 * 物理JISなら別キーの場合も
 */
#define KN_HE   "^"   // へ
#define KN_HO   "-"   // ほ

/* --- ま行 (ま/み/む/め/も) --- */
/* ※ ユーザー要望: KN_MA は "j" (小文字) */
#define KN_MA   "j"   // ま
#define KN_MI   "n"   // み
/* 「む」は US配列で ']' (シフトなし) を想定 */
#define KN_MU   "]"   // む
#define KN_ME   "/"   // め
#define KN_MO   "m"   // も

/* --- や行 (や/ゆ/よ) --- */
#define KN_YA   "7"   // や
#define KN_YU   "8"   // ゆ
#define KN_YO   "9"   // よ

/* --- ら行 (ら/り/る/れ/ろ) --- */
#define KN_RA   "o"   // ら
#define KN_RI   "l"   // り
#define KN_RU   "."   // る
#define KN_RE   ";"   // れ
/*
 * 「ろ」= unshifted '\' (US配列の場合)
 *  JIS物理だと \ キー(別スキャンコード)になることあり
 */
#define KN_RO   "\\"  // ろ

/* --- わ行 (わ/を/ん) --- */
#define KN_WA   "0"   // わ
/* 「を」= Shift+0 → ')' の例 */
#define KN_WO   ")"   // を
#define KN_NN   "y"   // ん

/* === 濁点・半濁点 (単体) ===
 *   - 例: Shift+2 = "["、Shift+3 = "]" と想定
 */
#define KN_DAKUTEN    "["  // ゛
#define KN_HANDAKUTEN "]"  // ゜

/* --- が行 (が/ぎ/ぐ/げ/ご) ---
 *   「が」= "か" + 濁点 = "t[" 等
 */
#define KN_GA   "t["  // が
#define KN_GI   "g["  // ぎ
#define KN_GU   "h["  // ぐ
#define KN_GE   ":["  // げ
#define KN_GO   "b["  // ご

/* --- ざ行 (例: ざ, じ, ず, ぜ, ぞ) --- */
#define KN_ZA   "x["  // ざ
#define KN_JI   "d["  // じ
#define KN_ZU   "r["  // ず
#define KN_ZE   "p["  // ぜ
#define KN_ZO   "c["  // ぞ

/* --- だ行 (例: だ, ぢ, づ, で, ど) --- */
#define KN_DA   "q["  // だ
#define KN_DI   "a["  // ぢ
#define KN_DU   "z["  // づ
#define KN_DE   "w["  // で
#define KN_DO   "s["  // ど

/* --- ば行 (ば/び/ぶ/べ/ぼ) --- */
#define KN_BA   "f["  // ば
#define KN_BI   "v["  // び
#define KN_BU   "2["  // ぶ
#define KN_BE   "^["  // べ
#define KN_BO   "-["  // ぼ

/* --- ぱ行 (ぱ/ぴ/ぷ/ぺ/ぽ) ---
 *   「ぱ」= "は" + 半濁点 = "f]"
 */
#define KN_PA   "f]"  // ぱ
#define KN_PI   "v]"  // ぴ
#define KN_PU   "2]"  // ぷ
#define KN_PE   "^]"  // ぺ
#define KN_PO   "-]"  // ぽ

/* --- 小文字/拗音 (ぁ/ぃ/ぅ/ぇ/ぉ/ゃ/ゅ/ょ/ゎ/っ 等) ---
 *   どのキーに割り当てられているかは環境により違うので一例
 *   （US配列で Shift+3 = '#', Shift+7 = '&', など）
 */

/* 例: ぁ/ぃ/ぅ/ぇ/ぉ */
#define KN_XA   "#"  // ぁ (例: Shift+3)
#define KN_XI   "$"  // ぃ (Shift+4)
#define KN_XU   "%"  // ぅ (Shift+5)
#define KN_XE   "^"  // ぇ (Shift+6) → へ と被る可能性有
#define KN_XO   "&"  // ぉ (Shift+7)

/* 例: ゃ/ゅ/ょ (小さいやゆよ) */
#define KN_XYA  "&"  // ゃ (Shift+7) → 同じく ぉ と衝突例 (環境要確認)
#define KN_XYU  "*"  // ゅ (Shift+8)
#define KN_XYO  "("  // ょ (Shift+9)

/* 例: ゎ */
#define KN_XWA  "_"  // ゎ (Shift + '-' → '_' など, 一例)

/* 例: っ */
#define KN_XTU  "Z"  // っ (Shift+z → 'Z') など (衝突注意)

/* --- 読点/句点など --- */
/* 「、」= Shift + ',' → '<' (US配列例) */
#define KN_TOUTEN "<" // 、
/* 「。」= Shift + '.' → '>' */
#define KN_KUTEN  ">" // 。
/* 「・」などを割り当てる場合は '/' or '?' など適宜 */

/* --- 拗音の複合例: ぴゃ/ぴゅ/ぴょ ---
 *  「ぴ」= "v#"  +  「ゃ」= "&"  → "v#&"
 */
#define KN_PYA   "v#&"  // ぴゃ
#define KN_PYU   "v#*"  // ぴゅ
#define KN_PYO   "v#("  // ぴょ

/* ========== ふぁ/ふぃ/ふぇ/ふぉ ========== */
/* ふ = "2",  ぁ = "#",  ぃ = "$",  ぇ = "^",  ぉ = "&" */
#define KN_FA   "2#"  // ふぁ
#define KN_FI   "2$"  // ふぃ
#define KN_FE   "2^"  // ふぇ
#define KN_FO   "2&"  // ふぉ

/* ========== うぃ/うぇ/うぉ ========== */
/* う = "4",  ぃ = "$",  ぇ = "^",  ぉ = "&" */
#define KN_WI   "4$"  // うぃ
#define KN_WE   "4^"  // うぇ
#define KN_UXO  "4&"  // うぉ ( "uxo" と表記するローマ字流儀があるため )

/* ========== ヴ (vu) ========== */
/* ヴ = う(4) + 濁点([) → "4[" */
#define KN_VU   "4["  // ヴ

/* ========== てぃ/でぃ ========== */
/* て = "w",  で = "w[",  ぃ = "$" */
#define KN_TELI "w$"   // てぃ
#define KN_DELI "w[$"  // でぃ

/* ========== しぇ/じぇ/ちぇ ========== */
/* し = "d",  じ = "d[",  ち = "a",  ぇ = "^" */
#define KN_SYE  "d^"    // しぇ
#define KN_JE   "d[^"   // じぇ
#define KN_TILE "a^"    // ちぇ (「tile」というローマ字に対応)

/* ========== ひゅ/しゅ/しょ など ========== */
/* ひ = "v",  し = "d",  ゅ = "*",  ょ = "(" */
#define KN_HYU  "v*"  // ひゅ
#define KN_SYU  "d*"  // しゅ
#define KN_SYO  "d("  // しょ

/* ========== きゅ/ちゅ/ひょ/きょ/ちょ など ========== */
/* き = "g",  ち = "a" */
#define KN_KYU  "g*"  // きゅ
#define KN_TYU  "a*"  // ちゅ
#define KN_HYO  "v("  // ひょ
#define KN_KYO  "g("  // きょ
#define KN_TYO  "a("  // ちょ

/* ========== ひゃ/しゃ/くゃ(?) など ========== */
/* ひ = "v",  し = "d",  く = "h",  ゃ = "&" */
#define KN_HYA  "v&"  // ひゃ
#define KN_SYA  "d&"  // しゃ
#define KN_KYA  "g&"  // きゃ
#define KN_TYA  "a&"  // ちゃ

/* ========== りゅ/じゅ/じょ/ぎゅ/りょ など ========== */
/* り = "l",  じ = "d[",  ぎ = "g[" */
#define KN_RYU  "l*"   // りゅ
#define KN_ZYU  "d[*"  // じゅ
#define KN_ZYO  "d[("  // じょ
#define KN_GYU  "g[*"  // ぎゅ
#define KN_RYO  "l("   // りょ
#define KN_GYO  "g[("  // ぎょ

/* ========== にょ/りゃ/じゃ/ぎゃ/にゃ など ========== */
/* に = "i",  り = "l",  じ = "d[",  ぎ = "g[",  み = "n",  び = "v[" */
#define KN_NYO  "i("   // にょ
#define KN_RYA  "l&"   // りゃ
#define KN_ZYA  "d[&"  // じゃ
#define KN_GYA  "g[&"  // ぎゃ
#define KN_NYA  "i&"   // にゃ

/* ========== みゅ/びゅ/びょ/みょ/みゃ/びゃ ========== */
#define KN_MYU  "n*"   // みゅ
#define KN_BYU  "v[*"  // びゅ
#define KN_BYO  "v[("  // びょ
#define KN_MYO  "n("   // みょ
#define KN_MYA  "n&"   // みゃ
#define KN_BYA  "v[&"  // びゃ
