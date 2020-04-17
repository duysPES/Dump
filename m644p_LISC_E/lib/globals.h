#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <avr/io.h>
#include <stdint.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BITS_IN_BYTE 8
#define MAX_DATA_LEN 32

/* Extracts the upper value of a 16bit value */
#define UPPER_16(DATA) ((unsigned char)(DATA >> 8))

/* Extracts the lower 16bit value*/
#define LOWER_16(DATA) ((unsigned char)(DATA))

/* Sets a particular bit in byte */
#define SETBIT(ADDRESS, BIT) (ADDRESS |= (1 << BIT))

/*Clears a particular bit in byte*/
#define CLEARBIT(ADDRESS, BIT) (ADDRESS &= ~(1 << BIT))

/* Flips a bit in a byte 1->0 || 0->1*/
#define FLIPBIT(ADDRESS, BIT) (ADDRESS ^= (1 << BIT))

/* Checks to see if particular bit is set or not */
#define CHECKBIT(ADDRESS, BIT) (ADDRESS & (1 << BIT))

/* Sets contents of x based on the value of y */
#define SETBITMASK(x, y) (x |= (y))

/* Clears contents of x based on value of y */
#define CLEARBITMASK(x, y) (x &= (~y))

/* Flips contents of x based on that of y */
#define FLIPBITMASK(x, y) (x ^= (y))

/*Checks if bits are set based on y */
#define CHECKBITMASK(x, y) (x & (y))

//-- FSK Globals --//
#define MARK_CYCLES 4
#define SPACE_CYCLES 8
#define MAX_CYCLES SPACE_CYCLES
#define MARK_DELAY 500
#define SPACE_DELAY 250
#define DEFAULT_FSK_PREAMBLE 3

//-- DATA STRUCTURE --//
typedef struct {
  uint8_t size;
  uint8_t data[MAX_DATA_LEN];
} MESSAGE_t;

//-- XMT COMMANDS --//
#define CMD_GO_IDLE 0x1e
#define CMD_SEND_STATUS 0x05
#define CMD_PRE_ARM 0x3c
#define CMD_ARM 0x4b
#define CMD_FIRE 0x5a

#define FSK_TX_DDR DDRA
#define FSK_TX_PORT PORTA
#define A_FSK_TX _BV(PA7)

#define FSK_RX_DDR DDRB
#define FSK_RX_PORT PORTB
#define B_FSK_RX _BV(PB2)

#define RELAY_DDR DDRB
#define RELAY_PORT PORTB
#define RELAY1 _BV(PB0)
#define RELAY2 _BV(PB1)

#define DBG_DDR DDRC
#define DBG_PORT PORTC
#define DBG_FSK_XMIT _BV(PC0)
#define DBG_FSK_RECV _BV(PC1)
#define DBG_CHKSUM_ERR _BV(PC2)


extern MESSAGE_t Msg;

#endif
