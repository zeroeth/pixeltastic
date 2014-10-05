#include "segment_views.h"


// Replacement for C 'remainder' % operator that has continuous behavior instead of mirror/flipped about 0

int modulo(int dividend, int divisor)
{
    int remainder = dividend % divisor;

	if(remainder < 0) {
		return remainder + divisor;
	}

	return remainder;
}


// StripView Constructor

StripView::StripView (Adafruit_NeoPixel& n_strip, uint8_t n_starting_led, uint8_t n_length):
  strip (n_strip),
  starting_led (n_starting_led),
  length (n_length),
  spot_count (0), /* Initializer list */
  last_clear_time (0),
  motion_blur_time (0)
{
}


// Add spot to list of spots for this view

void StripView::add (Spot *spot)
{
  spots[spot_count] = spot;
  spot_count++;
}


// Update all spots

void StripView::update ()
{
  for(int i = 0; i < spot_count; i++)
  {
    spots[i]->update ();
  }
}


void StripView::draw ()
{
  /* TODO figure out where strip view and spot view separate for drawing logic.. does spot view create the dots and colors and then strip over lays those pixels into its buffer (additive or whatever) */

  // Draw every spot
  for (uint8_t i = 0; i < spot_count; i++)
  {
	// FIXME uint8 limits size for larger projects.
	uint8_t width;

	// Fluid (0.0->1.0) vs Fixed (pixel count) widths
	if(spots[i]->fixed_width)
	{
		width = spots[i]->width();
	}
	else
	{
		width = spots[i]->fluid_width() * length;
	}

    // For width of the spot
    for (uint8_t w = 0; w < width; w++)
    {
      // Map position to strip
      int8_t view_position = int(spots[i]->position() * length) + w;

      // Center width
      view_position -= width/2;

      // Wrap around the segment
	  // TODO add_at for color blending
      draw_at (modulo(view_position,length) + starting_led, spots[i]->color());

	  // Render into next pixel
    }
  }
}


// Clear strip

void StripView::clear ()
{
  // Delay buffer clearing since we remove 1 rgb value per clear. (Alternatively use float values)
  // more than 1 for harsher fx.
  if(millis() - last_clear_time > motion_blur_time) {
	  last_clear_time = millis();

	  for(uint8_t i = starting_led; i < (starting_led+length); i++)
	  {
		uint32_t start_color = strip.getPixelColor (i);
		uint8_t r,g,b;

		r = (uint8_t)(start_color >> 16),
		g = (uint8_t)(start_color >>  8),
		b = (uint8_t)(start_color >>  0);

		// Dim brightness FIXME fails to gracefully fade dim colors (because it runs a lot per second)
		//uint32_t color = strip.Color (r * 0.9, g * 0.9, b * 0.9);

		if(r > 0) { r -= 1; }
		if(g > 0) { g -= 1; }
		if(b > 0) { b -= 1; }
		uint32_t color = strip.Color (r, g, b);

		strip.setPixelColor (i, color);
		//strip.setPixelColor (i, strip.Color(0,0,0));
	  }
  }
}

// TODO draw and clear into virtual buffers so that motion blur is per view and all views are blended

// Draw a color into the strip

void StripView::draw_at (uint8_t position, uint32_t color)
{
  strip.setPixelColor (position, color);
}


// Add color into the strip

void StripView::add_at (uint8_t position, uint32_t color)
{
  uint32_t added_colors = add_colors (color, strip.getPixelColor (position));
  strip.setPixelColor (position, added_colors);
}


// Blend two colors together

uint32_t StripView::add_colors (uint32_t color1, uint32_t color2)
{
  uint8_t r1,g1,b1;
  uint8_t r2,g2,b2;
  uint8_t r3,g3,b3;

  r1 = (uint8_t)(color1 >> 16),
  g1 = (uint8_t)(color1 >>  8),
  b1 = (uint8_t)(color1 >>  0);

  r2 = (uint8_t)(color2 >> 16),
  g2 = (uint8_t)(color2 >>  8),
  b2 = (uint8_t)(color2 >>  0);


  return strip.Color (constrain (r1+r2, 0, 255), constrain (g1+g2, 0, 255), constrain (b1+b2, 0, 255));
}


// Prepare for a new theme

void StripView::unload_theme ()
{
  for(int i = 0; i < spot_count; i++)
  {
    delete spots[i];
  }
  spot_count = 0;
}
