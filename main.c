/*
8051_Load_Control_System/
│
├── 📄 main.c                 - Core application logic
├── 📄 lcd.h                  - LCD display interface
├── 📄 lcd.c                  - LCD driver (I2C)
├── 📄 keypad.h               - Keypad interface
├── 📄 keypad.c               - 4x4 matrix keypad driver
├── 📄 uart.h                 - UART (Bluetooth) interface
├── 📄 uart.c                 - UART communication driver
├── 📄 password.h             - Password authentication interface
├── 📄 password.c             - Password verification logic
├── 📄 delay.h                - Delay function declarations
├── 📄 delay.c                - Millisecond delay implementation
├── 📄 i2c.h                  - I2C protocol interface
├── 📄 i2c.c                  - I2C communication driver
└── 📄 README.md              - Project documentation
*/

#include <REG51.H>
#include "password.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "delay.h"

/* Hardware Definitions */
sbit Load_1 = P0^0;
sbit Load_2 = P0^1;
sbit Load_3 = P0^2;
sbit Load_4 = P0^3;
sbit Flame_Sensor = P3^3;  // Flame sensor on P3.3 (INT1)

/* Function Prototypes */
void initialize_system(void);
void display_load_states(unsigned char load_state[4]);
void check_flame_sensor(unsigned char load_state[4]);
void process_command(char cmd, unsigned char load_state[4]);
void update_outputs(unsigned char load_state[4]);

/* Main Application */
void main(void) {
    unsigned char load_state[4] = {0, 0, 0, 0}; // All loads OFF by default
    unsigned char keypad_cmd, bt_cmd;
    
    initialize_system();
    
    // Password authentication
    password_entry_screen();
    
    // System ready message
    lcd_cmd(0x01);
    lcd_string("System Ready");
    delay_ms(50);
    display_load_states(load_state);
    
    // Main control loop
    while (1) {
        check_flame_sensor(load_state);
        
        // Check keypad input
        keypad_cmd = keypad_scan();
        if (keypad_cmd) {
            process_command(keypad_cmd, load_state);
            if (!Flame_Sensor) {
                update_outputs(load_state);
            }
        }
        
        // Check Bluetooth input
        bt_cmd = UART_Receive();
        if (bt_cmd) {
            process_command(bt_cmd, load_state);
            if (!Flame_Sensor) {
                update_outputs(load_state);
            }
        }
    }
}

/* System Initialization */
void initialize_system(void) {
    // Safety first - all loads OFF
    Load_1 = Load_2 = Load_3 = Load_4 = 0;
    
    // Initialize peripherals
    lcd_init();
    UART_Init();
		
		// Show initialization message
    lcd_cmd(0x01);
    lcd_string("Initializing...");
		delay_ms(50);
}

/* Process Control Commands */
void process_command(char cmd, unsigned char load_state[4]) {
    switch (cmd) {
        case '0':  // All OFF
            load_state[0] = load_state[1] = load_state[2] = load_state[3] = 0;
            break;
        case '1':
            load_state[0] = !load_state[0];
            break;
        case '2':
            load_state[1] = !load_state[1];
            break;
        case '3':
            load_state[2] = !load_state[2];
            break;
        case '4':
            load_state[3] = !load_state[3];
            break;
        case '5':  // All ON
            load_state[0] = load_state[1] = load_state[2] = load_state[3] = 1;
            break;
    }
}

/* Update Physical Outputs */
void update_outputs(unsigned char load_state[4]) {
    Load_1 = load_state[0];
    Load_2 = load_state[1];
    Load_3 = load_state[2];
    Load_4 = load_state[3];
    display_load_states(load_state);
}

/* LCD Display Update */
void display_load_states(unsigned char load_state[4]) {
    lcd_cmd(0x80);
    lcd_string("L1:");
    lcd_string(load_state[0] ? "ON " : "OFF");
    lcd_string(" L2:");
    lcd_string(load_state[1] ? "ON " : "OFF");

    lcd_cmd(0xC0);
    lcd_string("L3:");
    lcd_string(load_state[2] ? "ON " : "OFF");
    lcd_string(" L4:");
    lcd_string(load_state[3] ? "ON " : "OFF");
}

/* Flame Sensor Handling */
void check_flame_sensor(unsigned char load_state[4]) {
    static bit fire_mode = 0;
    
    if (Flame_Sensor && !fire_mode) {  // Rising edge detection
        lcd_cmd(0x01);
        lcd_string("WARNING! FIRE");
			  delay_ms(50);
				lcd_cmd(0xC0);
        lcd_string("ALL LOADS OFF");
			  delay_ms(50);
			
        // Emergency shutdown
        Load_1 = Load_2 = Load_3 = Load_4 = 0;
        load_state[0] = load_state[1] = load_state[2] = load_state[3] = 0;
        fire_mode = 1;
    }
    else if (!Flame_Sensor && fire_mode) {  // Falling edge detection
        lcd_cmd(0x01);
        lcd_string("System Normal");
        delay_ms(50);
        display_load_states(load_state);
        fire_mode = 0;
    }
}
