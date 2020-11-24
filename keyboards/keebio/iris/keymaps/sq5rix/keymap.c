#include QMK_KEYBOARD_H 
#define _QWERTY 0
#define _BEAKL15 1
#define _LOWER 2
#define _RAISE 3

enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   BEAKL15,
   LT_DAT,
   LT_COM,
   LT_QUOT
};

#define LOWER  LT(_LOWER, KC_ENT)
#define RAISE  LT(_RAISE, KC_SPC)
#define SH_ESC MT(MOD_LSFT, KC_ESC)
#define SH_CWD MT(MOD_LALT, KC_SCLN)
#define SH_LTAB MT(MOD_LALT, KC_TAB)
#define SH_RTAB MT(MOD_RALT, KC_TAB)
#define SH_RABS MT(MOD_RALT, KC_BSPC)
#define SH_UND MT(MOD_LCTL, KC_MINUS)
#define SH_LEAD MT(MOD_LCTL, KC_WH_D)
#define SH_DEL LALT(LCTL(KC_DEL))

bool sh_key(keyrecord_t *record, uint8_t sk, uint8_t nk);
bool sh_key8(keyrecord_t *record, uint8_t sk, uint8_t nk);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
     SH_LTAB, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LGUI,
     SH_UND,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, SH_RABS,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, RGB_TOG,              BL_TOGG, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                    SH_LEAD, LOWER, RAISE,                        SH_ESC,  SH_RTAB,  SH_CWD 
  ),

 [_BEAKL15] = LAYOUT(
     _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
     _______,  KC_Q,    KC_H,    KC_O,    KC_U,    KC_X,                               KC_G,    KC_C,    KC_R,    KC_F,    KC_V,    _______, 
     _______,  KC_Y,    KC_I,    KC_E,    KC_A,    LT_DAT,                             KC_D,    KC_S,    KC_T,    KC_N,    KC_W,    _______, 
     _______,  KC_J,    KC_SLSH, LT_COM,  KC_K,    LT_QUOT, _______,          _______, KC_B,    KC_M,    KC_L,    KC_P,    KC_Z,    _______, 
                                    _______, _______, _______,                   _______, _______, _______
  ),

  [_LOWER] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______, 
     _______, _______, KC_LT,   KC_DLR,  KC_GT,   KC_EXLM,                             _______, KC_LBRC, KC_UNDS, KC_RBRC, KC_EXLM, _______,
     _______, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH,                             KC_PERC, KC_LCBR, KC_EQL,  KC_RCBR, KC_PIPE, _______,
     _______, KC_GRV,  KC_COLN, KC_ASTR, KC_PLUS, KC_SCLN,  _______,          _______, _______, KC_AMPR, KC_CIRC, KC_TILD, KC_SCLN, _______,
                                    _______, _______, _______,                    _______, _______, _______

  ),

  [_RAISE] = LAYOUT(
     RESET,    KC_VOLD, KC_VOLU, KC_MUTE, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,    KC_PSCREEN, _______, _______, _______, RGB_VAI, _______, 
     BEAKL15,  KC_PLUS, KC_6,    KC_5,    KC_4,    KC_PERC,                        KC_CIRC, KC_PGUP, KC_UP,   KC_PGDN, _______, RGB_SPI, 
     QWERTY,   KC_3,    KC_2,    KC_1,    KC_0,    KC_EQL,                         KC_EQL,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
     KC_MUTE,  KC_MSTP, KC_9,    KC_8,    KC_7,    KC_MINS,  _______,     _______, KC_PLUS, KC_HOME, KC_COLN, KC_END,  _______, RGB_MOD, 
                                    _______, _______, _______,                    _______, _______, _______
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
      return sh_key8(record, KC_2, KC_DOT);
    case LT_COM:
      return sh_key8(record, KC_1, KC_COMM);
    case LT_QUOT:
      return sh_key(record, KC_GRV, KC_QUOT);
    default:
      return true;
  }
}

bool sh_key(keyrecord_t *record, uint8_t sk, uint8_t nk){
      if (record->event.pressed) { 
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
           unregister_code(KC_LSFT);
           unregister_code(KC_RSFT);
           register_code(sk);
        } else {
           register_code(nk);
        }
      }
      else {
           unregister_code16(sk);
           unregister_code(nk);
      }
      return false;
}

bool sh_key8(keyrecord_t *record, uint8_t sk, uint8_t nk){
      if (record->event.pressed) { 
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)){
           register_code(sk);
        } else {
           register_code(nk);
        }
      }
      else {
           unregister_code(sk);
           unregister_code(nk);
      }
      return false;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(C(G(KC_LEFT)));
        } else {
            tap_code16(C(G(KC_RGHT)));
        }
    }
    else if (index == 1) {
        if (clockwise) {
            send_string(":bn"SS_TAP(X_ENTER));
        } else {
            send_string(SS_LCTL("B")"n");
        }
    }
}

