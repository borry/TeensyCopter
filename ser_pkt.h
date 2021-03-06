/*
 *  ser_pkt.h
 *  Created by Tim O'Brien
 *  
 *  used to encode, send, and decode serilized data
 *  created for UAVs and RC projects
 *  
 *  ideas and some code from microgear.googlecode.com
 */


/*  Packets look like this:
 *  
 *  /------------------------Header--------------------------/ /--data--/ /-------checksum-------/
 *  | Start byte0 | Start1 | packet ID | packet Type | length | **data** | Checksum0 | Checksum1 |
 *  
 *  the data section is variable length is specified (in __ bytes long).
 *  all bytes are sent as uint8_t (unsigned 8 bit ints)
 */

#ifndef SER_PKT_H
#define SER_PKT_H
//allow for easy C++ compile
#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/*****************************************/
/**********   datatypes/macros  **********/
/*****************************************/

// packet IDs (first byte of two)
#define BACKEND_CONTROL	0
#define USER_CONTROL	1
	#define ACC_DATA		0
	#define FULL_REMOTE		1
#define TELEM_FEEDBACK	2
	#define STATUS			0
	#define PITCH_ROLL		1
	#define MOTOR_OUTPUT	2
	#define DEBUG_OUTPUT	3
    #define ALTITUDE        4
#define SETTINGS_COMM	3
	#define REMOTE_2_QUAD_SETTINGS	0
	#define QUAD_2_REMOTE_SETTINGS	1

// packet types

typedef struct {
	double x;
	double y;
} ACCtelem;

typedef struct {
	uint16_t d0;
	uint16_t d1;
	uint16_t d2;
	uint16_t d3;
} FourU16;

/*****************************************/
/**********		declarations	**********/
/*****************************************/
void send_packet (uint8_t,uint8_t,uint8_t*,uint8_t );

void send_some_int16s(uint8_t pktID, uint8_t pktTYPE, int16_t * values, uint8_t number);
void send_int16_packet(uint8_t,uint8_t,int16_t,int16_t,int16_t,int16_t);
void send_float_packet(uint8_t,uint8_t,float,float);
void send_byte_packet(uint8_t,uint8_t,uint8_t);

uint8_t process_incoming_packet(uint8_t * data, uint8_t * position);

void decode_some_int16s( uint8_t * buf, int16_t * values, uint8_t number );
ACCtelem decode_acc_data( uint8_t *buf );
FourU16 decode_4xint16( uint8_t *buf );
void decode_4xint16_alt( uint8_t * buf, unsigned int* d0, unsigned int* d1, unsigned int* d2, unsigned int*d3);

    
#ifdef __cplusplus
}
#endif
#endif
