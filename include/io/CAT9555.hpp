//TODO
/*
    replace define with const
*/


#ifndef CAT9555_H
#define CAT9555_H

/* standard headers */
#include <iostream>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa headers */
#include "mraa/common.hpp"
#include "mraa/i2c.hpp"
#include "CAT9555.hpp"

#define MAX_BUFFER_LENGTH 6 //todo ??

//define address
#define	INPUT_PORT0				(uint8_t)0x00
#define	INPUT_PORT1				(uint8_t)0x01
#define	OUTPUT_PORT0			(uint8_t)0x02
#define	OUTPUT_PORT1			(uint8_t)0x03
#define	POLARITY_PORT0		    (uint8_t)0x04
#define	POLARITY_PORT1		    (uint8_t)0x05
#define	CONFIG_PORT0			(uint8_t)0x06
#define	CONFIG_PORT1			(uint8_t)0x07
#define	ADDRESS					(uint8_t)0x20

#define I2C_BUS 0 //todo ??

////////////////////////////////
// CAT9555 Class Declaration  //
////////////////////////////////
class CAT9555
{
public:	
    CAT9555(uint8_t addr = ADDRESS);
	void begin();
    void update();
    bool get_status (char index);

private:
    mraa::I2c i2c(I2C_BUS);
    unsigned char cat_address;
    uint16_t data = 0;
};

extern CAT9555 cat9555;

#endif