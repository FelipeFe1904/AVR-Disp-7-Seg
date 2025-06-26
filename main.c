// Programming 2 Seven-Segment Displays

#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char dig7seg[16] = {  0x3F, 0x06, 0x5B, 0x4F, 
                      0x66, 0x6D, 0x7D, 0x07, 
                      0x7F, 0x6F, 0x77, 0x7C, 
                      0x39, 0x5E, 0x79, 0x71  };

void disp7seg_int(void) {
    DDRD  = 0xFF; // Pins 0 to 7 as output (segments)
    PORTD = 0x00;
    DDRB |= (1 << 0); // Pin 8 as output (units display)
    DDRB |= (1 << 1); // Pin 9 as output (tens display)
}

unsigned char disp7seg_dig = 0;

void disp7seg(unsigned char d) {
    if (disp7seg_dig % 2) {
        PORTB &= ~(1 << 1);         // Turns off tens display
        PORTD = dig7seg[d % 10];    // Units digit
        PORTB |= (1 << 0);          // Turns on units display
    } else {
        PORTB &= ~(1 << 0);             // Turns off units display
        PORTD = dig7seg[(d / 10) % 10]; // Tens digit
        PORTB |= (1 << 1);              // Turns on tens display
    }
    disp7seg_dig++;
}

int main(void) {
    unsigned char t = 0;
    unsigned long n = 0;

    disp7seg_int();

    while (1) {
        disp7seg(t);

        if (n % 1000 == 0) { // Every 1000 ms (1 second)
            t = (t + 1) % 100;
        }

        _delay_ms(1);
        n++;
    }
}
