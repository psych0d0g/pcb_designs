To get an ir hex code for a specific unused button of your remote to be used for toslink input cycle use the following code on your arduino which is connected to a TSOP, then open the serial monitor while the Arduino is still connected to see the hex codes received

```C#
#include <IRremote.h>

// Create an instance of the object to decode the signal from the IR receiver,
// passing in the value of the analog pin you chose
IRrecv irReceiver(A0);
// Create a container for the decoding result
decode_results result;

void setup()
{
  // Ensure the serial monitor is set to the same frequency you pass into Serial.begin
  // in this case 9600
  Serial.begin(9600);
  irReceiver.enableIRIn();
}

void loop()
{
  if (irReceiver.decode(&result))
  {
      irReceiver.resume();
      Serial.println(result.value, HEX);
  }
}
```
