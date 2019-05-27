# -*- coding: utf-8 -*-
#coding:utf-8
import cv2
import numpy as np
import glob

# 找棋盘格角点
# 阈值
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
#棋盘格模板规格
w = 9
h = 6
# 世界坐标系中的棋盘格点,例如(0,0,0), (1,0,0), (2,0,0) ....,(8,5,0)，去掉Z坐标，记为二维矩阵
objp = np.zeros((w*h,3), np.float32)
objp[:,:2] = np.mgrid[0:w,0:h].T.reshape(-1,2)
# 储存棋盘格角点的世界坐标和图像坐标对
objpoints = [] # 在世界坐标系中的三维点
imgpoints = [] # 在图像平面的二维点

images = glob.glob('calib/*.jpg')
for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    # 找到棋盘格角点
    ret, corners = cv2.findChessboardCorners(gray, (w,h),None)
    # 如果找到足够点对，将其存储起来
    if ret == True:
        cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        objpoints.append(objp)
        imgpoints.append(corners)
        # 将角点在图像上显示
        cv2.drawChessboardCorners(img, (w,h), corners, ret)
        cv2.imshow('findCorners',img)
        cv2.waitKey(1)
cv2.destroyAllWindows()

# 标定
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

# 去畸变
img2 = cv2.imread('calib/00169.jpg')
h,  w = img2.shape[:2]
newcameramtx, roi=cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),0,(w,h)) # 自由比例参数
dst = cv2.undistort(img2, mtx, dist, None, newcameramtx)
# 根据前面ROI区域裁剪图片
#x,y,w,h = roi
#dst = dst[y:y+h, x:x+w]
cv2.imwrite('calibresult.png',dst)

# 反投影误差
total_error = 0
for i in range(len(objpoints)):
    imgpoints2, _ = cv2.projectPoints(objpoints[i], rvecs[i], tvecs[i], mtx, dist)
    error = cv2.norm(imgpoints[i],imgpoints2, cv2.NORM_L2)/len(imgpoints2)
    total_error += error
print ("total error: ", total_error/len(objpoints))
img=cv2.imread(images[0])
testpoint=np.zeros((1,3), np.float32)
testpoint[0,:]=[5,3,0]
testpoint2, _ = cv2.projectPoints(testpoint, rvecs[0], tvecs[0], mtx, dist)
#cv2.drawChessboardCorners(img, (w,h), corners, ret)
point_size = 1
point_color = (0, 0, 255) # BGR
thickness = 4 # 可以为 0 、4、8
point=(testpoint2[0][0][0],testpoint2[0][0][1])
cv2.circle(img, point, point_size, point_color, thickness)
cv2.namedWindow("image")
cv2.imwrite('imagetest.png', img)
cv2.imshow('findCorners',img)
cv2.destroyAllWindows()