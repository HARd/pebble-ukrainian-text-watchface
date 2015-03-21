#include <pebble.h>
#include "text_formal.h"

#define TIME_BUFFER_SIZE 32

static Window *window;
static TextLayer *text_layer;
static GFont time_font;
static char time_buffer[TIME_BUFFER_SIZE];

static void update_time(struct tm *t) {
  say_formal(time_buffer, TIME_BUFFER_SIZE, t->tm_hour, t->tm_min);
  //strcat(time_buffer, "привіт");
  text_layer_set_text(text_layer, time_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPEN_SANS_BOLD_36));

  text_layer = text_layer_create(GRect(5, 20, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(text_layer, time_font);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  // force update for the first time
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  update_time(t);

  // subscribe to updates
  tick_timer_service_subscribe(MINUTE_UNIT, &tick_handler);
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
  fonts_unload_custom_font(time_font);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
