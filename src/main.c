#include "main.h"

signed
main (void) {

    init();

    char long_times [23] = "";
    strftime(long_times, 22, "%Y|%a %d %b|(%Z)", ticks);
    long_times[4] = '\0';
    long_times[15] = '\0';

    text_layer_set_text(state.y, long_times);
    text_layer_set_text(state.d, long_times+5);
    text_layer_set_text(state.z, long_times+16);

    app_event_loop();
    cleanup();
}

void
init (void) {

    state.w = window_create();
    window_set_background_color(state.w, toGColor8(state.bg));
    window_stack_push(state.w, true);

    Layer * rt_layer = window_get_root_layer(state.w);
    GRect rt_bounds = layer_get_bounds(rt_layer),
          tz_bounds, tm_bounds, dt_bounds, yr_bounds;

    tz_bounds = tm_bounds = dt_bounds = yr_bounds = rt_bounds;
    tz_bounds.origin.y = rt_bounds.size.h / 8;
    tm_bounds.origin.y = rt_bounds.size.h / 4;
    dt_bounds.origin.y = rt_bounds.size.h / 2;
    yr_bounds.origin.y = rt_bounds.size.h - rt_bounds.size.h / 3;

    init_text(&state.z, tz_bounds, state.z_fn);
    init_text(&state.t, tm_bounds, state.t_fn);
    init_text(&state.d, dt_bounds, state.d_fn);
    init_text(&state.y, yr_bounds, state.y_fn);

    //state.b = bitmap_layer_create(GRect(0, 60, 144, 80));

    tick_timer_service_subscribe(MINUTE_UNIT, tick);

    tm_fmt[1] += !clock_is_24h_style();
    update_time();
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
    text_layer_destroy(state.z);
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
    strftime(str_buffer, 6, tm_fmt, ticks);
    text_layer_set_text(state.t, str_buffer);
}

// vim: set ts=4 sw=4 et:
