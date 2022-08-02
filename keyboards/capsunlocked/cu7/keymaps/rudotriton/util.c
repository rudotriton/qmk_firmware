#include "util.h"

int get_layer(void) {
    for (int i = _DEFAULT; i <= _MUSIC; i++) {
        if (layer_state_is(i)) return i;
    }
    return -1;
}

