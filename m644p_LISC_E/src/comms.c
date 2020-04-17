
#include "../lib/comms.h"

#include "../lib/globals.h"

void Usart_Write(unsigned char data) {
  while (!CHECKBIT(UCSR0A, UDRE0))
    ;
  UDR0 = data;
}

void Usart_Init(void) {
  //-- USART DBG INIT --//
  UBRR0 = UBRR_9600;
  UCSR0B = _BV(TXEN0);
  //			1stop    |-------8bit-------------|
  UCSR0C = _BV(USBS0) | _BV(UCSZ01) | _BV(UCSZ00);
}

void Spi_Init(void) {
  //  SPI_DDR |= B_MISO;  // set  MISO as output; leave rest as input
  //  PORTD |= B_SS;      // leave SS as input high
  //  SPCR |= _BV(SPE);   //| _BV(SPIE);  // turn on SPI and SPI interrupt
}

void Sync_Spi() {
  //  uint8_t pre_buf;
  //  uint8_t preamble = 0;
  //  while (1) {
  //    pre_buf = Spi_Recv();
  //    if (pre_buf == 0xFF) {
  //      preamble++;
  //    } else {
  //      preamble = 0;
  //    }
  //
  //    if (preamble == 3) {
  //      break;
  //    }
  //  }
}

uint8_t Spi_Recv() {
  while (!(SPSR & (1 << SPIF)))
    ;
  return SPDR;
}
