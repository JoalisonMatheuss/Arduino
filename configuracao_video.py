import numpy as np
import cv2
import glob

#----------------------------------Configuração------------------------------------------------------

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# preparar pontos de objeto, como (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((6*7,3), np.float32)
objp[:,:2] = np.mgrid[0:7,0:6].T.reshape(-1,2)

# Arrays para armazenar pontos de objeto e pontos de imagem de todas as imagens
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

cap = cv2.VideoCapture('/home/joalison/Documentos/workspace/my_video-1.mkv')

while (cap.isOpened()):
  ret,frame = cap.read()
  gray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)

  # Find the chess board corners
  ret, corners = cv2.findChessboardCorners(gray, (7,9), None)

  # If found, add object points, image points (after refining them)
  if ret == True:
    objpoints.append(objp)
    corners2 = cv2.cornerSubPix(gray, corners, (11,11), (-1,-1), criteria) #Refina os locais dos cantos
    imgpoints.append(corners2)
    # Draw and display the corners
    cap = cv2.drawChessboardCorners(cap, (7,9), corners2,ret)
    cv2.imshow('cap',cap) #Exibe textura OPenGL 2D na janela especificada
    cv2.waitKey(500) #Aguarda por uma tecla pressionada
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break
 

cap.release()
cv2.destroyAllWindows() #Destroi todas as janelas do HighGUI


#--------------------------------------Calibração---------------------------------------------------

ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)


#-------------------------------------Undistortion--------------------------------------------------

cap = cv2.imread('/home/joalison/Documentos/workspace/photo-3.jpg') #Carrega uma imagem de um arquivo

h,  w = cap.shape[:2]
newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h)) #Retorna a nova matriz da câmera com base no parâmetro de escala livre
#----------------------------------Usadondo o unsdistort-------------------------------------------- 

# undistort
dst = cv2.undistort(cap, mtx, dist, None, newcameramtx) #Transfomra uma imagem para compensar a distorção da lente

# crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('calibresult.png',dst) #Salva uma imagem em um arquivo especificado 

#----------------------------------Usando o remapeamento--------------------------------------------

# undistort
mapx,mapy = cv2.initUndistortRectifyMap(mtx,dist, None, newcameramtx, (w,h), 5)
dst = cv2.remap(cap, mapx, mapy, cv2.INTER_LINEAR) #Aplica um atrnasformação geométrica genérica a uma imagem

# crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('calibresult.png',dst) #Salva uma imagem em um arquivo especificado
a = np.array(newcameramtx)
print(newcameramtx)

#----------------------------------Erro de Re-projeção------------------------------------------------

mean_error = 0
for i in list(range(len(objpoints))):
  imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist) #Projetos 3D aponta para um plano de imagem
  error = cv2.norm(imgpoints[i], imgpoints2, cv2.NORM_L2)/len(imgpoints2) #Projetos 3D aponta para um plano de imagem
  mean_error += error
print( "total error: {}".format(mean_error/len(objpoints)) )
