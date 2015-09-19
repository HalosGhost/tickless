#include <pebble.h>

struct tickless {
    Window * w;
    TextLayer * t, * d;
    struct GRect * b;
    uint8_t bg, t_fg, d_fg, b_fg;
};

#define toGColor8(c) (GColor8 ){ .argb = (c) }

static void init (void);
static void cleanup (void);
static void tick (struct tm *, TimeUnits);
static void update_time (void);

// vim: set ts=4 sw=4 et:
