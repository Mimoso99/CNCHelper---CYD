// System Layer in LVGL. Cursor level, always on top, can be used to display information like CPU usage, or even for debugging
#include "header.h"
#include <Arduino.h>
#include <stdio.h>

// Forward declaration
uint8_t get_cpu_usage(void);

// Declare top layer and CPU usage label
lv_obj_t *top_layer;
lv_obj_t *cpu_usage_label;

// Function to update CPU usage display
static void update_cpu_usage(lv_timer_t *timer)
{
    uint8_t cpu_usage = get_cpu_usage();  // Replace with actual code to get CPU usage

    // Format and set the CPU usage text
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "CPU: %d%%", cpu_usage);
    lv_label_set_text(cpu_usage_label, buffer);
}

// Function to create the CPU usage display on the top layer
void create_cpu_usage_display(void)
{
    top_layer = lv_layer_top(); // Create top layer

    // Create and style the CPU usage label
    cpu_usage_label = lv_label_create(top_layer);
    lv_obj_align(cpu_usage_label, LV_ALIGN_TOP_RIGHT, -10, 10); // Position in top-right corner

    // Define and apply a style for the label
    static lv_style_t label_style;
    lv_style_init(&label_style);
    lv_style_set_text_color(&label_style, lv_color_white()); // Text color
    lv_style_set_text_font(&label_style, &lv_font_montserrat_14); // Font size

    lv_obj_add_style(cpu_usage_label, &label_style, 0);

    // Create a timer to update the CPU usage every second
    lv_timer_create(update_cpu_usage, 1000, NULL);
}

uint8_t get_cpu_usage(void)
{
    // Placeholder implementation; replace with actual CPU usage retrieval code.
    // For example, reading from a specific hardware register or OS API.
    return 42; // For testing, returning a constant value.
}