#include "header.h"

// Declare the home screen object
lv_obj_t *home_screen;

void create_home_screen() {
    home_screen = lv_obj_create(NULL);

    // Button to go to Parameters Screen
    lv_obj_t *btn_parameters = lv_btn_create(home_screen);
    lv_obj_align(btn_parameters, LV_ALIGN_CENTER, -80, 0);
    lv_obj_set_size(btn_parameters, 100, 50);
    lv_obj_add_event_cb(btn_parameters, show_parameters_screen, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_btn_parameters = lv_label_create(btn_parameters);
    lv_label_set_text(label_btn_parameters, "Parameters");
    lv_obj_center(label_btn_parameters);

    // Button to go to Settings Screen
    lv_obj_t *btn_settings = lv_btn_create(home_screen);
    lv_obj_align(btn_settings, LV_ALIGN_CENTER, 80, 0);
    lv_obj_set_size(btn_settings, 100, 50);
    lv_obj_add_event_cb(btn_settings, show_settings_screen, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_btn_settings = lv_label_create(btn_settings);
    lv_label_set_text(label_btn_settings, "Settings");
    lv_obj_center(label_btn_settings);
}

void show_home_screen(lv_event_t *e) {
    lv_scr_load(home_screen);
}