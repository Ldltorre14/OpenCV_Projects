import pickle
import cv2
import cvzone
import numpy as np

#Read the video capture
cap = cv2.VideoCapture('Resources/carPark.mp4')

#We load the pickle object with the positions 
with open('CarParkingPos', 'rb') as f:
    posList = pickle.load(f)

#width and height of every parking space
width, height = 107, 48


def checkParkingSpace(imgPro):
    spaceCounter = 0
    #We traverse through the list of positions 
    for pos in posList:
        x, y = pos
        #We crop from the image, every parking space
        imgCrop = imgPro[y:y + height, x:x + width]
        # cv2.imshow(str(x * y), imgCrop)
        #We count for every space, the pixels different of 0
        #pixels higher than 0, means that there is something in that space
        count = cv2.countNonZero(imgCrop)

        #if the pixels different than 0, are higher than 900, then there is a car
        if count < 900:
            color = (0, 255, 0)
            thickness = 1
            spaceCounter += 1
        else:
            color = (0, 0, 255)
            thickness = 1

        cv2.rectangle(img, pos, (pos[0] + width, pos[1] + height), color, thickness)
        cvzone.putTextRect(img, str(count), (x, y + height - 3), scale=1,
                           thickness=2, offset=0, colorR=color)

    cvzone.putTextRect(img, f'Free: {spaceCounter}/{len(posList)}', (100, 50), scale=3,
                           thickness=5, offset=20, colorR=(0,200,0))
    
    
while True:
    #We check the actual frame of the video
    #If it ends, then we restart the video by seting to the first frame
    if cap.get(cv2.CAP_PROP_POS_FRAMES) == cap.get(cv2.CAP_PROP_FRAME_COUNT):
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
    success, img = cap.read()
    """We first turn the image to gray scale, then we add a blur so we can identify
    the figures a bit better.
    then we apply a threshold for for getting the edges of the objects (the cars) and 
    we apply a median filter for removing noise and we end applying a dilate process so
    we can get a clear black and white view to see clearly where are the cars (white pixels)
    """
    imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    imgBlur = cv2.GaussianBlur(imgGray, (3, 3), 1)
    imgThreshold = cv2.adaptiveThreshold(imgBlur, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                         cv2.THRESH_BINARY_INV, 25, 16)
    imgMedian = cv2.medianBlur(imgThreshold, 5)
    kernel = np.ones((3, 3), np.uint8)
    imgDilate = cv2.dilate(imgMedian, kernel, iterations=1)

    """We call the method with the processed image as an argument for checking
       every space in the parking and make the entire process"""
    checkParkingSpace(imgDilate)
    cv2.imshow("Image", img)
    # cv2.imshow("ImageBlur", imgBlur)
    # cv2.imshow("ImageThres", imgMedian)
    cv2.waitKey(10)