import cv2
import numpy as np
import tensorflow as tf
# to loadload model 
model = tf.keras.models.load_model('myTrue_model.h5')
# image files
imgs = ['ZERO.png','ONE.png','TWO.png','THREE.png','FOUR.png','FIVE.png','SIX.png','SEVEN.png','EIGHT.png','NINE.png']
def predict(image):
    # resize image so that model can predict 
    image1 = cv2.resize(image,(28,28))
    # to save resize image
    cv2.imwrite('resize.png',image1)
    #normalizing image
    image2 = image1 / 255.0
    # reshaping and typecasting
    image3 = image2.reshape(1,28,28,1).astype(float)
    # prediction
    predict = model.predict(image3)
    return (imgs[np.argmax(predict)])

# window name
windowName = 'Draw'
# for background
img = cv2.imread('black.png')
cv2.namedWindow(windowName)


# drawing variable
drawing = False

#to handle mouse events
def draw_circle(event,x,y,flags,param):
    global  drawing 
    
    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
    if event == cv2.EVENT_LBUTTONUP:
        drawing = False  
    # to draw     
    if event == cv2.EVENT_LBUTTONDBLCLK:
                 cv2.circle(img,(x,y),85,(0,0,0),-1) # -1 to fill the circle  
                   
    # to erase   
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing == True:
                cv2.circle(img,(x,y),15,(0,255,255),-1) # -1 to fill the circle  
                  

cv2.setMouseCallback(windowName,draw_circle)        

while True:
    cv2.putText(img,"Draw Here",(240,80),cv2.FONT_HERSHEY_SIMPLEX,0.9,(0,255,0),2)
    cv2.rectangle(img,(100,100),(500,500),(0,255,0),1)
    
    # for output box
    cv2.putText(img,"Output",(740,80),cv2.FONT_HERSHEY_SIMPLEX,0.9,(234,0,123),2)
    cv2.rectangle(img,(600,100),(1000,500),(234,0,123),1)
    
    #for hints
    cv2.putText(img,"Double click left mouse button to erase",(320,580),cv2.FONT_HERSHEY_SIMPLEX,0.6,(240,240,24),1)
    cv2.putText(img,"Press P to predict",(320,620),cv2.FONT_HERSHEY_SIMPLEX,0.6,(240,240,24),1)
    cv2.putText(img,"Press Q to quit",(320,660),cv2.FONT_HERSHEY_SIMPLEX,0.6,(240,240,24),1)

    
    k = cv2.waitKey(10)
    if k  == ord('p'):
        # select the region of draw box 
        img2= img[110:490,110:480]
        # save selected region as image
        cv2.imwrite("image.png",img2)
        # read saved image
        image = cv2.imread('image.png',0)
        # to predict the digit inside the image
        pred = predict(image)
        # read image from images folde
        img1 = cv2.imread('images/{}'.format(pred),1)
        # to resize image so that it fit in the box
        img2 = cv2.resize(img1,(398,398))
        # to place image in output rectangle
        img[101:499,602:1000] = img2   
                 
    # to display all
    cv2.imshow(windowName,img)
    # to quit
    k = cv2.waitKey(10)
    if k == ord('q'):
        break
    
cv2.destroyAllWindows()