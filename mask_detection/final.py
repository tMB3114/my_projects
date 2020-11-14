# import packages
import tensorflow as tf
import keras
import cv2
from keras.models import load_model
import numpy as np
import datetime
# load pretrained cnn model
model = load_model('yes_model1.h5') # cnn
 
# height and width of image trained 
img_width, img_height = 200, 200
 

#font style 
font = cv2.FONT_HERSHEY_SIMPLEX
font2 = cv2.FONT_HERSHEY_COMPLEX
#labels
LABELS = ' '
# Blue color
COLOR = (255,0,0)
# Load the Cascade for face detection
face_cascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
 
#start  web cam
cap = cv2.VideoCapture(0) 
# set height and width of the frame
cap.set(3,540)
cap.set(4,1080)

# height and width of frame
height = 'Height: ' + str(cap.get(4))
width ='Width: ' + str(cap.get(3))
# get time
time = str(datetime.datetime.now())

#infinite loop for video capture 
while True:
    ret, img = cap.read()
    # to flip the image
    img = cv2.flip(img, 1)
    #ret --> return value
    # to convert image to grayscale
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    #detect coordinates of rectangle for face 
    faces = face_cascade.detectMultiScale(gray,1.2,3)
    
    #################################################
    
    for (x,y,w,h) in faces:
         # cropping image 
         face_img = img[y:y+w, x:x+w]
         #resizing image
         resized = cv2.resize(face_img, (img_height, img_width))
         # normalizing image
         normalized = resized / 255.0
         # reshaping image 
         reshaped = np.reshape(normalized, (1,img_height, img_width,3))
         # predicting
         result = model.predict(reshaped) 
         # since i have used sigmoid activation function in my output layer.predicted  Value greater than 0.5 is for face with mask and less 
         # than 0.5 is for face without mask
         if result > 0.5: 
             LABELS = 1
             COLOR = (0,255,0)
             # for accuracy
             acc1 = np.round(result[0][0] * 100,2)
         else: 
             LABELS = 0
             COLOR = (0,0,255)
             acc2 = 100 - np.round(result[0][0] * 100,2)
         # drawing colored rectangle around the detected face    
         cv2.rectangle(img,(x,y),(x+w,y+h),color=COLOR,thickness = 3)
         
         
         if LABELS == 1:
             # to put Text and accuracy score
                cv2.putText(img,text = "MASK",org=(x+90,y-10),fontFace=font2,fontScale=1,color = COLOR,thickness=3)
                cv2.putText(img,text = 'Accuracy: '+str(acc1) + "%" ,org=(x+10,y+h+30),fontFace=font,fontScale=1,color = COLOR,thickness=2)
         if LABELS == 0:
             # to put text and accuracy score
                 cv2.putText(img,text = "NO MASK",org=(x+40,y-10),fontFace=font2,fontScale=1,color = COLOR,thickness=3)
                 cv2.putText(img,text = 'Accuracy: '+str(acc2) + "%" ,org=(x+10,y+h+30),fontFace=font,fontScale=1,color = COLOR,thickness=2)   
     
     
    # to set height and width 
    cv2.putText(img,height,org=(5,20),fontFace=cv2.FONT_HERSHEY_SIMPLEX,fontScale=.5,color=(200,200,0),thickness = 2)
    cv2.putText(img,width,org=(5,40),fontFace=cv2.FONT_HERSHEY_SIMPLEX,fontScale=.5,color=(200,200,0),thickness = 2)
     # to put date and time
    cv2.putText(img,time,org=(350,20),fontFace=cv2.FONT_HERSHEY_SIMPLEX,fontScale=.5,color=(200,0,0),thickness = 2) 
         
   
    # to show the image      
    cv2.imshow("LIVE",img)
    # to quit the live video capture...
    # press key q for quit
    if cv2.waitKey(1) & 0xff == ord('q'): 
        # to break out of infinite loop
        break

cv2.destroyAllWindows()               
                       