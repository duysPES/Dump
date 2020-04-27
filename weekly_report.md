
## 4/21/2020

### Achievements

* A stable prototype telemetry protocol communication between RaspberryPi and Slave device via SPI (99.99% working)

* Able to communicate to more than one slave device using current alpha version of software on Rpi. Able to successfully communicate to a
SerLCD and uC with custom f/w that listens to SPI and modulates a packet on pin using FSK signal.

* Prototype SPI universal library on uC, so all slaves can utilize the same API and version. The SPI comms protocol includes 3 standard communication design
and requires programmer to define 3 functions for each uC that utilizes SPI to communicate with host. Library is still in alpha stage, and much testing must be done.
Library should be at a stage now where I can implement the code design in the first modular circuit ( Modulation of FSK signal from RPi )

* Able to use RPi's built-in SPI hardware for extremely fast data transmission speeds (1 Mega Baud) with current firmware. Will be using this in replacement of custom
Rust Software SPI. There was nothing wrong with my own custom library, but I essentially bit-banged the whole procedure and with all the overhead between function calls
this limited the data transmission speed to roughly 10k baud. Using hardware SPI ables to increase data speed 100x. A slight hack-around allows me to bypass the 2 slave device
limit. The only caveat is that it is not recommended to use CE0 & CE1 pins on RPi.

### To Do

* Create integration test of master that sends all available PAISI commands to Modulation uC to see if it works appropriately. (Each LED should blink that corresponds to specific command)

* ~~Expierement with using RPi's built-in hardware SPI and just using another GPIO for SS - this may actually be faster than custom hand-made SPI library for RPi...~~


* ~~Refactor code that handles recieving of SPI data on uC and create library that can be updated and reused throughout all firmware that requires uC
to operate as slave.~~

* ~~Create bi-directional communication protocol between master and slave devices~~

* ~~Create a way to memory map an MMIO (Memory Mapped I/O) to a struct - initial creation of HAL~~

* ~~Create default struct in Master SPI that uses default MISO, MOSI, SCLK, CS pins and uses standard telemetry protocol~~

* ~~Setup test scenerio where two slave devices are communicating with master device~~

### Problems

### Ideas
 
* Create a generic packet structure that can be reused between all communication devices.
* Switch communication protocol to I2C, instead of SPI?
