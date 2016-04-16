#include "main.h"

signed
main (void) {

    init(); update_time(); app_event_loop(); cleanup();
}

void
init (void) {

    state.w = window_create();
    window_set_background_color(state.w, toGColor8(state.bg));
    window_stack_push(state.w, true);

    init_text(&state.t, GRect(0, 40,  144, 60 ), state.t_fn);
    init_text(&state.d, GRect(0, 80,  144, 108), state.d_fn);
    init_text(&state.y, GRect(0, 108, 144, 120), state.y_fn);

    // state.b = bitmap_layer_create(GRect(0, 60, 144, 80));

    tick_timer_service_subscribe(MINUTE_UNIT, tick);

    tm_fmt = clock_is_24h_style() ? "%H.%M|%a %d %b|%Y" : "%I.%M|%a %d %b|%Y";
}

void
init_text (TextLayer ** t, GRect r, const char * f) {

    *t = text_layer_create(r);
    text_layer_set_background_color(*t, toGColor8(GColorClearARGB8));
    text_layer_set_text_color(*t, toGColor8(state.fg));
    text_layer_set_font(*t, fonts_get_system_font(f));
    text_layer_set_text_alignment(*t, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(state.w), text_layer_get_layer(*t));
}

void
cleanup (void) {

    tick_timer_service_unsubscribe();
    //bitmap_layer_destroy(state.b);
    text_layer_destroy(state.t);
    text_layer_destroy(state.d);
    text_layer_destroy(state.y);
    window_destroy(state.w);
}

void
tick (struct tm * ticks, TimeUnits deltat) {

    update_time();
}

void
update_time (void) {

    tmp = time(NULL);
    ticks = localtime(&tmp);
    strftime(str_buffer, 23, tm_fmt, ticks);
    str_buffer[5] = '\0';
    str_buffer[16] = '\0';
    text_layer_set_text(state.t, str_buffer);
    text_layer_set_text(state.d, str_buffer+6);
    text_layer_set_text(state.y, str_buffer+17);
}

// vim: set ts=4 sw=4 et:
