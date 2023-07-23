//A wall following bot based on PID Algorithm
#define TRIG_PINL  3
#define ECHO_PINL     2
 #define VCC   6

#define TRIG_PINF  5
#define ECHO_PINF     4

int en1 = 7;
int en2 = 8;
int en3 = 12;
int en4 = 11;
int enA = 9;
int enB = 10;

//condition return values in the presence of an obstacle 
int NO_OBS = 0;
int OBS = 1;

//left distance to follow is 20cm nd front obstacle distance is 35cm
int LEFT_DISTANCE= 20;
int FRONT_DISTANCE = 35;

int Left_Stat = 0;
int Front_Stat = 0;

//Obstacle in Left PID values
float Kp_l = 6;
float Ki_l = 0;
float Kd_l = 3;

//Obstacle in Front Sharp right turn PID values
float Kp_F = 10;
float Ki_F = 0; 
float Kd_F = 4; 

//variables for left pid
float Error = 0;
int  Correction = 0;
float Integ = 0;
float Deriv = 0;
float LastError = 0;



int LeftTurnSpeed = 0;
int RightTurnSpeed = 0;

//here 0 stands for true and 1 stands for false
int rightTurnBegin = 0;
int leftTurnBegin = 0;
int straightLineBegin = 0;
long Left;


void setup() {
//initialize  
  delay(1200);
  Serial.begin(9600);//serial monitor output
  for (int i= 6; i<= 12; i++)
  pinMode(i, OUTPUT);
   digitalWrite(vcc , HIGH);//vcc 5v for left sensor
  pinMode(TRIG_PINF, OUTPUT);
  pinMode(TRIG_PINL, OUTPUT);
  pinMode(ECHO_PINF ,INPUT);
  pinMode(ECHO_PINL , INPUT);


}

void loop() {
  //code here is running repetatively
 
beginning:

//    delay(1200);
    //when a the bot starts following the straight line(until there is a obstacle,initialize the flag to true
    rightTurnBegin = 0;

    Left = readRangeWall();//checking left status
     
     Serial.println(Left);
    Error = Left - LEFT_DISTANCE;//calculate error proportional
    Integ = (Error + Integral);//integral error
    Deriv = (Error - LastError);// derivative error
    Serial.println(Error);

    Correction = Kp_l * Error + Kd_l * Deriv + Ki_l * Integ;//for left wall follow, pid correction

    Serial.println("Correction");
        Serial.println(Correction);


    Front_Status = FIND_FRO_OBS();//what is the status in front

    if(Front_Status == OBS ) {

        //I Initialize WALL only once just in the beginning of right turn
        if (rightTurnBegin == 0)
          INITIALIZE_WALL();
          CONTINUE_WALL_FRO();

        //right turn flag false, until the next time there arises a right turn
        rightTurnBegin = 1;
        straightLineBegin = 0;

        goto beginning;
    }

    //if error is less than 10, means the robot is following the wall correctly, keep continuing
    else  {

      //Initialize the wall, just in the beginning of straight line
      if (straightLineBegin == 0)
        INITIALIZE_WALL();

      if(Correction > 90 && Correction > 0)//since the base speed is 128 we want the motor to have values only between
        Correction = 90;// 0-255 so we map 128+- correction so that it always falls in our desired range of pwm 0-255

      if(Correction < -90 && Correction < 0)
        Correction = -90;//l298 handles negative speeds like 255 in +ve 
        //gives max speed but -255 is zero speed and -1 is full speed whith no direction changes whatsoever 

      LeftTurnSpeed = (90 -Correction);
      RightTurnSpeed = (90 +Correction);

      leftTurnBegin = 0;
      straightLineBegin = 1;
    

    }

      analogWrite(enB,RightTurnSpeed);//setting pwm speed
      analogWrite(enA,LeftTurnSpeed);
     Serial.println("UNDER LEFT CORRECTION");//some debug help using serial montiro
     Serial.println("RMS:");
     Serial.println(RightTurnSpeed);

     Serial.println("LMS:");
     Serial.println(LeftTurnSpeed);
    

  
    MOVE();//sets the l298n to make the wheels right and left both to go forward.
   
   
    LastError = Error;
    INITIALIZE_WALL_FRONT();

}
//Utility Functions - use case depends on the bot and the path and local environment 
void INITIALIZE_WALL(void) {//just initialization for smooth operation
  Integral = 0;
  Derivative = 0;
  LastError = 0;
}

void INITIALIZE_WALL_FRONT(void) {
  Integral_F = 0;
  Derivative_F = 0;
  LastError_F = 0;
}


//When there is an obstacle in front, take a right turn 

void CONTINUE_WALL_FRO(void) {
  //As the bot was quite heavy , direct speeds were provided to the motor 
        analogWrite(enA,200);
        analogWrite(enB,0);
        FORWARD();
        delay(600);//makes sure of a complete turn 
}


int FIND_LEFT_OBS(void) {// returnss whether left wall is present or not
  Serial.println("Left Distance=");
  Serial.println(readRangeWall());
     if(readRangeWall() < DISTANCE)
       return OBSTACLE;
     else
      return NO_OBSTACLE;
}

int FIND_FRO_OBS(void) {//whether front obstacle is present or not
  Serial.println("Front Distance=");
  Serial.println(readRangeFront());
     if(readRangeFront() < FRONT_DISTANCE)
       return OBS;
     else
       return NO_OBS;
}

int readRangeFront(){// initializes and completes the hcsr04 commands and finally obtains and returns the front sensor value
 long dur;
 digitalWrite(TRIG_PINF, LOW); 
 delayMicroseconds(2);
 digitalWrite(TRIG_PINF, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PINF, LOW);
 dur = pulseIn(ECHO_PINF, HIGH);
 return (dur/50);
}

int readRangeWall(){// initializes and completes the hcsr04 commands and finally obtains and returns the left sensor value
  long dur;
 digitalWrite(TRIG_PINL, LOW); 
 delayMicroseconds(2);
 digitalWrite(TRIG_PINL, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PINL, LOW);
 dur = pulseIn(ECHO_PINL, HIGH);
 return (dur/50);
}
  void MOVE() {//sets the motor driver pins for a forward motion 
    digitalWrite(en1,HIGH);   
    digitalWrite(en2,LOW);
    digitalWrite(en3, HIGH);  
    digitalWrite(en4, LOW);
    }
