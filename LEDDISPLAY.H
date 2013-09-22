// MATRIX LED DISPLAY

void leddisplay(unsigned char msg[]);

void leddisplay(unsigned char msg[])
{

	lcd_cmd(1);

	lcd_string("UART INITIALIZED");
	delay(1000);

	uart_data('#');
	delay(2000);
	delay(2000);

	uart_data('4');
	delay(2000);
	delay(2000);

	uart_data('1');
	delay(2000);
	delay(2000);

	uart_string("<M ");
	uart_string(msg);
	uart_string("><S 2><D L1>");
	uart_enter();
	delay(2000);
	delay(2000);
	
	uart_data('6');
	delay(2000);

	lcd_cmd(1);
	lcd_string("MESSAGE ENTERED");
	delay(1000);

	lcd_cmd(1);
	lcd_string("SUCCESS");
	delay(1000);
}
