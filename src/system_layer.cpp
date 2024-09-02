// System Layer in LVGL. Cursor level, always on top, can be used to display information like CPU usage, or even for debugging
#include "header.h"
#include <stdio.h>

// Forward declaration
uint8_t get_cpu_usage(void);

// Global label for CPU usage
lv_obj_t *cpu_usage_label;

// Function to update CPU usage display
static void update_cpu_usage(lv_timer_t *timer)
{
    // Here, you should have a way to get the CPU usage, 
    // e.g., `uint8_t cpu_usage = get_cpu_usage();`
    uint8_t cpu_usage = get_cpu_usage();  // Placeholder function

    // Format the CPU usage into a string
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "CPU: %d%%", cpu_usage);

    // Set the text of the label to display the CPU usage
    lv_label_set_text(cpu_usage_label, buffer);
}

// Function to create the CPU usage display on the system layer
void create_cpu_usage_display(void)
{
    // Create a system layer
    lv_obj_t *sys_layer = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(sys_layer);  // Remove background and other styles
    lv_obj_set_size(sys_layer, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_set_style_bg_opa(sys_layer, LV_OPA_TRANSP, 0);
    
    // Create a label for CPU usage
    cpu_usage_label = lv_label_create(sys_layer);
    lv_obj_align(cpu_usage_label, LV_ALIGN_TOP_RIGHT, -10, 10); // Align at top-right corner

    // Create a periodic timer to update the CPU usage every second
    lv_timer_create(update_cpu_usage, 1000, NULL);
}

uint8_t get_cpu_usage(void)
{
    // Placeholder implementation; replace with actual CPU usage retrieval code.
    // For example, reading from a specific hardware register or OS API.
    return 42; // For testing, returning a constant value.
}