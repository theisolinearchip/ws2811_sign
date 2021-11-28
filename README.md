# Custom 3d printed sign with addresable leds
![Snake 1](http://albertgonzalez.coffee/projects/elfuns_sign/img/header_small.jpg)

__Attiny85__ firmware for a 3d-printed sign with a single strip of __ws2812-based addresable leds__. Allows multiple "modes" that can display different animations (available by pressing a button attached to PB2 - _INT0 pin_).

More info on [my hackaday.io project page](https://hackaday.io/project/182790/details/).

## How it works
There's a single "main loop" that shows the current animation frame, updates it (according to the mode criteria) and then waits a small delay (different for each mode).

Each "mode" is a bunch of __three__ functions: _init_, _step_ and _delay_. The first one is called when changing from one mode to another, and the other two are called in an endless loop of blinking (or static!) lights.

### Array of function pointers

There's an array of pointers (that points to the different functions for each mode) and three "main pointers" for the current active mode.

When changing the mode, those three pointers values are changed to the next ones in the array, allowing the loop to continue but with a different set of actions (the _init_/_step_ and _delay_ from the next mode)

Adding a mode is easy as creating and including the proper file, defining the three functions and adding them in the main pointers array.

### INT0 for mode changes

There's a button on PB2 that triggers the external _INT0_ interrupt. On each falling edge on this pin (aka "each time the button is pressed") the interrupt changes the current mode and sets a flag to be checked by the main loop. Then, on the beginning of the next iteration, the new _init_ will be executed (so if the button is pressed _before_ the delay, the system will wait until the end of the "frame" to advance to the next mode - that's the reason the delays needs to be short!).

### Secondary color

By holding the button down when powering up the micro an extra check will be made and the "secondary color" will be activated (as requested when I was making this sign, it can work in two different "color modes": all red / all blue).

## Available modes

- Static color
- Slow fade in/out
- Larson scanner (aka "the Knight Rider / Cylon thing")
- Double Larson scanner
- Malfunction blink like a broken motel sign
- Turn on and off each led sequentially (some sort of "diagnostic mode" to make sure the whole strip is working fine)

## ws2812 driver
The connection with the led strip is made using [this library by Danny Havenith](https://github.com/DannyHavenith/ws2811). The small part I used here (the _ASM core function_ that makes everything work) is on the __ws2811_controller.h__ file.
