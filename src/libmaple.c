#include <avr/io.h>
#include "libmaple.h"

void maple_init()
{
	// Initialise serial port
	//uart_init();

	// Maple bus data pins as output -- NB needs corresponding changes in libMaple.S
	DDRB = 0xff;

	//puts("Hi there \n");
}

bool maple_test_transact()
{
	return true;
}

bool maple_transact()
{
	unsigned char *rx_buf_end;
	//unsigned char *rx_buf_ptr;

	// debug
	/*
	packet.header[0] = 0; // Number of additional words in frame
	packet.header[1] = 0; // Sender address = Dreamcast
	packet.header[2] = 1; //(1 << 5); // Recipient address = main peripheral on port 0
	packet.header[3] = 1; // Command = request device information
	packet.data[0]   = compute_checksum(0);
	packet.data_len  = 5;
	*/

	/*packet.header[0] = (192 + 4) / 4; // Number of additional words in frame
	packet.header[1] = 0; // Sender address = Dreamcast
	packet.header[2] = 1;
	packet.header[3] = 12; // block write
	packet.data[0]   = 0x4; // LCD
	packet.data[1]   = 0; // partition
	packet.data[2]   = 0; // phase
	packet.data[3]   = 0; // block number
	packet.data[4]   = 0xff;
	packet.data[5]   = 0x0f;
	packet.data[6]   = 0xff;
	packet.data[192 + 4] = compute_checksum(192 + 4);
	packet.data_len  = 4 + 192 + 4 + 1;
	*/

	maple_tx_raw(&(packet.header[0]), packet.data_len);
	rx_buf_end = maple_rx_raw(&(packet.header[0]));

	packet.data_len_rx = (rx_buf_end - (&(packet.header[0])));

	return true;

	// debug
	/*Serial.print("All done \n");
	Serial.println((int)(rx_buf_end - (&(packet.header[0]))), HEX);
	rx_buf_ptr = (&(packet.header[0]));
	while(rx_buf_ptr <= rx_buf_end) {
		Serial.println(*rx_buf_ptr, HEX);
		rx_buf_ptr ++;
	}
	*/
}

unsigned char maple_compute_checksum(unsigned char data_bytes)
{
	unsigned char *ptr = &(packet.header[0]);
	int count;
	unsigned char checksum = 0;

	for(count = 0; count < data_bytes + 4; count ++) {
		checksum ^= *ptr;
		ptr++;
	}
	return checksum;
}

bool maple_packet_dest_is_maple(void)
{
	return packet.data_len > 0;
}

// These functions are for interacting with the serial console - stub them off for now.
//bool maple_read_packet(void) { return true; }
//void maple_send_packet(void) { }
/*
// Read packet to send from the controller.
bool maple_read_packet(void)
{
	// First byte: #bytes in packet (including header and checksum)
	packet.data_len = uart_getchar();
	if(packet.data_len > 0) {
		unsigned char *data = &(packet.header[0]);
		int i;
		for(i = 0; i < packet.data_len; i++) {
			*data = uart_getchar();
			data ++;
		}
		return true;
	} else {
		return false;
	}
}

void maple_send_packet(void)
{
	uart_putchar((packet.data_len_rx & 0xff00) >> 8);
	uart_putchar(packet.data_len_rx & 0xff);
	if(packet.data_len_rx) {
		int i;
		uint8_t *data = &(packet.header[0]);
		for (i = 0; i < packet.data_len_rx; i++) {
			uart_putchar(data[i]);
		}
	}
}
*/