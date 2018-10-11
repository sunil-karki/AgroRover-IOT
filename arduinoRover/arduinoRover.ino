//RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).
#include<SoftwareSerial.h>
#include <dht.h>
#include <Servo.h>
Servo servo1;
Servo servo2;

dht DHT;                  //sensors...
#define DHT11_PIN 41                        //pin 41

SoftwareSerial ArduinoSerial(53,52);  //Rx, Tx   
                                           //pin 52 and 53
int key=1;
//right side motor control

int IN1 = 42;                              //pin 42
int IN2 = 43;                              //pin 43
//enable right  
int IN_ENABLE1 = 6;                        //pin 6
    
//left side motor control
int IN3 = 44;                              //pin 44
int IN4 = 45;                              //pin 45
//enable left 
int IN_ENABLE2 = 5;                        //pin 5

//watering...
int WA2 = 26;                              //pin32

//  DRILLER AND GEAR..
int OM1 = 36;                              //pin 36....gear
int OM2 = 37;                              //pin 37....gear
int OM_ENABLE1 = 10;                       //pin 10....gear

int OM3 = 38;                              //pin 38
int OM4 = 39;                              //pin 39
int OM_ENABLE2 = 11;                       //pin 11

int gear_speed = 60;
int motor_speed = 80;
float val;  //command from Module
float drill_count = 0;
String drill_times;

long duration;
int distance;
const int trigPin = 48;//7;  //9
const int echoPin = 49;//2;  //10

float temperature_1;
float humidity_1;

String temperature_2;
String humidity_2;

void setup() {
 
  Serial.begin(115200);
  ArduinoSerial.begin(4800);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
    pinMode(IN_ENABLE1, OUTPUT);
    pinMode(IN_ENABLE2, OUTPUT);

  pinMode(OM1, OUTPUT);
  pinMode(OM2, OUTPUT);
  pinMode(OM3, OUTPUT);
  pinMode(OM4, OUTPUT);
    pinMode(OM_ENABLE1, OUTPUT);
    pinMode(OM_ENABLE2, OUTPUT);

  pinMode(WA2, OUTPUT);
  
  servo1.attach(9);                    //servo_flap  pin 9
  servo2.attach(7);                   //servo_pipe   pin 7 

pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(115200); // Starts the serial communication

digitalWrite(OM1, HIGH);  //up
    digitalWrite(OM2, LOW);
    analogWrite(OM_ENABLE1, 36);
  
}


void loop() {
  //ArduinoSerial.print(21);
  //ArduinoSerial.print("\n");


  while( ArduinoSerial.available()>0 )
  {
    val = ArduinoSerial.parseFloat();
    if(ArduinoSerial.read() == '\n')
    {
      Serial.println(val);
     // Serial.print();
    }
  }

  if(val==5)
  {
      startRover();
  }
  else if(val == 10)     //10 means move the robot
  {
      forward();
  }
  else if(val == 20)             //20 means stop robot
  {
      stop_it();
      val = 0;
  }
  else if(val == 30)
  {
      leftTurn();
  }
  else if(val == 40)
  {
      rightTurn();
  }
  else if(val == 50)
  {
      back();
  }
  else if(val == 55)
  {
    driller_gear();
    val = 0;       //initializing back to original value
  }
  else if(val == 60)
  {
    servo_pipe();
    val = 0;
  }
  else if(val == 65)
  {
    servo_flap_up();
    val = 0;
  }
  else if(val == 67)
  {
    servo_flap_down();
    val = 0;
  }
  else if(val == 70)
  {
    water();
    val = 0;
  }
  else if(val == 72)
  {
     temp_hum();
     send_data();
     val = 0;
  }

  
}





void forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(IN_ENABLE1, 110);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(IN_ENABLE2, 110);
  Serial.println("forward");
  //delay(2000);
}

void stop_it()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(IN_ENABLE1, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(IN_ENABLE2, 0);
  //delay(2000);
  Serial.println("stop");
}

void leftTurn(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(IN_ENABLE1, 88);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(IN_ENABLE2, 88);
  Serial.println("leftTurn");
 // delay(2000);
 Serial.println("left");
}

void rightTurn(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(IN_ENABLE1, 88);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(IN_ENABLE2, 88);
  Serial.println("rightTurn");
 // delay(2000);
 Serial.println("right");
}

void back()
{
  digitalWrite(IN1, LOW); //7,6,5,4
  digitalWrite(IN2, HIGH);
  analogWrite(IN_ENABLE1, 110);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(IN_ENABLE2, 110);
  Serial.println("reverse");
 // delay(2000);
}

void servo_flap_down(){
   servo1.write(110);
   delay(400);
} 

void servo_flap_up(){
   servo1.write(90);
   delay(400);
  
   } 
  


void servo_pipe()
{
   servo2.write(30);
   delay(400);
   servo2.write(40);
   //delay(400);
   Serial.println("servo_pipe");
}

void driller_gear_stop()
{
     digitalWrite(OM1, LOW);      
      digitalWrite(OM2, LOW);
      analogWrite(OM_ENABLE1, 0);
      
     digitalWrite(OM3, LOW);
     digitalWrite(OM4, LOW);
     analogWrite(OM_ENABLE2, 0);
        delay(20);
}

void driller_gear()
{
     digitalWrite(OM1, LOW);  //down
  digitalWrite(OM2, HIGH);
  analogWrite(OM_ENABLE1, 30); //36  //60
  
  digitalWrite(OM3, HIGH);
  digitalWrite(OM4, LOW);
  analogWrite(OM_ENABLE2, 60);

   delay(2000);

  digitalWrite(OM3, HIGH);
  digitalWrite(OM4, LOW);
  analogWrite(OM_ENABLE2, 60);
   delay(5000);
   
   digitalWrite(OM3, LOW);  //DRILLER
  digitalWrite(OM4, HIGH);
  analogWrite(OM_ENABLE2, 60);

   digitalWrite(OM1, HIGH);  //down
  digitalWrite(OM2, LOW);
  analogWrite(OM_ENABLE1, 58);

  delay(6000);

  digitalWrite(OM1, HIGH);  //up
    digitalWrite(OM2, LOW);
    analogWrite(OM_ENABLE1, 36);
  delay(2000);  
  digitalWrite(OM3, LOW);  //DRILLER
  digitalWrite(OM4, LOW);
  analogWrite(OM_ENABLE2, 0);

     drill_count = drill_count +1;
                        
            drill_times = String(drill_count, DEC);
  delay(2000);
  
}


void water()
{     
   digitalWrite(WA2, HIGH);
   delay(15000);
   digitalWrite(WA2,LOW);
}

void startRover()
{
       while( 1 )
       { 
        
            servo_flap_down();
            kq:
               //obstacle detecton...    
          if(ultrasonic_obstacle()<= 19)                      //obstacle within 7cm
          {
             stop_it();
             goto kq;
          }
               
       
        forward();
        delay(2000);               //moves for 2 sec
        stop_it();
            servo_flap_up();
            delay(300);
        driller_gear();
 //           drill_count = drill_count +1;
                        
   //         drill_times = String(drill_count, DEC);
                        
        delay(900);
        servo_pipe();
             
        delay(20);                        //servo le kaam gareko heri rahada sensor is working
      
        water();
//Taking data from dht
      temp_hum();

// float to string conversion.....
 /*     temperature_2 = String(temperature_1);
      humidity_2 = String(humidity_1);

      ArduinoSerial.print('\a');
      ArduinoSerial.print(drill_times);
      ArduinoSerial.print("\f");

      ArduinoSerial.print(temperature_2);
      ArduinoSerial.print('\n');
      
      ArduinoSerial.print(humidity_2);
      ArduinoSerial.print('\r');
 */    
     
   delay(2000);
 }     //end of while loop
}

float ultrasonic_obstacle()
{
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
delay(200);
return distance;
}

void temp_hum()
{
  int chk = DHT.read11(DHT11_PIN);
   
  temperature_1 = DHT.temperature;
        
  humidity_1 = DHT.humidity;
  delay(100);
}

void send_data()
{
      temperature_2 = String(temperature_1);
      humidity_2 = String(humidity_1);

      ArduinoSerial.print('\a');
      ArduinoSerial.print(drill_times);
      ArduinoSerial.print("\f");

      ArduinoSerial.print(temperature_2);
      ArduinoSerial.print('\n');
      
      ArduinoSerial.print(humidity_2);
      ArduinoSerial.print('\r');
}

