#include <Adafruit_NeoPixel.h>

#include "segment_models.h"
#include "segment_views.h"
#include "themes.h"


// Initialize

#define PIN 4
#define LED_COUNT 84

#define MINDS_EYE_START 0
#define HALO_RING_START 24

#define EYE_LED_COUNT 24
#define HALO_LED_COUNT 60

#define THEME_SWITCH_DELAY 5000 // Milliseconds

Adafruit_NeoPixel led_strip = Adafruit_NeoPixel (40, PIN, NEO_GRB + NEO_KHZ800);


// Create containers for sections of your LED strands/circles.

StripView  outer_ring = StripView (led_strip,  0, 24);
StripView  inner_ring = StripView (led_strip, 24, 16);
StripView  whole_loop = StripView (led_strip,  0, 40);

void setup ()
{
  // Aways give your project a safe boot delay so you can re-upload code when:
  //   - it uses too much current when your LEDs are too bright
  //   - the serial doesn't respond because of some timing issue

  delay(2000);

  led_strip.begin ();

  inner_ring.motion_blur_time = 0;
  outer_ring.motion_blur_time = 20;
  whole_loop.motion_blur_time = 0;

  inner_ring.clear_amount = 255;
  outer_ring.clear_amount = 1;
  whole_loop.clear_amount = 0;

  Theme::switch_every (THEME_SWITCH_DELAY);
}



// Main Loop

void loop ()
{
  // Switch themes every {x} seconds
  //Theme::switch_every (THEME_SWITCH_DELAY);

  // TODO abstract a way to clear each layers pixel values (with opacity)
  outer_ring.clear ();
  inner_ring.clear ();
  whole_loop.clear ();

  // Update the spots
  outer_ring.update ();
  inner_ring.update ();
  whole_loop.update ();


  // Draw the spots.
  outer_ring.draw ();
  inner_ring.draw ();
  whole_loop.draw ();

  led_strip.show ();
}
