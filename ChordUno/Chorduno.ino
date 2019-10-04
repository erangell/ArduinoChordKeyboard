/* ENGELBART CHORD KEYBOARD FOR ARDUINO UNO
*/

#define strobe  2
#define d5      3
#define d4      4
#define d6      5
#define d2      6
#define d3      7
#define d0      8
#define d1      9
#define reset   10

#define ledstatus 13

#define pinTHUMB  A0
#define pinINDEX  A1
#define pinMIDDLE A2
#define pinRING   A3
#define pinPINKY  A4

byte asciinum = 0;
char asciival = 0;
byte maxascii= 127;
byte minascii= 1;

int thumb = 0;  
int index = 0;  
int middle = 0;
int ring = 0;
int pinky = 0;

bool firstnibble = 1;
int  nibble = 0;
int lownibble = 0;
int highnibble = 0;


// read the buttons
int read_chord_buttons()
{
  thumb  = digitalRead(pinTHUMB);
  index  = digitalRead(pinINDEX);
  middle = digitalRead(pinMIDDLE);
  ring   = digitalRead(pinRING);
  pinky  = digitalRead(pinPINKY);  

  return pinky * 8 + ring * 4 + middle * 2 + index;
}


void setup() {
 Serial.begin(9600);
 // while (!Serial) {
 //   ; // wait for serial port to connect. Needed for native USB port only
 // }

 pinMode (d0,OUTPUT);
 pinMode (d1,OUTPUT);
 pinMode (d2,OUTPUT);
 pinMode (d3,OUTPUT);
 pinMode (d4,OUTPUT);
 pinMode (d5,OUTPUT);
 pinMode (d6,OUTPUT);
 pinMode (strobe,OUTPUT);
 digitalWrite (strobe,LOW);
 digitalWrite (d0,LOW);
 digitalWrite (d1,LOW);
 digitalWrite (d2,LOW);
 digitalWrite (d3,LOW);
 digitalWrite (d4,LOW);
 digitalWrite (d5,LOW);
 digitalWrite (d6,LOW);


 pinMode (pinTHUMB, INPUT);
 pinMode (pinINDEX, INPUT);
 pinMode (pinMIDDLE, INPUT);
 pinMode (pinRING, INPUT);
 pinMode (pinPINKY, INPUT);

 pinMode (ledstatus, OUTPUT);
 digitalWrite (ledstatus, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

 nibble = read_chord_buttons();  // read the buttons
 //Serial.println(nibble);

 
 if (thumb)
 {
    int thumbdown = 1;
    while (thumbdown) // wait for thumb up
    {
      thumbdown = digitalRead(pinTHUMB);
      delay(20); // debounce the button
    }
    if (firstnibble == 1)
    {
      highnibble = nibble;
    }
    else
    {
      lownibble = nibble;

      if ((highnibble == 15) && (lownibble == 15))
      {
        SendReset();
      }
      else
      {
        SendAscii();
      }
    }
    firstnibble = !(firstnibble);  
 }

 if (firstnibble == 1)
 {
      highnibble = nibble;
      digitalWrite (ledstatus, LOW);
 }
 else
 {
      lownibble = nibble;
      asciinum = highnibble * 16 + lownibble;
      digitalWrite (ledstatus, HIGH);
 }
}


void SendReset()
{
    digitalWrite(reset,HIGH);
    delay(100);
    digitalWrite(reset,LOW);  
}


void SendAscii()
{
       asciival = (char)asciinum;
       Serial.print(asciival);

       int testval = asciival;
       
       int bit8 = (testval >= 128);
       testval = testval - 128 * bit8;
       
       int bit7 = (testval >= 64);
       testval = testval - 64 * bit7;
       digitalWrite(d6, bit7);

       int bit6 = (testval >= 32);
       testval = testval - 32 * bit6;
       digitalWrite(d5, bit6);
       
       int bit5 = (testval >= 16);
       testval = testval - 16 * bit5;
       digitalWrite(d4, bit5);

       int bit4 = (testval >= 8);
       testval = testval - 8 * bit4;
       digitalWrite(d3, bit4);

       int bit3 = (testval >= 4);
       testval = testval - 4 * bit3;
       digitalWrite(d2, bit3);

       int bit2 = (testval >= 2);
       testval = testval - 2 * bit2;
       digitalWrite(d1, bit2);

       int bit1 = (testval >= 1);
       digitalWrite(d0, bit1);

       digitalWrite(strobe,HIGH);
       long tgttime = micros() + 10;
       while (micros() < tgttime)
       {
       }
       digitalWrite(strobe,LOW);
       
       tgttime = millis() + 13; // delay between characters
       while (millis() < tgttime)
       {
       }      
}


