import numpy as np
import cv2

cap = cv2.VideoCapture('/home/joalison/Documentos/workspace/my_video-1.mkv') #Classe para captura de vídeo a partir de arquivos de vídeo, seqüências de imagens ou câmeras.

while(cap.isOpened()):
    ret, frame = cap.read() #retorna um bool (True / False). Se o quadro for lido corretamente, será True

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #mudar a cor e deixa cinza(gray em inglês)

    cv2.imshow('frame',gray) #para exibir uma imagem em uma janela
    if cv2.waitKey(1) & 0xFF == ord('q'): #Aguarda por uma tecla pressionada
        break #para o if

cap.release() #Fecha o arquivo de vídeo ou o dispositivo de captura
cv2.destroyAllWindows() #Destrói todas as janelas do HighGUI
