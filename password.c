#include "password.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"

unsigned char check_password(unsigned char *input) {
    const unsigned char password[PASSWORD_LENGTH] = {'1','2','3','4'};
    unsigned char i;
    
    for(i = 0; i < PASSWORD_LENGTH; i++) {
        if(input[i] != password[i]) {
            return 0; // Incorrect
        }
    }
    return 1; // Correct
}

void password_entry_screen(void) {
    unsigned char input[PASSWORD_LENGTH];
    unsigned char key, count = 0;
    unsigned char i;
    
    while(1) {
        lcd_cmd(0x01); // Clear display
        lcd_string("Enter Password:");
        lcd_cmd(0xC0); // Move to second line
        
        count = 0;
        for(i = 0; i < PASSWORD_LENGTH; i++) input[i] = 0;
        
        while(count < PASSWORD_LENGTH) {
            key = keypad_scan();
            if(key) {
                if(key == KEY_CLEAR) {
                    count = 0;
                    lcd_cmd(0xC0);
                    lcd_string("                "); // Clear line
                    lcd_cmd(0xC0);
                    break;
                }
                
                if(key >= '0' && key <= '9') {
                    input[count] = key;
                    lcd_data('*'); // Show asterisk for each digit
                    count++;
                    delay_ms(200); // Small delay for debounce
                }
            }
        }
        
        if(count == PASSWORD_LENGTH) {
            lcd_cmd(0x01);
            if(check_password(input)) {
                lcd_string("Correct!");
                delay_ms(1000);
                return; // Password correct, exit function
            } else {
                lcd_string("Incorrect!");
                delay_ms(1000);
                lcd_cmd(0x01);
                lcd_string("Try Again");
                delay_ms(1000);
            }
        }
    }
}