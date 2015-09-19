#include "main.h"

static struct tickless state = {
    .w = 0, .t = 0, .d = 0, .b = 0,
    .bg = GColorBlackARGB8,
    .t_fg = GColorWhiteARGB8,
    .d_fg = GColorWhiteARGB8,
    .b_fg = 0
};

signed main (void) {

    init();
    app_event_loop();
    cleanup();
}

void init (void) {

    state.w = window_create();
    window_set_background_color(state.w, toGColor8(state.bg));
    window_stack_push(state.w, true);

    state.t = text_layer_create(GRect(0, 20, 144, 60));
    text_layer_set_background_color(state.t, toGColor8(GColorClearARGB8));
    text_layer_set_text_color(state.t, toGColor8(state.t_fg));
    text_layer_set_font(state.t, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
    text_layer_set_text_alignment(state.t, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(state.w), text_layer_get_layer(state.t));

    //state.d = text_layer_create(GRect(0, 60, 144, 100));
    //text_layer_set_background_color(state.d, toGColor8(GColorClearARGB8));
    //text_layer_set_text_color(state.d, toGColor8(state.d_fg));
    //text_layer_set_font(state.d, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
    //text_layer_set_text_alignment(state.d, GTextAlignmentCenter);
    //layer_add_child(window_get_root_layer(state.w), text_layer_get_layer(state.d));

    tick_timer_service_subscribe(MINUTE_UNIT, tick);
    update_time();
}

void cleanup (void) {

    text_layer_destroy(state.t);
    window_destroy(state.w);
}

void tick (struct tm * ticks, TimeUnits deltat) {

    update_time();
}

void update_time (void) {

    time_t tmp = time(NULL);
    struct tm * ticks = localtime(&tmp);
    static char buf [6] = "00.00";

    strftime(buf, 6, clock_is_24h_style() ? "%H.%M" : "%I:%M", ticks);
    text_layer_set_text(state.t, buf);
}

// vim: set ts=4 sw=4 et:
