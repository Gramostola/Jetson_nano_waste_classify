
2023 임베디드 소프트웨어 경진대회 자유공모 부문 출품작

팀번호:1091 

작품명(주제) : 물질분류장치

[설명]

투입된 쓰레기를 알루미늄캔, 유리병, 플라스틱, 일반쓰레기로 분류하는 장치입니다. 

객체 인식 부분은 Yolov5 모델을 사용하였습니다. 

학습된 모델을 기반으로 Jetson nano에서 실시간 Object detection을 수행합니다. 

학습 데이터는 원본 이미지 325장에서 Data argument를 거쳐 총 800장 가량을 train : vaild : test = 8:1:1로 분할하여 학습을 진행하였습니다. 

[동작 과정]

1. Jetson nano는 연결된 CSI카메라모듈을 통해 실시간으로 이미지 데이터를 받아 Object detction을 수행합니다. 

2. Jetson nano는 Object detction 추론 결과에 따라 Arduino mega에 제어 신호를 전송합니다.

3. Arduino mega는 Jetson nano에서 수신된 신호에 따라 4개의 선형 액추에이터를 각각 제어하고 총 4 방향으로 쓰레기를 분류합니다. 

[참고]

Jetson nano에서 Yolov5 install : Running YoloV5 with TensorRT Engine on Jetson, https://github.com/mailrocketsystems/JetsonYolov5

