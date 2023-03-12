/* Copyright 2019 jrfhoutx
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _WORK,
    _LOWER,
    _RAISE,
    _ARROW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│         │& 7│* 8│( 9│) 0│_ -│+ =│BS │BS │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │   │ │Tab  │ Q │ W │ E │ R │ T │         │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │Wrk│ │Caps  │ A │ S │ D │ F │ G │         │ H │ J │ K │ L │: ;│" '│   Enter│
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │LShift  │ Z │ X │ C │ V │ B │     │ B │ N │ M │< ,│> .│? /│  Shft│Fn │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │Ctrl │     │Opt  │Spc/Lwr│Cmd │   │   Spc/Rai│  Cmd│           │ ARW │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
[_BASE] = LAYOUT_all(
    KC_ESC,    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
    _______,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    TG(_WORK), KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
               KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_LOWER),
               KC_LCTL,          KC_LOPT, KC_SPC,  KC_LCMD,           KC_SPC,  KC_RCMD,                                     TG(_ARROW)
),

/* WORK
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│         │& 7│* 8│( 9│) 0│_ -│+ =│BS │BS │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │   │ │Tab  │" '│ , │ . │ P │ Y │         │ F │ G │ C │ R │ L │/ ?│} ]│ | \ │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │Bse│ │Caps  │ A │ O │ E │ U │ I │         │ D │ H │ T │ N │ S │ - │   Enter│
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │LShift  │ ; │ Q │ J │ K │ X │     │ X │ B │ M │ W │ V │ Z │  Shft│Fn │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │Cmd  │     │Opt  │Spc/Lwr│Rai │   │   Spc/Rai│  Cmd│           │     │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
[_WORK] = LAYOUT_all(
    KC_ESC,    KC_GRV,  KC_1,         KC_2,         KC_3,                KC_4,         KC_5,       KC_6,    KC_7,         KC_8,         KC_9,         KC_0,         KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
    _______,   KC_TAB,  KC_QUOT,      KC_COMM,      KC_DOT,              KC_P,         KC_Y,       KC_F,    KC_G,         KC_C,         KC_R,         KC_L,         KC_SLSH, KC_RBRC, KC_BSLS,
    TG(_WORK), KC_CAPS, LCTL_T(KC_A), LOPT_T(KC_O), LCMD_T(KC_E),        LSFT_T(KC_U), KC_I,       KC_D,    RSFT_T(KC_H), RCMD_T(KC_T), LOPT_T(KC_N), RCTL_T(KC_S), KC_MINS, KC_ENT,
               KC_LSFT, KC_SCLN,      KC_Q,         KC_J,                KC_K,         KC_X,       KC_X,    KC_B,         KC_M,         KC_W,         KC_V,         KC_Z,    KC_RSFT, MO(_LOWER),
               KC_LCMD,               KC_LOPT,      LT(_LOWER, KC_SPC),  MO(_RAISE),               KC_SPC,  KC_RCMD,                                                         _______
),

/* Lower
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │ │   │ F1│ F2│ F3│ F4│ F5│ F6│         │ F7│ F8│ F9│F10│F11│F12│   │   │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │   │ │RMod │RH+│RS+│ ! │ @ │ & │         │ * │ { │ } │ = │PgU│Hom│End│  Del│
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │   │ │RTgl  │RH-│RS-│ # │ $ │ | │         │ + │ ( │ ) │ < │ > │ ↑ │        │
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │        │   │   │ % │ ^ │ ~ │     │ ~ │ ` │ [ │ ] │ ← │ ↓ │   →  │   │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │     │     │     │       │    │   │          │     │           │     │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
[_LOWER] = LAYOUT_all(
    _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,
    _______, RGB_MOD, RGB_HUI, RGB_SAI, KC_EXLM, KC_AT,   KC_AMPR,     KC_ASTR, KC_LCBR, KC_RCBR, KC_EQL,  KC_PGUP, KC_HOME, KC_END,   KC_DEL,
    _______, RGB_TOG, RGB_HUD, RGB_SAD, KC_HASH, KC_DLR,  KC_PIPE,     KC_PLUS, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, KC_UP,   _______,
             _______, _______, _______, KC_PERC, KC_CIRC, KC_TILD,     KC_TILD, KC_GRV,  KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_RIGHT, _______,
             _______,                   _______, _______, _______,     _______, _______,                                     _______
 
),

/* Raise
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │ │   │   │   │   │   │   │   │         │   │   │   │   │   │   │   │   │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │   │ │     │   │   │   │   │   │         │   │ 7 │ 8 │ 9 │   │   │   │     │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │   │ │      │   │   │   │   │   │         │   │ 4 │ 5 │ 6 │   │   │        │
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │        │   │   │   │   │   │     │   │   │ 1 │ 2 │ 3 │   │      │   │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │     │     │     │       │    │   │    0     │     │           │     │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
[_RAISE] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,  _______,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,            _______, KC_7,     KC_8, KC_9, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,            _______, KC_4,     KC_5, KC_6, _______, _______, _______,
             _______, _______, _______, _______, _______, _______,            _______, _______,  KC_1, KC_2, KC_3,    _______, _______, _______,
             _______,                   _______, _______, _______,            KC_0,    _______,                            _______
 
),

/* Arrow
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │   │ │   │   │   │   │   │   │   │         │   │   │   │   │   │   │   │   │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │   │ │     │   │   │   │   │   │         │   │   │   │   │   │   │   │     │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │   │ │      │   │   │   │   │   │         │   │   │   │   │   │ ↑ │        │
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 *       │        │   │   │   │   │   │     │   │   │   │   │ ← │ ↓ │   →  │   │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │     │     │     │       │    │   │          │     │           │     │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
[_ARROW] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______, _______,  _______,
    _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, KC_UP,   _______,
             _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______,
             _______,                   _______, _______, _______,            _______, _______,                            _______
 
),
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ARROW);
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _WORK:
            rgblight_setrgb(RGB_BLUE);
            break;
        case _BASE:
            rgblight_setrgb(RGB_WHITE);
            break;
        default:
            break;
    }
  return state;
}
