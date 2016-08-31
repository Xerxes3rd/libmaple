#ifndef LIBMAPLE_h
#define LIBMAPLE_h
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ON 1
#define OFF 0

struct maplepacket {
	unsigned char data_len; /* Bytes: header, data, and checksum */
	unsigned short data_len_rx; /* For Rx -- didn't realise we could get up to 512 bytes */

	unsigned char header[4];
	unsigned char data[600]; /* Our maximum packet size */
} packet;

void maple_debug(int on);
void maple_tx_raw(unsigned char *buf, unsigned char length);
unsigned char *maple_rx_raw(unsigned char *buf);
void maple_timer_test();
void maple_init();
bool maple_transact();
unsigned char maple_compute_checksum(unsigned char data_bytes);
bool maple_read_packet(void);
bool maple_packet_dest_is_maple(void);
void maple_send_packet(void);

#ifdef __cplusplus
}
#endif

#endif