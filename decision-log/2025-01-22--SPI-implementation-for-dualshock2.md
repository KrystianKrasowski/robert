# SPI implementation for dualshock2 controller

## Description
The dualshock2 controller requires a clock signal pause after every byte exchange. That was quite obvious for me when I was implementing this communication for ATmega88PA, since it's an 8 bit microcontroller. However, while dealing with bare metal STM32 the idea was to send whole command sequence for the dualshock (in this project it is a static 9 bytes sequence) at once. Thus, it kept clock busy until all 9 bytes were exchanged. It didn't work that way in atmega, every exchenged byte was followed by ~20us clock pause. I wonder what is the standard here. Obvoiusly, transmitting all 9 bytes in a continous clock did not work. From the logic state analyzer it could be told, that the slave device "assumed" the pause.

## Action points
* Determine the **proper** behaviour of the SPI protocol - clock pauses are mandatory or not?
* Generalise the SPI driver implementation - now the communication logic is leaking through `spi_xxMCUxx.c` and `dulashock2.c`
    * `dualshock.c` should only determine CS, command sequence, and trigger the communication
    * `spi_x.c` should provide an api to configure the delays before first frame transmission

## Decision
For now I'll stick to the current working implementation as it is a showcase project and at this moment I have to deliver more important things:
* circuit
* documentation
* some unit tests