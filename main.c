#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7seg_init( void )
{
    DDRD  = 0xFF;
    PORTD = 0x00;
}

void disp7seg( unsigned char d )
{
    PORTD = digitos7seg[d];
}

int main(void)
{
    char i = 0;
    disp7seg_init();
    while( 1 )
    {
        disp7seg( i );
        _delay_ms(500);

        // Incremento limitado: 0..15
        i = ++i % 16;
    }
}