#include QMK_KEYBOARD_H

#include "layout.h"

#include "keydefs/keycodes.h"
#include "keydefs/shortcuts.h"
#include "keydefs/overrides.h"

#include "g/keymap_combo.h"

#include "features/oneshot.h"
#include "features/tabber.h"
#include "features/shortcut.h"
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
    AS(Q),    AS(W),    AS(E),    AS(R),    AS(T),          AS(Y),    AS(U),    AS(I),    AS(O),    AS(P),
    AS(A),    AS(S),    AS(D),    AS(F),    AS(G),          AS(H),    AS(J),    AS(K),    AS(L),    AS(QUOT),
    AS(Z),    AS(X),    AS(C),    AS(V),    AS(B),          AS(N),    AS(M),    AS(COMM), AS(DOT),  AS(QUES),
                                    LA_NAV, KC_LSFT,        KC_SPC, LA_SYM,

                                 XX, XX, XX, XX, XX,        XX, XX, XX, XX, XX
  ),

  [NAV] = LAYOUT_ferris_hlc(
    KC_ESC,   KC_TABL,  TB_NEXT,  KC_TABR,  KC_TABN,        KC_PGUP,  KC_BSPC,   KC_UP,   KC_DEL,   CW_TOGG,
    OS_GUI,   OS_ALT,   OS_SHFT,  OS_CTRL,  SC_LCHR,        KC_PGDN,  KC_LEFT,   KC_DOWN, KC_RIGHT, KC_TAB,
    SC_UNDO,  SC_CUT,   SC_COPY,  SC_PASTE, SC_REDO,        SC_PSCR,  KC_MPRV,   KC_MPLY, KC_MNXT,  SC_OVRW,
                                             __, __,        KC_ENT, __,

                                 XX, XX, XX, XX, XX,        XX, XX, XX, XX, XX
  ),

  [SYM] = LAYOUT_ferris_hlc(
    AS(PLUS), AS(LBRC), AS(LCBR), AS(LPRN), AS(LABK),       AS(RABK), AS(RPRN), AS(RCBR), AS(RBRC), UD(TILD),
    AS(MINS), AS(ASTR), AS(UNDS), AS(EQL),  AS(AT),         AS(HASH), OS_CTRL,  OS_SHFT,  OS_ALT,   OS_GUI,
    UD(CIRC), AS(COLN), AS(SCLN), AS(SLSH), AS(PERC),       AS(DLR),  AS(BSLS), AS(AMPR), AS(PIPE), UD(GRV),
                                          __, KC_ENT,       KC_SPC,  __,

                                  XX, XX, XX, XX, XX,       XX, XX, XX, XX, XX
  ),

  [NUM] = LAYOUT_ferris_hlc(
    XX,      AS(EQL),   AS(SLSH), AS(ASTR), XX,             XX,       AS(7),    AS(8),    AS(9),    XX,
    OS_GUI,  OS_ALT,    OS_SHFT,  OS_CTRL,  OS_FN,          AS(DOT),  AS(4),    AS(5),    AS(6),    AS(0),
    XX,      AS(UNDS),  AS(MINS), AS(PLUS), XX,             XX,       AS(1),    AS(2),    AS(3),    XX,
                                             __,  __,       __,  __,

                                  XX, XX, XX, XX, XX,       XX, XX, XX, XX, XX
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
    case AS(1):    return KC_F1;
    case AS(2):    return KC_F2;
    case AS(3):    return KC_F3;
    case AS(4):    return KC_F4;
    case AS(5):    return KC_F5;
    case AS(6):    return KC_F6;
    case AS(7):    return KC_F7;
    case AS(8):    return KC_F8;
    case AS(9):    return KC_F9;
    case AS(EQL):  return KC_F10;
    case AS(SLSH): return KC_F11;
    case AS(ASTR): return KC_F12;
    default:       return KC_NO;
  }
}

#define UD_TAP(kc) tap_code16(AS(kc)); tap_code(KC_SPC)

bool process_undead_keys(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) return true;
  
  switch (keycode) {
    case UD(TILD): UD_TAP(TILD); return false;
    case UD(GRV):  UD_TAP(GRV);  return false;
    case UD(CIRC): UD_TAP(CIRC); return false;
    default: return true;
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

  if (!update_oneshot_fn(&os_fn_pending, OS_FN, keycode, record)) return false;
  if (!process_undead_keys(keycode, record)) return false;

  update_tabber(
    &tabber, TB_NEXT,
    keycode, record
  );

  process_shortcut_key(
    KC_TABL, SC_TABL,
    keycode, record
  );

  process_shortcut_key(
    KC_TABR, SC_TABR,
    keycode, record
  );

  process_shortcut_key(
    KC_TABN, SC_TABN,
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
    case AS(MINS):

    case AS(A) ... AS(Z):
    case AS(ADIA):
    case AS(ARNG):
    case AS(ODIA):
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;

    case AS(1) ... AS(0):

    case KC_BSPC:
    case KC_DEL:

    case AS(UNDS):
      return true;

    default:
      return false;
  }
}
