
#include <Servo.h>

const int FLEX_PIN0 = A0; // Pin connected to voltage divider output
const int FLEX_PIN1 = A1; 
const int FLEX_PIN2 = A2; 
const int FLEX_PIN3 = A3; 
const int FLEX_PIN4 = A4; 


// Measure the voltage at 5V and the actual resistance of your
// 10k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 14500.0; // Measured resistance of 3.3k resistor

// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight *********************
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg
Servo myservo0;  // create servo object to control a servo
Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 

int val;
int angle0=0;
int angle1=0;
int angle2=0;
int angle3=0;
int angle4=0;
int anglet=0;
int button=0;
int lastCommand = 0; 
int breaking =0;
void setup() 
{
  
  Serial.begin(9600);
  pinMode(FLEX_PIN0, INPUT);
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
  myservo0.attach(3);  // attaches the servo on pin 10 to the servo object
  myservo1.attach(5);
  myservo2.attach(6);
  myservo3.attach(9);
  myservo4.attach(10);

}

void loop() 
{ 


  if (Serial.available() > 0)
  {
    String data = Serial.readStringUntil('.');
    char a = data.charAt(0);
    lastCommand = ((int)a)-48;
  }
   
   switch (lastCommand)
   {
    case 1 : both_led_OFF (); first_led_ON (); break;
    case 2 : both_led_OFF (); second_led_ON (); break;
    case 3 : both_led_OFF (); break;
    case 4 : breaking =0; break;
    case 5 : breaking =1; break;
    //case 6 : ; break;
   }

  if (breaking==0){
   move0();
   move1();
   move2(); 
   move3();
   move4(); 
}
   

  delay(60);
}

void move0 ()
{
   int flexADC0 = analogRead(FLEX_PIN0);
   float flexV0 = flexADC0 * VCC / 1023.0;
   float flexR = R_DIV * (VCC / flexV0 - 1.0);

   float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
   ////Serial.println("Bend: " + String(angle) + " degrees");
   
    if (angle >0 && abs(angle - angle0) > 15)
    { 
     myservo0.write(angle+55);
      angle0=angle;
    }
}

void move1 ()
{
   int flexADC0 = analogRead(FLEX_PIN1);
   float flexV0 = flexADC0 * VCC / 1023.0;
   float flexR = R_DIV * (VCC / flexV0 - 1.0);

   float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
  ////Serial.println("Bend: " + String(angle) + " degrees");
   
    if (angle >0 && abs(angle - angle1) > 15)
    { 
     myservo1.write((angle-30)*0.9);
      angle1=angle;
    }

}

void move2 ()
{
   int flexADC0 = analogRead(FLEX_PIN2);
   float flexV0 = flexADC0 * VCC / 1023.0;
   float flexR = R_DIV * (VCC / flexV0 - 1.0);

   float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
 //  //Serial.println("Bend: " + String(200-angle) + " degrees");

    if (angle >0 && abs(angle - angle2) > 25)
    { 
     myservo2.write(220-angle);
      angle2=angle;
    }

}

void move3 ()
{
   int flexADC0 = analogRead(FLEX_PIN3);
   float flexV0 = flexADC0 * VCC / 1023.0;
   float flexR = R_DIV * (VCC / flexV0 - 1.0);

   float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
 //  //Serial.println("Bend: " + String(angle) + " degrees");
   
    if (angle >0 && abs(angle - angle3) > 15)
    { 
     myservo3.write(angle);
      angle3=angle;
    }

}

void move4 ()
{
   int flexADC0 = analogRead(FLEX_PIN4);
   float flexV0 = flexADC0 * VCC / 1023.0;
   float flexR = R_DIV * (VCC / flexV0 - 1.0);

   float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
 //  //Serial.println("Bend: " + String(angle) + " degrees");
   
    if (angle >0 && abs(angle - angle4) > 10)
    { 

      myservo4.write((200-angle));

     angle4=angle; 
      
     
      }
     
    }

void first_led_ON ()
{
  digitalWrite(11, HIGH);
}

void second_led_ON ()
{
  digitalWrite(12, HIGH);
}

void both_led_OFF ()
{
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void brake ()
{
  digitalWrite(13, HIGH);
}

void releasse ()
{
  digitalWrite(13, LOW);
}

