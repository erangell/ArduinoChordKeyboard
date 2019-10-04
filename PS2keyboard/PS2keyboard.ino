#define strobe  6
#define d5      10
#define d4      9
#define d6      11
#define d2      4
#define d3      5
#define d0      2
#define d1      3
#define reset   12

int dat[512];
char hex[16];
char scancode[7];

byte asciinum = 0;
char asciival = 0;

void setup() {
  // put your setup code here, to run once:

hex[0] = '0';
hex[1] = '1';
hex[2] = '2';
hex[3] = '3';
hex[4] = '4';
hex[5] = '5';
hex[6] = '6';
hex[7] = '7';
hex[8] = '8';
hex[9] = '9';
hex[10] = 'A';
hex[11] = 'B';
hex[12] = 'C';
hex[13] = 'D';
hex[14] = 'E';
hex[15] = 'F';

pinMode(7,INPUT); //clock
pinMode(8,INPUT); //data
pinMode(13,OUTPUT);


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


Serial.begin(9600);
Serial.println("PS2 Keyboard");

}

void loop() {
  // put your main code here, to run repeatedly:

int clk= digitalRead(8);
int prevclk = clk;
while (clk == prevclk)
{
  clk = digitalRead(8);
}
prevclk = digitalRead(8);

for (int i=0; i<512; i++)
{
  dat[i] = digitalRead(7);
  
  clk = digitalRead(8);
  while (clk = prevclk)
  {
    clk = digitalRead(8);
  }
  prevclk = clk;
}

int totct = 0;
int bitct = 8;
int prevbit = 0;
int nibct = 4;
int nibble = 0;
int hexct = 0;
for (int j=0; j<8; j++)
{
   for (int k=0; k<64; k++)
   {
      int ix = (j*10)+k;
      if ((dat[ix] != prevbit)  || (bitct == 0))
      {        
        Serial.print(prevbit);
        totct++;
        nibble = nibble * 2;
        nibble += prevbit;
        nibct--;
        if (nibct == 0)
        {
          nibct = 4;
          
          if (hexct < 6)
          {
            scancode[hexct] = hex[nibble];
          }
          hexct++;
          nibble = 0;
        }
        
        bitct = 12;
      }
      prevbit = dat[ix];
      bitct--;
   }
}
scancode[6] = '\0';
Serial.print("------------ ");
Serial.print(scancode);
Serial.print(" --- ");

char outch = ' ';
switch (scancode[0])
{
  case '0':
  {
    //ignore key up 0431C
    break;
  }
  case '1':
  {
    if (scancode[1] == '8') { 
      outch = 'T'; 
    }
    else if (scancode[1] == '0')
    {
       if (scancode[2] == '9')
       {
         outch = 'E';
       }
       else if (scancode[2] == '8')
       {
         outch = 'O';
       }
    }
    else if (scancode[1] == '4')
    {
       outch = 'G';
    }
    else if (scancode[1] == 'C')
    {
      
      if (strcmp(scancode,"1CE738")==0) 
      {
          outch = 'A'; 
      }
      else
      { 
        if (strcmp(scancode,"1CF7BC")==0)
        {
          outch = 'U';
        }
      }   
    }
    break;
  }
  case '2':
  {
    
    if (strcmp(scancode,"2F7BDE")==0)
    {
      outch = '7'; 
    }
    else if (strcmp(scancode,"294A52")==0)
    {
      outch = '4'; 
    }
    else if (strcmp(scancode,"294228")==0)
    {
      outch = '0'; 
    }
    else if (scancode[1] == '5') { 
      outch = 'B'; 
    }
    else if (scancode[1] == '1') {
      if (scancode[2] == '0') {
        outch = 'K';
      }
      else if (scancode[2]=='1') {
        outch = 'X';
      }
    }
    else if (scancode[1] == 'D') {
      if (scancode[2] == '7') {
        outch = 'M';
      }
      else if (scancode[2] == '6') {
        if (strcmp(scancode,"2D6B5A")==0)
        {
          if (totct == 46) // fix issue with R key sometimes generating CR
          {
            outch = 0x0D;
          }
        }
        else if (strcmp(scancode,"2D6B2C")==0)
        {
          outch = 'Z';
        }
      }
    }
    else if (scancode[1] == '9') {
      outch = 'V';
    }

    break;
  }
  case '3':
  {
    if (strcmp(scancode,"35BDEE")==0)
    {
      outch = 0x1B; // ESC;
    }
    else if (strcmp(scancode,"35AD34")==0)
    {
      outch = '1'; 
    }
    else if (strcmp(scancode,"35AD28")==0)
    {
      outch = '1'; 
    }
    else if (strcmp(scancode,"3DEF3C")==0)
    {
      outch = '2'; 
    }
    else if (strcmp(scancode,"3DEF38")==0)
    {
      outch = '2'; 
    }
    else if (strcmp(scancode,"319CB2")==0)
    {
      outch = '3'; 
    }
    else if (strcmp(scancode,"319CA4")==0)
    {
      outch = '3'; 
    }
    else if (strcmp(scancode,"39DEBA")==0)
    {
      outch = '5'; 
    }
    else if (strcmp(scancode,"39DEB4")==0)
    {
      outch = '5'; 
    }
    else if (strcmp(scancode,"35BDB6")==0)
    {
      outch = '6'; 
    }
    else if (strcmp(scancode,"35BDAC")==0)
    {
      outch = '6'; 
    }
    else if (strcmp(scancode,"3DFFBC")==0)
    {
      outch = '8'; 
    }
    else if (strcmp(scancode,"3DFFBE")==0)
    {
      outch = '8'; 
    }
    else if (strcmp(scancode,"318C62")==0)
    {
      outch = '9';
    }
    break;
  }
  case '4':
  {
    if (scancode[1] == '2')
    {
      outch = 'C';
    }
    else if (scancode[1] == '6')
    {
      outch = 'N';
    }
    break;
  }
  case '5':
  {
    if (strcmp(scancode,"5294A4")==0)
    {
      outch = '4';
    }
    else if (strcmp(scancode,"5EF7BC")==0)
    {
      outch = '7'; 
    }
    else if (strcmp(scancode,"528451")==0)
    {
      outch = '0'; 
    }
    else if (scancode[1] == '6')
    {
      if (scancode[2] == 'A')
      {
        outch = 'Q';
      }
      else if (scancode[2] == 'B')
      {
        outch = 'Y';
      }
    }
    else if (scancode[1] == 'A')
    {
      if (scancode[2] == 'C')
      {
        outch = 'P';
      }
      else if (scancode[2] == 'D')
      {
        outch = 'R';
      }
    }
    else if (scancode[1] == 'E')
    {
      outch = 'W';
    }

    break;
  }
  case '6':
  {
    if (scancode[1] == '3')
    {
      if (scancode[2] == '1')
      {
        outch = 'D';
      }
      else if (scancode[2] == '0')
      {
        outch = 'I';
      }
    }    
    else if (scancode[1] == 'B')
    {
      if (scancode[2] == '5')
      {
        outch = 'F';
      }
      else if (scancode[2] == '4')
      {
        outch = 'L';
      }
    }
    else if (scancode[1] == '7')
    {
      outch = 'H';
    }
    else if (scancode[1] == 'F')
    {
      if (scancode[2] == '7')
      {
        outch = 'J';
      }
      else if (scancode[2] == '6')
      {
        outch = 'S';
      }
    }
    break;
  }
  case '7':
  {
    
    break;
  }
  case '8':
  {

    break;
  }
  case '9':
  {
    
    break;
  }
  case 'A':
  {
    
    break;
  }
  case 'B':
  {

    break;
  }
  case 'C':
  {

    break;
  }
  case 'D':
  {
    
    break;
  }
  case 'E':
  {
    
    break;
  }
  case 'F':
  {

    break;
  }
}
if (outch == 0x1B)
{
  Serial.println("ESC");
}
else if (outch == 0x0D)
{
  Serial.println("CR");
}
else
{
  Serial.println (outch);
}

asciinum = outch;
SendAscii();


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


