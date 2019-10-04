/* ENGELBART CHORD KEYBOARD
*/

//Pin numbers on Arduino Mega connected to Replica 1+ keyboard socket
#define strobe  23
#define d5      25
#define d4      27
#define d6      29
#define d2      31
#define d3      33
#define d0      35
#define d1      37
#define reset   39

#define pinTHUMB  41
#define pinINDEX  43
#define pinMIDDLE 45
#define pinRING   47
#define pinPINKY  49

#define led1a  22
#define led1b  24
#define led1c  26
#define led1d  28
#define led1e  30
#define led1f  32
#define led1g  34
#define led1p  36

#define led2a  38
#define led2b  40
#define led2c  42
#define led2d  44
#define led2e  46
#define led2f  48
#define led2g  50
#define led2p  52

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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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

 pinMode (led1a, OUTPUT);
 pinMode (led1b, OUTPUT);
 pinMode (led1c, OUTPUT);
 pinMode (led1d, OUTPUT);
 pinMode (led1e, OUTPUT);
 pinMode (led1f, OUTPUT);
 pinMode (led1g, OUTPUT);
 pinMode (led1p, OUTPUT);
 pinMode (led2a, OUTPUT);
 pinMode (led2b, OUTPUT);
 pinMode (led2c, OUTPUT);
 pinMode (led2d, OUTPUT);
 pinMode (led2e, OUTPUT);
 pinMode (led2f, OUTPUT);
 pinMode (led2g, OUTPUT);
 pinMode (led2p, OUTPUT);

 digitalWrite(led1a, HIGH);
 digitalWrite(led1b, HIGH);
 digitalWrite(led1c, HIGH);
 digitalWrite(led1d, HIGH);
 digitalWrite(led1e, HIGH);
 digitalWrite(led1f, HIGH);
 digitalWrite(led1g, HIGH);
 digitalWrite(led1p, HIGH);

 digitalWrite(led2a, HIGH);
 digitalWrite(led2b, HIGH);
 digitalWrite(led2c, HIGH);
 digitalWrite(led2d, HIGH);
 digitalWrite(led2e, HIGH);
 digitalWrite(led2f, HIGH);
 digitalWrite(led2g, HIGH);
 digitalWrite(led2p, HIGH);

 delay(3000);

 digitalWrite(led1a, LOW);
 digitalWrite(led1b, LOW);
 digitalWrite(led1c, LOW);
 digitalWrite(led1d, LOW);
 digitalWrite(led1e, LOW);
 digitalWrite(led1f, LOW);
 digitalWrite(led1g, LOW);
 digitalWrite(led1p, LOW);

 digitalWrite(led2a, LOW);
 digitalWrite(led2b, LOW);
 digitalWrite(led2c, LOW);
 digitalWrite(led2d, LOW);
 digitalWrite(led2e, LOW);
 digitalWrite(led2f, LOW);
 digitalWrite(led2g, LOW);
 digitalWrite(led2p, LOW);

       
 asciinum = 48;
 asciival = (char)asciinum;
}

void loop() {
  // put your main code here, to run repeatedly:

 nibble = read_chord_buttons();  // read the buttons

 if (thumb)
 {
    int thumbdown = 1;
    while (thumbdown) // wait for thumb up
    {
      thumbdown = digitalRead(pinTHUMB);
      led7seg (0, highnibble, 1); 
      led7seg (1, lownibble, 1); 
    }
    if (firstnibble == 1)
    {
      highnibble = nibble;
    }
    else
    {
      lownibble = nibble;
      SendAscii();
    }
    firstnibble = !(firstnibble);  
 }

 if (firstnibble == 1)
 {
      highnibble = nibble;
      led7seg (0, highnibble, 1); 
      led7seg (1, lownibble, 0);  
 }
 else
 {
      lownibble = nibble;
      asciinum = highnibble * 16 + lownibble;
      led7seg (0, highnibble, 0);
      led7seg (1, lownibble, 1);   
 }
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


void led7seg (int segnum, int nibble, int decimal)
{
    int pinoffset = 0;
    if (segnum > 0)
    {
      pinoffset = 16;
    }

    switch (nibble)
    {
      case 0:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, LOW);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 1:
      {
        digitalWrite (pinoffset + led1f, LOW);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, LOW);
        digitalWrite (pinoffset + led1g, LOW);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 2:
      {
        digitalWrite (pinoffset + led1f, LOW);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, LOW);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 3:
      {
        digitalWrite (pinoffset + led1f, LOW);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 4:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, LOW);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 5:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 6:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);        
        break;
      }
      case 7:
      {
        digitalWrite (pinoffset + led1f, LOW);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, LOW);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);        
        break;
      }
      case 8:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 9:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, LOW);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 10:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 11:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, LOW);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 12:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, LOW);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, LOW);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 13:
      {
        digitalWrite (pinoffset + led1f, LOW);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, LOW);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, HIGH);
        digitalWrite (pinoffset + led1c, HIGH);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 14:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, HIGH);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, LOW);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }
      case 15:
      {
        digitalWrite (pinoffset + led1f, HIGH);
        digitalWrite (pinoffset + led1e, HIGH);
        digitalWrite (pinoffset + led1a, HIGH);
        digitalWrite (pinoffset + led1g, HIGH);
        digitalWrite (pinoffset + led1d, LOW);
        digitalWrite (pinoffset + led1b, LOW);
        digitalWrite (pinoffset + led1c, LOW);
        digitalWrite (pinoffset + led1p, decimal);
        break;
      }  
    }
}

