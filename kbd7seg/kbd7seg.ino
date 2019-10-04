//Apple 2+ ascii keyboard to LEDs and 7 segment hex displays

//Top 7 segment display = A
const int pinALVT = 36;
const int pinALVB = 34;
const int pinATOP = 32;
const int pinAMID = 30;
const int pinABOT = 28; 
const int pinARVT = 26; 
const int pinARVB = 24;
const int pinADEC = 22;

//Bottom 7 segment display = B
const int pinBLVT = 52;
const int pinBLVB = 50; 
const int pinBTOP = 48;
const int pinBMID = 46;
const int pinBBOT = 44; 
const int pinBRVT = 42;
const int pinBRVB = 40;
const int pinBDEC = 38;

const int pinOUT1 = 23;
const int pinOUT2 = 25;
const int pinOUT4 = 27;
const int pinOUT8 = 29;
const int pinOUT16 = 31;
const int pinOUT32 = 33;
const int pinOUT64 = 35;

const int pinIN64 = 37;
const int pinIN32 = 39;
const int pinIN16 = 41;
const int pinIN8 = 43;
const int pinIN4 = 45;
const int pinIN2 = 47;
const int pinIN1 = 49;

int in64 = 0;
int in32 = 0;
int in16 = 0;
int in8 = 0;
int in4 = 0;
int in2 = 0;
int in1 = 0;

int show64 = 1;
int show32 = 1;
int show16 = 1;
int show8 = 1;
int show4 = 1;
int show2 = 1;
int show1 = 1;

int displayhex = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode (pinALVT, OUTPUT);
  digitalWrite (pinALVT, LOW);
  pinMode (pinALVB, OUTPUT);
  digitalWrite (pinALVB, LOW);
  pinMode (pinATOP, OUTPUT);
  digitalWrite (pinATOP, LOW);
  pinMode (pinAMID, OUTPUT);
  digitalWrite (pinAMID, LOW);
  pinMode (pinABOT, OUTPUT);
  digitalWrite (pinABOT, LOW);
  pinMode (pinARVT, OUTPUT);
  digitalWrite (pinARVT, LOW);
  pinMode (pinARVB, OUTPUT);
  digitalWrite (pinARVB, LOW);
  pinMode (pinADEC, OUTPUT);
  digitalWrite (pinADEC, LOW);

  pinMode (pinBLVT, OUTPUT);
  digitalWrite (pinBLVT, LOW);
  pinMode (pinBLVB, OUTPUT);
  digitalWrite (pinBLVB, LOW);
  pinMode (pinBTOP, OUTPUT);
  digitalWrite (pinBTOP, LOW);
  pinMode (pinBMID, OUTPUT);
  digitalWrite (pinBMID, LOW);
  pinMode (pinBBOT, OUTPUT);
  digitalWrite (pinBBOT, LOW);
  pinMode (pinBRVT, OUTPUT);
  digitalWrite (pinBRVT, LOW);
  pinMode (pinBRVB, OUTPUT);
  digitalWrite (pinBRVB, LOW);
  pinMode (pinBDEC, OUTPUT);
  digitalWrite (pinBDEC, LOW);

  pinMode (pinIN64, INPUT);
  pinMode (pinOUT64, OUTPUT);
  pinMode (pinIN32, INPUT);
  pinMode (pinOUT32, OUTPUT);
  pinMode (pinIN16, INPUT);
  pinMode (pinOUT16, OUTPUT);
  pinMode (pinIN8, INPUT);
  pinMode (pinOUT8, OUTPUT);
  pinMode (pinIN4, INPUT);
  pinMode (pinOUT4, OUTPUT);
  pinMode (pinIN2, INPUT);
  pinMode (pinOUT2, OUTPUT);
  pinMode (pinIN1, INPUT);
  pinMode (pinOUT1, OUTPUT);

  digitalWrite (pinOUT64, LOW);
  digitalWrite (pinOUT32, LOW);
  digitalWrite (pinOUT16, LOW);
  digitalWrite (pinOUT8, LOW);
  digitalWrite (pinOUT4, LOW);
  digitalWrite (pinOUT2, LOW);
  digitalWrite (pinOUT1, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  in64 = digitalRead(pinIN64);
  in32 = digitalRead(pinIN32);
  in16 = digitalRead(pinIN16);
  in8  = digitalRead(pinIN8);
  in4  = digitalRead(pinIN4);
  in2 =  digitalRead(pinIN2);
  in1 =  digitalRead(pinIN1);

  int hex1 = 8 + (in64*4) + (in32*2) + in16;
  int hex2 = (in8*8) + (in4*4) + (in2*2) + in1;
  int hextop = 0;
  int hexbot = 0;


  if (displayhex == 0)
  {
    displayhex = 1;
    hextop = 8 + (show64*4) + (show32*2) + show16;
    hexbot = (show8*8) + (show4*4) + (show2*2) + show1;
  }
  else
  {
    displayhex = 0;
    hextop = hex1;
    hexbot = hex2;
  }

  show64 = in64;
  show32 = in32;
  show16 = in16;
  show8 = in8;
  show4 = in4;
  show2 = in2;
  show1 = in1;

  if (displayhex == 0)
  {
    digitalWrite (pinOUT64, show64);
    digitalWrite (pinOUT32, show32);
    digitalWrite (pinOUT16, show16);
    digitalWrite (pinOUT8, show8);
    digitalWrite (pinOUT4, show4);
    digitalWrite (pinOUT2, show2);
    digitalWrite (pinOUT1, show1);
    
    digitalWrite (pinALVT, LOW);
    digitalWrite (pinALVB, LOW);
    digitalWrite (pinATOP, LOW);
    digitalWrite (pinAMID, LOW);
    digitalWrite (pinABOT, LOW);
    digitalWrite (pinARVT, LOW);
    digitalWrite (pinARVB, LOW);
    digitalWrite (pinADEC, LOW);
    digitalWrite (pinBLVT, LOW);
    digitalWrite (pinBLVB, LOW);
    digitalWrite (pinBTOP, LOW);
    digitalWrite (pinBMID, LOW);
    digitalWrite (pinBBOT, LOW);
    digitalWrite (pinBRVT, LOW);
    digitalWrite (pinBRVB, LOW);
    digitalWrite (pinBDEC, LOW);
  }
  else
  {
    digitalWrite (pinOUT64, LOW);
    digitalWrite (pinOUT32, LOW);
    digitalWrite (pinOUT16, LOW);
    digitalWrite (pinOUT8, LOW);
    digitalWrite (pinOUT4, LOW);
    digitalWrite (pinOUT2, LOW);
    digitalWrite (pinOUT1, LOW);
  
    switch (hexbot)
    {
      case 0:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, LOW);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 1:
      {
        digitalWrite (pinALVT, LOW);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, LOW);
        digitalWrite (pinAMID, LOW);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 2:
      {
        digitalWrite (pinALVT, LOW);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, LOW);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 3:
      {
        digitalWrite (pinALVT, LOW);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 4:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, LOW);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 5:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 6:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);        
        break;
      }
      case 7:
      {
        digitalWrite (pinALVT, LOW);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, LOW);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);        
        break;
      }
      case 8:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 9:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, LOW);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 10:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 11:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, LOW);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 12:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, LOW);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, LOW);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 13:
      {
        digitalWrite (pinALVT, LOW);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, LOW);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, HIGH);
        digitalWrite (pinARVB, HIGH);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 14:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, HIGH);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, LOW);
        digitalWrite (pinADEC, LOW);
        break;
      }
      case 15:
      {
        digitalWrite (pinALVT, HIGH);
        digitalWrite (pinALVB, HIGH);
        digitalWrite (pinATOP, HIGH);
        digitalWrite (pinAMID, HIGH);
        digitalWrite (pinABOT, LOW);
        digitalWrite (pinARVT, LOW);
        digitalWrite (pinARVB, LOW);
        digitalWrite (pinADEC, LOW);
        break;
      }  
    }
    switch (hextop)
    {
      case 0:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, LOW);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 1:
      {
        digitalWrite (pinBLVT, LOW);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, LOW);
        digitalWrite (pinBMID, LOW);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 2:
      {
        digitalWrite (pinBLVT, LOW);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, LOW);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 3:
      {
        digitalWrite (pinBLVT, LOW);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 4:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, LOW);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 5:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 6:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);        
        break;
      }
      case 7:
      {
        digitalWrite (pinBLVT, LOW);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, LOW);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);        
        break;
      }
      case 8:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 9:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, LOW);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 10:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 11:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, LOW);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 12:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, LOW);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, LOW);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 13:
      {
        digitalWrite (pinBLVT, LOW);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, LOW);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, HIGH);
        digitalWrite (pinBRVB, HIGH);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 14:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, HIGH);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, LOW);
        digitalWrite (pinBDEC, LOW);
        break;
      }
      case 15:
      {
        digitalWrite (pinBLVT, HIGH);
        digitalWrite (pinBLVB, HIGH);
        digitalWrite (pinBTOP, HIGH);
        digitalWrite (pinBMID, HIGH);
        digitalWrite (pinBBOT, LOW);
        digitalWrite (pinBRVT, LOW);
        digitalWrite (pinBRVB, LOW);
        digitalWrite (pinBDEC, LOW);
        break;
      }  
    } //switch
  } //else
  delay(3); 
} // loop
