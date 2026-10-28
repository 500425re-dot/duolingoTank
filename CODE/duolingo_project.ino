#include <AFMotor.h>
#define tazerPin 10 //Needs to be ON to power down en OFF to power up
unsigned long time;
unsigned long antTime;
bool tazerState = 0;
char data = '0';

//inicializando motores
AF_DCMotor motor(1);
AF_DCMotor motor2(2);
void setup() {
  // put your setup code here, to run once:
pinMode(tazerPin, OUTPUT);
Serial.begin(9600);
digitalWrite(tazerPin, HIGH);

//setando motores
	motor.setSpeed(200);
	motor.run(RELEASE);
  motor2.setSpeed(200);
	motor2.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
if( Serial.available() > 0){ 

  data = Serial.read();
  if(data == '1' && tazerState == 0){ 
   digitalWrite(tazerPin, LOW);
   tazerState = 1;
   antTime = time;
  } else if(data == '0'){ 
    digitalWrite(tazerPin, HIGH);
    motor.run(RELEASE);
    motor2.run(RELEASE);
  }

  //motor control plus move direction
  if(data == '2'){ //2 dc high torque motors:
    motor.run(FORWARD);
    motor2.run(FORWARD);
  }else if(data == '3'){  //left
    motor.run(BACKWARD);
    motor2.run(FORWARD);

  }else if(data == '4'){ // right
    motor.run(FORWARD);
    motor2.run(BACKWARD);

  }else if(data == '5'){ //backwards
    motor.run(BACKWARD);
    motor2.run(BACKWARD);
  }

 }

//tazer delay
time = millis();
if(tazerState == 1 && time - antTime >= 5000){
  tazerState = 0;
  antTime = time;
 }else if(tazerState == 1 && time - antTime >= 1000)
   digitalWrite(tazerPin, HIGH);
}
