#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "g/keymap_combo.h"

#include "oneshot.h"

enum layers {
    DEF,
    NAV,
    SYM,
    NUM,
};

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SHFT,
  OS_CTRL,
};

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)

#define QK_UNDO  LCTL(KC_Z)
#define QK_CUT   LCTL(KC_X)
#define QK_COPY  LCTL(KC_C)
#define QK_PASTE LCTL(KC_V)
#define QK_BSPC  LCTL(KC_BSPC)

const key_override_t ques_exlm_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUES, SE_EXLM); // S-? -> ?
const key_override_t quot_dquo_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUOT, SE_DQUO); // S-' -> "

const key_override_t *key_overrides[] = {
	&ques_exlm_override,
  &quot_dquo_override 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3_ex2(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   XXXXXXX,XXXXXXX,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   XXXXXXX,XXXXXXX,   KC_H,    KC_J,    KC_K,    KC_L,    SE_QUOT,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_QUES,
                          XXXXXXX, LA_NAV,  KC_LSFT,                   KC_SPC,  LA_SYM,  XXXXXXX
    ),
    
    [NAV] = LAYOUT_split_3x5_3_ex2(
      KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, XXXXXXX, XXXXXXX, KC_PGDN, KC_HOME, KC_END,  KC_PGUP, KC_CAPS,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_TAB,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ESC,
      QK_UNDO, QK_CUT,  QK_COPY, QK_PASTE,QK_REP,                    QK_BSPC, KC_BSPC, KC_DEL,  KC_PSCR, KC_APP,
                        _______, _______, _______,                   KC_ENT,  _______, _______
    ),

    [SYM] = LAYOUT_split_3x5_3_ex2(
      SE_BSLS, SE_PIPE, SE_UNDS, SE_AMPR, SE_PERC, XXXXXXX, XXXXXXX, SE_PLUS, SE_MINS, SE_EQL,  SE_ASTR, SE_SLSH,
      SE_LABK, SE_COLN, SE_LCBR, SE_LPRN, SE_LBRC, XXXXXXX, XXXXXXX, SE_DLR,  OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      SE_RABK, SE_SCLN, SE_RCBR, SE_RPRN, SE_RBRC,                   SE_EURO, SE_AT,   SE_HASH, SE_CIRC, SE_TILD,
                        _______, _______, _______,                   _______, _______, _______
    ),
    
    [NUM] = LAYOUT_split_3x5_3_ex2(
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX, XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_F11,  XXXXXXX, XXXXXXX, KC_F12,  OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                        _______, _______, _______,                   _______, _______, _______
    ),
 };

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case LA_NAV:
  case LA_SYM:
      return true;
  default:
      return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case LA_NAV:
  case LA_SYM:
  case KC_LSFT:
  case OS_SHFT:
  case OS_CTRL:
  case OS_ALT:
  case OS_GUI:
      return true;
  default:
      return false;
  }
}

oneshot_state os_gui_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_oneshot(
      &os_gui_state, KC_LGUI, OS_GUI,
      keycode, record
  );

  update_oneshot(
      &os_shft_state, KC_LSFT, OS_SHFT,
      keycode, record
  );

  update_oneshot(
      &os_alt_state, KC_LALT, OS_ALT,
      keycode, record
  );

  update_oneshot(
      &os_ctrl_state, KC_LCTL, OS_CTRL,
      keycode, record
  );

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, SYM, NAV, NUM);
}
