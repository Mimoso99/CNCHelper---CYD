#include "header.h"
#include <Arduino.h>

// Declare the screen and objects
lv_obj_t *parameters_tool_screen;
lv_obj_t *roller_diameter;
lv_obj_t *roller_teeth;
lv_obj_t *dropdown_tip;
lv_obj_t *dropdown_flute;

// Forward declaration of the callback function
void proceed_to_pick_job(lv_event_t *e);

void create_parameters_tool_screen() {
    parameters_tool_screen = lv_obj_create(NULL);

    // Create the label identifying this screen
    lv_obj_t *label_title = lv_label_create(parameters_tool_screen);
    lv_label_set_text(label_title, "Parameters Wizard");
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 20);

    // Create a roller for "Tool Diameter"
    lv_obj_t *label_diameter = lv_label_create(parameters_tool_screen);
    lv_label_set_text(label_diameter, "Tool Diameter");
    lv_obj_align(label_diameter, LV_ALIGN_TOP_LEFT, 20, 60);

    roller_diameter = lv_roller_create(parameters_tool_screen);
    lv_roller_set_options(roller_diameter, "2\n3\n4\n5\n6\n8", LV_ROLLER_MODE_INFINITE);
    lv_obj_align(roller_diameter, LV_ALIGN_TOP_LEFT, 20, 90);
    lv_roller_set_visible_row_count(roller_diameter, 3);

    // Create a roller for "Number of Teeth"
    lv_obj_t *label_teeth = lv_label_create(parameters_tool_screen);
    lv_label_set_text(label_teeth, "Number of Teeth");
    lv_obj_align(label_teeth, LV_ALIGN_TOP_RIGHT, -20, 60);

    roller_teeth = lv_roller_create(parameters_tool_screen);
    lv_roller_set_options(roller_teeth, "1\n2\n3", LV_ROLLER_MODE_INFINITE);
    lv_obj_align(roller_teeth, LV_ALIGN_TOP_RIGHT, -20, 90);
    lv_roller_set_visible_row_count(roller_teeth, 3);

    // Create a dropdown for "Tool Tip"
    lv_obj_t *label_tip = lv_label_create(parameters_tool_screen);
    lv_label_set_text(label_tip, "Tool Tip");
    lv_obj_align(label_tip, LV_ALIGN_TOP_LEFT, 20, 160);

    dropdown_tip = lv_dropdown_create(parameters_tool_screen);
    lv_dropdown_set_options(dropdown_tip, "Flat\nRounded\nV");
    lv_obj_align(dropdown_tip, LV_ALIGN_TOP_LEFT, 20, 190);

    // Create a dropdown for "Tool Flute"
    lv_obj_t *label_flute = lv_label_create(parameters_tool_screen);
    lv_label_set_text(label_flute, "Tool Flute");
    lv_obj_align(label_flute, LV_ALIGN_TOP_RIGHT, -20, 160);

    dropdown_flute = lv_dropdown_create(parameters_tool_screen);
    lv_dropdown_set_options(dropdown_flute, "Straight\nUp Spiral\nDown Spiral");
    lv_obj_align(dropdown_flute, LV_ALIGN_TOP_RIGHT, -20, 190);

    // Create a button to proceed to the next screen
    lv_obj_t *btn_next = lv_btn_create(parameters_tool_screen);
    lv_obj_set_size(btn_next, 120, 40);
    lv_obj_align(btn_next, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *label_next = lv_label_create(btn_next);
    lv_label_set_text(label_next, "Pick a Job");
    lv_obj_center(label_next);

    lv_obj_add_event_cb(btn_next, proceed_to_pick_job, LV_EVENT_CLICKED, NULL);
}

// Callback function to proceed to the next screen
void proceed_to_pick_job(lv_event_t *e) {
    // Retrieve the selected options
    int diameter = lv_roller_get_selected(roller_diameter);
    int teeth = lv_roller_get_selected(roller_teeth);
    const char *tip = lv_dropdown_get_text(dropdown_tip);
    const char *flute = lv_dropdown_get_text(dropdown_flute);

    // Here you would process these values or pass them to the next screen

    // For now, just print them to the serial console
    Serial.printf("Diameter: %d\n", diameter);
    Serial.printf("Teeth: %d\n", teeth);
    Serial.printf("Tip: %s\n", tip);
    Serial.printf("Flute: %s\n", flute);

    // Load the next screen, e.g., job selection screen
    // lv_scr_load(job_screen);
}

void show_parameters_tool_screen(lv_event_t *e) {
    lv_scr_load(parameters_tool_screen);
}
