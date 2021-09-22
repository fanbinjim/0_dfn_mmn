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
    _3
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        _______,      TO(1),                      KC_AUDIO_MUTE, KC_AUDIO_VOL_UP,
        KC_NUMLOCK,   KC_BSPACE,    KC_DELETE,    KC_KP_SLASH, KC_AUDIO_VOL_DOWN,
        KC_KP_7,      KC_KP_8,      KC_KP_9,      KC_KP_ASTERISK,
        KC_KP_4,      KC_KP_5,      KC_KP_6,      KC_KP_MINUS,
        KC_KP_1,      KC_KP_2,      KC_KP_3,      KC_KP_PLUS,
        KC_KP_ENTER,  KC_KP_0,      KC_KP_DOT,    KC_KP_ENTER
    ),
    [_1] = LAYOUT(
         TO(0) ,     TO(2) ,                _______,    _______,
        _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_2] = LAYOUT(
         TO(1) ,     TO(3) ,                _______,    _______,
        _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______
    ),
    [_3] = LAYOUT(
         TO(2) ,     TO(3) ,                _______,    _______,
        _______,    _______,    _______,    RGB_MODE_FORWARD,    _______,
        RGB_MODE_XMAS,    RGB_MODE_GRADIENT,    _______,    RGB_MODE_REVERSE,
        RGB_MODE_SWIRL,    RGB_MODE_SNAKE,    RGB_MODE_KNIGHT,    RGB_SPI,
        RGB_MODE_PLAIN,    RGB_MODE_BREATHE,    RGB_MODE_RAINBOW,    RGB_SPD,
        _______,    _______,    _______,    _______
    )

    /*
    RGB_MODE_PLAIN,     // 5CCE
    RGB_MODE_BREATHE,   // 5CCF
    RGB_MODE_RAINBOW,   // 5CD0
    RGB_MODE_SWIRL,     // 5CD1
    RGB_MODE_SNAKE,     // 5CD2
    RGB_MODE_KNIGHT,    // 5CD3
    RGB_MODE_XMAS,      // 5CD4
    RGB_MODE_GRADIENT,  // 5CD5
    */
};

static uint32_t oled_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    oled_timer = timer_read32();
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
#ifdef CONSOLE_ENABLE

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

#include "i2c_master.h"

static i2c_status_t i2c_transmit_P(uint8_t address, const uint8_t *data, uint16_t length, uint16_t timeout) {
    i2c_status_t status = i2c_start(address | I2C_WRITE, timeout);

    for (uint16_t i = 0; i < length && status >= 0; i++) {
        status = i2c_write(pgm_read_byte((const char *)data++), timeout);
        if (status) break;
    }

    i2c_stop();

    return status;
}

#define I2C_TRANSMIT_P(data) i2c_transmit_P((OLED_DISPLAY_ADDRESS << 1), &data[0], sizeof(data), OLED_I2C_TIMEOUT)

void ssd1316_oled_init(void) {
    static const uint8_t PROGMEM display_setup1[] = { 
        0x00,0xAE,0x00,0x10,0x40,0xB0,0x81,0xc5,0xA1,0xA6,0xA8,0x1F,0xC0,0xD3,0x00,0xD5,0x80,0xD9,0x22,0xDA,0x12,0xdb,0x20,0x8d,0x15,0xAF
    };
    I2C_TRANSMIT_P(display_setup1);
}

static uint8_t init_oled_user_flag = 0;
void oled_task_user(void) {
    if(!init_oled_user_flag) {
        init_oled_user_flag = 1;
        ssd1316_oled_init();
        return;
    }
    if(0) {
        render_logo();
    }

    // if (timer_elapsed32(oled_timer) < 5000) {
    //     oled_on();
    //     oled_scroll_off();
    //     oled_write_P(PSTR("DFN's mmn"), false);
    //     char layer[2] = {0};
    //     uint8_t n        = get_highest_layer(layer_state);
    //     layer[1]         = '\0';
    //     layer[0]         = '0' + n % 10;
    //     oled_write_P(PSTR("   L:"), false);
    //     oled_write_ln(layer, false);
    //     oled_write_ln_P(PSTR("--------------"), false);
    //     // render_user_status();
    // } else {
    //     if (timer_elapsed32(oled_timer) < 10000) {
    //         oled_on();
    //         render_logo();
    //         oled_scroll_right();
    //     } else {
    //         oled_off();
    //     }
    // }

    // Host Keyboard Layer Status

    if (timer_elapsed32(oled_timer) < 5000) {
        oled_write_P(PSTR("Layer: "), false);
        print("Layer: \n");
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Default\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("FN\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("GAME\n"), false);
                break;
            case 3: 
                oled_write_P(PSTR("RGB\n"), false);
                break;
            default:
                // Or use the write_ln shortcut over adding '\n' to the end of your string
                oled_write_ln_P(PSTR("Undefined"), false);
        }
        oled_write_ln_P(PSTR("--------------"), false);
        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    } else {
        render_logo();
    }

}
#endif

#ifdef ENCODER_ENABLE

// uint8_t codeC[2][4] = {
//     {KC_VOLU, KC_1, KC_3, KC_5},
//     {KC_VOLD, KC_2, KC_4, KC_6}
// };

bool encoder_update_user(uint8_t index, bool clockwise) {
    oled_timer = timer_read32();
    uint8_t layer = get_highest_layer(layer_state);
    uint16_t en_p_keycode = keymap_key_to_keycode(layer, (keypos_t){.row = 0, .col = 4});
    uint16_t en_m_keycode = keymap_key_to_keycode(layer, (keypos_t){.row = 1, .col = 4});

    if (index == 0) { /* First encoder */
        if (clockwise) {
            // tap_code(codeC[0][layer]);
            tap_code(en_p_keycode);
        } else {
            // tap_code(codeC[1][layer]);
            tap_code(en_m_keycode);
        }
    }
    return true;
}
#endif
