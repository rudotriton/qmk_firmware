/*
Copyright 2021 CapsUnlocked
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "cu7.h"

// #include <quantum.h>
// #include <led_tables.h>
// #include <rgb_matrix.h>

led_config_t g_led_config = {{
        { NO_LED, NO_LED, NO_LED },
        { 0, 1, 2 },
        { 3, 4, 5 }
    }, {
        {0, 0}, {16, 0}, {32, 0},
        {0, 16}, {16, 16}, {32, 16},
    }, {
        1, 1, 1,
        1, 1, 1,
}};
