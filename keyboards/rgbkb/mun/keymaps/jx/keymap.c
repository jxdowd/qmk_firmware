/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "common_oled.h"

enum keymap_layers {
    _QWERTY,
    //_COLEMAK,
    _GAME,
    _FN,
    _ALTER,
    _LOWER,
    _RAISE,
    _ADJUST,
    _VIA1,
    _VIA2,
    _VIA3
};

enum keymap_keycodes {
    // Disables touch processing
    TCH_TOG = SAFE_RANGE,
    MENU_BTN,
    MENU_UP,
    MENU_DN
};

// Default Layers
#define QWERTY   DF(_QWERTY)
// #define COLEMAK  DF(_COLEMAK)
#define GAME     DF(_GAME)

// Momentary Layers
#define FN       MO(_FN)
#define ALTER   MO(_ALTER)
#define RAISE    MO(_LOWER)
#define LOWER    MO(_RAISE)
#define ADJUST   MO(_ADJUST)


#define FN_CAPS  LT(_FN, KC_CAPS)
#define FN_ESC   LT(_FN, KC_ESC)

/* This keyboard is enabled with an RGB Menu Control system.
This functionality is enabled, but still requires a little configuration based on your exact setup.
The RGB Menu will appear on the Right Half's OLED and can be controlled by the MENU keycodes:
MENU_BTN - Triggers a button action for the menu
MENU_UP - Triggers an increase action for the menu
MENU_DN - Triggers a decrease action for the menu

To finish configuration for your board, you will want to change the default keycodes for an encoder on the right half.
Encoder press keycode should be set to MENU_BTN, Clockwise should be MENU_UP, and Counter Clockwise should be MENU_DN.
Depending on where you add an encoder to the right half will determin in the default keymap where you should put those keycodes.
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* QWERTY
     * .--------------------------------------------------------------.  .--------------------------------------------------------------.
     * |   \    |   `    | 1      | 2      | 3      | 4      | 5      |  | 6      | 7      | 8      | 9      | 0      |   -    |    =   |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |   [    | Esc    | Q      | W      | E      | R      | T      |  | Y      | U      | I      | O      | P      | Enter  |    ]   |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |   (    | Tab    | A      | S      | D      | F      | G      |  | H      | J      | K      | L      | :      | '      |    )   |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * |   {    | Shift  | Z      | X      | C      | V      | B      |  | N      | M      | ,      | .      | /      |Shft/Ent|    }   |
     * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     * | RGBTOG | Space  | Ctrl   | Alt    | GUI    | Adjust | Space  |  | Bckspc | FN     | Left   | Down   | Up     | Right  | Ctrl   |
     * '--------+--------+--------+--------+--------+--------+--------'  '--------+--------+--------+--------+--------+--------+--------'
     *      Encoder 1         Encoder 2                                                                  Encoder 3         Encoder 4
     * .-----------------------------------.                                                        .-----------------------------------.
     * | VolUp  | VolDn  | VolUp  | VolDn  |                                                        | PgUp   | PgDn   | PgUp   | PgDn   |
     * |--------+--------+--------+--------+--------.                                      .--------+--------+--------+--------+--------|
     * | VolDn  | VolUp  | Next   | Play   | Prev   | Touch Encoder          Touch Encoder | RgbHuI | RgbHuD | RgbMdD | RgbTog | RgbMdI |
     * '--------+--------+--------+--------+--------'                                      '--------+--------+--------+--------+--------'
     */
    [_QWERTY] = LAYOUT(
        KC_BSLS, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,
        KC_LBRC, KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_RBRC,  KC_RBRC,
        KC_LPRN, KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_RPRN,
        KC_LCBR, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCBR, KC_RCBR, KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_RCBR,
        RGB_TOG, KC_SPC,  KC_LCTRL,KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_RCTL,

        KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD,                                                          KC_PGDN, KC_PGUP, KC_PGDN, KC_PGUP,
        KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV,                                        RGB_HUI, RGB_HUD, RGB_RMOD,RGB_TOG, RGB_MOD
    ),
/*
    [_GAME] = LAYOUT(
        _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, _______, _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_F2,   KC_F6,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_F3,   KC_F7,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
        _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_F4,   KC_F8,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
        _______, KC_NO,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD,                                                          KC_PGDN, KC_PGUP, KC_PGDN, KC_PGUP,
        KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV,                                        RGB_HUI, RGB_HUD, RGB_RMOD,RGB_TOG, RGB_MOD
    ),
*/
    [_LOWER] = LAYOUT(
        _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, _______, _______,
        _______, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, _______,
        _______, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, _______,
        _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______, _______, TCH_TOG, _______, _______, _______, _______, ADJUST,  KC_PAGE_UP, KC_VOLD, KC_VOLU, KC_PAGE_DOWN, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, _______,
        _______, KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, _______,
        _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______, _______, TCH_TOG, _______, ADJUST,  _______, _______, _______, KC_HOME, KC_VOLD, KC_VOLU, KC_END,  _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, ALTER,   RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  _______,
        _______, KC_CAPS, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, KC_WH_U, _______,
        _______, _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, RGB_MOD, RGB_TOG, RGB_RMOD, KC_WH_D,_______,
        _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_ALTER] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, RGB_SAD, RGB_VAI, RGB_SAI, RESET,   _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, RGB_HUD, RGB_VAD, RGB_HUI, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, _______,
        _______, RGB_SPD, _______, RGB_SPI, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, GAME,
        _______, RGB_RMOD,_______, RGB_MOD, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_NLCK, QWERTY, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_VIA1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_VIA2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),

    [_VIA3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______,                                                       _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
        case MENU_BTN:
            if (record->event.pressed) {
                rgb_menu_selection();
            }
            return false;
        case MENU_UP:
            if (record->event.pressed) {
                rgb_menu_action(true);
            }
            return false;
        case MENU_DN:
            if (record->event.pressed) {
                rgb_menu_action(false);
            }
            return false;
        case TCH_TOG:
            if (record->event.pressed) {
                touch_encoder_toggle();
            }
            return false;  // Skip all further processing of this key
        default:
            return true;
    }
}

static void render_layer(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWRTY"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("Game  "), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FN   "), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjst"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ALTER:
            oled_write_ln_P(PSTR("Alter"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

static void render_leds(void)
{
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUMLK")     : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPLK")    : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRLK")  : PSTR("     "), false);
}

static void render_touch(void)
{
    // Host Touch LED Status
    oled_write_P(touch_encoder_is_on() ? PSTR("TOUCH")  : PSTR("     "), false);
    oled_write_P(touch_encoder_is_calibrating() ? PSTR("CLBRT")  : PSTR("     "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_left()) {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_layer();
        oled_write_P(PSTR("     "), false);
        render_leds();
        oled_write_P(PSTR("     "), false);
        render_touch();
    }
    else {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_rgb_menu();
    }
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
