# Jetson_nano_waste_classify
투입된 쓰레기를 알루미늄캔, 유리병, 플라스틱, 일반쓰레기로 분류하는 Yolov5 모델을 학습하였고 이를 Jetson nano에서 실행합니다.  
학습 데이터는 원본 이미지 325장에서 Data argument를 거쳐 총 800장 가량을 학습 데이터로 사용하였습니다. 

Jetson nano는 Object detction 결과에 따라 Arduino에 제어 신호를 전송합니다. 

Arduino는 Jetson nano에서 수신된 신호에 따라 4개의 선형 액추에이터를 각각 제어하고 총 4 방향으로 쓰레기를 분류합니다. 

Jetson nano에서 Yolov5 install 참고 : Running YoloV5 with TensorRT Engine on Jetson, https://github.com/mailrocketsystems/JetsonYolov5

