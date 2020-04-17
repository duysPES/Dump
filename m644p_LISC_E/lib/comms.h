/**
 *
 * Comms for LISC for serial and FSK Modulation/Demodulation
 *
 * **/

#ifndef __COMMS_H__
#define __COMMS_H__

#include <avr/interrupt.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "../lib/globals.h"

#define UBRR_9600 (103)  // assumes 16Mhz clock

/******************* SERIAL COMMS **************************/
extern void Usart_Init(void);
extern void Usart_Write(unsigned char data);  // write to main serial
/**************************************************************/

/******************* SPI COMMS **************************/
extern void Spi_Init(void);
extern void Sync_Spi(void);
extern uint8_t Spi_Recv(void);
/**************************************************************/

/************************** FSK *******************************/
/**
 * According to PAS1-C Specs the following are hardcoded.
 *
 * BAUDRATE = 250
 *
 * Spacing FREQ is 2Khz // logi 0
 * Marking FREQ is 1Khz // logic 1
 *
 * Spacing CYCLES = 1 / BAUDRATE * 2000 = 8
 * Marking CYCLES = 1 / BAUDRATE * 1000 = 4
 *
 * Spacing Delay = 1 / BAUDRATE / SPACING_CYCLES / 2 = 500 us
 * Marking Delay = 1 / BAUDRATE / MARKING_CYCLES / 2  = 250 us
 **/

/*
        Main modulating function. Sends start bit, 8 bits, stop bit,  then
        when modulating the uint8_t, we must have LSb first in time
        with MSb last

 */

#define MODULATE(DELAY, PORT, PIN, NCYCLES)     \
  for (unsigned char t = 0; t < NCYCLES; t++) { \
    PORT &= ~PIN;                               \
    _delay_us(DELAY);                           \
    PORT |= PIN;                                \
    _delay_us(DELAY);                           \
  }

#define FSK_START_BIT() MODULATE(SPACE_DELAY, FSK_TX_PORT, A_FSK_TX, SPACE_CYCLES)
#define FSK_STOP_BIT() MODULATE(MARK_DELAY, FSK_TX_PORT, A_FSK_TX, MARK_CYCLES)
#define FSK_PREAMBLE(N) MODULATE(MARK_DELAY, FSK_TX_PORT, A_FSK_TX, N)
#define FSK_ONE() FSK_STOP_BIT()
#define FSK_ZERO() FSK_START_BIT()

static inline void fsk_modulate(const MESSAGE_t *msg,
                                const uint8_t nPreambles) {
  uint8_t data[MAX_DATA_LEN];
  const uint8_t size = msg->size;

  memcpy(data, msg->data, size);
  const uint8_t *b = data;

  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    DBG_PORT |= DBG_FSK_XMIT;
    FSK_PREAMBLE(nPreambles);

    // iterate through data message and start by sending LSb first
    for (uint8_t i = 0; i < size; i++) {
      // send startbit logic 0
      FSK_START_BIT();

      for (uint8_t j = 0; j < BITS_IN_BYTE; j++) {
        if (CHECKBIT(*b, j)) {
          FSK_ONE();
        } else {
          FSK_ZERO();
        }
      }

      // send stop bit
      FSK_STOP_BIT();
      b++;
    }
    DBG_PORT &= ~DBG_FSK_XMIT;
  }
}  // modulate()s

/**************************************************************/

#endif
