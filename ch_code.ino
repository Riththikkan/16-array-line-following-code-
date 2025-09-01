//ch
#define AIN1 3
#define AIN2 8
#define PWMA 5
#define BIN1 4
#define BIN2 7
#define PWMB 6
#define STBY 9   


#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define SIG A4


int readOrder[16] = {9,10,11,12,13,14,15,16,8,7,6,5,4,3,2,1};


float Kp = 0.25;       
float Kd = 5.0;        
int baseSpeed = 120;   
int maxSpeed = 255;     
int threshold = 500;    

int sensorValues[16];
int lastError = 0;


void setup() {  
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT); pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);

  digitalWrite(STBY, HIGH);

  Serial.begin(9600);
  
  calibrateSensors();
}


int readMux(int channel) {
  digitalWrite(S0, channel & 1);
  digitalWrite(S1, (channel >> 1) & 1);
  digitalWrite(S2, (channel >> 2) & 1);
  digitalWrite(S3, (channel >> 3) & 1);
  delayMicroseconds(5);
  return analogRead(SIG);
}


void calibrateSensors() {
  int minVal = 1023, maxVal = 0;

  Serial.println("Cal");
  for (int i = 0; i < 200; i++) {
    for (int j = 0; j < 16; j++) {
      int idx = readOrder[j] - 1;
      int val = readMux(idx);
      if (val < minVal) minVal = val;
      if (val > maxVal) maxVal = val;
    }
    delay(10);
  }
  threshold = (minVal + maxVal) / 2;
  Serial.print("Cal done.");
  Serial.println(threshold);
}


long readLine() {
  long weightedSum = 0;
  int activeCount = 0;

  for (int i = 0; i < 16; i++) {
    int sensorIndex = readOrder[i] - 1;
    int value = readMux(sensorIndex);
    sensorValues[i] = value;

    if (value < threshold) { 
      weightedSum += (i * 1000);
      activeCount++;
    }
  }

  if (activeCount == 0) return -1;  
  return weightedSum / activeCount;
}


void setMotor(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

   
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, leftSpeed);

   
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, rightSpeed);
}


void loop() {
  long position = readLine();

  if (position == -1) {
    
    setMotor(0, 0);
    return;
  }

  int error = position - 7500; 
  int correction = (Kp * error) + (Kd * (error - lastError));
  lastError = error;

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  setMotor(leftSpeed, rightSpeed);
}