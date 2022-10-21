#include <Servo.h>
#include "tones.h"


// Servo Stuff
Servo myservo;
int pos = 0;


// Sound Stuff

int melody[] = { // Hedwig's theme fromn the Harry Potter Movies
  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2, 
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  // NOTE_F4, 2, NOTE_GS4, 4,
  // NOTE_D4, -1, 
  // NOTE_D4, 4,
};

int tempo = 144;
int buzzer = 11;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

// Proximity Stuff
#define echoPin 2
#define trigPin 3
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


// Moar Sound Stuff
void playSong() {
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }
    tone(buzzer, melody[thisNote], noteDuration*0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void sweepServo() {
    for (pos = 0; pos <= 180; pos += 2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos); 
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 2) { 
    myservo.write(pos);
    delay(15); 
  }
}

void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  myservo.attach(9);
}

void loop() {
  checkDistance();
  if (distance < 50) {
    playSong();
    sweepServo();
  }
}