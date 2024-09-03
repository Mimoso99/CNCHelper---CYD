#include "header.h"
#include <Arduino.h>

// Declare screen and objects
lv_obj_t *job_screen;
lv_obj_t *priority_slider;

// Forward declaration of the callback functions
void create_parameters_job_screen();
void calculate_job(lv_event_t *e);

void create_parameters_job_screen() {
    job_screen = lv_obj_create(NULL);

    // Create the label identifying this screen
    lv_obj_t *label_title = lv_label_create(job_screen);
    lv_label_set_text(label_title, "Parameters Wizard");
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 10);

    // Create the slider for job priority
    priority_slider = lv_slider_create(job_screen);
    lv_slider_set_range(priority_slider, 0, 6);  // 7 positions
    lv_slider_set_value(priority_slider, 3, LV_ANIM_OFF);  // Default to mid-position
    lv_obj_set_size(priority_slider, 200, 20);
    lv_obj_align(priority_slider, LV_ALIGN_CENTER, 0, 0);

    // Create the labels for the slider
    lv_obj_t *label_finish = lv_label_create(job_screen);
    lv_label_set_text(label_finish, "Finish");
    lv_obj_align(label_finish, LV_ALIGN_BOTTOM_LEFT, lv_obj_get_width(priority_slider) / 2 - 70, lv_obj_get_height(priority_slider) + 10);

    lv_obj_t *label_safe = lv_label_create(job_screen);
    lv_label_set_text(label_safe, "Safe");
    lv_obj_align(label_safe, LV_ALIGN_BOTTOM_LEFT, lv_obj_get_width(priority_slider) / 2 - 20, lv_obj_get_height(priority_slider) + 10);

    lv_obj_t *label_fast = lv_label_create(job_screen);
    lv_label_set_text(label_fast, "Fast");
    lv_obj_align(label_fast, LV_ALIGN_BOTTOM_RIGHT, -lv_obj_get_width(priority_slider) / 2 + 70, lv_obj_get_height(priority_slider) + 10);

    // Create the button to calculate and proceed to the next screen
    lv_obj_t *btn_calculate = lv_btn_create(job_screen);
    lv_obj_set_size(btn_calculate, 120, 40);
    lv_obj_align(btn_calculate, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *label_calculate = lv_label_create(btn_calculate);
    lv_label_set_text(label_calculate, "Calculate");
    lv_obj_center(label_calculate);

    lv_obj_add_event_cb(btn_calculate, calculate_job, LV_EVENT_CLICKED, NULL);
}

// Callback function to handle the Calculate button
void calculate_job(lv_event_t *e) {
    // Here you would get the selected job priority and proceed
    // For example:
    int priority = lv_slider_get_value(priority_slider);
    Serial.print("Selected job priority: ");
    Serial.println(priority);

    // Load the next screen if needed
    // lv_scr_load(next_screen);
}
