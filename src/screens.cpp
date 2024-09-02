#include "header.h"

// Declare screens and objects
lv_obj_t *main_screen;
lv_obj_t *screen_2;
lv_obj_t *screen_3;

// Forward declarations for callback functions
void show_main_screen(lv_event_t *e);
void show_screen_2(lv_event_t *e);
void show_screen_3(lv_event_t *e);

void create_main_screen();
void create_screen_2();
void create_screen_3();


void create_main_screen() {
    main_screen = lv_obj_create(NULL);

    // Button to go to Screen 2
    lv_obj_t *btn_screen_2 = lv_btn_create(main_screen);
    lv_obj_align(btn_screen_2, LV_ALIGN_CENTER, -80, 0);
    lv_obj_set_size(btn_screen_2, 100, 50);
    lv_obj_add_event_cb(btn_screen_2, show_screen_2, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_btn_2 = lv_label_create(btn_screen_2);
    lv_label_set_text(label_btn_2, "Screen 2");
    lv_obj_center(label_btn_2);

    // Button to go to Screen 3
    lv_obj_t *btn_screen_3 = lv_btn_create(main_screen);
    lv_obj_align(btn_screen_3, LV_ALIGN_CENTER, 80, 0);
    lv_obj_set_size(btn_screen_3, 100, 50);
    lv_obj_add_event_cb(btn_screen_3, show_screen_3, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label_btn_3 = lv_label_create(btn_screen_3);
    lv_label_set_text(label_btn_3, "Screen 3");
    lv_obj_center(label_btn_3);
}

void create_screen_2() {
    screen_2 = lv_obj_create(NULL);

    lv_obj_t *label = lv_label_create(screen_2);
    lv_label_set_text(label, "Hello");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void create_screen_3() {
    screen_3 = lv_obj_create(NULL);

    lv_obj_t *label = lv_label_create(screen_3);
    lv_label_set_text(label, "World");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void show_main_screen(lv_event_t *e) {
    lv_scr_load(main_screen);
}

void show_screen_2(lv_event_t *e) {
    lv_scr_load(screen_2);
}

void show_screen_3(lv_event_t *e) {
    lv_scr_load(screen_3);
}