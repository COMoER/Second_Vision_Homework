# 第二次视觉部作业
## 第一题矩阵公式

![](https://latex.codecogs.com/svg.latex?P_r%20=%20R_{ir}^T(R_{ci}^TK^{-1}d(u,v,1)^T-t_{ci}))
## 第二题
### 结果放在output.txt
### 这里用到的函数是solvePnP，它的参数为
- 输入参数：
- objectpoints 空间坐标 可用vector<Point3f>
- imagepoints 像素坐标 可用vector<Point2f>
- CameraMatrix 相机内参
- DistCoeffs 畸变系数
- 输出参数：
- rvec 输出旋转向量，可用Mat类型，不接受Mat数组
- tvec 同上
- 输出的旋转向量可用Rodrigues(src,dst)函数转换为旋转矩阵
  
## 第三题
### 结果放在tri_output.txt，每一行是三角测量出的世界坐标和原先假定的世界坐标
### 这里用到了函数triregulatePoints函数，这个函数使用比较有讲究
 - 输入参数：
 - projmatrix1 这个是相机1的位姿（网上用的这个说法，其实就是[R,t],一个3*4矩阵）
 - projmatrix2 相机2的位姿
 - projpoints1 这里要相机1坐标系中坐标，不能用像素坐标系中坐标，需要转换，用undistortPoints(src,dst,cameraMatrix,DistCoeffs,R,P),P若设置为内参为实际纠正后的像素坐标，而对于三角测量来说需要的二维坐标是归一化后坐标的前两位，所以P应用默认参数（noArray）
 - projpoints2 同1
 - 输出参数：
 - point4D 其实opencv没有Point4d这个类型，所以找一个Mat放一下就好了
 - 输出了后point4D形式为（x,y,z,w）是在齐次坐标中归一化过的，故需要整体除一个w来使w为1得到真正的三维坐标
 ### opencv中矩阵的一些用法
 - copyTo(M(Rect)) 类似于MatLab和python中M[x0:x1,y0:y1]的做法,可以取矩阵中某一ROI的引用，从而使用矩阵区域的整体复制
 - M.row(i)和M.col(i)可以调用矩阵行列向量的引用，比ROI要快捷一点
 - M.at\<T\>(i,j)可以访问矩阵中某处值，实际上是引用，这也是进行矩阵元素访问的一种快捷方法，中间的模板类型要对应图像矩阵类型详见https://blog.csdn.net/Young__Fan/article/details/81866237
 - hconcat和vconcat可以实现矩阵拼接，h是横向，v是纵向

