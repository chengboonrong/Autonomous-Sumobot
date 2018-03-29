#include <SoftwareSerial.h>
#include <MotorControl.h>

const int echoPin ;
const int trigPin ;

int a1, a2;

MotorControl motorL(6, 5, 0, 'H');
MotorControl motorR(11, 10, 0, 'H');

void setup()
{
  pinMode(echoPin, LOW);
  pinMode(trigPin, HIGH);
  Serial.begin(9600);
}

bool check = false;
long duration;
double distance_cm;
const int normal_spd = 100;
const int full_spd = 300;

void loop()
{
  if (enemy_spotted()) {
    if (distance_cm < 150) {
      forward(full_spd);
    }
    else {
      forward(normal_spd);

    }
  }


    else{
      brake();
    }
}

  // functions
  bool enemy_spotted() {
    if (distance_cm >= 80 and distance_cm <= 250) {
      check = true;
    }
    return check;
  }

  void self_rotate() {
    motorR.speed(normal_spd);
    motorL.speed(-normal_spd);
    delay(1000);
  }

  void turnleft()
  {
    motorR.speed(normal_spd);
    motorL.speed(0);
    delay(1000);
  }

  void turnright()
  {
    motorR.speed(0);
    motorL.speed(normal_spd);
    delay(1000);
  }

  void forward(int spd)
  {
    motorR.speed(spd);
    motorL.speed(spd);
    delay(1000);
  }

  void reverse()
  {
    forward(-normal_spd);
    delay(1000);
  }

  void brake()
  {
    motorR.speed(0);
    motorL.speed(0);
    delay(1000);
  }


  void ReadSensors() // IR / ultrasonic sensors
  {
    //digitalWrite(D1, HIGH); // Turn on LED
    delayMicroseconds(500);
    //a1 = analogRead(A1);
    //digitalWrite(D2, HIGH);
    //a2 = analogRead(A2);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance_cm = duration * (0.034 / 2);
    Serial.print(distance_cm);
    Serial.println("cm ");
  }
