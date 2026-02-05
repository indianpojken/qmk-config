#include QMK_KEYBOARD_H

#include "keymap_swedish_pro_mac_ansi.h"

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

  TB_NEXT,
};

#define LA_NAV MO(NAV)
#define LA_SYM MO(SYM)
#define LA_NUM MO(NUM)
#define LA_EXT OSL(EXT)

#define TB_LEFT  C(S(KC_TAB))
#define TB_RIGHT C(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3_ex2(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    SE_QUOT,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_QUES,
                        _______, LA_NAV,  KC_LSFT,                   KC_SPC,  LA_SYM, _______
    ),

    [NAV] = LAYOUT_split_3x5_3_ex2(
      KC_APP,  TB_LEFT, TB_NEXT, TB_RIGHT,LA_EXT,  XXXXXXX, XXXXXXX, KC_PGUP, KC_BSPC, KC_UP,  KC_DEL,  CW_TOGG,
      OS_CTRL, OS_ALT,  OS_SHFT, OS_GUI,  MC_LCHR, XXXXXXX, XXXXXXX, KC_TAB,  KC_LEFT, KC_DOWN,KC_RIGHT,KC_ESC,
      MC_UNDO, MC_CUT,  MC_COPY, MC_PASTE,MC_SLCT,                   KC_PGDN, KC_HOME, QK_REP, KC_END,  MC_PSCR,
                        _______, _______, _______,                   KC_ENT, _______, _______
    ),

    [EXT] = LAYOUT_split_3x5_3_ex2(
      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, KC_BRMU, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_CAPS,
      XXXXXXX, MC_ZDEC, MC_ZRST, MC_ZINC, KC_BRMD, XXXXXXX, XXXXXXX, XXXXXXX, MC_TGLF, MC_FILE, MC_TMGR, MC_QUIT,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        _______, _______, _______,                   KC_ENT, _______, _______
    ),

    [SYM] = LAYOUT_split_3x5_3_ex2(
      SE_CIRC, SE_LBRC, SE_LCBR, SE_LPRN, SE_LABK, XXXXXXX, XXXXXXX, SE_RABK, SE_RPRN, SE_RCBR, SE_RBRC, SE_TILD,
      SE_MINS, SE_ASTR, SE_UNDS, SE_EQL,  SE_AT,   XXXXXXX, XXXXXXX, SE_HASH, OS_GUI,  OS_SHFT, OS_ALT,  OS_CTRL,
      SE_PLUS, SE_COLN, SE_SLSH, SE_SCLN, SE_PERC,                   SE_DLR,  SE_AMPR, SE_BSLS, SE_PIPE, SE_EURO,
                        _______, _______, _______,                   KC_SPC, _______, _______
    ),

    [NUM] = LAYOUT_split_3x5_3_ex2(
      KC_7,    KC_5,    KC_3,    KC_1,    KC_9,    XXXXXXX, XXXXXXX, KC_8,    KC_0,    KC_2,    KC_4,    KC_6,
      OS_CTRL, OS_ALT,  OS_SHFT, OS_GUI,  KC_F11,  XXXXXXX, XXXXXXX, KC_F12,  OS_GUI,  OS_SHFT, OS_ALT,  OS_CTRL,
      KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,                     KC_F8,   KC_F12,  KC_F2,   KC_F4,   KC_F6,
                        _______, _______, _______,                   KC_SPC, _______, _______
    ),
 };

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case TB_LEFT:
  case TB_NEXT:
  case TB_RIGHT:

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

  .modifier = KC_LGUI,
  .key = KC_TAB,
};

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
    &tabber, TB_NEXT,
    keycode, record
  );

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
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
            return false;  // Deactivate Caps Word.
    }
}
