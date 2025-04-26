#ifndef PASSWORD_H
#define PASSWORD_H

#define PASSWORD_LENGTH 4
#define CORRECT_PASSWORD "1234"

unsigned char check_password(unsigned char *input);
void password_entry_screen(void);

#endif