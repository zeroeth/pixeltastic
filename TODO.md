More modular approach for tweening any values. And combining FX.

# ie. circling grower with pulsing color
spot = new Spot()

# this?
spot.wiggle()

# or per attribute
wiggler = new Wiggle(spot->color)
wiggler->amplitude(5);
wiggler->speed(0.5); // or helper function to slow down relative to amplitude?
wiggler->motion(LINEAR); // or cubic function?


# sub pixel rendering
# view fading vs clearing (and how to deal with it.. ie fixed frame rate or how to scale super tiny amounts per frame?)
# auto register themes?
# auto register views
# fluid width

# random color (every cycle)
# fade between two colors
# pulsar that picks new color

# sample grid
# (sample rotating line for pov on grid)

# random tweening, so it moves between values (ie position) smoothly

# allow widths to be composits of multiple objects (or just have a factory?)
# ex for gradients out from the center.. or random colorfades along a wide spot?

# sequencing effects (and tweening)

# TODO emscripten hook to visualize/edit

# Add readme, and make into a zip-droppable library for arduino + example.

# 'Twinkler' that fades out and then finds a new position

# amplitude vs width vs frequency. which names make sense for different effects
