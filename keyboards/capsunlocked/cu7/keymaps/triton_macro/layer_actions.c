#include "layer_actions.h"

void default_actions(int key_idx, bool release) {
    if (release) return;
    switch (key_idx) {
        case 1:
            tap_code(KC_MPRV);
            break;
        case 2:
            tap_code(KC_MPLY);
            break;
        case 3:
            tap_code(KC_MNXT);
            break;
        case 4:
            // Switch to Kitty and hide other windows
            tap_code(KC_ESC);
            tap_code16(G(C(KC_M)));
            tap_code16(G(A(KC_H)));
            break;
        case 5:
            tap_code(KC_MUTE);
            break;
        case 6:
            tap_code16(G(S(KC_RBRC))); // open spotify w/ BTT
            break;
    }
}

void layer_one_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                if (to_move_win) {
                    tap_code16(G(A(KC_L)));
                } else {
                    tap_code16(C(KC_LEFT)); // prev desktop
                }
            }
            break;
        case 2:
            if (release) {
                unregister_code16(C(KC_UP));
            } else {
                if (to_move_win) {
                    tap_code16(G(A(KC_E)));
                } else {
                    register_code16(C(KC_UP));
                }
            }
            break;
        case 3:
            if (!release) {
                if (to_move_win) {
                    tap_code16(G(A(KC_Y)));
                } else {
                    tap_code16(C(KC_RGHT)); // next desktop
                }
            }
            break;
        case 4:
            if (!release)
                tap_code16(G(A(KC_V)));
            break;
        case 5:
            if (release)
                unregister_code16(C(KC_DOWN));
            else
                register_code16(C(KC_DOWN));
            break;
        case 6:
            if (is_cmd_tab_active && !release) {
                tap_code(KC_ENT); // allow bypassing the timeout
            } else if (release)
                unregister_code16(KC_F11);
            else
                register_code16(KC_F11);
            break;

    }
}

void layer_two_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 6:
            if (!release) {
                ltwo_flag = key_idx; // 6
            } else {
                ltwo_flag = 0;
            }
            break;
        default:
            if (release) return;
            ltwo_flag = ltwo_flag == key_idx ? 0 : key_idx;
            break;
    }
}

void layer_three_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                tap_code16(G(KC_A));
            }
            break;
        case 2:
            if (!release) {
                tap_code16(G(KC_C));
            }
            break;
        case 3:
            if (!release)
                tap_code16(G(KC_V));
            break;
        case 4:
            if (!release) {
                tap_code16(G(KC_Z));
            }
            break;
        case 5:
            if (!release) {
                register_code(KC_5);
            } else {
                unregister_code(KC_5);
            }
            break;
        case 6:
            if (!release) {
                tap_code16(G(S(KC_Z)));
            }
            break;
    }
}

void layer_four_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 1:
            tap_code16(C(S(KC_TAB))); // previous tab
            break;
        case 2:
            tap_code16(G(KC_W)); // close tab
            break;
        case 3:
            tap_code16(C(KC_TAB)); // next tab
            break;
        case 4:
            tap_code16(G(KC_R)); // refresh
            break;
        case 5:
            tap_code16(G(S(KC_T))); // reopen last closed tab
            break;
        case 6:
            // copy, open new tab, paste, enter
            tap_code16(G(KC_C));
            tap_code16(G(A(KC_J))); // launch firefox w/ betterTouchTool
            tap_code16(G(KC_T));
            tap_code16(G(KC_V));
            tap_code(KC_ENT);
            break;
    }
}

void layer_five_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            tap_code16(G(S(KC_BSLS)));
            break;
        case 5:
            tap_code16(G(A(KC_RBRC))); // toggle system theme
            break;
        case 6:
            tap_code16(G(C(KC_Q))); // lock screen
            break;
    }
}

void layer_six_actions(int key_idx, bool release) {
    if (release) return;

    switch (key_idx) {
        case 6:
            layer_move(_RESET);
            break;
        default:
            rgb_flag = rgb_flag == key_idx ? 0 : key_idx;
            break;
    }
}

void layer_seven_actions(int key_idx, bool release) {
    if (key_idx == 6 && release)
        layer_move(_META);
}

// some spotify actions
void layer_eight_actions(int key_idx, bool release) {
    if (release) return; // early return, since we don't use release for other keys

    switch (key_idx) {
        case 1:
            tap_code16(G(KC_S)); // shuffle
            break;
        case 2:
            tap_code(KC_MPLY);
            break;
        case 3:
            tap_code16(G(KC_R)); // repeat
            break;
        case 4:
            if (l_eight_lock) {
                layer_move(_DEFAULT);
            } else {
                l_eight_lock = true;
                layer_move(_MUSIC);
            }
            break;
        case 5:
            tap_code(KC_BSPC); // delete for removing a song from the playlist
            break;
        case 6:
            layer_move(_DEFAULT);
            break;
    }
}

void (*layer_actions[9]) (int, bool) = {
    default_actions,
    layer_one_actions,
    layer_two_actions,
    layer_three_actions,
    layer_four_actions,
    layer_five_actions,
    layer_six_actions,
    layer_seven_actions,
    layer_eight_actions
};

