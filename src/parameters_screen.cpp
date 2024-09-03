#include "header.h"

// Declare the parameters screen object
lv_obj_t *parameters_screen;

void create_parameters_screen() {
    parameters_screen = lv_obj_create(NULL);

    lv_obj_t *label = lv_label_create(parameters_screen);
    lv_label_set_text(label, "Parameters Screen");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void show_parameters_screen(lv_event_t *e) {
    lv_scr_load(parameters_screen);
}
