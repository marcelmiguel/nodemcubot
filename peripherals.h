// Peripherals configuration params

// BME280 constants
#define SEALEVELPRESSURE_HPA (1013.25)
#define SENSOR_TEMP_ADDRESS 0x76

// SSD1306 constants
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADRRESS 0x3C

// Serial port speed
#define SERIAL_BAUD 115200

// IO control
// D1  & D2 already used for i2c comms
#define RELAY1IO 0 // D3 on nodemcu, MANUAL SWITCH POSITION
#define RELAY2IO 2 // D4 on nodemcu, SIM SWITCH POSITION
#define SWITCH1IO 14 // D5 on nodemcu
#define SWITCH2IO 12 // D6 on nodemcu

// Specific logic
#define SW_MANUAL "MANUAL"
#define SW_SIM "SIM"