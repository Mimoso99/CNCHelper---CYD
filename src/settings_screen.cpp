#include "header.h"

// Declare the settings screen object
lv_obj_t *settings_screen;

void create_settings_screen() {
    settings_screen = lv_obj_create(NULL);

    lv_obj_t *label = lv_label_create(settings_screen);
    lv_label_set_text(label, "Settings Screen");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void show_settings_screen(lv_event_t *e) {
    lv_scr_load(settings_screen);
}
