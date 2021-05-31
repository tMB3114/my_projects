# import necessary libraries 
import cv2
import os

# path to save image
PATH = '/home/tmb3114/scissor_paper_rock/dataset/train/paper'
COUNT = 1500
start_capture = False
# to capture video
cap = cv2.VideoCapture(0)
# to set height and width of the frame
cap.set(3,640)
cap.set(4,640)# infinte loop to capture frames of the video
while True:
    ret, img = cap.read()
    if ret == False:
        break
    if not ret:
        continue
    # to flip the image
    img = cv2.flip(img,1)
    # draw rectangle for region of interest in video
    cv2.rectangle(img,(500,100),(50,500), (255,255,0), thickness= 3)
    
    if  start_capture:
        region_of_interest = img[50:500,50:500]
        save_image = os.path.join(PATH, '{}.jpg'.format(COUNT + 1))
        cv2.imwrite(save_image,region_of_interest)
        COUNT += 1
   
    cv2.putText(img, "Collecting {}......".format(COUNT),
            (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2, cv2.LINE_AA)
    cv2.imshow("Collecting images", img)    
    
    wait_key = cv2.waitKey(10)
    if wait_key == ord('s'):
        start_capture = not start_capture
     
    # to quit
    if wait_key == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()     
