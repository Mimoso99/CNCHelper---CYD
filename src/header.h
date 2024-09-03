#define ENABLE_LOGGING  // Uncomment to enable logging

#ifndef SCREENS_H
#define SCREENS_H

#include <lvgl.h>

// Function prototypes for screen creation and event handling
// Function prototypes for screen creation and event handling
void create_home_screen();
void create_parameters_screen();
void create_parameters_tool_screen();
void create_parameters_job_screen();
void create_settings_screen();
void create_top_layer();
void create_system_layer(void);

void show_home_screen(lv_event_t *e);
void show_parameters_screen(lv_event_t *e);
void show_parameters_tool_screen(lv_event_t *e);
void show_parameters_job_screen(lv_event_t *e);
void show_settings_screen(lv_event_t *e);

// Declare LVGL screen objects
extern lv_obj_t *home_screen;
extern lv_obj_t *parameters_screen;
extern lv_obj_t *parameters_tool_screen;
extern lv_obj_t *job_screen;
extern lv_obj_t *settings_screen;
extern lv_obj_t *home_button;

#endif