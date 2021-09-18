/* Copyright 2021 fanbinjim
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        _______,      TO(1),                KC_KP_1,
        KC_NUMLOCK, KC_BSPACE,    KC_DELETE,    KC_KP_SLASH,
        KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_KP_1,
        KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_MINUS,
        KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_KP_1,
        KC_KP_ENTER,    KC_KP_0,    KC_KP_DOT,    KC_KP_ENTER
    ),
    [_1] = LAYOUT(
         TO(0) ,     TO(2) ,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_2] = LAYOUT(
         TO(1) ,     TO(3) ,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_3] = LAYOUT(
         TO(2) ,     TO(4) ,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_4] = LAYOUT(
         TO(3) ,     TO(5) ,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_5] = LAYOUT(
         TO(4) ,     TO(6) ,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_6] = LAYOUT(
         TO(5) ,    _______,                _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
 
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
 
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}
#endif
