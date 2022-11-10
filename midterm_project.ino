// LCD
#include <LiquidCrystal.h> 
int Contrast=75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

// LDRs
int ldrLower = A0;
int ldrUpper = A1;
int ldrLeft = A2;

int ledPin = 13; // LED
int buzzerPin = 9; // Buzzer

// Servos
#include <Servo.h>
int sensorValueLower = 0;
int sensorValueUpper = 0;
int sensorValueLeft = 0;
int sensorValueBuzzer = 0;
int servoLowerPin = A3;
int servoUpperPin = A4;
int servoLeftPin = A5;
Servo servoLower;
Servo servoUpper;
Servo servoLeft;

// Variables
int score = 0; // to display score on lcd
int time = 20; // for timer
int i = 0; // to move servos

// millis
unsigned long previousTimerMillis = 0;
const long interval = 1000; // for timer

void setup() {
  // LCD
  analogWrite(6,Contrast);
  lcd.begin(16, 2);

  // LDRs
  pinMode(ldrLower, INPUT);
  pinMode(ldrUpper, INPUT);
  pinMode(ldrLeft, INPUT);
  
  pinMode(ledPin, OUTPUT); // LED
  pinMode(buzzerPin, OUTPUT); // Buzzer

  // Servos
  servoLower.write(0);
  servoUpper.write(0);
  servoLeft.write(0);  
  servoLower.attach(servoLowerPin);
  servoUpper.attach(servoUpperPin);
  servoLeft.attach(servoLeftPin);
  
  // Starting the program
  Serial.begin(9600);
  Serial.println("---START---");
}
 
void loop() {
  unsigned long currentMillis = millis();

  // TIMER COUNTDOWN  
  if (currentMillis - previousTimerMillis >= interval) {
    previousTimerMillis = currentMillis;
    time -= 1;
  } 

  // Reading the values of each sensor
  sensorValueLower = analogRead(ldrLower);
  sensorValueUpper = analogRead(ldrUpper);
  sensorValueLeft = analogRead(ldrLeft);

  /*Displaying LDR's values on serial machine to make sure everything is working fine*/
  Serial.print(sensorValueLower);
  Serial.print(" | ");
  Serial.print(sensorValueUpper);
  Serial.print(" | ");
  Serial.println(sensorValueLeft);

  if(time == 0){
    // Finishing the program when timer is off
    // TONE
    tone(buzzerPin, 4000); // Send 1KHz sound signal...
    delay(500);        // ...for 1 sec
    noTone(buzzerPin);  

    // LCD
    lcd.setCursor(0, 0);
    lcd.print("   GAME  OVER ");
    lcd.setCursor(0, 1);
    lcd.print("TOTAL SCORE: ");
    lcd.print(score);

    delay(50);
    Serial.print("---> TOTAL SCORE: ");
    Serial.println(score);
    Serial.println("---GAME--OVER---");
    delay(50);
    exit(0); // stopping the loop
  } 
  else { // When the timer is still on
    // LCD
    lcd.setCursor(0, 0);
    lcd.print("SCORE: ");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print("TIME: ");
    lcd.print(time);
    lcd.print(" "); // bug solved "16x2 LCD displays all single digit integers as ‘x0’ rather than ‘0x'"

    // Moving Servos
    // Moving the Lower Servo
    if(sensorValueLower > 30) {
      Serial.println("...+3 for hitting the lower zombie");
      digitalWrite(ledPin, HIGH);
      
      for(i = 0; i < 90; i+=10) {
        servoLower.write(i);
        delay(10);
      }
      delay(500);
      for (i = 90; i > 0; i-=10) {
        servoLower.write(i);
        delay(10);     
      }           
      score += 3; // adding score to the variable          
      digitalWrite(ledPin, LOW);   
    }
    // Moving the Upper Servo
    else if(sensorValueUpper > 30) {
      Serial.println("...+1 for hitting the upper zombie");
      digitalWrite(ledPin, HIGH);
      
      for(i = 0; i < 90; i+=10) {
        servoUpper.write(i);
        delay(10);
      }
      delay(500);
      for (i = 90; i > 0; i-=10) {
        servoUpper.write(i);
        delay(10);     
      }           
      score += 1; // adding score to the variable          
      digitalWrite(ledPin, LOW);   
    }
    // Moving the Left Servo
    else if(sensorValueLeft > 30) {
      Serial.println("...+2 for hitting the left zombie");
      digitalWrite(ledPin, HIGH);
      
      for(i = 0; i < 90; i+=10) {
        servoLeft.write(i);
        delay(10);
      }
      delay(500);
      for (i = 90; i > 0; i-=10) {
        servoLeft.write(i);
        delay(10);     
      }           
      score += 2; // adding score to the variable          
      digitalWrite(ledPin, LOW);   
    }
  }
}