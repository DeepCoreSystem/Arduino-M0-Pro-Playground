/**
 * \file
 *
 * \brief User board initialization
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

static struct usart_module debug_uart;

/**
 * \brief  Board-specific initialization code
 *
 * This function is meant to contain board-specific initialization code
 * for, e.g., the I/O pins. The initialization can rely on application-
 * specific board configuration, found in conf_board.h.
 * 
 * \param  none
 * 
 * \return void
 */
void system_board_init(void)
{
	 // Initialize the on-board LED
	 
	 struct port_config pin_config;
	 port_get_config_defaults(&pin_config);

	 pin_config.direction = PORT_PIN_DIR_OUTPUT;

	 port_pin_set_config(LED_L,&pin_config);
	 port_pin_set_output_level(LED_L, LED_INACTIVE);


	 // Initialize the serial-usb-bridge for debugging

	 struct usart_config uart_config;
	 usart_get_config_defaults(&uart_config);

	 uart_config.baudrate = 9600;
	 uart_config.character_size = USART_CHARACTER_SIZE_8BIT;
	 uart_config.parity = USART_PARITY_NONE;
	 uart_config.stopbits = USART_STOPBITS_1;

	 uart_config.mux_setting = USART_RX_3_TX_2_XCK_3;  // RX on pad 3, TX on pad 2
	 uart_config.pinmux_pad0 = PINMUX_UNUSED;
	 uart_config.pinmux_pad1 = PINMUX_UNUSED;
	 uart_config.pinmux_pad2 = PINMUX_PB22D_SERCOM5_PAD2;  // TX on pin PB22
	 uart_config.pinmux_pad3 = PINMUX_PB23D_SERCOM5_PAD3;  // RX on pin PB23

	 stdio_serial_init(&debug_uart, SERCOM5, &uart_config);
	 usart_enable(&debug_uart);
}