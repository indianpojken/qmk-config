#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "keydefs/keycodes.h"
#include "keydefs/macros.h"
#include "keydefs/overrides.h"

#include "g/keymap_combo.h"

#include "features/oneshot.h"
#include "features/tabber.h"
#include "features/macro.h"
#include "features/magic_caps.h"
#include "features/oneshot_fn.h"

enum layers {
  DEF,
  NAV,
  SYM,
  NUM,
};

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF] = LAYOUT_ferris_hlc(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    SE_QUOT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_QUES,
                               LA_NAV,  KC_LSFT,         KC_SPC,  LA_SYM,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [NAV] = LAYOUT_ferris_hlc(
    MC_PSCR, KC_TABL, TB_NEXT, KC_TABR, KC_TABN,         KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  CW_TOGG,
    OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, MC_LCHR,         KC_TAB,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_ESC,
    MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE,MC_REDO,         KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, KC_APP,
                              _______, _______,          KC_ENT,  _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [SYM] = LAYOUT_ferris_hlc(
    SE_CIRC, SE_LBRC, SE_LCBR, SE_LPRN, SE_LABK,         SE_RABK, SE_RPRN, SE_RCBR, SE_RBRC, SE_TILD,
    SE_MINS, SE_ASTR, SE_UNDS, SE_EQL,  SE_AT,           SE_HASH, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
    SE_PLUS, SE_COLN, SE_SCLN, SE_SLSH, SE_PERC,         SE_DLR,  SE_BSLS, SE_AMPR, SE_PIPE, SE_GRV,
                               _______, _______,         KC_SPC,  _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [NUM] = LAYOUT_ferris_hlc(
    XXXXXXX, SE_EQL,  SE_SLSH, SE_ASTR, XXXXXXX,         XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX,
    OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, OS_FN,           XXXXXXX, KC_4,    KC_5,    KC_6,    KC_0,
    XXXXXXX, SE_DOT,  SE_MINS, SE_PLUS, XXXXXXX,         XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,
                                _______, _______,        KC_SPC,  _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case KC_TABL:
  case TB_NEXT:
  case KC_TABR:

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
  case OS_FN:
    return true;
  default:
    return false;
  }
}

oneshot_state os_gui_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;

bool is_tabber_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case KC_UP:
  case KC_DOWN:
  case KC_LEFT:
  case KC_RIGHT:
    return true;
  default:
    return false;
  }
}

tabber_t tabber = {
  .enabled = false,

  .modifier = KC_LALT,
  .key = KC_TAB,
};

bool os_fn_pending = false;

uint16_t oneshot_fn_press_user(uint16_t keycode) {
  switch (keycode) {
    case KC_1:    return KC_F1;
    case KC_2:    return KC_F2;
    case KC_3:    return KC_F3;
    case KC_4:    return KC_F4;
    case KC_5:    return KC_F5;
    case KC_6:    return KC_F6;
    case KC_7:    return KC_F7;
    case KC_8:    return KC_F8;
    case KC_9:    return KC_F9;
    case SE_EQL:  return KC_F10;
    case SE_SLSH: return KC_F11;
    case SE_ASTR: return KC_F12;
    default:      return KC_NO;
  }
}

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

  if (!update_oneshot_fn(&os_fn_pending, OS_FN, keycode, record)) {
    return false;
  }

  update_tabber(
    &tabber, TB_NEXT,
    keycode, record
  );

  process_macro_key(
    KC_TABL, MC_TABL,
    keycode, record
  );

  process_macro_key(
    KC_TABR, MC_TABR,
    keycode, record
  );

  process_macro_key(
    KC_TABN, MC_TABN,
    keycode, record
  );

  if (!process_magic_caps(keycode, record)) {
    return false;
  }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  os_fn_pending = false; // cancel OS_FN on layer change
  return update_tri_layer_state(state, SYM, NAV, NUM);
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    case SE_MINS:

    case KC_A ... KC_Z:
    case SE_ADIA:
    case SE_ARNG:
    case SE_ODIA:
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;

    case KC_1 ... KC_0:

    case KC_BSPC:
    case KC_DEL:

    case SE_UNDS:
        return true;

    default:
        return false;
  }
}
