/*

 'codesend' hacked from 'send' by @justy
 
 - The provided rc_switch 'send' command uses the form systemCode, unitCode, command
   which is not suitable for our purposes.  Instead, we call 
   send(code, length); // where length is always 24 and code is simply the code
   we find using the RF_sniffer.ino Arduino sketch.

 Usage: ./codesend decimalcode
 (Use RF_Sniffer.ino to check that RF signals are being produced by the RPi's transmitter)
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     

int main(int argc, char *argv[]) {
    
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 27;
    int bitlength = 32;
    int pulse = 160;
    
    // Parse the firt parameter to this command as an integer
    int code = atoi(argv[1]);
    // bit length of code default is 24
    
    if (argc < 4) {
	printf("You need to specify code bitlength pulse.\nE.g. 'codesend 12345678 32 260'\n");
    } else {
    	bitlength = atoi(argv[2]);
	pulse = atoi(argv[3]);

    	printf("bitlength: %i\n", bitlength);
    	printf("pulse: %i\n", pulse);

    	if (wiringPiSetup () == -1) return 1;
    	
	RCSwitch mySwitch = RCSwitch();
    	mySwitch.setPulseLength(pulse);
    	mySwitch.enableTransmit(PIN);    
    	mySwitch.send(code, bitlength);
    	
	printf("sending code[%i]\n", code);

    	return 0;
    }
}
