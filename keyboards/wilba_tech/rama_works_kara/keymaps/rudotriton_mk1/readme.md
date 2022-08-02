# rudotriton_mk1 custom KARA keymap

## Things to maybe improve

- `_FNTWO` change to layers 8 or 9 don't work, only through double tapping.
  - `TO()` switches to layer 9, and switches everything else off, so when `_FNTWO` is released, `update_tri_layer()` turns 9 off, since `_FNTWO` is off.
  - `TG()` or a custom key code
  - it really doesn't matter though
- remove the led testing code and keys on `_FNBOTH`
- should the `TO`s be `DF`s for changing default layers?
