/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <conf_board.h>
#include "main.h"




void setup_port_pins(void)
{
    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);

	// Configure the blinky LED pin as output and set it to low level
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(BLINKY, &config_port_pin);
	port_pin_set_output_level(BLINKY, false);
}



int main (void)
{
	system_init();
	delay_init();	// Initialize the delay library of ASF

	setup_port_pins();

	/* Insert application code here, after the board has been initialized. */

	while(1)
	{
		delay_ms(500);
		port_pin_toggle_output_level(BLINKY);
	}
}
