// Copyright (C) 2019, 2020  Keyboard.io, Inc
//               2021  Antoine R. Dumont (@ardumont) <antoine.romain.dumont@gmail.com>
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE,
    _FN0,
    _FN1,
    _MAGIC,
};

#define Z_SFT     SFT_T(KC_Z)
#define SLSH_SFT  SFT_T(KC_SLSH)
#define GRAVE_SFT SFT_T(KC_GRAVE)
#define RBRC_SFT  SFT_T(KC_RBRC)

#define BSPC_SFT  SFT_T(KC_BSPC)
#define SPACE_SFT SFT_T(KC_SPC)
#define ESC_GUI LGUI_T(KC_ESC)
#define TAB_CTL LCTL_T(KC_TAB)

#define FN0 MO(_FN0)
#define FN1 MO(_FN1)

#define A_MAGIC LT(_MAGIC, KC_A)
// #define EXLM_MAGIC LT(_MAGIC, KC_EXLM)

#define ESC_GUI LGUI_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Colemak */
    KC_Q,    KC_W,    KC_F,     KC_P,     KC_G,                         KC_J,     KC_L,    KC_U,    KC_Y,    KC_SCLN,
    A_MAGIC, KC_R,    KC_S,     KC_T,     KC_D,                         KC_H,     KC_N,    KC_E,    KC_I,    KC_O,
    Z_SFT,   KC_X,    KC_C,     KC_V,     KC_B,      KC_GRAVE, KC_BSLS, KC_K,     KC_M,    KC_COMM, KC_DOT,  SLSH_SFT,
    KC_LCTRL,KC_TAB,  KC_LALT,  ESC_GUI,  SPACE_SFT, FN0,      FN0,     BSPC_SFT, KC_LALT, KC_MINS, KC_QUOT, KC_ENT
  ),
  [_FN0] = LAYOUT( /* [> FN0 <] */
    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,     KC_7,    KC_8,     KC_9,    KC_0    ,
    KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC,  KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN ,
    GRAVE_SFT, KC_TILD, _______, _______, _______, _______,  _______,  KC_PLUS,  KC_MINS,  _______, KC_LBRC, RBRC_SFT,
    _______,   _______, _______, KC_LGUI, _______, FN1,      FN1,      _______,  _______,  KC_EQL,  KC_LCBR, KC_RCBR
  ),
  [_FN1] = LAYOUT( /* [> FN1 <] */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 ,
    _______, _______, _______, _______, _______,                   KC_F11, KC_F12,   _______, _______, _______ ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  
  ),
  [_MAGIC] = LAYOUT( /* [> MAGIC <] */
    _______,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   _______, _______, _______, _______, _______  ,
    _______,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   _______, _______, _______, _______, _______  ,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  ,
    _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;

bool substitute_keycode(uint16_t keycode, keyrecord_t *record, uint8_t mod_state, uint16_t substitute_keycode) {
    /* Substitute keycode if condition matches */
    // Initialize a boolean variable that keeps track
    // of the delete key status: registered or not?
    static bool key_registered;
    // ctrl activated?
    if ((mod_state & MOD_BIT(KC_LCTRL)) == MOD_BIT(KC_LCTRL)) {
        if (record->event.pressed) {
            // No need to register KC_LCTRL because it's already active.
            unregister_code(KC_LCTRL);
            // Send substitute code
            register_code(substitute_keycode);
            // Update the boolean variable to reflect the status of the register
            key_registered = true;
            // Reapplying modifier state so that the held shift key(s)
            // still work even after having tapped the Backspace/Delete key.
            set_mods(mod_state);
            // Do not let QMK process the keycode further
            return false;
        } else {
            // In case substitude_keycode is still even after release of the key
            if (key_registered) {
                unregister_code(substitute_keycode);
                key_registered = false;
                // Do not let QMK process the keycode further
                return false;
            }
        }
    } else { // ctrl got released
        // In case substitude_keycode is still sent after release of the ctrl key
        if (key_registered) {
            unregister_code(substitute_keycode);
            key_registered = false;
        }
    }
    // Else, let QMK process the keycode as usual
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif

    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {
    case ESC_GUI:
        if (record->tap.count && record->event.pressed) {
            if (record->tap.count >= 2) {
                tap_code16(KC_LGUI); 
            } else {
                tap_code16(KC_ESC);    
            }

            return false;
        }
        break;
    case KC_I:
        return substitute_keycode(keycode, record, mod_state, KC_TAB);
    case KC_M:
        return substitute_keycode(keycode, record, mod_state, KC_ENTER);
    case KC_H:
        return substitute_keycode(keycode, record, mod_state, KC_BSPC);
    case KC_D:
        return substitute_keycode(keycode, record, mod_state, KC_DEL);
    }
    return true;
};
