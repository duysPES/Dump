/**
 *
 * Project Name: Custom LISC-E F/W for Testing
 * Date: 3/18/2020
 * Author: Duan Uys
 *
 * Description:
 * 	Using existing Matrix-5 LISC-E, the m644p is reflashed to generate a single
 * 	and reoccuring valid packet, according to PEISI protocols.
 * 	
 * Theory of Operations:* 
 *	N/A
 *
 * *All Rights Reserved*
 **/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

#include "../lib/comms.h"
#include "../lib/globals.h"


void Blink(uint8_t bv) {
  DBG_PORT |= bv;
  _delay_ms(10);
  DBG_PORT &= ~bv;
  _delay_ms(10);
}

void Setup() {
  //-- RELAY INIT --//
  RELAY_DDR |= RELAY1 | RELAY2;
  
  //-- DBG INIT --//
  DBG_DDR |= DBG_FSK_XMIT | DBG_FSK_RECV | DBG_CHKSUM_ERR;

  //-- FSK INIT --//
  FSK_TX_DDR |= A_FSK_TX;
  FSK_TX_PORT |= A_FSK_TX;
  DBG_PORT &= ~DBG_FSK_XMIT;

  //Spi_Init();
  Usart_Init();
  sei();
}

uint8_t Verify_Checksum(const MESSAGE_t *msg) {
  uint8_t chksum = 0;
  uint8_t size = msg->size;
  uint8_t data[size];
  const uint8_t *arr = data;

  memcpy(data, msg->data, size);

  for (uint8_t i = 0; i < size; i++) {
    chksum ^= *(arr + i);
  }

  return !chksum ? TRUE : FALSE;
}

int main(void) {
  MESSAGE_t *msg = &Msg;
  uint8_t packet[] = {0xbe, 0xef, 0xfa, 0x05, 0xae}; 

  memcpy(msg->data, packet, 5);

  Setup();
  for (;;) {
   if(Verify_Checksum(msg))
    fsk_modulate(msg, DEFAULT_FSK_PREAMBLE);
   else
    Blink(DBG_CHKSUM_ERR);
 }
}
