#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "g/keymap_combo.h"

#include "keydefs/macros.h"
#include "keydefs/overrides.h"

#include "features/oneshot.h"
#include "features/swapper.h"

enum layers {
    DEF,
    NAV,
    EXT,
    SYM,
    NUM,
};

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SHFT,
  OS_CTRL,
  SW_TAB,
};

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)
#define LA_EXT OSL(EXT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEF] = LAYOUT_ferris_hlc(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    SE_QUOT,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_QUES,
                               LA_NAV,  KC_LSFT,         KC_SPC,  LA_SYM,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [NAV] = LAYOUT_ferris_hlc(
    LA_EXT,  MC_TABL, SW_TAB,  MC_TABR, MC_LCHR,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_CAPS,
    OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_TAB,          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ESC,
    MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE,QK_REP,          QK_REP,  KC_BSPC, MC_WBSPC,KC_DEL,  KC_APP,
                              _______, _______,          KC_ENT,  _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [EXT] = LAYOUT_ferris_hlc(
    XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,         XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
    XXXXXXX, MC_ZDEC, MC_ZRST, MC_ZINC, XXXXXXX,         KC_PSCR, MC_FILE, MC_TMGR, MC_TGLF, MC_QUIT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______,         KC_ENT,  _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [SYM] = LAYOUT_ferris_hlc(
    SE_CIRC, SE_LBRC, SE_LCBR, SE_LPRN, SE_LABK,         SE_RABK, SE_RPRN, SE_RCBR, SE_RBRC, SE_TILD,
    SE_MINS, SE_ASTR, SE_UNDS, SE_EQL,  SE_AT,           SE_HASH, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
    SE_PLUS, SE_SLSH, SE_COLN, SE_SCLN, SE_PERC,         SE_EURO, SE_AMPR, SE_PIPE, SE_BSLS, SE_DLR,
                               _______, _______,         _______, _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [NUM] = LAYOUT_ferris_hlc(
    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,            KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
    OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_F11,          KC_F12,  OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
    KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,           KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                                _______, _______,        _______, _______,

    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case LA_NAV:
  case LA_EXT:
  case LA_SYM:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case LA_NAV:
  case LA_EXT:
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

bool sw_tab_active = false;

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

  update_swapper(
    &sw_tab_active, KC_LALT, KC_TAB, SW_TAB,
    keycode, record
  );

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, SYM, NAV, NUM);
}
