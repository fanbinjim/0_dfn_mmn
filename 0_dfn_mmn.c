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

#include "0_dfn_mmn.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
  // Key Matrix to LED Index
    {   NO_LED, NO_LED, NO_LED,  NO_LED },
    {0,  1,  2,  3},
    {7,  6,  5,  4},
    {8,  9,  10, 11},
    {15, 14, 13, 12},
    {16, 17, 18, 19},
}, {
  // LED Index to Physical Position
  { 0,  0}, {20,  0}, {40,  0}, {60,  0},
  {60, 20}, {40, 20}, {20, 20}, { 0, 20},
  { 0, 40}, {20, 40}, {40, 40}, {60, 40},
  {60, 60}, {40, 60}, {20, 60}, { 0, 60},
  { 0, 80}, {20, 80}, {40, 80}, {60, 80},
}, {
  // LED Index to Flag
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1,
  1, 1, 1, 1
} };

#endif