#include QMK_KEYBOARD_H 
#define _QWERTY 0
#define _BEAKL15 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   BEAKL15,
   LT_DAT
};

#define LOWER  LT(_LOWER, KC_ENT)
#define RAISE  LT(_RAISE, KC_SPC)
#define ADJUST LT(_ADJUST, KC_ESC)
#define SH_ESC MT(MOD_LSFT, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSPC,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, BL_TOGG,             RGB_TOG, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                    KC_LGUI, RAISE, LOWER,                     KC_ESC,   KC_RCTL, KC_RALT
  ),

 [_BEAKL15] = LAYOUT(
     KC_GRV,  KC_4,    KC_0,    KC_1,    KC_2,    KC_3,                               KC_7,    KC_6,    KC_5,    KC_9,    KC_8,    KC_BSLS,    
     KC_TAB,  KC_Q,    KC_H,    KC_O,    KC_U,    KC_X,                               KC_G,    KC_C,    KC_R,    KC_F,    KC_Z,    KC_QUOT,
     SH_ESC,  KC_Y,    KC_I,    KC_E,    KC_A,    LT_DAT,                              KC_D,    KC_S,    KC_T,    KC_N,    KC_B,    KC_BSPC,   
     KC_LSFT, KC_J,    KC_BSLS, KC_COMM, KC_K,    KC_QUOT, BL_TOGG,          RGB_TOG, KC_W,    KC_M,    KC_L,    KC_P,    KC_V,    KC_RSFT,
                                    KC_LCTL, RAISE, LOWER,                     SH_ESC,   KC_LALT, KC_RALT
  ),

  [_LOWER] = LAYOUT(
     RESET,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PGUP,
     KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGDN,
     KC_DEL,  _______, KC_LEFT, KC_RGHT, KC_UP,   KC_LBRC,                            RGB_HUD, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_HOME,
     BL_STEP, BEAKL15, QWERTY,  _______, KC_DOWN, KC_LCBR, KC_LPRN,          KC_RPRN, KC_RCBR, KC_P1,   KC_P2,   KC_P3,   KC_MINS, KC_END,
                                    _______, _______, _______,                   _______, _______, _______
  ),

  [_RAISE] = LAYOUT(
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     RGB_TOG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_UP,   KC_LPRN, KC_RPRN, _______,
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS,                            KC_EQL,  KC_LEFT, KC_DOWN, KC_RGHT, RGB_VAD, _______,
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_LEFT, KC_DOWN, KC_RGHT, RGB_HUD, _______,
                                    _______, _______, _______,                   _______, _______, _______
  ),

  [_ADJUST] = LAYOUT(
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
     RGB_TOG, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_UP,   KC_LPRN, KC_RPRN, _______,
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS,                            KC_EQL,  KC_LEFT, KC_DOWN, KC_RGHT, RGB_VAD, _______,
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_LPRN,          _______, KC_PLUS, KC_LEFT, KC_DOWN, KC_RGHT, RGB_HUD, _______,
                                    _______, _______, _______,                   _______, _______, _______
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case BEAKL15:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_BEAKL15);
      }
      return false;
    case LT_DAT:
      if (record->event.pressed) { 
        if (get_mods() & MOD_BIT(KC_LSHIFT)){
           register_code16(KC_AT);
        } else {
           register_code(KC_DOT);
        }
      }
      else {
           unregister_code16(KC_AT);
           unregister_code(KC_DOT);
      }
      return false;
    default:
      return true;
  }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(LCA(KC_UP));
        } else {
            tap_code16(LCA(KC_DOWN));
        }
    }
    else if (index == 1) {
        if (clockwise) {
            send_string(":bn"SS_TAP(X_ENTER));
        } else {
            send_string(":bp"SS_TAP(X_ENTER));
        }
    }
}

