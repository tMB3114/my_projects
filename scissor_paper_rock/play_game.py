# import necessary libraries
import cv2
import numpy as np
from keras.models import load_model

# load model
model = load_model("final_model4.h5")
# defining font
font = cv2.FONT_HERSHEY_SIMPLEX
# all categories
classes = ['None','Paper','Rock','Scissor']
# mapper function
def mapper(ind):
    return classes[ind]
# determine winner
def who_is_winner(a,b):
    if a == b:
        return "Tie"
    if a == "Rock":
        if b == "Scissor":
            return "User"
        if b == "Paper":
            return "Computer"
    if a == "Paper": 
        if b == "Rock": 
            return "User"
        if b == 'Scissor': 
            return "Computer"
    if a == "Scissor": 
        if b == "Paper": 
            return "User"
        if b == "Rock": 
            return "Computer"  

font = cv2.FONT_HERSHEY_COMPLEX
# video capture
cap = cv2.VideoCapture(0)
# to set the size of window
cap.set(4,1080)
cap.set(3,1080)
# defining previous move 
previous_move = None
# infinite loop for video capture
while True:
    ret, img = cap.read()
    # to flip the image
    img = cv2.flip(img,1)
    
    # to check whether image is read or not
    if not ret:
        continue
    
    # draw rectangle for player
    cv2.rectangle(img,(100,100),(500,500),(25,255,0),2)
    # put text
    text = "Player"
    cv2.putText(img, text,(230,575),font,2,(255,0,0),2)
    # draw rectangle for computer
    cv2.rectangle(img,(700,100),(1100,500),(25,250,0),2)
    text_computer = "Computer"
    cv2.putText(img, text_computer,(930,575),font, 2,(255,0,0),2)
    
    # use the region of the player window for the prediction 
    # extracting the region of interest of  player window 
    interest = img[100:550,50:500]
    interest = cv2.cvtColor(interest, cv2.COLOR_BGR2RGB)
    interest = cv2.resize(interest, (224,224))
    interest = interest.reshape(1,224,224,3)
    
    # predicting the player move
    
    predict = model.predict(np.array(interest))    
    
    user_move_name = mapper(np.argmax(predict[0]))
    
    
    if previous_move != user_move_name:
        if user_move_name != 'None':
            # random choice for the computer 
            computer_move_name = classes[np.random.randint(1,4)]
            # calculating who is winner
            winner = who_is_winner(user_move_name,computer_move_name)
        else: 
            computer_move_name = "none"
            winner = "Waiting....."
    previous_move = user_move_name    
    
    
    cv2.putText(img, "Your Move: " + user_move_name,
                (50, 50), font, 1, (255, 255, 255), 2, cv2.LINE_AA)
    cv2.putText(img, "Computer's Move: " + computer_move_name,
                (750, 50), font, 1., (255, 255, 255), 2, cv2.LINE_AA)
    cv2.putText(img, "Winner: " + winner,
                (400, 690), font, 1.5, (0, 0, 255), 4, cv2.LINE_AA)       

        
    
    # to display the computer move in the screen
    if computer_move_name != "None":
        comp_img = cv2.imread("computer_move/{}.jpeg".format(computer_move_name))
       
        comp_img = cv2.flip(comp_img,1)
        comp_img = cv2.resize(comp_img, (400,400))
        img[100:500, 700:1100] = comp_img
    
    
    cv2.imshow( "Scissor Paper", img)
   
    
    key = cv2.waitKey(10)
    # q to quit the window
    if key == ord('q'):
        break;
    
cap.release()
cv2.destroyAllWindows()    