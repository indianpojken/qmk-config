#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
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

#define SE_BSLSH RALT(KC_MINUS)

const uint16_t PROGMEM esc_combo[] =  { KC_W, KC_E,       COMBO_END };
const uint16_t PROGMEM bspc_combo[] = { KC_I, KC_O,       COMBO_END };
const uint16_t PROGMEM tab_combo[] =  { KC_X, KC_C,       COMBO_END };
const uint16_t PROGMEM ent_combo[] =  { SE_COMM, SE_DOT,  COMBO_END };

const uint16_t PROGMEM arng_combo[] = { KC_U, KC_I,       COMBO_END }; // Å
const uint16_t PROGMEM adia_combo[] = { KC_J, KC_K,       COMBO_END }; // Ä
const uint16_t PROGMEM odia_combo[] = { KC_M, SE_COMM,    COMBO_END }; // Ö

const uint16_t PROGMEM grv_combo[] =  { SE_PLUS, SE_EQL,  COMBO_END }; // `
const uint16_t PROGMEM acut_combo[] = { SE_AMPR, SE_PIPE, COMBO_END }; // ´

combo_t key_combos[] = {
    COMBO(esc_combo,  KC_ESC),
    COMBO(bspc_combo, KC_BSPC), 
    COMBO(tab_combo,  KC_TAB),
    COMBO(ent_combo,  KC_ENT),
  
    COMBO(arng_combo, SE_ARNG), // Å
    COMBO(adia_combo, SE_ADIA), // Ä
    COMBO(odia_combo, SE_ODIA), // Ö

    COMBO(grv_combo,  SE_GRV),  // `
    COMBO(acut_combo, SE_ACUT)  // ´
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [DEF] = LAYOUT_ferris_hlc(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    SE_QUES,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    SE_COMM, SE_DOT,  SE_EXLM,
                                   LA_NAV,  KC_SPC,          KC_LSFT, LA_SYM,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      ),

      [NAV] = LAYOUT_ferris_hlc(
        KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TAB,          KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_ESC,          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_BSPC,
        QK_UNDO, QK_CUT,  QK_COPY, QK_PASTE,QK_REP,          QK_REP,  KC_VOLD, KC_VOLU, KC_PSCR, KC_ENT,
                                   _______, _______,         _______, _______,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      ),
  
      [SYM] = LAYOUT_ferris_hlc(
        SE_SLSH, SE_ASTR, SE_MINS, SE_PLUS, SE_EQL,          SE_AMPR, SE_PIPE, SE_UNDS, SE_PERC, SE_BSLSH,
        SE_LABK, SE_LBRC, SE_LCBR, SE_LPRN, SE_QUOT,         SE_DQUO, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        SE_RABK, SE_RBRC, SE_RCBR, SE_RPRN, SE_DLR,          SE_EURO, SE_AT,   SE_HASH, SE_CIRC, SE_TILD,
                                   _______, _______,         _______, _______,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
      ),

      [NUM] = LAYOUT_ferris_hlc(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_F11,          KC_F12,  OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                                   _______, _______,         _______, _______,
        
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
