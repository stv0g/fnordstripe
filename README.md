fnordstripe is a fnordlicht compatible module to control dumb and LPD6803 compatible RGB LED strips

see http://www.steffenvogel.de/2013/07/14/fnordstripe/ for a blog post about this project

# Variants

## Dumb

schematic/ contains a layout for dumb RGB LED strips without any brain power.
This strips are not addressable and therefore not compatible with the source code in stv0g/fnordstripe/src

Please use /stv0g/fnordlicht as a firmware for this version.

## Smart

Smart variants of REG LED strips are addressable. Mostly every third or even every LED on the strip is addressable and has its own IC to generate PWM signals.
src/ contains a proof of concept firmware for LPD6803 strips.
It's my goal to implement the fnordlicht protocol for this.

