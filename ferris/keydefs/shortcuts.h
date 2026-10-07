#pragma once

#include "layout.h"

#define SC_UNDO  C(KC_Z)
#define SC_CUT   C(KC_X)
#define SC_COPY  C(KC_C)
#define SC_PASTE C(KC_V)
#define SC_REDO  C(KC_Y)

#define SC_LCHR G(KC_SPC) // Launcher
#define SC_WINI G(KC_R) // Increase window size
#define SC_WIND G(S(KC_R)) // Decrease window size
#define SC_PSCR KC_PSCR // Screenshot
#define SC_OVRW G(KC_O) // Overview

#define SC_ZINC C(SE_PLUS) // Zoom in
#define SC_ZDEC C(SE_MINS) // Zoom out
#define SC_ZRST C(KC_0) // Restore zoom

#define SC_BWRD C(KC_BSPC)
#define SC_DWRD C(KC_DEL)

#define SC_QUIT G(KC_Q)

#define SC_TABL C(S(KC_TAB))
#define SC_TABR C(KC_TAB)
#define SC_TABC C(KC_W)
#define SC_TABN C(KC_T)
#define SC_TABU C(S(KC_T))
