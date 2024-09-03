#include "header.h"
#include <Arduino.h>

// Declare screen and objects
lv_obj_t *parameters_screen;
lv_obj_t *material_buttons[6];
lv_obj_t *selected_material_label;

// Enum to represent the material options
enum Material {
    WOOD,
    CORK,
    PLASTIC,
    MDF,
    ALUMINIUM,
    MY_MATERIALS,
    NONE
};

// Keep track of the currently selected material
Material selected_material = NONE;

// Forward declaration of the callback functions
void material_button_event_cb(lv_event_t *e);
void proceed_to_next_screen(lv_event_t *e);

void create_parameters_screen() {
    parameters_screen = lv_obj_create(NULL);

    // Create the label identifying this screen
    lv_obj_t *label_title = lv_label_create(parameters_screen);
    lv_label_set_text(label_title, "Parameters Wizard\nPick a Material");
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 20);

    // Create a grid for the material buttons
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    lv_obj_t *grid = lv_obj_create(parameters_screen);
    lv_obj_set_layout(grid, LV_LAYOUT_GRID);
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
    lv_obj_set_size(grid, 240, 160);
    lv_obj_align(grid, LV_ALIGN_CENTER, 0, 0);

    // Material names
    const char *material_names[] = {"Wood", "Cork", "Plastic", "MDF", "Aluminium", "MyMaterials"};

    // Create the buttons in the grid
    for (int i = 0; i < 6; i++) {
        material_buttons[i] = lv_btn_create(grid);
        lv_obj_set_grid_cell(material_buttons[i], LV_GRID_ALIGN_STRETCH, i % 3, 1, LV_GRID_ALIGN_STRETCH, i / 3, 1);
        lv_obj_t *label = lv_label_create(material_buttons[i]);
        lv_label_set_text(label, material_names[i]);
        lv_obj_center(label);

        lv_obj_add_event_cb(material_buttons[i], material_button_event_cb, LV_EVENT_CLICKED, (void *)(intptr_t)i);
    }

    // Create a button to proceed to the next screen
    lv_obj_t *btn_next = lv_btn_create(parameters_screen);
    lv_obj_set_size(btn_next, 120, 40);
    lv_obj_align(btn_next, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_t *label_next = lv_label_create(btn_next);
    lv_label_set_text(label_next, "Pick a Tool");
    lv_obj_center(label_next);

    lv_obj_add_event_cb(btn_next, proceed_to_next_screen, LV_EVENT_CLICKED, NULL);
}

// Callback function for material buttons
void material_button_event_cb(lv_event_t *e) {
    lv_obj_t *btn = (lv_obj_t *)lv_event_get_target(e);  // Explicitly cast to lv_obj_t*
    int btn_id = (intptr_t)lv_event_get_user_data(e);

    // Deselect the previously selected button
    if (selected_material != NONE) {
        lv_obj_clear_state(material_buttons[selected_material], LV_STATE_CHECKED);
    }

    // Select the new button
    lv_obj_add_state(btn, LV_STATE_CHECKED);
    selected_material = (Material)btn_id;
}

// Callback function to proceed to the next screen
void proceed_to_next_screen(lv_event_t *e) {
    if (selected_material != NONE) {
        // Here you would load the next screen, e.g.:
        // lv_scr_load(tool_screen);
    } else {
        // Optionally, you could show a message asking the user to select a material first
        Serial.println("Please select a material before proceeding.");
    }
}

// Function to load the Parameters screen
void show_parameters_screen(lv_event_t *e) {
    create_parameters_screen();
    lv_scr_load(parameters_screen);
}
