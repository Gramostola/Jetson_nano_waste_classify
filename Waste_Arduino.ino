int relay1 = 3; // 아두이노 디지털 핀 3에 릴레이1번.
int relay2 = 4; // 아두이노 디지털 핀 4에 릴레이2번.
int relay3 = 5;
int relay4 = 6;
int relay5 = 7;
int relay6 = 8;
int relay7 = 9;
int relay8 = 10;
int value = 8; // value 변수를 setup 함수 밖으로 이동하여 전역 변수로 만듭니다.
int count=0;
const int switchPin = 12;
int sensor = A0;
int led1 = 11;
int sensorValue = 0;
int sens = 0;
unsigned long lastValueChangeTime = 0;
unsigned long sensStartTime = 0;
bool movePending = false;

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(switchPin, INPUT);
}

void loop() {

  sensorValue = analogRead(sensor);

  Serial.print("적외선 센서 값: ");
  Serial.println(sensorValue);
  Serial.println(value);
  Serial.println(sens);
  //Serial.println(sensStartTime);
  delay(50);

  if (sens == 0) {
    if (sensorValue > 500) {
      digitalWrite(led1, LOW);
    }
    else {
      digitalWrite(led1, HIGH);
      sens = 1;
      value = 8;
      if (!movePending) {
        sensStartTime = millis();
      }
    }
  }

  /*int switchState = digitalRead(switchPin); // 스위치 상태 읽기
  if (switchState == HIGH) {
    Serial.println("스위치가 눌렸습니다.");
    value = 5;
    // 스위치가 눌렸을 때 실행할 작업을 여기에 추가
  }*/

  if (Serial.available()) {
    value = Serial.parseInt();
    Serial.println(value);
  }  
  if(sens == 1 && value == 8)
  {
    if (!movePending) {
      movePending = true;
      lastValueChangeTime = millis();
    }
  }
  
  if (sens == 1 && value >=0 && value <= 2) 
  {
    move(value+1);
    value = 8;
    movePending = false;
    sens = 0; // move 함수 호출 후 value 초기화
  }
  else if(sens == 1 && value >=3 && value <=4)
  {
    move(value);
    value = 8;
    movePending = false;
    sens = 0;
  }
  else if (value == 5) // 액추에이터 높이 기본값으로 세팅
  {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, HIGH);
    digitalWrite(relay4, LOW);
    digitalWrite(relay5, HIGH);
    digitalWrite(relay6, LOW);
    digitalWrite(relay7, HIGH);
    digitalWrite(relay8, LOW);
    delay(2500);
    
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
    digitalWrite(relay5, LOW);
    digitalWrite(relay6, HIGH);
    digitalWrite(relay7, LOW);
    digitalWrite(relay8, HIGH);
    delay(850);
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, HIGH);
    digitalWrite(relay5, LOW);
    digitalWrite(relay6, HIGH);
    digitalWrite(relay7, LOW);
    digitalWrite(relay8, HIGH);
    delay(100);

    for (int i = relay1; i <= relay8; i++) {
      digitalWrite(i, LOW);
    }// 5에 대한 동작 수행
    value = 8; // value 초기화
    sens = 0;
    movePending = false;
  }
  else if (value==6) // 반복테스트
  {
    for(int i = 1; i <= 5; i++)
    {
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, LOW);
      digitalWrite(relay5, HIGH);
      digitalWrite(relay6, LOW);
      digitalWrite(relay7, HIGH);
      digitalWrite(relay8, LOW);
      delay(800);
    
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, LOW);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, LOW);
      digitalWrite(relay8, HIGH);
      delay(760);
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, LOW);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, LOW);
      digitalWrite(relay8, LOW);
      delay(30);
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, HIGH);
      digitalWrite(relay5, LOW);
      digitalWrite(relay6, HIGH);
      digitalWrite(relay7, LOW);
      digitalWrite(relay8, LOW);
      delay(25);
  
    }
    for (int i = relay1; i <= relay8; i++) {
    digitalWrite(i, LOW);
    }
      
    value = 8;
    sens = 0;
    movePending = false;
    // 5에 대한 동작 수행
  }
  else if (value==7) // 끝까지 내리기
  {
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,LOW);
    digitalWrite(relay4,HIGH);
    digitalWrite(relay5,LOW);
    digitalWrite(relay6,HIGH);
    digitalWrite(relay7,LOW);
    digitalWrite(relay8,HIGH);
    delay(2500);

    for (int i = relay1; i <= relay8; i++) {
      digitalWrite(i, LOW);
    }// 5에 대한 동작 수행
    value = 8;
    sens = 0;
    movePending = false;
  }
    
  
  if (sens == 1 && value == 8 && movePending && (millis() - lastValueChangeTime >= 8000)) {
    move(4);
    sens=0;
    movePending = false;
  }
  
  
  sensStartTime=0;
}


void move(int a) {

  digitalWrite((2 * a - 2) % 8 + 3, HIGH);
  digitalWrite((2 * a - 1) % 8 + 3, LOW);
  digitalWrite((2 * a) % 8 + 3, HIGH);
  digitalWrite((2 * a + 1) % 8 + 3, LOW);
  digitalWrite((2 * a + 2) % 8 + 3, LOW);
  digitalWrite((2 * a + 3) % 8 + 3, HIGH);
  digitalWrite((2 * a + 4) % 8 + 3, LOW);
  digitalWrite((2 * a + 5) % 8 + 3, HIGH);
  delay(900);

  // 나머지 리레이 끄기
  for (int i = relay1; i <= relay8; i++) {
    digitalWrite(i, LOW);
  }

  delay(3000);

  digitalWrite((2 * a - 2) % 8 + 3, LOW);
  digitalWrite((2 * a - 1) % 8 + 3, HIGH);
  digitalWrite((2 * a) % 8 + 3, LOW);
  digitalWrite((2 * a + 1) % 8 + 3, HIGH);
  digitalWrite((2 * a + 2) % 8 + 3, HIGH);
  digitalWrite((2 * a + 3) % 8 + 3, LOW);
  digitalWrite((2 * a + 4) % 8 + 3, HIGH);
  digitalWrite((2 * a + 5) % 8 + 3, LOW);
  delay(900);

  // 나머지 리레이 끄기
  for (int i = relay1; i <= 11; i++) {
    digitalWrite(i, LOW);
  }
}