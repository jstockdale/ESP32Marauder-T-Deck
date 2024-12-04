// ST7789 240 x 280 display with no chip select line
#define USER_SETUP_ID 210

#define ST7789_DRIVER     // Configure all registers

#define TFT_WIDTH  320
#define TFT_HEIGHT 240

// #define CGRAM_OFFSET      // Library will add offsets required

#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
// #define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red
#define INIT_SEQUENCE_2         //Different gamma values
// #define TFT_INVERSION_ON
// #define TFT_INVERSION_OFF  //For the first sample of T-Deck need to turn on color inversion

// DSTIKE stepup
//#define TFT_DC    23
//#define TFT_RST   32
//#define TFT_MOSI  26
//#define TFT_SCLK  27

// Generic ESP32 setup
#define TFT_MISO 38
#define TFT_MOSI 41
#define TFT_SCLK 40
#define TFT_CS   12 // Not connected
#define TFT_DC   11
#define TFT_RST  -1  // Connect reset to ensure display initialises
#define TFT_BACKLIGHT_ON 1
#define TFT_BL     42    //Turn off backlight function by default


#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT


// #define SPI_FREQUENCY  27000000
#define SPI_FREQUENCY  40000000

#define SPI_READ_FREQUENCY  20000000

#define SPI_TOUCH_FREQUENCY  2500000

// #define SUPPORT_TRANSACTIONS

#define BOARD_POWERON       10

#define BOARD_I2S_WS        5
#define BOARD_I2S_BCK       7
#define BOARD_I2S_DOUT      6

#define BOARD_I2C_SDA       18
#define BOARD_I2C_SCL       8

#define BOARD_BAT_ADC       4

#define BOARD_TOUCH_INT     16
#define BOARD_KEYBOARD_INT  46

#define BOARD_SDCARD_CS     39
#define BOARD_TFT_CS        12
#define RADIO_CS_PIN        9

#define BOARD_TFT_DC        11
#define BOARD_TFT_BACKLIGHT 42

#define BOARD_SPI_MOSI      41
#define BOARD_SPI_MISO      38
#define BOARD_SPI_SCK       40

#define BOARD_BOOT          0
#define BOARD_TBOX_G02       3
#define BOARD_TBOX_G01     2
#define BOARD_TBOX_G04     1
#define BOARD_TBOX_G03    15

#define BOARD_ES7210_MCLK   48
#define BOARD_ES7210_LRCK   21
#define BOARD_ES7210_SCK    47
#define BOARD_ES7210_DIN    14

#define RADIO_BUSY_PIN    13
#define RADIO_RST_PIN     17
#define RADIO_DIO1_PIN    45

#define BOARD_BOOT_PIN      0

#define BOARD_BL_PIN        42
