#include "segment_models.h"



/*** Spot Methods *********************************************/

// Base Spot Constructor

Spot::Spot (double n_position, uint8_t n_width, uint32_t n_color):
  _position (n_position),
  width     (n_width),
  color     (n_color), /* Initializer list */
  speed     (1.0),
  amplitude (1.0),
  offset    (0.0)
{
}



// Virtual update to be implemented by subclasses

void Spot::update () { }


// Return a 0.0 to 1.0 scaled over {speed} + {offset} seconds

double Spot::percent ()
{
  return (int((millis() * speed) + (offset*1000)) % 1000) * 0.001;
}

// Getters

double Spot::position()
{
	return _position;
}

// Setters

double Spot::position(double n_position)
{
	return _position = n_position;
}


/*** Circler Methods ******************************************/

// Circler Constructor

Circler::Circler (double n_position, uint8_t n_width, uint32_t n_color):
  Spot(n_position, n_width, n_color) /* Base Class Constructor */
{
  start_position = _position;
}


// Scale from 0 to 1 once a second

void Circler::update ()
{
  _position = percent () + start_position;
}



/*** Wobbler Methods ******************************************/

// Wobbler Constructor

Wobbler::Wobbler (double n_position, uint8_t n_width, uint32_t n_color):
  Spot(n_position, n_width, n_color) /* Base Class Constructor */
{
  start_position = _position;
}



void Wobbler::update ()
{
  // Scale from 0 to 6.28 every second
  _position = percent () * M_PI * 2;

  // Scale -1/1 to 0/1
  _position  = (sin(_position) + 1) * 0.5;
  _position *= amplitude;
  _position += start_position;
}



/*** Pulsar Methods ******************************************/

// Pulsar Constructor

Pulsar::Pulsar (double n_position, uint8_t n_width, uint32_t n_color):
  Spot(n_position, n_width, n_color) /* Base Class Constructor */
{
  start_color = color;
}

void Pulsar::update ()
{
  double value = percent () * M_PI * 2;

  // Scale -1/1 to 0/1
  value = (sin(value) + 1) * 0.5;

  // Extract original r g b
  uint8_t r,g,b;

  r = (uint8_t)(start_color >> 16),
  g = (uint8_t)(start_color >>  8),
  b = (uint8_t)(start_color >>  0);

  // Dim brightness
  color = led_strip.Color (r * value, g * value, b * value);
}



/*** Grower Methods ******************************************/

// Grower Constructor

Grower::Grower (double n_position, uint8_t n_width, uint32_t n_color):
  Spot(n_position, n_width, n_color) /* Base Class Constructor */
{
  start_width = width;
}

void Grower::update ()
{
  double value = percent () * M_PI * 2;

  // Scale -1/1 to 0/1
  value = (sin(value) + 1) * 0.5;

  // Width 0 to 10
  width = value * start_width;

}


/*** Warper Methods ********************************************/

Warper::Warper ( ):
  Spot(0.0, 1, led_strip.Color (5, 0, 5)) /* Base Class Constructor */
{
	tick_start = millis();
}


void Warper::update ()
{
	if(millis() - tick_start > speed * 1000)
	{
		tick_start = millis();
		_position = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
}

/*** Colortron Methods ********************************************/

Colortron::Colortron (uint8_t n_width, uint32_t n_color):
  Spot(0.0, n_width, n_color) /* Base Class Constructor */
{
	tick_start = millis();
}

void Colortron::update ()
{
	// TODO take into account offset (for chained delays) and amplitude (variation)
	if(millis() - tick_start > speed * 1000)
	{
		tick_start = millis();

		color = led_strip.Color (rand() % 10, rand() % 10, rand() % 10);
	}
}

