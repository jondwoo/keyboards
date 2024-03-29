/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include <stdio.h>

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
// uint8_t oled_set_brightness = 50;

char wpm_str[10];

enum layers {
    _DVORAK = 0,
    _DVORAK_MAC,
    _NUM,
    _SYMBOL,
    _NAV,
    _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Layer: DVORAK
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |  '"  |   ,<  |   .>  |  P  |  Y  |                              |   F  |   G  |   C  |   R  |   L    |  /? | 
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  TAB   |   A  |   O  |  E   |   U  |   I  |                              |   D  |   H  |   T  |   N  |  S    |   -  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | CTRL  |   ;:  |   Q  |   J  |   K  |   X  | Space| DVRK|  |       |     |   B  |   M  | W   |  V   |   Z  | Adjust |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt | NAV  | SYMBOL| NUM |   |Enter | Space | Bkspc|     |      |
 *                        |     |     |       |      |      |   |      |       |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_DVORAK] = LAYOUT(
    KC_ESC,    KC_QUOT,       KC_COMM,       KC_DOT,        KC_P,          KC_Y,                                                              KC_F,     KC_G,          KC_C,          KC_R,          KC_L,         KC_SLSH,
    KC_TAB,    LGUI_T(KC_A),  LALT_T(KC_O),  LCTL_T(KC_E),  LSFT_T(KC_U),  KC_I,                                                              KC_D,     RSFT_T(KC_H),  RCTL_T(KC_T),  LALT_T(KC_N),  RGUI_T(KC_S), KC_MINS,
    KC_LCTL,   KC_SCLN,       KC_Q,          KC_J,          KC_K,          KC_X,     KC_SPC,       TG(_DVORAK_MAC),     _______,    _______,  KC_B,     KC_M,          KC_W,          KC_V,          KC_Z,         MO(_ADJUST),
                                             KC_LGUI,       KC_LALT,       MO(_NAV), MO(_SYMBOL),  MO(_NUM),            KC_ENT,     KC_SPC,   KC_BSPC,  _______,       _______
  ),
/*
 * Layer: DVORAK_MAC
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |  '"  |   ,<  |   .>  |  P  |  Y  |                              |   F  |   G  |   C  |   R  |   L    |  /? | 
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  TAB   |   A  |   O  |  E   |   U  |   I  |                              |   D  |   H  |   T  |   N  |  S    |   -  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | CTRL  |   ;:  |   Q  |   J  |   K  |   X  | Space| DVRK|  |       |     |   B  |   M  | W   |  V   |   Z  | Adjust |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Alt | NAV  | SYMBOL| NUM |   |Enter | Space | Bkspc|     |      |
 *                        |     |     |       |      |      |   |      |       |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
  [_DVORAK_MAC] = LAYOUT(
    KC_ESC,    KC_QUOT,        KC_COMM,       KC_DOT,        KC_P,          KC_Y,                                                             KC_F,     KC_G,          KC_C,          KC_R,          KC_L,           KC_SLSH,
    KC_TAB,    LCTL_T(KC_A) ,  LOPT_T(KC_O),  LCMD_T(KC_E),  LSFT_T(KC_U),  KC_I,                                                             KC_D,     RSFT_T(KC_H),  RCMD_T(KC_T),  LOPT_T(KC_N),  RCTL_T(KC_S),   KC_MINS,
    KC_LCTL,   KC_SCLN,        KC_Q,          KC_J,          KC_K,          KC_X,     KC_SPC,       TG(_DVORAK_MAC),     _______,  _______,   KC_B,     KC_M,          KC_W,          KC_V,          KC_Z,           MO(_ADJUST),
                                              KC_LGUI,       KC_LALT,       MO(_NAV), MO(_SYMBOL),  MO(_NUM),            KC_ENT,   KC_SPC,    KC_BSPC,  _______,       _______
  ),
/*
 * SYMBOL Layer
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |  !   |  @   |   &  |                              |   *  |  {    |  }    |   =  |      |      |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |     |       |  #   |  $   |   |  |                              |   +  |  (   |  )    |   <  |  >   |       |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |       |     |        |  %   |  ^   |   ~  |      |      |  |      |      |  `   |  [   |   ]   |  \|  |      |       |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOL] = LAYOUT(
      _______, _______, _______, KC_EXLM, KC_AT,   KC_AMPR,                                            KC_ASTR, KC_LCBR, KC_RCBR, KC_EQL,  _______, _______,
      _______, _______, _______, KC_HASH, KC_DLR,  KC_PIPE,                                            KC_PLUS, KC_LPRN, KC_RPRN, KC_LABK, KC_RABK, _______,
      _______, _______, _______, KC_PERC, KC_CIRC, KC_TILD, _______, _______,       _______,  _______, KC_GRV, KC_LBRC,  KC_RBRC, KC_BSLS, _______, _______,
                                 _______, _______, _______, _______, _______,       _______,  _______, _______, _______, _______
    ),
/*
 * NUM Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |       |      |     |                              |      |  7    |  8   |  9   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |       |     |                              |     |  4    |  5   |  6   |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |     |      |      |  |      |      |     |  1   |  2    |  3   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |   0   |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                      _______,    KC_7,    KC_8,    KC_9,    _______,    _______,
      _______, _______, _______, _______, _______, _______,                                      _______,    KC_4,    KC_5,    KC_6,    _______,    _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,    KC_1,    KC_2,    KC_3,    _______,    _______,
                                 _______, _______, _______, _______, _______, _______, KC_0,     _______,    _______, _______
    ),
/*
 * NAV Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |     |       |      |      |                              |        |       |     |     | Right|       |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |     |      |      |       |                              |       | Left |      |     |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      | Down |  Up  |     |      |      |   |      |      |       |     |      |     |       |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______,  _______,                                          _______,    _______,    _______,    _______,    KC_RIGHT,    _______,
      _______, _______, _______, _______, _______,  _______,                                          _______,    KC_LEFT,    _______,    _______,    _______,    _______,
      _______, _______, _______, KC_DOWN, KC_UP,    _______, _______, _______,     _______, _______,  _______,    _______,    _______,   _______,    _______,    _______,
                                 _______, _______,  _______, _______, _______,     _______, _______,  _______,    _______,    _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |       |      |      |      |      |                              |      |  F7   |  F8  | F9  | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |  F4  |  F5  |  F6  | F11  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |  F1  | F2  |  F3  |  F12  |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, KC_F7, KC_F8, KC_F9, KC_F10, _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, KC_F4, KC_F5, KC_F6, KC_F11, _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, KC_F1, KC_F2, KC_F3, KC_F12, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Kyria rev3.1\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
          case _DVORAK:
            oled_write_P(PSTR("DVORAK\n"), false);
            break;
          case _DVORAK_MAC:
              oled_write_P(PSTR("DVORAK MAC\n"), false);
              break;
          case _NUM:
              oled_write_P(PSTR("NUMPAD\n"), false);
              break;
          case _SYMBOL:
              oled_write_P(PSTR("SYMBOLS\n"), false);
              break;
          case _NAV:
              oled_write_P(PSTR("NAV\n"), false);
              break;
          case _ADJUST:
              oled_write_P(PSTR("F KEYS\n"), false);
              break;
          default:
              oled_write_P(PSTR("Undefined"), false);
          }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif
