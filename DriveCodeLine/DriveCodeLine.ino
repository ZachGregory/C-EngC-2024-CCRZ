#include <ESP32Servo.h>
Servo myservo;

#define m1PWM 14  //PWM
#define m1Dir 25


#define m2PWM 27  //PWM
#define m2Dir 33

#define trigPin 13  // Ultrasonic Sensor
#define echoPin 34

#define servoPin 26   // Servo

char lineArray[180][20];  // variable to store colours during sweep

//const int s0 = 26;  // Colour sensor
//const int s1 = 27;  
const int s2 = 12;  
const int s3 = 26;  
const int out = 35;   

long duration;
float distance;

int pos = 0;    // variable to store the servo position

// values
int red = 0;  
int green = 0;  
int blue = 0;  

float distArray[180];
int objectLeftAngle;
int objectRightAngle;

float thresh = 10.0;
int sweepAngle = 30;  // Angle to execute the sweep in


void setup() {
  Serial.begin(115200);

  pinMode(m1PWM, OUTPUT);
  pinMode(m1Dir, OUTPUT);
  pinMode(m2PWM, OUTPUT);
  pinMode(m2Dir, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  
  digitalWrite(s0, LOW);  
  digitalWrite(s1, HIGH);  

  myservo.attach(servoPin, 1000, 2000); // attaches the servo


  forward();
}

void loop() {
  // 180 turn
  right();
  setSpeed(150);
  delay(500);




  if (blue > 750 && blue < 900 && red > 700 && red < 900 && green > 200 && green < 300){  
    Serial.println("Blue Tape");
  } else if (blue > 700 && blue < 900 && red > 700 && red < 900 && green > 190 && green < 300){  
    Serial.println("Green Tape");
  } else if (blue > 390 && blue < 500 && red > 380 && red < 550 && green > 180 && green < 300){  
    Serial.println("Red Tape");
  } else if (blue > 300 && blue < 400 && red > 300 && red < 400 && green > 110 && green < 250){  
    Serial.println("Yellow Tape");
  } else if (blue > 750 && blue < 1100 && red > 750 && red < 1100 && green > 200 && green < 350){  
    Serial.println("Black Tape");
  } else {
    Serial.println("Table");
  }

  

}

//============ FUNCTIONS =============

void setSpeed(int speed){
  // Speed is the PWM value between 0 and 255
  analogWrite(m1PWM, speed);
  analogWrite(m2PWM, speed);
}

void stop(){
  // Speed is the PWM value between 0 and 255
  analogWrite(m1PWM, 0);
  analogWrite(m2PWM, 0);
}

void forward(){
  digitalWrite(m1Dir, HIGH);
  digitalWrite(m2Dir, HIGH);
}

void backward(){
  digitalWrite(m1Dir, LOW);
  digitalWrite(m2Dir, LOW);
}

void left(){
  digitalWrite(m1Dir, LOW);
  digitalWrite(m2Dir, HIGH);
}

void right(){
  digitalWrite(m1Dir, HIGH);
  digitalWrite(m2Dir, LOW);
}

float pulse(){
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin and calculate the pulse duration in microseconds
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout of 30ms (30000us)

  // Calculate distance in centimeters (speed of sound = 343 m/s)
  distance = duration * 0.034 / 2; // 0.034 cm/us is the speed of sound in air
  
  // Check for out-of-range readings
  if (duration == 0) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
  }
  return 0;
}

void color(int i)  
{
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  

  if (blue > 750 && blue < 900 && red > 700 && red < 900 && green > 200 && green < 300){  
    Serial.println("Blue Tape");
    lineArray[i] = "blue";
  } else if (blue > 700 && blue < 900 && red > 700 && red < 900 && green > 190 && green < 300){  
    Serial.println("Green Tape");
    lineArray[i] = "green";
  } else if (blue > 390 && blue < 500 && red > 380 && red < 550 && green > 180 && green < 300){  
    Serial.println("Red Tape");
    lineArray[i] = "red";
  } else if (blue > 300 && blue < 400 && red > 300 && red < 400 && green > 110 && green < 250){  
    Serial.println("Yellow Tape");
    lineArray[i] = "yellow";
  } else if (blue > 750 && blue < 1100 && red > 750 && red < 1100 && green > 200 && green < 350){  
    Serial.println("Black Tape");
    lineArray[i] = "black";
  } else {
    Serial.println("Table");
    lineArray[i] = "table";
  }
}

void sweep(){
  stop();
  right();
  setSpeed(150);
  delay(200);
  left();

  //  Read the values during the sweep
  for (int i = 0; i < 90; i++){
    color(i);
  }

  right();
  delay(x); // Whatever gets us going straight on the line

}