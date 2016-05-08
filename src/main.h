#include <pebble.h>

static struct tickless {
    Window * w;
    TextLayer * t, * d, * y, * z;
    Layer * b;
    char * t_fn, * d_fn, * y_fn, * z_fn;
    uint8_t bg, fg;
} state = {
    .w = 0, .t = 0, .d = 0, .y = 0, .z = 0, .b = 0,
    .t_fn = FONT_KEY_LECO_36_BOLD_NUMBERS,
    .d_fn = FONT_KEY_GOTHIC_28_BOLD,
    .y_fn = FONT_KEY_LECO_20_BOLD_NUMBERS,
    .z_fn = FONT_KEY_GOTHIC_24_BOLD,
    .bg   = PBL_IF_COLOR_ELSE(GColorTiffanyBlueARGB8, GColorBlackARGB8),
    .fg   = GColorWhiteARGB8,
};

static char str_buffer [18] = "";
static char tm_fmt [] = "%H.%M|%a %d %b";

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
batt_update (BatteryChargeState);

static void
batt_bar_update (Layer *, GContext *);

// vim: set ts=4 sw=4 et:
