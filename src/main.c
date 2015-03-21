#include <pebble.h>
#include "text_formal.h"

static Window *window;
static TextLayer *text_layer;
static GFont time_font;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char buffer[32];
  memset(buffer, 0, 32);
  say_formal(buffer, tick_time->tm_hour, tick_time->tm_min);

  text_layer_set_text(text_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OLD_TYPER_28));

  text_layer = text_layer_create(GRect(5, 20, window_bounds.size.w - 5, window_bounds.size.h));
  text_layer_set_font(text_layer, time_font);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  // subscribe to updates
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // force update for the first time
  update_time();
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
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
