#define ENABLE_LOGGING  // Uncomment to enable logging

#ifndef SCREENS_H
#define SCREENS_H

#include <lvgl.h>

// Function prototypes for screen creation and event handling
void create_main_screen();
void create_screen_2();
void create_screen_3();
void create_top_layer();
void create_cpu_usage_display(void);

void show_main_screen(lv_event_t *e);
void show_screen_2(lv_event_t *e);
void show_screen_3(lv_event_t *e);

// Declare LVGL screen objects
extern lv_obj_t *main_screen;
extern lv_obj_t *screen_2;
extern lv_obj_t *screen_3;
extern lv_obj_t *home_button;

#endif