# Jetson_nano_waste_classify
Yolov5을 이용하여 투입된 쓰레기를 알루미늄캔, 유리병, 플라스틱병, 플라스틱컵, 일반쓰레기 로 분류하는 모델을 학습하였습니다. 
Jetson nano에서 Object detction 결과에 따라 Arduino에 제어 신호를 전송합니다. 
Arduino는 Jetson nano에서 수신된 신호에 따라 4개의 선형 액추에이터를 제어하고 총 4 방향으로 쓰레기를 분류합니다. 

참고 : TensorRT engine을 사용한 Jetson nano에서 Yolov5 실행, https://github.com/mailrocketsystems/JetsonYolov5

