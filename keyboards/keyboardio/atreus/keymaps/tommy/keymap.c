// Copyright (C) 2019, 2020  Keyboard.io, Inc
//               2021  Antoine R. Dumont (@ardumont) <antoine.romain.dumont@gmail.com>
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

// #define TAPPING_TERM 200

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE,
    _FN0,
    _FN1,
    _MAGIC,
    _NUMPAD,
};

#define SPACE_SFT SFT_T(KC_SPC)

#define A_MAGIC LT(_MAGIC, KC_A)
#define D_NUMPAD LT(_NUMPAD, KC_D)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Colemak */
    KC_Q,     KC_W,    KC_F,     KC_P,     KC_G,                         KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,
    A_MAGIC,  KC_R,    KC_S,     KC_T,     D_NUMPAD,                     KC_H,     KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,      XXXXXXX,  XXXXXXX, KC_K,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_LCTL,  KC_LSFT, KC_LALT,  KC_LGUI,  SPACE_SFT, XXXXXXX,  XXXXXXX, KC_BSPC,  KC_TAB,  KC_ENT,  KC_QUOT, OSL(_FN0)
  ),
  [_FN0] = LAYOUT( /* [> FN0 <] */
    S(KC_1),     S(KC_2),  S(KC_3), S(KC_4), S(KC_5),                     S(KC_6),   S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0),
    S(KC_GRV),   KC_GRV,   XXXXXXX, XXXXXXX, XXXXXXX,                     S(KC_EQL), KC_MINS,    S(KC_BSLS), KC_LBRC,    KC_RBRC,
    XXXXXXX,     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  KC_EQL,    S(KC_MINS), KC_BSLS,    S(KC_LBRC), S(KC_RBRC),
    KC_ESC,      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    OSL(_FN1)
  ),
  [_FN1] = LAYOUT( /* [> FN1 <] */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_F11, KC_F12,   XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  
  ),
  [_MAGIC] = LAYOUT( /* [> MAGIC <] */
    XXXXXXX,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_NUMPAD] = LAYOUT( /* [> MAGIC <] */
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P7,    KC_P8,    KC_P9,   XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_P4,    KC_P5,    KC_P6,   XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,    KC_P2,    KC_P3,   XXXXXXX,
    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,    KC_P0,    KC_DOT,  XXXXXXX
  ),
};
