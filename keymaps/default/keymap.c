/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"

const custom_shift_key_t custom_shift_keys[] = {
  {KC_DOT , KC_COLON}, 
  {KC_COMM, KC_SCLN}, 
};
uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

enum layers {
    _COLEMAK_DH = 0,
    _QWERTY,
    _DVORAK,
    _NAV,
    _SYM,
    _SYM2,
    _FUNCTION,
    _ADJUST,
    _NUM,
};

enum MyCombos {
  ST_LPAR,
  NE_RPAR,
  CD_LSQR,
  HH_RSQR,
  FP_LCUR,
  LU_RCUR,
  TG_LANG,
  MN_RANG,
  C_CapLock,
  COMBO_LENGTH,
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_custom_shift_keys(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)
#define DVORAK   DF(_DVORAK)

#define SYM      MO(_SYM)
#define SYM2     MO(_SYM2)
#define NAV      MO(_NAV)
#define FKEYS    MO(_FUNCTION)
#define ADJUST   MO(_ADJUST)
#define NUM      MO(_NUM)

#define LSHFT_T   MT(MOD_LSFT, KC_T)
#define RSHFT_N   MT(MOD_RSFT, KC_N)
#define LSHFT_F   MT(MOD_LSFT, KC_F)
#define RSHFT_J   MT(MOD_RSFT, KC_J)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_TAB  MT(MOD_LALT, KC_TAB)

#define SYM_ENT  LT(SYM2, KC_ENT)
#define NAV_DEL  LT(NAV, KC_DEL)
#define SYM_SPC  LT(SYM, KC_SPC)

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM LBracketcombo[] = {KC_S, LSHFT_T, COMBO_END};
const uint16_t PROGMEM RBracketcombo[] = {RSHFT_N, KC_E, COMBO_END};
const uint16_t PROGMEM LSquarecombo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM RSquarecombo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM LCurlycombo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM RCurlycombo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM LAngcombo[] = {KC_G, LSHFT_T, COMBO_END};
const uint16_t PROGMEM RAngcombo[] = {RSHFT_N, KC_M, COMBO_END};
const uint16_t PROGMEM CapLock[] = {LSHFT_T, RSHFT_N, COMBO_END};

combo_t key_combos[] = {
  [ST_LPAR] = COMBO(LBracketcombo, KC_LPRN),
  [NE_RPAR] = COMBO(RBracketcombo, KC_RPRN),
  [CD_LSQR] = COMBO(LSquarecombo, KC_LBRC),
  [HH_RSQR] = COMBO(RSquarecombo, KC_RBRC),
  [FP_LCUR] = COMBO(LCurlycombo, KC_LCBR),
  [LU_RCUR] = COMBO(RCurlycombo, KC_RCBR),
  [TG_LANG] = COMBO(LAngcombo, KC_LABK),
  [MN_RANG] = COMBO(RAngcombo, KC_RABK),
  [C_CapLock] = COMBO(CapLock, CW_TOGG),
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  -  _  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  '  "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   D  |   V  | PgDN |LLock |  |F-keys| PgUp |   K  |   H  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LCTL |Adjust| LAlt/| Space| Num/ |  | Sym/ | Bksp | NAV  | RGUI |  UP  |
 *                        |      |      | Tab  |      | Del  |  | ENT  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_MUTE , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN,  KC_MINS,
     QK_GESC , KC_A ,  KC_R   ,  KC_S  , LSHFT_T,   KC_G ,                                        KC_M, RSHFT_N,  KC_E ,   KC_I ,  KC_O , KC_QUOTE,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , KC_PGDN, QK_LOCK,     FKEYS  , KC_PGUP, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                 KC_LCTL, ADJUST, ALT_TAB, SYM_SPC, NAV_DEL,     SYM_ENT, KC_BSPC, TT(NUM), KC_RGUI, KC_UP
    ),
     
 /*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  -  _  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   S  |   D  |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  '  "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |   (  |      |  |F-keys|   )  |   N  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LCTL |Adjust| LAlt/| Space| Num/ |  | Sym/ | Bksp | NAV  | RGUI |  UP  |
 *                        |      |      | Tab  |      | Del  |  | ENT  |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
     KC_TAB  , KC_Q ,  KC_W   ,  KC_E  ,   KC_R ,   KC_T ,                                        KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P , KC_MINS,
     KC_ESC  , KC_A ,  KC_S   ,  KC_D  ,LSHFT_F ,   KC_G ,                                        KC_H,RSHFT_J ,  KC_K ,   KC_L ,KC_SCLN,KC_QUOTE,
     KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B , KC_LPRN,  QK_LOCK,     FKEYS  , KC_RPRN, KC_N,   KC_M ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                KC_LCTL,  ADJUST, ALT_TAB, KC_SPC, NAV_DEL,     SYM_ENT, KC_BSPC,  NAV, KC_RGUI, KC_UP
    ),

/*
 * Base Layer: Dvorak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Tab   | ' "  | , <  | . >  |   P  |   Y  |                              |   F  |   G  |   C  |   R  |   L  |  -  _  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Esc   |   A  |   O  |   E  |   U  |   I  |                              |   D  |   H  |   T  |   N  |   S  |  '  "  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | ; :  |   Q  |   J  |   K  |   X  |   (  |      |  |F-keys|   )  |   B  |   M  |   W  |   V  |   Z  | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | LCTL |Adjust| LAlt/| Space| Num/ |  | Sym/ | NAV/ | RAlt | RGUI |  UP  |
 *                        |      |      | Tab  |      | Del  |  | ENT  | Bksp |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_DVORAK] = LAYOUT(
     KC_TAB  ,KC_QUOTE,KC_COMM,  KC_DOT,   KC_P ,   KC_Y ,                                        KC_F,   KC_G ,  KC_C ,   KC_R ,  KC_L , KC_MINS,
     KC_ESC  , KC_A ,  KC_O   ,  KC_E  ,   KC_U ,   KC_I ,                                        KC_D,   KC_H ,  KC_T ,   KC_N ,  KC_S , KC_QUOTE,
     KC_LSFT ,KC_SCLN, KC_Q   ,  KC_J  ,   KC_K ,   KC_X , KC_LBRC,  QK_LOCK,     FKEYS  , KC_RBRC, KC_B,   KC_M ,  KC_W ,   KC_V ,  KC_Z , KC_RSFT,
                                KC_LCTL,  ADJUST, ALT_TAB, KC_SPC, NAV_DEL,     SYM_ENT, KC_BSPC, KC_RALT, KC_RGUI, KC_UP
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              | PgUp | Home |   ↑  | End  | VolUp| Delete |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  GUI | Ctrl |  Alt | Shift| ScLck|                              | PgDn |  ←   |   ↓  |   →  | VolDn| Insert |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      | Pause|M Prev|M Play|M Next|VolMut| PrtSc  |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
      _______, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, KC_SCRL,                                     KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    KC_MINUS, KC_AMPR, KC_PIPE, KC_TILDE,  KC_GRV, KC_PLUS,
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    KC_EQUAL, KC_EXLM,   KC_AT,  KC_HASH, KC_ASTR, KC_CIRC,
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, _______, _______, _______, _______, KC_PERC,  KC_DLR, KC_SCLN, KC_COLON, KC_BSLS, KC_SLSH,
                              _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym2 Layer: Numbers and symbolsFsh
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |   =    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |    ~   |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |   +    |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |    |   |   \  |  :   |  ;   |  -   |  [   |  {   |      |  |      |   }  |   ]  |  _   |  ,   |  .   |  /   |   ?    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM2] = LAYOUT(
      KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
     KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
     KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC, KC_LCBR, _______, _______, KC_RCBR, KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Function Layer: Function keys
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F9  | F10  | F11  | F12  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |                              |      | Shift| Ctrl |  Alt |  GUI |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_FUNCTION] = LAYOUT(
      _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |QWERTY|      |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |Dvorak|      |      |                              | TOG  | SAI  | HUI  | VAI  | MOD  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |Colmak|      |      |      |      |  |      |      |      | SAD  | HUD  | VAD  | RMOD |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, QWERTY , _______, _______,                                    _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, DVORAK , _______, _______,                                    RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD, _______,
      _______, _______, _______, COLEMAK, _______, _______,_______, _______, _______, _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Num Pad Layer
//  *
//  * ,-------------------------------------------.                              ,------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |   7  |   8  |   9  |   -  |   /   |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+-------|
//  * |        |      |      |      |      |      |                              |   $  |   4  |   5  |   6  |   +  |   *   |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+-------|
//  * |        |      |      |      |      |      |      |      |  |      |      |   %  |   1  |   2  |   3  | Enter|   ,   |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+---------------------'
//  *                        |      |      |      |      |      |  |   =  | Bksp |   0  |   0  |   .  |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
       [_NUM] = LAYOUT(
         KC_NO,   KC_NO, KC_7, KC_8,    KC_9, KC_COMM,                                      KC_NUM,KC_EQUAL,   KC_NO,   KC_NO,   KC_NO,  KC_NO,
         KC_NO,    KC_0, KC_4, KC_5,    KC_6,    KC_0,                                      KC_DLR, KC_PLUS, KC_ASTR,   KC_NO,   KC_NO,  KC_NO,
         KC_NO, KC_SLSH, KC_1, KC_2,    KC_3,  KC_DOT, _______, _______, _______, _______, KC_PERC, KC_MINS, KC_SLSH,   KC_NO,   KC_NO,  KC_NO,
                            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
      ),
};
