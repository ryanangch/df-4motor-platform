// Part A: H-bridge pins to Arduino digital pins
/*Convention: 
 Only Arduino Uno pins 3,5,6,9,10,11 can be used for PWM
 pins 5,6 may experience higher duty cycle than expected
 due to interactions involving delay() & millis()

 PWM pins: 9 for  Right PWM, 10 for Left PWM
 Direction pins: 5,6,7,8, in order +-+-, RRLL
 H-bridge (right, flip +- for left side) in1, in3, out1, out3 (odd num) as +ve; in2, in4, out2, out4 (even num) as -ve 
 Heat sink of H-bridges face outwards of vehicle (platform)
 */


// Part B: wheel encoder for dfrobot mobile platform connection for Arduino Uno
/*left wheel encoder -> digital pin 2, right wheel encoder -> digital pin 4 */

#define LEFT 0
#define RIGHT 1

long encoder[2]={0,0};
int prevSpeed[2]={0,0};

//right H-bridge to Arduino Uno connection
int pwmRight = 9; //enA and enB on right H-bridge
int dirRight_pve = 5; //in1 and in3 on right H-bridge
int dirRight_nve = 6; //in2 and in4 on right H-bridge

//left H-bridge to Arduino Uno connection
int pwmLeft = 10; //enA and enB on left H-bridge
int dirLeft_pve = 7; //in1 and in3 on left H-bridge
int dirLeft_nve = 8; //in2 and in4 on left H-bridge
=======


void goStraight(int pwm, int ms, int dir){
  // input parameter ms is time in ms
  // pwm is pwm speed (0-255)
  // dir is 0 for backward; 1 for forward

  if(dir==0){ // move backward
    digitalWrite(dirRight_pve,HIGH);
    digitalWrite(dirRight_nve,LOW);
    digitalWrite(dirLeft_pve,HIGH);
    digitalWrite(dirLeft_nve,LOW);
  }
  else{
    // set motor direction to move forward
    digitalWrite(dirRight_pve,LOW);
    digitalWrite(dirRight_nve,HIGH);
    digitalWrite(dirLeft_pve,LOW);
    digitalWrite(dirLeft_nve,HIGH);   
  }

  // set speed

  analogWrite(pwmRight,constrain(pwm,0,255));
  analogWrite(pwmLeft,constrain(pwm,0,255));

  // set duration
  delay(ms); // to be changed to millis() later
  // turn off motors
  digitalWrite(dirRight_pve,LOW);
  digitalWrite(dirRight_nve,LOW);
  digitalWrite(dirLeft_pve,LOW);
  digitalWrite(dirLeft_nve,LOW);
  
}

void demoOne(){
  // this func will run the motors in both directions at a fixed speed
  // turn on all motors
  digitalWrite(dirRight_pve,HIGH);
  digitalWrite(dirRight_nve,LOW);
  digitalWrite(dirLeft_pve,LOW);
  digitalWrite(dirLeft_nve,HIGH);
  // set speed to 200 out of possible range of 0-255

  analogWrite(pwmRight,200);
  analogWrite(pwmLeft,200);


  delay(2000);

  // change motor directions
  digitalWrite(dirRight_pve,LOW);
  digitalWrite(dirRight_nve,HIGH);
  digitalWrite(dirLeft_pve,HIGH);
  digitalWrite(dirLeft_nve,LOW);
  
  delay(2000);

  // turn off motors
  digitalWrite(dirRight_pve,LOW);
  digitalWrite(dirRight_nve,LOW);
  digitalWrite(dirLeft_pve,LOW);
  digitalWrite(dirLeft_nve,LOW);
}

/*
void demoTwo(){
  // this function will run the motors across range of possible speeds
  // choose motor direction
  digitalWrite(dirRight_pve,LOW);
  digitalWrite(dirRight_nve,HIGH);
  digitalWrite(dirLeft_pve,LOW);
  digitalWrite(dirLeft_nve,HIGH);
  
  // accelerate from zero to max PWM speed
  for(int i=0;i<256;i+=1){
    analogWrite(pwmFR,i);
    //analogWrite(pwmRR,i);
    //analogWrite(pwmRL,i);
    analogWrite(pwmFL,i);
    delay(20);

    //Serial.print("accelerating num ");
    //Serial.println(i);
  }
  
  // decelerate from max speed to zero
  for(int i=255;i>=0;i-=1){
    analogWrite(pwmFR,i);
    //analogWrite(pwmRR,i);
    //analogWrite(pwmRL,i);
    analogWrite(pwmFL,i);
    delay(20);

    //Serial.print("decelerating num ");
    //Serial.println(i);
  }

  // turn off motors
  digitalWrite(dirRight_pve,LOW);
  digitalWrite(dirRight_nve,LOW);
  digitalWrite(dirLeft_pve,LOW);
  digitalWrite(dirLeft_nve,LOW);
}
*/


void encodeLeftWheel(){
  encoder[LEFT]++; // count the left wheel encoder interrupts
}

void encodeRightWheel(){
  encoder[RIGHT]++; // count the right wheel encoder interrupts
}

void setup() {
  // Set motor control pin modes
  pinMode(pwmRight,OUTPUT);
  pinMode(dirRight_pve,OUTPUT);
  pinMode(dirRight_nve,OUTPUT);

  pinMode(pwmLeft,OUTPUT);
  pinMode(dirLeft_pve,OUTPUT);
  pinMode(dirLeft_nve,OUTPUT);

  Serial.begin(9600); // init serial port to print data, in bits/s

  // Set encoder pin modes
  // For Arduino Uno, interrupt number 0 = pin 2, interrupt number 1 = pin 3
  attachInterrupt(LEFT, encodeLeftWheel,CHANGE); // init interrupt mode for digital pin 2
  attachInterrupt(RIGHT, encodeRightWheel, CHANGE); // init interrupt mode for digital pin 3
}

void loop(){
  // motor work

  demoOne();
  //delay(2000);
  //demoTwo();
  //goStraight(180,3000,1); // go forward
  //delay(1000);
  //goStraight(180,3000,0); // go backwards
  delay(1000);

  // encoder work
  static unsigned long timer =0; // print manager timer

  if(millis() - timer > 500){
    Serial.print("Coder value: ");
    Serial.print(encoder[LEFT]);
    Serial.print("[Left Wheel] ");
    Serial.print(encoder[RIGHT]);
    Serial.println("[Right Wheel]");
    Serial.println(" ");

    prevSpeed[LEFT] = encoder[LEFT]; // record the latest speed value
    prevSpeed[RIGHT] = encoder[RIGHT];
    encoder[LEFT]=0; // clear the data buffer
    encoder[RIGHT]=0;
    timer=millis();
}
