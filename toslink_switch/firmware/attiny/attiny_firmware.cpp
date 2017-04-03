// found @ https://blog.turboturbo.net/2016/10/01/ir-pc-power-on-quick-n-dirty/
// Load IR library
#include <tiny_IRremote.h>

// Define IR Hexcodes to match
#define IR_POWERBTN 0x800f840c
#define IR_POWERBTN2 0x800f040c

// Delay between succesfull ir recieves
#define TIMERDELAY 1000

// Power pules
#define PULSETIME 20

// Led pulse time
#define LEDTIME 250

//Pin Assignment
int RECV_PIN = 3;
int SWITCH_PIN = 2;
int LED_PIN = 1;

//Timer
long timer;

//Init IR Reciever
IRrecv IR_Reciever(RECV_PIN);

//Init Decoder and buffer
decode_results IR_Decoder;

void setup()
{
  //Start IR Reciever
  IR_Reciever.enableIRIn(); 

  //Init Switch Pin
  pinMode(SWITCH_PIN,OUTPUT);
  digitalWrite(SWITCH_PIN,LOW);

  //Init LED Indicator and indicate power on
  pinMode(LED_PIN,OUTPUT);
  for(int i = 0; i<5;i++) {
    digitalWrite(LED_PIN,HIGH);
    delay(50);
    digitalWrite(LED_PIN,LOW);
    delay(50);
  }

  //Init Timer
  timer = 0;
}

void loop() {
  // Reset timer after timeout
  if(timer != 0 && timer + TIMERDELAY < millis()) {
    timer = 0;
  }

  // Check if anything is recieved
  if (IR_Reciever.decode(&IR_Decoder)) {
    IR_Reciever.resume();  // Continue recieving

    // Match code if timer is reset 
    if(timer == 0 && (IR_Decoder.value == IR_POWERBTN || IR_Decoder.value == IR_POWERBTN2)){
      // Flash LED and pull switch pin
      timer = millis();
      digitalWrite(LED_PIN,HIGH);
      digitalWrite(SWITCH_PIN,HIGH);
      delay(PULSETIME);
      digitalWrite(SWITCH_PIN,LOW);
      delay(LEDTIME);
      digitalWrite(LED_PIN,LOW);
    } else {
    }
  }
}
