// initial condition
int lock1;
int lock2;
int lock3;
int key1 = random(0,500);
int key2 = random(0,500);
int key3 = random(0,500);
boolean start = true;

#define echoPin 6 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D3 Arduino to pin Trig of HC-SR04
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
lcd.begin(16, 2);

}

void loop() {
digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  
  // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //LCD to show the process of game
  if(start){
lcd.setCursor(0, 1);
  lcd.print("Game start!");
  }
digitalWrite(8,LOW);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
lock1 = analogRead(A0);
lock2 = analogRead(A1);
lock3 = analogRead(A2);
if(abs(lock1-key1)<15){
  digitalWrite(8,HIGH);
}
if(abs(lock2-key2)<15){
  digitalWrite(9,HIGH);
}
if(abs(lock3-key3)<15){
  digitalWrite(10,HIGH);
}

// detection of too much motion
if(start){
if((distance<3)&&(distance!=0)){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Be Found");
  lcd.setCursor(0,1);
  lcd.print("Game over!");
  tone(13,300);
  delay(1500);
  noTone(13);
  start = false;
}

// The victory condition
if(abs(lock1-key1)<15&&abs(lock2-key2)<15&&abs(lock3-key3)<15){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Victory!");
}
}
}
