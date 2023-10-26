/* Copyright 2023 Cyboard LLC (@Cyboard-DigitalTailor)
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

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

enum custom_keycodes {
    EM = SAFE_RANGE,
    PW,
};

#include "features/achordion.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_achordion(keycode, record)) { return false; }
  // Your macros ...
  switch (keycode) {
    case EM:
        if (record->event.pressed) {
            // when keycode EM is pressed
            SEND_STRING("blubek@uillinois.edu");
        } else {
            // when keycode EM is released
        }
        break;
    case PW:
        if (record->event.pressed) {
            // when keycode QMKURL is pressed
            SEND_STRING("050165QwArZx");
        } else {
            // when keycode PW is released
        }
        break;
    case LT(0,EM): //sends colon on tap and semicolon on hold
    if (record->tap.count && record->event.pressed) {
        return true; // Return true for normal processing of tap keycode
        break;
    } else if (record->event.pressed) {
        tap_code16(PW); // Intercept hold function to send SEMICOLON    
        return false;
    }
return true; // this allows for normal processing of key release!
}

void matrix_scan_user(void) {
  achordion_task();
}

const key_override_t EM_key_override = ko_make_basic(MOD_MASK_SHIFT, EM, PW);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&EM_key_override,
	NULL // Null terminate the array of overrides!
};

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
#define LALT_S    MT(MOD_LALT, KC_S)
#define RALT_E    MT(MOD_RALT, KC_E)
#define LCTL_R    MT(MOD_LCTL, KC_R)
#define RCTL_I    MT(MOD_RCTL, KC_I)
#define LGUI_A    MT(MOD_LGUI, KC_A)
#define RGUI_O    MT(MOD_RGUI, KC_O)

#define LSHFT_F   MT(MOD_LSFT, KC_F)
#define RSHFT_J   MT(MOD_RSFT, KC_J)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_TAB  MT(MOD_LALT, KC_TAB)
#define EMPW     MT(MOD_LALT, KC_TAB)

#define SYM_ENT  LT(SYM2, KC_ENT)
#define NAV_DEL  LT(NAV, KC_DEL)
#define SYM_SPC  LT(SYM, KC_SPC)

#define CUT   LCTL(KC_X)
#define COPY  LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define UNDO  LCTL(KC_Z)
#define REDO  LCTL(KC_Y)
#define FIND  LCTL(KC_F)

const key_override_t space_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPCE, KC_MINS);
const key_override_t comma_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t dot_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLON);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &space_key_override,
    &comma_key_override,
    &dot_key_override,
    NULL // Null terminate the array of overrides!
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM LBracketcombo[] = {LALT_S, LSHFT_T, COMBO_END};
const uint16_t PROGMEM RBracketcombo[] = {RSHFT_N, RALT_E, COMBO_END};
const uint16_t PROGMEM LSquarecombo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM RSquarecombo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM LCurlycombo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM RCurlycombo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM LAngcombo[] = {KC_G, LSHFT_T, COMBO_END};
const uint16_t PROGMEM RAngcombo[] = {RSHFT_N, KC_M, COMBO_END};
const uint16_t PROGMEM CapLock[] = {LSHFT_T, EM, COMBO_END};

combo_t key_combos[] = {
  [ST_LPAR] = COMBO(LBracketcombo, KC_LPRN),
  [NE_RPAR] = COMBO(RBracketcombo, KC_RPRN),
  [CD_LSQR] = COMBO(LSquarecombo, KC_LBRC),
  [HH_RSQR] = COMBO(RSquarecombo, KC_RBRC),
  [FP_LCUR] = COMBO(LCurlycombo, KC_LCBR),
  [LU_RCUR] = COMBO(RCurlycombo, KC_RCBR),
  [TG_LANG] = COMBO(LAngcombo, KC_LABK),
  [MN_RANG] = COMBO(RAngcombo, KC_RABK),
  [C_CapLock] = COMBO(CapLock, PW),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK_DH] = LAYOUT_manuform_let(
           UNDO,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                             KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, LALT(KC_TAB),
           REDO,  LGUI_A,  LCTL_R,  LALT_S, LSHFT_T,    KC_G,                             KC_M, RSHFT_N,  RALT_E,  RCTL_I,  RGUI_O, KC_QUOT,
            CUT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                             KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,      EM,
          KC_UP, KC_DOWN,    COPY,   PASTE,  KC_TAB, SYM_SPC,  KC_DEL,        SYM_ENT, KC_BSPC, TT(NUM),    FIND, KC_RGUI, KC_LEFT,KC_RIGHT,
                                            KC_ESC,  KC_CAPS, KC_UNDS,        KC_TILD, KC_PGDN, KC_PGUP
    ),

    [_QWERTY] = LAYOUT_manuform_let(
        _______,   KC_Q ,  KC_W  ,  KC_E  ,   KC_R ,   KC_T ,                             KC_Y,   KC_U ,   KC_I ,   KC_O ,   KC_P , KC_MINS,
        _______,   KC_A ,  KC_S  ,  KC_D  ,LSHFT_F ,   KC_G ,                             KC_H, RSHFT_J,   KC_K ,   KC_L , KC_SCLN,KC_QUOTE,
        _______,   KC_Z ,  KC_X  ,  KC_C  ,   KC_V ,   KC_B ,                             KC_N,   KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_DVORAK] = LAYOUT_manuform_let(
        _______, KC_QUOTE,KC_COMM,  KC_DOT,   KC_P ,   KC_Y ,                             KC_F,   KC_G ,   KC_C ,   KC_R ,   KC_L , KC_MINS,
        _______, KC_A ,   KC_O   ,  KC_E  ,   KC_U ,   KC_I ,                             KC_D,   KC_H ,   KC_T ,   KC_N ,   KC_S ,KC_QUOTE,
        _______, KC_SCLN, KC_Q   ,  KC_J  ,   KC_K ,   KC_X ,                             KC_B,   KC_M ,   KC_W ,   KC_V ,   KC_Z , KC_RSFT,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_NAV] = LAYOUT_manuform_let(
        _______, _______, _______, _______, _______, _______,                          KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_VOLU,  KC_DEL,
        _______, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, KC_SCRL,                          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,  KC_INS,
        _______, _______, _______, _______, _______, _______,                         KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_SYM] = LAYOUT_manuform_let(
        _______, _______, _______, _______, _______, _______,                         KC_MINUS, KC_AMPR, KC_PIPE,KC_TILDE,  KC_GRV, KC_PLUS,
        _______, _______, _______, _______, _______, _______,                         KC_EQUAL, KC_EXLM,   KC_AT, KC_HASH, KC_ASTR, KC_CIRC,
        _______, _______, _______, _______, _______, _______,                          KC_PERC,  KC_DLR, KC_SCLN,KC_COLON, KC_BSLS, KC_SLSH,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_SYM2] = LAYOUT_manuform_let(
        KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                            KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL ,
        KC_TILD, KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT_manuform_let(
        _______,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12, _______,                          _______, _______, _______, _______, _______, _______,
        _______,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 , _______,                          _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
        _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 , _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_ADJUST] = LAYOUT_manuform_let(
        _______, _______, _______, QWERTY , _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, DVORAK , _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, COLEMAK, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),

    [_NUM] = LAYOUT_manuform_let(
        _______, _______,   KC_7 ,   KC_8 ,   KC_9 , KC_COMM,                          _______, KC_EQL , _______, _______, _______, _______,
        _______,    KC_0,   KC_4 ,   KC_5 ,   KC_6 ,    KC_0,                           KC_DLR, KC_PLUS, KC_ASTR, _______, _______, _______,
        _______, KC_SLSH,   KC_1 ,   KC_2 ,   KC_3 ,  KC_DOT,                          KC_PERC, KC_MINS, KC_SLSH, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
                                            _______, _______, _______,        _______, _______, _______
    ),
};
