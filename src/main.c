#include "main.h"

static struct tickless state = {
    .w = 0, .t = 0, .d = 0, .b = 0,
    .t_fn = FONT_KEY_BITHAM_42_BOLD,
    .d_fn = FONT_KEY_BITHAM_30_BLACK,
    .bg   = GColorBlackARGB8,
    .t_fg = GColorWhiteARGB8,
    .d_fg = GColorWhiteARGB8,
    .b_fg = 0
};

signed
main (void) {

    init(); update_time(); app_event_loop(); cleanup();
}

void
init (void) {

    state.w = window_create();
    window_set_background_color(state.w, toGColor8(state.bg));
    window_stack_push(state.w, true);

    init_text(&state.t, state.t_fg, GRect(0, 20, 144, 60 ), state.t_fn);
    init_text(&state.d, state.d_fg, GRect(0, 80, 144, 120), state.d_fn);

    tick_timer_service_subscribe(MINUTE_UNIT, tick);
}

void
init_text (TextLayer ** t, uint8_t fg, GRect r, const char * f) {

    *t = text_layer_create(r);
    text_layer_set_background_color(*t, toGColor8(GColorClearARGB8));
    text_layer_set_text_color(*t, toGColor8(fg));
    text_layer_set_font(*t, fonts_get_system_font(f));
    text_layer_set_text_alignment(*t, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(state.w), text_layer_get_layer(*t));
}

void
cleanup (void) {

    text_layer_destroy(state.t);
    text_layer_destroy(state.d);
    window_destroy(state.w);
}

void
tick (struct tm * ticks, TimeUnits deltat) {

    update_time();
}

void
update_time (void) {

    time_t tmp = time(NULL);
    struct tm * ticks = localtime(&tmp);
    const char * hr_fmt = clock_is_24h_style() ? "%H.%M" : "%I:%M";
    static char hrs [6];
    strftime(hrs, 6, hr_fmt, ticks);
    text_layer_set_text(state.t, hrs);

    const char * dt_fmt = "%a, %d %b %Y";
    static char dte [17];
    strftime(dte, 17, dt_fmt, ticks);
    text_layer_set_text(state.d, dte);
}

// vim: set ts=4 sw=4 et:
