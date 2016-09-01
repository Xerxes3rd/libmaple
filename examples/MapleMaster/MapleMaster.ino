#include "libmaple.h"

void setup() {
  Serial.begin(57600);
  maple_init();
}

void loop() {
  read_maple_packet_from_serial();
  maple_debug(0);
  
  if(maple_packet_dest_is_maple()) {
    maple_transact();
    maple_debug(1);
    send_maple_packet_to_serial();
  } else {
    // Debug
    Serial.print(1);
    //uart_putchar(1);
  }
  maple_debug(1);
}

bool read_maple_packet_from_serial()
{
  // First byte: #bytes in packet (including header and checksum)
  if (Serial.available() > 0) {
    packet.data_len = Serial.read();
    if(packet.data_len > 0) {
      unsigned char *data = &(packet.header[0]);
      int i;
      for(i = 0; i < packet.data_len; i++) {
        *data = Serial.read();
        data++;
      }
      return true;
    } else {
      
    }
  }

  return false;
}

void send_maple_packet_to_serial() 
{
  Serial.write((packet.data_len_rx & 0xff00) >> 8);
  Serial.write(packet.data_len_rx & 0xff);
  if(packet.data_len_rx) {
    //int i;
    uint8_t *data = &(packet.header[0]);
    Serial.write(data, packet.data_len_rx);
    //for (i = 0; i < packet.data_len_rx; i++) {
    //  uart_putchar(data[i]);
    //}
  }
}