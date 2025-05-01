import cv2

path="."

fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.mp4', fourcc, 20.0, (640,480))
rt=5000
while(rt<100000):
    rt=rt+1
    try:
        frame=cv2.imread(path+"/img"+str(rt)+".jpg")
        out.write(frame)
        c = cv2.waitKey(1)
        if c & 0xFF == ord('q'):
            break
    except KeyboardInterrupt:
        break
    except:
        print("not available", rt)
        #raise
        

out.release()
cv2.destroyAllWindows()