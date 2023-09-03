import sys
import cv2
import serial
import imutils
import time
from yoloDet import YoloTRT

##아두이노와 연결된 포트(lsusb로 확인)
serial_port = '/dev/ttyACM0'  

ToArduino = serial.Serial(serial_port, 9600)

model = YoloTRT(library="yolov5/build/libmyplugins.so", engine="yolov5/build/best.engine", conf=0.4, yolo_ver="v5")

shot_cnt = 0
material_cnt = [0, 0, 0, 0, 0]
##순서 : aluminum can, glass bottle, plastic bottle, plastic cup, waste


##리스트에서 가장 큰값을 가진 인덱스와 두번째로 큰 값을 가진 인덱스를 반환
def find_first_second_index(lst):
    largest_idx = None
    second_idx = None
    for i in range(len(lst)):
        if largest_idx is None or lst[i] > lst[largest_idx]:
            second_idx = largest_idx
            largest_idx = i
        elif second_idx is None or lst[i] > lst[second_idx]:
            second_idx = i
    return int(largest_idx), int(second_idx)
    

def gstreamer_pipeline(
    capture_width=1640,
    capture_height=1232,
    display_width=1920,
    display_height=1080,
    framerate=30,
    flip_method=0,
):
    return (
        "nvarguscamerasrc ! "
        "video/x-raw(memory:NVMM), "
        "width=(int)%d, height=(int)%d, framerate=(fraction)%d/1 ! "
        "nvvidconv flip-method=%d ! "
        "video/x-raw, width=(int)%d, height=(int)%d, format=(string)BGRx ! "
        "videoconvert ! "
        "video/x-raw, format=(string)BGR ! appsink drop=True"
        % (
            capture_width,
            capture_height,
            framerate,
            flip_method,
            display_width,
            display_height,
        )
    )

cap = cv2.VideoCapture(gstreamer_pipeline(), cv2.CAP_GSTREAMER)

while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    frame = imutils.resize(frame, width=640)
    detections, t = model.Inference(frame)
    
    for obj in detections:
        print(obj['class'], obj['conf'], obj['box'])
        shot_cnt += 1

        if obj['class'] == 'aluminum_can':
            material_cnt[0] += 1
        elif obj['class'] == 'glass_bottle':
            material_cnt[1] += 1
        elif obj['class'] == 'plastic_bottle':
            material_cnt[2] += 1
        elif obj['class'] == 'plastic_cpu':
            material_cnt[3] += 1
        elif obj['class'] == 'waste':
            material_cnt[4] += 1

    if (shot_cnt >= 4):
        #send_value = material_cnt.index(max(material_cnt))
        send_value,compare_value = find_first_second_index(material_cnt)
        
        ##스코어가 가장 높은 인덱스와 두번째 인덱스의 감지 횟수를 비교하여 그 차이가 크치않을 때 
        #if (compare_value > 4) and (send_value - compare_value < 1):
            ##음성인식 모듈의 추론결과를 우선시 함.
        ToArduino.write(bytes([send_value]))  # serial 통신을 위해 bytes로 변환하여 보냄
        time.sleep(0.05)
        print("아두이노로 제어 신호 전송 :", send_value)
        shot_cnt = 0
        material_cnt = [0, 0, 0, 0, 0]  # 초기화

    cv2.imshow("Output", frame)
    key = cv2.waitKey(1)
    if key == ord('q'):
        break
    elif key == ord('t'):
        ToArduino.write(bytes([5]))  # serial 통신을 위해 bytes로 변환하여 보냄
        time.sleep(0.01)
cap.release()
ToArduino.close()
cv2.destroyAllWindows()
