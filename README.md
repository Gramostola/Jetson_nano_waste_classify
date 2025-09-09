
2023 임베디드 SW경진대회 자유공모 부문 출품작


팀명 : MESS(Mechanic Electronic Software Synergy)

팀번호 : 1091 

작품명(주제) : 지능형 폐기물분류장치

시연 영상 : https://www.youtube.com/watch?v=P6nT9Uv6HWQ&list=WL&index=42

[설명]

장치에 투입된 폐기물을 각각 알루미늄캔, 유리병, 플라스틱, 일반쓰레기로 분류하는 장치입니다. 

객체 인식 및 분류를 위해 Yolov5 모델을 적용하여 Jetson Nano(JetPack 4.6.4)에서 실시간 Object detection을 수행합니다. 

학습 데이터는 원본 이미지 325장에서 Data argument를 거쳐 총 800장 가량을 확보하고, train : vaild : test = 8:1:1로 분할하여 학습을 진행하였습니다. 

Jetson Nano와 Arduino 에서 동작하는 코드를 각각 업로드하였습니다.


[동작 과정]

1. 폐기물이 투입되면 근접 센서가 이를 감지하고 LED 조명을 작동합니다. 

2. Jetson Nano는 연결된 CSI카메라모듈(Fisheye lens)을 통해 실시간으로 이미지 데이터를 수신하고 Object detction을 수행합니다.

3. Jetson Nano의 Object detction 추론 결과에 따라 Arduino에 제어 신호를 Serial 통신으로 전송합니다.

4. Arduino는 Jetson Nano로부터 수신된 제어 신호에 따라 4개의 선형 액추에이터를 제어하여 총 4 방향으로 쓰레기를 분류합니다.

5. 분류 작업이 완료되면 액추에이터의 위치를 초기화 합니다. 이후 과정을 반복합니다.


[참고 자료]

Running YoloV5 with TensorRT Engine on Jetson, https://github.com/mailrocketsystems/JetsonYolov5

