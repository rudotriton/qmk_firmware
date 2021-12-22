# rudotriton_mk1 custom KARA keymap

## Things to maybe improve

- `_FNTWO` change to layers 8 or 9 don't work, only through double tapping.
  - `TO()` switches to layer 9, and switches everything else off, so when `_FNTWO` is released, `update_tri_layer()` turns 9 off, since `_FNTWO` is off.
  - `TG()` or a custom key code
  - it really doesn't matter though
- remove the led testing code and keys on `_FNBOTH`
- should the `TO`s be `DF`s for changing default layers?

## suspend and LEDs

I have my keyboards connected through my monitor, so when the monitor is off, they turn off as well, so far so good. The port on the side of the monitor seems to stay on when the monitor is off, e.g. I can charge my phone. However, my keyboard doesn't work when connected to it and the monitor is off, but its LEDs stay on. It also doesn't seem to be in a suspend state, because the suspend code isn't run.
