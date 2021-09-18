#include "kb.h"
// #include "print.h"

bool onMac = false;
bool isModPressed = false;

uint16_t cmdOverrideKcs[] = {
	KC_A,
	KC_B,
	KC_C,
	// KC_D,
	// KC_E,
	KC_F,
	KC_G,
	KC_H,
	KC_I,
	KC_J,
	KC_K,
	KC_L,
	KC_M,
	KC_N,
	KC_O,
	KC_P,
	KC_Q,
	KC_R,
	KC_S,
	KC_T,
	KC_U,
	KC_V,
	KC_W,
	KC_X,
	KC_Y,
	KC_Z,
	KC_GRV,
	KC_COMM,
	KC_DOT,
	KC_SLSH
};

const int cmdOverrideKcsSize = sizeof(cmdOverrideKcs) / sizeof(cmdOverrideKcs[0]);

enum planck66_layers {
	_QWERTY,
	_COLEMAK,
	_FN,
	_FN2,
	_QMK
};

enum planck66_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
	MAC_TGL,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = KEYMAP(
			KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_HOME, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  KC_BSPC,
			KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, KC_DELETE,  
			KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
			KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   MO(_FN), 
			KC_LCTL, KC_LALT, KC_LGUI,          KC_SPC,           KC_END,  KC_MINS, KC_EQL,  MO(_FN2),         KC_LEFT, KC_DOWN, KC_RGHT
	),
	[_COLEMAK] = KEYMAP(
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    _______, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______, _______, 
			KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,             KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    _______, _______,
			_______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______, _______,
			_______, _______, _______,          _______,          _______, _______, _______, _______,          _______, _______, _______
	),
	[_FN] = KEYMAP(
			_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______,
			_______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
			_______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______,          _______,          _______, KC_F11,  KC_F12,  _______,          _______, _______, _______
	),
	[_FN2] = KEYMAP(
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
			_______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______,          _______,          _______, _______, _______, _______,          _______, _______, _______
	),
	[_QMK] = KEYMAP(
			MAC_TGL, QWERTY,  COLEMAK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
			_______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
			_______, _______, _______,          _______,          _______, _______, _______, _______,          _______, _______, _______
	)
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _FN, _FN2, _QMK);
}

void convert_to_modded_code(uint16_t mod, uint16_t kc, keyrecord_t *record) {
	if (record->event.pressed) {
		register_code(mod);
		_delay_ms(1);
		register_code(kc);
	} else {
		unregister_code(mod);
		unregister_code(kc);
	}
}

// void keyboard_post_init_user(void) {
//   debug_enable=true;
// }

bool qmk_mode_set(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	 	case QWERTY:
      if (record->event.pressed) {
				set_single_persistent_default_layer(_QWERTY);
      }
      return false;
		case COLEMAK:
      if (record->event.pressed) {
				set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
		case MAC_TGL:
			if (record->event.pressed) {
				onMac = !onMac;
      }
			return false;
 	}

	return true;
}

bool osx_override(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case KC_HOME:  // make the home behave the same on OSX
			convert_to_modded_code(KC_LGUI, KC_LEFT, record);
			return false;
			break;
		case KC_END:  // make the end behave the same on OSX
			convert_to_modded_code(KC_LGUI, KC_RIGHT, record);
			return false;
			break;
 	}

	return true;
}

bool is_include(uint16_t value, uint16_t list[], const int size) {
	int i = 0;
	while (i < size) {
		const bool isEqual = list[i] == value;
		// uprintf("is_include, i %d, keycode %d, value %d, equal %s \n", i, list[i], value, isEqual ? "true" : "false");
		i++;
		if (isEqual) return true;
	}
	return false;
}

// Most used shortcut, e.g. copy / paste / etc.
bool command_override(uint16_t keycode, keyrecord_t *record) {
	static uint16_t lgui_timer;

	if (keycode == KC_LGUI) {
		if (record->event.pressed) {
			lgui_timer = timer_read();
			isModPressed = true;
     } else {
			isModPressed = false;
			if (timer_elapsed(lgui_timer) < get_tapping_term(keycode, record)) {  
					tap_code(keycode);
			}
		 }
		 return false;
	}

	if (!isModPressed) return true;

	if (is_include(keycode, cmdOverrideKcs, cmdOverrideKcsSize)) {
		// uprintf("Command Override");
		convert_to_modded_code(KC_LCTL, keycode, record);
		return false;
	} else {
		convert_to_modded_code(KC_LGUI, keycode, record);
		return false;
	}

	return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!qmk_mode_set(keycode, record)) return false;
	if (onMac && !osx_override(keycode, record)) return false;
	if (!onMac && !command_override(keycode, record)) return false;
	return true;
}
