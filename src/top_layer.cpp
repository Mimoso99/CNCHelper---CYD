#include "header.h"

// Declare screens and objects

lv_obj_t *home_button;

// Forward declarations for callback functions
void create_top_layer();

// Create a home button in the top layer
void create_top_layer() {
    lv_obj_t *top_layer = lv_layer_top();

    home_button = lv_btn_create(top_layer);
    lv_obj_set_size(home_button, 60, 40);
    lv_obj_align(home_button, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(home_button, show_main_screen, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_home = lv_label_create(home_button);
    lv_label_set_text(label_home, "Home");
    lv_obj_center(label_home);
}