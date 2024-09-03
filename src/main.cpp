// This code prints the event of a button

// Libraries
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "header.h"

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

/* The touchscreen communicates with the board using SPI communication protocol.
We’ll use VSPI for the touchscreen. We start by initializing a new SPI class on VSPI
called touchscreenSPI. Then, create a XPT2046_Touchscreen object called touchscreen with the CS and
interrupt pins defined earlier.*/
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// Define screen size
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// Define buffer to draw on the display (this values are recommended by lvgl)
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// If logging is enabled, it will inform the user about what is happening in the library
#ifdef ENABLE_LOGGING
void log_print(lv_log_level_t level, const char * buf) {
    LV_UNUSED(level);
    Serial.println(buf);
    Serial.flush();
}
#endif

// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();

    // Advanced Touchscreen calibration
    float alpha_x, beta_x, alpha_y, beta_y, delta_x, delta_y;
    // REPLACE WITH YOUR OWN CALIBRATION VALUES
    // https://RandomNerdTutorials.com/touchscreen-calibration/
    alpha_x = 0.090;
    beta_x = -0.000;
    delta_x = -34.623;
    alpha_y = -0.000;
    beta_y = 0.066;
    delta_y = -15.602;

    x = alpha_x * p.x + beta_x * p.y + delta_x;
    // Clamp x between 0 and SCREEN_WIDTH -1
    x = max(0, x);
    x = min(SCREEN_WIDTH -1, x);

    y = alpha_y * p.x + beta_y * p.y + delta_y;
    // Clamp y between 0 and SCREEN_WIDTH -1
    y = max(0, y);
    y = min(SCREEN_WIDTH -1, y);

    /*// Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;*/

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;

    /* Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" |");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();*/
    }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

void setup() {
  // Prints the lvgl version that's being used (troubleshooting)
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);
  
  // Start LVGL
  lv_init();

  // Register print function for debugging
  #ifdef ENABLE_LOGGING
  lv_log_register_print_cb(log_print);
  #endif

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 1: touchscreen.setRotation(1);
  touchscreen.setRotation(3);

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  
  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Initialize and set the theme
  lv_theme_t * th = lv_theme_default_init(disp, 
                                              lv_palette_main(LV_PALETTE_BLUE),     // Primary color
                                              lv_palette_main(LV_PALETTE_CYAN),     // Secondary color
                                              true,                                 // Light or dark mode (true for dark)
                                              &lv_font_montserrat_18);               // 10, 14, 18, Small, Normal, Large font
      
  lv_disp_set_theme(disp, th);

  // Create the screens
  create_home_screen();
  create_parameters_screen();
  create_parameters_tool_screen();
  create_parameters_job_screen();
  create_settings_screen();
  
  // Set the main screen as the active screen
  lv_scr_load(home_screen);

  // Create the top layer (home button)
  create_top_layer();

  // Create the system layer (CPU usage and/or debugging)
  create_system_layer();
}

void loop() {
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);           // let this time pass
}