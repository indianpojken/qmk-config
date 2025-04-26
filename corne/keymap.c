#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "oneshot.h"

enum layers {
    DEF,
    NAV,
    SYM,
    NUM,
    FUN
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
#define LA_FUN MO(FUN)

#define QK_UNDO  LCTL(KC_Z)
#define QK_CUT   LCTL(KC_X)
#define QK_COPY  LCTL(KC_X)
#define QK_PASTE LCTL(KC_V)
#define QK_SLCTA LCTL(KC_A)

#define SE_BSLSH RALT(KC_MINUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3_ex2(
      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    SE_EXLM, SE_QUES, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    SE_COMM, SE_DOT,  KC_H,    KC_J,    KC_K,    KC_L,    SE_ODIA,
      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M,    SE_ARNG, SE_ADIA, KC_SLASH,
                        LA_NUM,  LA_NAV,  KC_SPC,                    KC_LSFT, LA_SYM,  LA_FUN
    ),
    
    [NAV] = LAYOUT_split_3x5_3_ex2(
      KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR, KC_VOLU, KC_PGUP, KC_TAB,  KC_HOME, KC_END,  XXXXXXX, KC_DEL,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_ESC,  KC_VOLD, KC_PGDN, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_BSPC,
      QK_UNDO, QK_CUT,  QK_COPY, QK_PASTE,QK_SLCTA,                  KC_RGUI, XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,
                        _______, _______, _______,                   _______, _______, _______
    ),

    [SYM] = LAYOUT_split_3x5_3_ex2(
      SE_SLSH, SE_ASTR, SE_MINS, SE_PLUS, SE_EQL,  SE_DLR,  SE_EURO, SE_AMPR, SE_PIPE, SE_UNDS, SE_PERC, SE_BSLSH,
      SE_LABK, SE_LBRC, SE_LCBR, SE_LPRN, SE_SCLN, SE_GRV,  SE_ACUT, SE_COLN, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      SE_RABK, SE_RBRC, SE_RCBR, SE_RPRN, SE_QUOT,                   SE_DQUO, SE_AT,   SE_HASH, SE_CIRC, SE_TILD,
                        _______, _______, _______,                   _______, _______, _______
    ),
    
    [NUM] = LAYOUT_split_3x5_3_ex2(
      SE_SLSH, SE_ASTR, SE_MINS, SE_PLUS, SE_EQL,  XXXXXXX, XXXXXXX, SE_COMM, KC_7,    KC_8,    KC_9,    KC_DEL,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_ESC,  XXXXXXX, XXXXXXX, SE_DOT,  KC_4,    KC_5,    KC_6,    KC_BSPC,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_0,    KC_1,    KC_2,    KC_3,    KC_ENT,
                        _______, _______, _______,                   _______, _______, _______
    ),
    
    [FUN] = LAYOUT_split_3x5_3_ex2(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      OS_GUI,  OS_ALT,  OS_SHFT, OS_CTRL, KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, OS_CTRL, OS_SHFT, OS_ALT,  OS_GUI,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                        _______, _______, _______,                   _______, _______, _______
    ),
 };

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NAV:
    case LA_SYM:
    case LA_NUM:
    case LA_FUN:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_NAV:
    case LA_SYM:
    case LA_NUM:
    case LA_FUN:
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
