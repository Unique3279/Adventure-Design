import picamera
import numpy as np
import cv2

#카메라 켜기
camera = picamera.PiCamera()


#검출 색 범위 설정하기
lower_laser = np.array([100,100,100])
upper_laser = np.array([200,200,200])


#카메라 스타트와 화면 크기 조정
def camera_start():
    camera.resolution=(640,480)
    camera.start_preview(fullscreen = False, window=(200,200,640,480))

#색 검출
def color_detect():
    while True:
        ret, frame = cap.read()

    #BGR을 HSV로 바꾸기
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    

    #HSV로 laser를 제외한 나머지를 까맣게 출력하는 마스크 생성
    mask_laser = cv2.inRange(hsv,lower_laser, upper_laser)
    res = cv2.bitwise_and(frame, frame, mask = mask_laser)

    #original 화면이랑  laser 검출 화면 생성
    cv2.imshow('original', frame)
    cv2.imshow('Laser', res )

    #Phython이 사용되어 가동시키기&esc 누르면 나가기
    k= cv2. waitKey(1) & 0xFF
    if k ==27:
        break

cv2.destroyAllWindows()

def endpoint():
    mask_condition = (hsv[:, :, 0] >= lower_laser[0]) & (hsv[:, :, 0] <= upper_laser[0]) & \
                 (hsv[:, :, 1] >= lower_laser[1]) & (hsv[:, :, 1] <= upper_laser[1]) & \
                 (hsv[:, :, 2] >= lower_laser[2]) & (hsv[:, :, 2] <= upper_laser[2])
    y_pixel, x_pixel = np.where(mask(mask_condition))


#명령내리기
def move_control():
    #통신이 가능한 곳에다가 뭐.. 넣기..



if __name__ == '__main__':
    camera_start()
    color_detect()