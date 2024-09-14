/*
   This is very simple teaching code to show you how to use the remote 
   delivered together with the RTL-SDR Radio Stick for other pruposes.
   Forked from IRremoteESP8266: IRrecvDemo
   An IR detector/demodulator must be connected to the input kRecvPin.
   Copyright 2009 Ken Shirriff, http://arcfn.com
   Example circuit diagram:
   https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-receiving

*/
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
#define kRecvPin 5

IRrecv irrecv(kRecvPin);
//IR code definitions for RTL-SDR ADS-B Stick
unsigned long keys[] = {0xFF48B7, 0xFF906F, 0xFFB847, 0xFFF807, 0xFFB04F, 0xFF9867, 0xFFD827, 0xFF8877, 0xFFA857, 0xFFE817, 0xFFA05F, 0xFF40BF, 0xFF6897, 0xFFB24D, 0xFF2AD5, 0xFF32CD, 0xFF30CF, 0xFF38C7, 0xFF02FD, 0xFF50AF, 0xFF7887, 0xFFFFFFFF};
// decode Key              0         1          2        3         4         5         6          7         8         9        sub+      sub-      Red       Green     Src       Recd     TimS      Recl      Full      Vol-     Vol+       Long
// decode to               0         1          2        3         4         5         6          7         8         9        10        11        12        13        14        15       16        17         18        19       20         21
byte keyNumber;
byte arraySize;
byte keyNr;

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  arraySize = sizeof(keys) / sizeof(keys[0]);
/*  
  * Debug reporting  
  Serial.print("Total number of keys = ");
  Serial.println(arraySize);
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  Serial.print("Codelist =");
  for (int i = 0; i < arraySize; i++)
  {
    serialPrintUint64(keys[i], HEX);
    Serial.print("=");
    Serial.print(i);
    Serial.print(", ");
  }
  Serial.println(", That's all!");
*/
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    Serial.println("Code: ");
    serialPrintUint64(results.value, HEX);
    keyNr = 255;
    for (int i = 0; i < arraySize; i++)
    {
    /*    
     * Debug reporting    
    Serial.print(", Comparing ");
    Serial.print(results.value);
    Serial.print(" with ");
    Serial.print(keys[i]);
    Serial.print(" at ");
    Serial.print(i);
     */
      if (results.value == keys[i])
      {
        keyNr = i;
        break;
      }
    }
    Serial.print(" Found at ");
    Serial.print(keyNr);
    Serial.println("");
    irrecv.resume();  // Receive the next value
  }
  delay(100);
}
