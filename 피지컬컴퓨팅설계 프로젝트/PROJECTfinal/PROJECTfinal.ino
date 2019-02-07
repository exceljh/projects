#include <Stepper.h>
#include <SoftwareSerial.h>
const int stepsPerRevolution = 64;
Stepper myStepper(stepsPerRevolution, 11,9,10,8);
SoftwareSerial BT(2,3); // TX->2, RX->3


#define C 262 // 도 
#define D 294 // 레 
#define E 330 // 미 
#define F 349 // 파 
#define G 392 // 솔 
#define A 440 // 라 
#define B 494 // 시 

const int  speakerPin = 12; //piezo
const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;
const int ledPin4 = 7;

//징글벨
char notes1[] = "eeeeeeegcde fffffeeeeddedg";
int beats1[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

//땡떙떙
int notes2[25] = { G, G, A, A, G, G, E, G, G, E, E, D, G, G, A, A, G, G, E, G, E, D, E, C }; 


int tempo1 = 100; //징글벨
int tempo2 = 100; //땡땡땡

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone); 
  }
}

//징글벨
void playNote1(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}


void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(300);
  BT.begin(9600);
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  
}

void loop() {
   Serial.println(analogRead(lightPin)); 
  
  if(BT.available())
  {
    char data = BT.read();
    if(data=='1') //1=spin
    {
    for(int i=0; i<1000; i++){
    myStepper.step(stepsPerRevolution);
   if(BT.read()=='2') // stop
   break;
  
   }
   
   }
  if(data=='3')//징글벨 sing, sound
  {
    for (int i = 0; i < 26; i++) {
          myStepper.step(stepsPerRevolution);
    if (notes1[i] == ' ') {
      delay(beats1[i] * tempo1); // rest
    } else {
      playNote1(notes1[i], beats1[i] * tempo1);
    }
    // pause between notes
    delay(tempo1 / 2); 
  }
  }
  if(data=='4'){// 땡떙땡 sing, sound
   for (int i = 0; i < 12; i++) {
        myStepper.step(stepsPerRevolution); 
     tone (speakerPin, notes2[i], tempo2); 
    delay (300); 
  } 
  delay(100); // 멜로디 중간에 짧게 멈추는 용도 

  for (int i = 12; i < 25; i++) {
        myStepper.step(stepsPerRevolution); 
    tone (speakerPin, notes2[i], tempo2); 
    delay(300); 
  } 
  
  }
if(data=='5') // all right
{
  while(1){
    myStepper.step(stepsPerRevolution);
  digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin4,HIGH);  
  
if(BT.read()=='5')
{  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);  
  break;
  
  }
  }
}

if(data=='6') //blink right
{
  while(1)
  {
    myStepper.step(stepsPerRevolution);
  digitalWrite(ledPin4,LOW);    
digitalWrite(ledPin1,HIGH);
delay(10);
myStepper.step(stepsPerRevolution);
digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,HIGH);
delay(10); 
myStepper.step(stepsPerRevolution);
digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,HIGH);
delay(10);
myStepper.step(stepsPerRevolution);
digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,HIGH);
delay(10);
if(BT.read()=='6')
{ digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);  
  
  break;
  }
    }
  }
  
if(data=='7') // spin, right, sound
{
 digitalWrite(ledPin1,HIGH);
  digitalWrite(ledPin2,HIGH);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin4,HIGH);  

 for (int i = 0; i < 26; i++) {
          myStepper.step(stepsPerRevolution);
    if (notes1[i] == ' ') {
      delay(beats1[i] * tempo1); // rest
    } else {
      playNote1(notes1[i], beats1[i] * tempo1);
    }
    // pause between notes
    delay(tempo1 / 2); 
  }
 
  
  }
 
if(data=='8') // right off
{  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);  
  
  }

  
  }
  Serial.write(BT.read());
  if(Serial.available())
  BT.write(Serial.read());
  
}
