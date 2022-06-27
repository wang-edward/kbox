#include "include/io/CAT9555.hpp"

volatile sig_atomic_t flag = 1;

void sig_handler(int signum) {
    if (signum == SIGINT) {
        std::cout << "Exiting..." << std::endl;
        flag = 0;
    }
}

CAT9555::CAT9555(uint8_t addr) {
    cat_address = addr;
}

void CAT9555::begin(){

    //handle interrupts
    signal(SIGINT, sig_handler);

    //set io direction to input (redundant since starts at input)
    i2c.address(cat_address);
    i2c.writeReg(CONFIG_PORT0, 0xFF);
    i2c.writeReg(CONFIG_PORT1, 0xFF);
}

void CAT9555::update() {
    uint8_t _data0, _data1;

    //read buffers
    i2c.address(cat_address);
    _data0 = i2c.readReg(INPUT_PORT0);
    _data1 = i2c.readReg(INPUT_PORT1);
    data = (_data0 << 8) | _data1; //concatenate buffers
    std::cout<<"port0: "<<_data0<<"\nport1: "<<_data1<<std::endl;
}

bool CAT9555::get_status(char index) {
    if (index < 16 && index >=0) {
        return (data >> index) & 1; //get bit at index 
                                    // example: index = 11
                                    // 1111000011110000

    }
    return -1; //TODO: throw exception?
}
