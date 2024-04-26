#ifndef ANALOG_HPP
#define ANALOG_HPP

#include <avr/io.h>

namespace analog {
    // Function to initialize the ADC
    void initADC() {
    // Set reference voltage to AVCC
    ADMUX |= (1 << REFS0);
    // Set prescaler to 128 to get 125 kHz ADC clock
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Enable ADC
    ADCSRA |= (1 << ADEN);
    }

    // Function to read from an analog pin
    uint16_t analogRead(uint8_t pin) {
        // Set ADC input channel
        ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);
        // Start conversion
        ADCSRA |= (1 << ADSC);
        // Wait for conversion to complete
        while (ADCSRA & (1 << ADSC))
            ;
        // Return the result
        return ADC;
    }
} // namespace analog

#endif