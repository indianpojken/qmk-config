#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "sendstring_swedish.h"

#include "g/keymap_combo.h"

#include "keydefs/macros.h"
#include "keydefs/overrides.h"

#include "features/oneshot.h"
#include "features/tabber.h"

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

    TB_REP,
  TB_PREV,
  TB_NEXT,
};

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)
#define LA_EXT OSL(EXT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3_ex2(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    SE_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_QUES,
                        _______, LA_NAV,  KC_LSFT,                   KC_SPC,  LA_SYM, _______
    ),
    
    [NAV] = LAYOUT_split_3x5_3_ex2(
      LA_EXT,  TB_PREV, TB_REP,  TB_NEXT, MC_LCHR, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_CAPS,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_TAB,  XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ESC,
      MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE,QK_REP,                    QK_REP,  KC_BSPC, MC_WBSPC,KC_DEL,  KC_APP,
                        _______, _______, _______,                   KC_ENT, _______, _______
    ),

    [EXT] = LAYOUT_split_3x5_3_ex2(
      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
      XXXXXXX, MC_ZDEC, MC_ZRST, MC_ZINC, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, MC_FILE, MC_TMGR, MC_TGLF, MC_QUIT,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        _______, _______, _______,                   KC_ENT, _______, _______
    ),

    [SYM] = LAYOUT_split_3x5_3_ex2(
      SE_CIRC, SE_LBRC, SE_LCBR, SE_LPRN, SE_LABK, XXXXXXX, XXXXXXX, SE_RABK, SE_RPRN, SE_RCBR, SE_RBRC, SE_TILD,
      SE_MINS, SE_ASTR, SE_UNDS, SE_EQL,  SE_AT,   XXXXXXX, XXXXXXX, SE_HASH, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      SE_PLUS, SE_SLSH, SE_COLN, SE_SCLN, SE_PERC,                   SE_EURO, SE_AMPR, SE_PIPE, SE_BSLS, SE_DLR,
                        _______, _______, _______,                   _______, _______, _______
    ),
    
    [NUM] = LAYOUT_split_3x5_3_ex2(
      KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    XXXXXXX, XXXXXXX, KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_F11,  XXXXXXX, XXXXXXX, KC_F12,  OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,                     KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
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

tabber_t tabber = {
  .enabled = false,
  .previous = KC_NO,

  .modifier = KC_LALT,
};

tabber_action_t tabber_prev = {
    .normal = C(S(KC_TAB)),
    .active = A(S(KC_TAB)),
};

tabber_action_t tabber_next = {
    .normal = C(KC_TAB),
    .active = A(KC_TAB),
};

bool is_tabber_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case TB_REP:
  case TB_PREV:
  case TB_NEXT:
    return true;
  default:
    return false;
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

    update_tabber(
    &tabber, TB_REP,
    keycode, record
  );

  update_tabber_action(
    &tabber, &tabber_prev, TB_PREV,
    keycode, record
  );

  update_tabber_action(
    &tabber, &tabber_next, TB_NEXT,
    keycode, record
  );

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, SYM, NAV, NUM);
}
