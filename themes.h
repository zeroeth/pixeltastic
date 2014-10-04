// Create all your movers and shakers here!

extern Adafruit_NeoPixel led_strip; /* FIXME temporary global */
extern StripView outer_ring;
extern StripView inner_ring;
extern StripView whole_loop;



namespace Theme {
  uint8_t       current_theme = 0;
  unsigned long last_millis   = 0;

  /*
  uint32_t yellow  = led_strip.Color (50, 50, 0);
  uint32_t cyan    = led_strip.Color (0, 50, 50);

  uint32_t blue    = led_strip.Color (0, 10, 50);
  uint32_t magenta = led_strip.Color (50, 0, 50);

  uint32_t pink    = led_strip.Color (50, 0, 10);

  uint32_t red     = led_strip.Color (50, 10, 0);
  uint32_t green   = led_strip.Color (0, 50, 10);

  uint32_t green2  = led_strip.Color (0, 50, 0);
  uint32_t white   = led_strip.Color (20, 20, 20);
  */

  uint32_t yellow  = led_strip.Color (5, 5, 0);
  uint32_t cyan    = led_strip.Color (0, 5, 5);

  uint32_t blue    = led_strip.Color (0, 1, 5);
  uint32_t magenta = led_strip.Color (5, 0, 5);

  uint32_t pink    = led_strip.Color (5, 0, 1);

  uint32_t red     = led_strip.Color (5, 1, 0);
  uint32_t green   = led_strip.Color (0, 5, 1);

  uint32_t green2  = led_strip.Color (0, 5, 0);
  uint32_t white   = led_strip.Color (2, 2, 2);



  // Yellow Pulsars and Blue Circlers
  void theme1 ()
  {
    Circler* circle1 = new Circler (/* position */ 0.0,
                                    /* width    */ 10,
                                    /* color    */ cyan);

    Circler* circle2 = new Circler (/* position */ 0.5,
                                    /* width    */ 8,
                                    /* color    */ white);

    Circler* circle3 = new Circler (/* position */ 0.0,
                                    /* width    */ 4,
                                    /* color    */ red);
	circle3->speed = 0.1;

    outer_ring.add (circle1);
    inner_ring.add (circle2);
	whole_loop.add (circle3);
  }



  // Blue/Magenta Grower and Blue/Magenta Wobbler (with 5 rotations around)
  void theme2 ()
  {
    Wobbler* wobble0 = new Wobbler (/* position */ 0.0,
                                    /* width    */ 1,
                                    /* color    */ magenta);

    Wobbler* wobble1 = new Wobbler (/* position */ 0.33,
                                    /* width    */ 1,
                                    /* color    */ blue);

    Wobbler* wobble2 = new Wobbler (/* position */ 0.66,
                                    /* width    */ 1,
                                    /* color    */ white);

	wobble0->speed = 0.5;
	wobble1->speed = 0.5;
	wobble2->speed = 0.5;

    outer_ring.add (wobble0);
    outer_ring.add (wobble1);
    outer_ring.add (wobble2);


     Circler* circle1 = new Circler (/* position */ 0.0,
                                    /* width    */ 1,
                                    /* color    */ cyan);

    Circler* circle2 = new Circler (/* position */ 0.16,
                                    /* width    */ 1,
                                    /* color    */ white);

     Circler* circle3 = new Circler (/* position */ 0.32,
                                    /* width    */ 1,
                                    /* color    */ cyan);

    Circler* circle4 = new Circler (/* position */ 0.48,
                                    /* width    */ 1,
                                    /* color    */ white);

     Circler* circle5 = new Circler (/* position */ 0.64,
                                    /* width    */ 1,
                                    /* color    */ cyan);

    Circler* circle6 = new Circler (/* position */ 0.82,
                                    /* width    */ 1,
                                    /* color    */ white);

	// TODO api 2.. shared 'speed' for multiples?

	circle1->speed = 0.3;
	circle2->speed = 0.3;
	circle3->speed = 0.3;
	circle4->speed = 0.3;
	circle5->speed = 0.3;
	circle6->speed = 0.3;

    inner_ring.add(circle1);
    inner_ring.add(circle2);
    inner_ring.add(circle3);
    inner_ring.add(circle4);
    inner_ring.add(circle5);
    inner_ring.add(circle6);

  }

  void theme3() {

    Grower* grower1 =  new Grower (/* position */ 0.0,
                                   /* width    */ 24,
                                   /* color    */ magenta);

    Grower* grower2 =  new Grower (/* position */ 0.0,
                                   /* width    */ 8,
                                   /* color    */ blue);

    outer_ring.add (grower1);
    inner_ring.add (grower2);
  }


  void theme4() {

    Pulsar* pulsar1 =  new Pulsar (/* position */ 0.0,
                                   /* width    */ 24,
                                   /* color    */ magenta);

    Pulsar* pulsar2 =  new Pulsar (/* position */ 0.0,
                                   /* width    */ 8,
                                   /* color    */ blue);

    Pulsar* pulsar3 =  new Pulsar (/* position */ 0.0,
                                   /* width    */ 40,
                                   /* color    */ green);


    //outer_ring.add (pulsar1);
    //inner_ring.add (pulsar2);
    whole_loop.add (pulsar3);
  }


  void theme5() {
	Warper* warper = new Warper ( );

	warper->position ( 0.0  );
	warper->width    ( 5    );
//	warper->color    ( blue );


	Colortron* colortron = new Colortron (5, blue);

	colortron->position ( 0.0  );
//	colortron->width    ( 0.5  );
//	colortron->color    ( blue );


	inner_ring.add (warper);
	outer_ring.add (colortron);
  }


  void switch_every (uint16_t delay)
  {
    if(millis() - last_millis > delay)
    {
      last_millis = millis();

  outer_ring.unload_theme();
  inner_ring.unload_theme();
  whole_loop.unload_theme();

      switch(current_theme)
      {
        case 0:
          theme5();
          break;

        case 1:
          theme2 ();
          break;

        case 2:
          theme3 ();
          break;

        case 3:
          theme4 ();
          break;

        default:
          break;
      }

      //current_theme++;
      //current_theme %= 4;
    }
  }
}
