int const buzzPin = 13;
int const trigPin = 9;
int const echoPin = 10;
int const GNDPin= 11;
int const VCCPin=8;
const int ENAPin=2;
const int ENBPin=3;
const int rMotFwd=4;  
const int rMotRev=5; 
const int lMotFwd=6;
const int lMotRev=7; 
const int onblack= 300;  // reading for black line is less than this
const int onWhite= 900; // reading for white line is greater than this


void setup() {
   Serial.begin(9600);
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT); 
   pinMode(buzzPin, OUTPUT);
   pinMode(GNDPin, OUTPUT);
   pinMode(VCCPin,OUTPUT);  
   pinMode(A1,INPUT);  //extreme left sensor
   pinMode(A2,INPUT);  //left
   pinMode(A4,INPUT);   // right
   pinMode(A5,INPUT);  // extreme right sensor
   pinMode(A3,INPUT);  // middle sensor
   pinMode(ENAPin, OUTPUT);
   pinMode(ENBPin, OUTPUT);
   pinMode(lMotFwd,OUTPUT);  //left motor forward
   pinMode(rMotFwd,OUTPUT);  //right motor forward
   pinMode(lMotRev,OUTPUT);  //left motor reversed
   pinMode(rMotRev,OUTPUT);  //right motor reversed
 }

bool isOnBlack(int sensor){ //check if the sensor is on black line

  if( sensor<=onblack)
  return true;
  else
  return false;
 }

bool isOnWhite(int sensor){ //check if the sensor is on white line
  if(sensor>=onWhite)
  return true;
  else
  return false;
 }

void moveForward() //the robot moves fwd
 {
   digitalWrite(lMotFwd,LOW); 
   digitalWrite(rMotFwd,LOW);

   digitalWrite(rMotRev,HIGH);
   digitalWrite(lMotRev,HIGH);
    
 }

void turnLeft() //the robot turns left
{
   digitalWrite(lMotFwd,LOW);
   digitalWrite(rMotFwd,LOW);

    
   digitalWrite(rMotRev,LOW); 
   digitalWrite(lMotRev,HIGH);
}


void turnRight() //the robot turns right
{
   digitalWrite(lMotFwd,LOW);
   digitalWrite(rMotFwd,LOW);
    
   digitalWrite(lMotRev,LOW);
   digitalWrite(rMotRev,HIGH);
}

void Stop() //the robot stops
{

   digitalWrite(lMotFwd,LOW);
   digitalWrite(rMotFwd,LOW);
   digitalWrite(lMotRev,LOW);
   digitalWrite(rMotRev,LOW);
  
}

void loop() {
  int duration, distance;
  int sensor1=analogRead(A1);//sensor1  
  int sensor2=analogRead(A2);//sensor2 
  int sensor4=analogRead(A4);//sensor4  
  int sensor5=analogRead(A5);//sensor5
  int sensor3=analogRead(A3);//sensor3  
  digitalWrite(GNDPin, LOW);
  digitalWrite(VCCPin, HIGH);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  // Measure the pulse input in echo pin
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; //distance to the obstacle
  Serial.print(distance);
  if (distance <= 10 && distance >0) { 
    Stop(); //robot stops
  digitalWrite(buzzPin, HIGH); //buzzer on
  } 
  else {
  digitalWrite(buzzPin, LOW);
  delay(60); 
  digitalWrite(ENAPin, HIGH);
  digitalWrite(ENBPin, HIGH);
  //display on serial monitor sensors' values
  Serial.print("extreme Left(1): ");
  Serial.print(sensor1);
  Serial.print("\t lower left(2): ");
  Serial.print(sensor2);
  Serial.print("\t lowerRight: ");
  Serial.print(sensor4);
  Serial.print("\t Extreme Right(5): ");
  Serial.println(sensor5);
  Serial.print("\t middle(3): ");
  Serial.print(sensor3);
  
  if(isOnWhite(sensor2) && isOnWhite(sensor4)){ //if the left and right sensors are on white, move fwd
    moveForward();
    }else
  if(isOnWhite(sensor1)&& isOnBlack(sensor2)&& isOnWhite(sensor4)&& isOnWhite(sensor5)){ //if the left sensor is on black, turn right
    turnRight();
    }else
  if(isOnWhite(sensor1)&& isOnWhite(sensor2)&& isOnBlack(sensor4)&& isOnWhite(sensor5)){ //if the right sensor is on black, turn left
    turnLeft();
    }else
  if(isOnBlack(sensor5)&& isOnWhite(sensor1)){ //if the extreme right sensor is on black, move left
    turnLeft();
    }else
  if(isOnBlack(sensor1)&& isOnWhite(sensor5)){ //if the extreme left sensor is on black, move right
    turnRight();

  }
}
}
