/* Copyright 2021 Jason Williams (Wilba)
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

#include "rama_works_kara.h"
#include <quantum.h>
#include <i2c_master.h>
#include <led_tables.h>
#include <rgb_matrix.h>

// led indices
#define _LA 0
#define _LB 18
#define _LC 36
#define _LD 54

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
*   driver
*   |  R location
*   |  |      G location
*   |  |      |      B location
*   |  |      |      | */
  {0, C2_1,  C3_1, C4_1},   // LA0 u
  {0, C1_1,  C3_2, C4_2},   // LA1 y
  {0, C1_2,  C2_2, C4_3},   // LA2 t
  {0, C1_3,  C2_3, C3_3},   // LA3 r
  {0, C1_4,  C2_4, C3_4},   // LA4 e
  {0, C1_5,  C2_5, C3_5},   // LA5 w
  {0, C1_6,  C2_6, C3_6},   // LA6 q
  {0, C1_7,  C2_7, C3_7},   // LA7 tab
  {0, C1_8,  C2_8, C3_8},   // LA8 caps
  {0, C9_1,  C8_1, C7_1},   // LA9 8
  {0, C9_2,  C8_2, C7_2},   // LA10 7
  {0, C9_3,  C8_3, C7_3},   // LA11 6
  {0, C9_4,  C8_4, C7_4},   // LA12 5
  {0, C9_5,  C8_5, C7_5},   // LA13 4
  {0, C9_6,  C8_6, C7_6},   // LA14 3
  {0, C9_7,  C8_7, C6_6},   // LA15 2
  {0, C9_8,  C7_7, C6_7},   // LA16 1
  {0, C8_8,  C7_8, C6_8},   // LA17 esc

  {0, C2_9,  C3_9,  C4_9},  // LB0 9
  {0, C1_9,  C3_10, C4_10}, // LB1 0
  {0, C1_10, C2_10, C4_11}, // LB2 -
  {0, C1_11, C2_11, C3_11}, // LB3 +
  {0, C1_12, C2_12, C3_12}, // LB4 |
  {0, C1_13, C2_13, C3_13}, // LB5 delete
  {0, C9_9,  C8_9,  C7_9},  // LB9 i
  {0, C9_10, C8_10, C7_10}, // LB10 o
  {0, C9_11, C8_11, C7_11}, // LB11 p
  {0, C9_12, C8_12, C7_12}, // LB12 [
  {0, C9_13, C8_13, C7_13}, // LB13 ]
  {0, C9_14, C8_14, C7_14}, // LB14 backspace

  {1, C2_1,  C3_1, C4_1}, // LC0 space
  {1, C1_1,  C3_2, C4_2}, // LC1 b
  {1, C1_2,  C2_2, C4_3}, // LC2 v
  {1, C1_3,  C2_3, C3_3}, // LC3 c
  {1, C1_4,  C2_4, C3_4}, // LC4 x
  {1, C1_5,  C2_5, C3_5}, // LC5 z
  {1, C1_6,  C2_6, C3_6}, // LC6 left stab
  {1, C1_7,  C2_7, C3_7}, // LC7 left command
  {1, C1_8,  C2_8, C3_8}, // LC8 left option
  {1, C9_1,  C8_1, C7_1}, // LC9 h
  {1, C9_2,  C8_2, C7_2}, // LC10 g
  {1, C9_3,  C8_3, C7_3}, // LC11 f
  {1, C9_4,  C8_4, C7_4}, // LC12 d
  {1, C9_5,  C8_5, C7_5}, // LC13 s
  {1, C9_6,  C8_6, C7_6}, // LC14 a
  {1, C9_8,  C7_7, C6_7}, // LC16 left shift

  {1, C2_9,  C3_9,  C4_9},  // LD0 j
  {1, C1_9,  C3_10, C4_10}, // LD1 k
  {1, C1_10, C2_10, C4_11}, // LD2 l
  {1, C1_11, C2_11, C3_11}, // LD3 '
  {1, C1_12, C2_12, C3_12}, // LD4 ;
  {1, C1_13, C2_13, C3_13}, // LD5 enter
  {1, C1_14, C2_14, C3_14}, // LD6 /
  {1, C1_15, C2_15, C3_15}, // LD7 right shift
  {1, C1_16, C2_16, C3_16}, // LD8 fn1
  {1, C9_9,  C8_9,  C7_9},  // LD9 n
  {1, C9_10, C8_10, C7_10}, // LD10 m
  {1, C9_11, C8_11, C7_11}, // LD11 ,
  {1, C9_12, C8_12, C7_12}, // LD12 .
  {1, C9_14, C8_14, C7_14}, // LD14 right stab
  {1, C9_15, C8_15, C6_14}, // LD15 right command
  {1, C9_16, C7_15, C6_15}, // LD16 right opt
};

led_config_t g_led_config = { {
// all the leds in sequence:
// 17, 16, 15, 14, 13, 12, 11, 10,  9, 18, 19, 20,  21,  22, 23
//  7,  6,  5,  4,  3,  2,  1,  0,  24, 25, 26, 27, 29, 30,
//  8, 45, 44, 43, 42, 41,  40,  47,  48,  49,  50,  51,  52,
// 46, 36  35,  34,  33,  32,  56, 57, 58, 59,  53,  54,  55,
// C17,  39,  38,  37, ---, ---, ---,  31, ---, 60, 61, 62,
//
// Note: Left spacebar stab is at 4,3 (LC6)
// Right spacebar stab is at 4,9 (LD13)
//
// A17, A16, A15, A14, A13, A12, A11, A10,  A9,  B0,  B1,  B2,  B3,  B4, (here's B5 actually)
//  A7,  A6,  A5,  A4,  A3,  A2,  A1,  A0,  B9, B10, B11, B12, B13, B14,
//  A8, C14, C13, C12, C11, C10,  C9,  D0,  D1,  D2,  D3,  D4,  D5,
// C16, C15,  C5,  C4,  C3,  C2,  C1,  D9, D10, D11, D12,  D6,  D7,  D8,
// C17,  C8,  C7,  C6, ---, ---, ---,  C0, ---, D13, D14, D15, D16, D17,
//
 { _LA+17, _LA+16, _LA+15, _LA+14, _LA+13, _LA+12, _LA+11, _LA+10,  _LA+9, _LB+0, _LB+1, _LB+2, _LB+3, _LB+4 },
 { _LA+7, _LA+6, _LA+5, _LA+4, _LA+3, _LA+2,  _LA+1,  _LA+0, _LB+9, _LB+10, _LB+11, _LB+12, _LB+13, _LB+14 },
 { _LA+8, _LC+14, _LC+13, _LC+12, _LC+11, _LC+10, _LC+9, _LD+0, _LD+1, _LD+2, _LD+3, _LD+4, _LD+5 },
 { _LC+16, _LC+5, _LC+4, _LC+3, _LC+2, _LC+1, _LD+9, _LD+10, _LD+11, _LD+12, _LD+6, _LD+7, _LD+8 },
 { _LC+17, _LC+8, _LC+7, _LC+6,  NO_LED,  NO_LED,  NO_LED, _LC+0, NO_LED, _LD+13, _LD+14, _LD+15, _LD+16, _LD+17 }
}, {
  // LA0..LA17
  {120,16}, {104,16}, {88,16}, {72,16}, {56,16}, {40,16}, {24,16}, {4,16}, {4,32},
  {128,0}, {112,0}, {96,0}, {80,0}, {64,0}, {48,0}, {32,0}, {16,0}, {0,0},
  // LB0..
  {144,0}, {160,0}, {176,0}, {192,0}, {216,0}, {224,0},
  // LB09..
  {136,16}, {152,16}, {168,16}, {184,16}, {200,16}, {220,16},
  // LC0
  {112,64}, {100,48}, {84,48}, {68,48}, {52,48}, {36,48}, {64,64}, {43,64}, {23,64},
  // LC09
  {108,32}, {92,32}, {76,32}, {60,32}, {44,32}, {28,32}, {2,48},
  // LD0
  {124,32}, {140,32}, {156,32}, {172,32}, {188,32}, {214,32}, {180,48}, {203,48}, {224,48},
  // LD09
  {116,48}, {132,48}, {148,48}, {164,48}, {161,64}, {181,64}, {201,64},
  }, {
  // LA0..LA17
  1, 1, 1, 1, 1, 1, 1, 4, 4,
  1, 1, 1, 1, 1, 1, 1, 1, 4,
  // LB0..LB17
  1, 1, 1, 1, 1, 4,
  1, 1, 1, 1, 1, 4,
  // LC0..LC17
  1, 1, 1, 1, 1, 1, 1, 4, 4,
  1, 1, 1, 1, 1, 1, 4,
  // LD0..LC17
  1, 1, 1, 1, 1, 4, 4, 4, 4,
  1, 1, 1, 1, 1, 4, 4,
} };
