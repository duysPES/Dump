## 5/4/2020

### Achievements

[ PEISI Addressable Switch ]

* Our 'football' is able to successfully demodulate a signal coming from the ISI switch.

* We managed to establish communication with ISI switch running PES protocol, with custom firmware and driver. 

[ Pioneer Surface System ]

* Added a UID to each individual module for use with host to establish location of module in slot. The UID is retrievable by an added command

* Converted the internal buffer registers on all digital components from unsigned 8 bit values to floats (for decimal support). The logic was added to serialize these float numbers and sent via SPI. The host (RPi) is able to reconstruct the raw values back into their respective float values. This decision was based on the fact that incoming values based on ADC logic will need to be represented as decimal values and not pure integers.

* Originally the design forced new digital components to define the functino `Spi_Process_Cmd` individually, however this logic has been moved into the background to be taken care of in the libraries as the logic to process individual commands should be universal on all digital components.

### To Do
### Problems

* We were NOT able to effectively use our 'football' to communicate to a switch. 

### Ideas

## 4/27/2020

### Achievements

* Integration test succeeds, f/w for Modulator checks each incoming packet from HOST and blinks an LED to indicate the command being modulated

* Replaced logic behind debugging led pins and visually showing commands being sent. Removed the global definitions floating all over the place and replaced with a global structure
wrapped around a Hardware Abstraction Layer. 

* Created logic that creates a timeout, when listening for incoming packets from host. Nominally, the first byte to arrive can mean either 1) Command 2)size of data or 3) filler
and if it is deterimined to be an arbitrary amount of data being sent, it will activate an SPI timeout of 125ms. In the event of a timeout, it will return an error with the signal
that it was garbaged that was recieved.

* There is now another layer of safety that is controlled by software in the Modulation f/w, one that prevents any information being modulated on the line if that packet does not
contain a valid PEISI command.

* Able to successfully ask slave device to dump both registers to host, when asked with specific command. The communication process is smart, in that instead of slave sending a fixed
length everytime, it first responds to host with the length of the buffer that is non-zero. The f/w for adding to these buffers is actually wrapped in a struct that keeps a constant
count of elements being added and removed, that way when the time comes to send the length (especially at SPI speeds) it doesn't waste time counting non-zero elements.

* Restructured the makefile to allow for conditional compilation - meaning the global libraries that are utilized throughout each project doesn't have to be added to any one project unless
you absolutely need it. Not including files that you will not need, will decrease size of program.

* Down graded entire operation to run @ 3.3V, this allows for lower current consumption and direct communication with RPi (no need for logic level converter). The only downside, is ADC resolution has
been decreased from 4.8mV per bit to 3.2mV per bit. Not a big deal, as if we are really going to utilize ADC channels, we would rather buy an off-the-shelf 12bit > adc for maximum resolution.

* MILESTONE - The software for Host and firmware on Modulation Module seems to be in a very stable and working condition, passing all  integration tests.

### To Do

* ~~Create Modulaion f/w that handles if incoming packets are not of valid length -- right now if packet is not at 5 bytes in length, code hangs in wrong state...~~

* Store valid COMMANDS in EERPOM, and construct a way to update commands

* ~~Operate whole system using 3.3V in order to see if we can get rid of logic level conversions~~

* ~~Create logic that dumps SPI registers to host~~

### Problems
### Ideas





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
