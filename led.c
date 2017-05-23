#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int current_led = 0;
bool sort_forwards = true;
bool loop_lock = false;
volatile uint8_t led_ports[6] = {0, 1, 2, 3, 4, 5};

int main (void) {
  // OUTPUT
  DDRB |= _BV(DDB0);
  DDRB |= _BV(DDB1);
  DDRB |= _BV(DDB2);
  DDRB |= _BV(DDB3);
  DDRB |= _BV(DDB4);
  DDRB |= _BV(DDB5);
  DDRB |= _BV(DDB5);

  // INPUT
  DDRD &= _BV(DDD4);

  // Turn the first pin on
  PORTB |= _BV(current_led);

  while(1) {
    if (PIND & _BV(PD4)) {
      // Check whenever the button is beeing pressed, we want to
      // Jump 1 led for each click
      if (loop_lock) {
        continue;
      } else {
        loop_lock = true;
      }

      // Check whenever we have reached the pin limits
      if (current_led == 5) {
        sort_forwards = false;
      } else if(current_led == 0) {
        sort_forwards = true;
      }

      // Turn the current pin OFF
      PORTB &= ~_BV(current_led);
      if (sort_forwards == true) {
        current_led = current_led + 1;
      } else {
        current_led = current_led - 1;
      }

      // Turn the new current pin ON
      PORTB |= _BV(current_led);
      _delay_ms(100);
    } else {
      loop_lock = false;
    }
  }
}
