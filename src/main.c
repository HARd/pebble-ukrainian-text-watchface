#include <pebble.h>
#include "main.h"
#include "text_formal.h"

static Window *window;
static InverterLayer *inverter_layer;
static TextLayer *hours_text_layer;
static TextLayer *minutes_text_layer;
static GFont time_font_bold_40;
static GFont time_font_bold_25;
static GFont time_font_bold_22;
static GFont time_font_regular;
static char hours_buffer[TIME_BUFFER_SIZE / 2];
static char minutes_buffer[TIME_BUFFER_SIZE];

static void update_time(struct tm *t) {
  say_formal(hours_buffer, minutes_buffer, t->tm_hour, t->tm_min);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "hours: %s, size %d", hours_buffer, strlen(hours_buffer) / 2);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "minutes: %s, size %d", minutes_buffer, strlen(minutes_buffer) / 2);

  size_t hours_buffer_length = strlen(hours_buffer) / 2;
  text_layer_set_font(hours_text_layer, time_font_bold_40);
  if (hours_buffer_length >= 6) {
    text_layer_set_font(hours_text_layer, time_font_bold_25);
  }
  if (hours_buffer_length >= 10) {
    text_layer_set_font(hours_text_layer, time_font_bold_22);
  }

  text_layer_set_text(hours_text_layer, hours_buffer);
  text_layer_set_text(minutes_text_layer, minutes_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
}

static void add_layers(Layer *window_layer) {
  GRect window_bounds = layer_get_bounds(window_layer);

  inverter_layer = inverter_layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));

  hours_text_layer = text_layer_create(
      GRect(0, window_bounds.size.h / 2 - 45, window_bounds.size.w, 45)
  );

  minutes_text_layer = text_layer_create(
      GRect(0, window_bounds.size.h / 2, window_bounds.size.w, window_bounds.size.h)
  );

  text_layer_set_font(minutes_text_layer, time_font_regular);

  text_layer_set_text_alignment(hours_text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(minutes_text_layer, GTextAlignmentCenter);

  layer_add_child(window_layer, text_layer_get_layer(hours_text_layer));
  layer_add_child(window_layer, text_layer_get_layer(minutes_text_layer));
  layer_add_child(window_layer, inverter_layer_get_layer(inverter_layer));
}

static void remove_layers() {
  inverter_layer_destroy(inverter_layer);
  text_layer_destroy(hours_text_layer);
  text_layer_destroy(minutes_text_layer);
}

static void load_fonts() {
  time_font_bold_40 = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_OPEN_SANS_BOLD_40)
  );
  time_font_bold_25 = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_OPEN_SANS_BOLD_25)
  );
  time_font_bold_22 = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_OPEN_SANS_BOLD_22)
  );
  time_font_regular = fonts_load_custom_font(
      resource_get_handle(RESOURCE_ID_FONT_OPEN_SANS_REGULAR_25)
  );
}

static void unload_fonts() {
  fonts_unload_custom_font(time_font_bold_40);
  fonts_unload_custom_font(time_font_bold_25);
  fonts_unload_custom_font(time_font_bold_22);
//  fonts_unload_custom_font(time_font_regular);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  load_fonts();

  add_layers(window_layer);

  // force update for the first time
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  update_time(t);

  // subscribe to updates
  tick_timer_service_subscribe(MINUTE_UNIT, &tick_handler);
}

static void window_unload(Window *window) {
  remove_layers();
  unload_fonts();
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
