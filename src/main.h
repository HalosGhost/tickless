#include <pebble.h>

struct tickless {
    Window * w;
    TextLayer * t, * d, * y;
    //BitmapLayer * b;
    char * t_fn, * d_fn, * y_fn;
    uint8_t bg, fg;
};

#define toGColor8(c) (GColor8 ){ .argb = (c) }

static void
init (void);

static void
init_text (TextLayer **, GRect, const char *);

static void
cleanup (void);

static void
tick (struct tm *, TimeUnits);

static void
update_time (void);

// vim: set ts=4 sw=4 et:
