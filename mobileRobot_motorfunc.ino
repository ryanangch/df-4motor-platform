// connect motor controller pins to Arduino digital pins

/*convention: 
 Only Arduino Uno pins 3,5,6,9,10,11 can be used for PWM
 pins 5,6 may experience higher duty cycle than expected
 due to interactions involving delay() & millis()

 PWM pins: 3,9,10,11 in CW order starting from FR
 Direction pins: 5,6,7,8, in order +-+-, RRLL
 H-bridge (right, flip +- for left side) in1, in3, out1, out3 (odd num) as +ve; in2, in4, out2, out4 (even num) as -ve 
 Heat sink of H-bridges face outwards of vehicle (platform)
 */

//right H-bridge
int pwmFR = 3; //enA on right H-bridge
int dirRight_pve = 5; //in1 and in3 on right H-bridge
int dirRight_nve = 6; //in2 and in4 on right H-bridge
int pwmRR = 9; //enB on right H-bridge

//left H-bridge
int pwmRL = 10; //enA on left H-bridge
int dirLeft_pve = 7; //in1 and in3 on left H-bridge
int dirLeft_nve = 8; //in2 and in4 on left H-bridge
int pwmFL = 11; //enB on left H-bridge


void setup() {
  // set all the motor control pins to outputs
  pinMode(pwmFR,OUTPUT);
  pinMode(dirRight_pve,OUTPUT);
  pinMode(dirRight_nve,OUTPUT);
  pinMode(pwmRR,OUTPUT);
  
  pinMode(pwmRL,OUTPUT);
  pinMode(dirLeft_pve,OUTPUT);
  pinMode(dirLeft_nve,OUTPUT);
  pinMode(pwmFL,OUTPUT);

  //Serial.begin(9600);
}

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
  analogWrite(pwmFR,constrain(pwm,0,255));
  analogWrite(pwmRR,constrain(pwm,0,255));
  analogWrite(pwmRL,constrain(pwm,0,255));
  analogWrite(pwmFL,constrain(pwm,0,255));
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
  analogWrite(pwmFR,200);
  analogWrite(pwmRR,200);
  analogWrite(pwmRL,200);
  analogWrite(pwmFL,200);

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
    analogWrite(pwmRR,i);
    analogWrite(pwmRL,i);
    analogWrite(pwmFL,i);
    delay(20);

    //Serial.print("accelerating num ");
    //Serial.println(i);
  }
  
  // decelerate from max speed to zero
  for(int i=255;i>=0;i-=1){
    analogWrite(pwmFR,i);
    analogWrite(pwmRR,i);
    analogWrite(pwmRL,i);
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

void loop(){
  // put your main code here, to run repeatedly:
  //demoOne();
  //delay(2000);
  //demoTwo();
  goStraight(180,3000,1); // go forward
  delay(1000);
  goStraight(180,3000,0); // go backwards
  delay(1000);
}
