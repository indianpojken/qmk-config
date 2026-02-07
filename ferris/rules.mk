COMBO_ENABLE = yes
VPATH += keyboards/gboards

SRC += features/oneshot.c
SRC += features/tabber.c

ENCODER_ENABLE = no
ENCODER_MAP_ENABLE = no

USER_NAME := halcyon_modules

REPEAT_KEY_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
CAPS_WORD_ENABLE = yes

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
