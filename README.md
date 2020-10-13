# 第二次视觉部作业
## 第一题矩阵公式

![](https://latex.codecogs.com/svg.latex?P_r%20=%20R_{ir}^TR_{ci}^T(K^{-1}(ud,vd,d)^T-t_{ci}))
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
### 结果放在tri_output.txt，上面存放了一个4*54的矩阵的输出，每一列的前三个是三角测量给定的世界坐标，下面是对照的假定的世界坐标
### 这里用到了函数triregulatePoints函数，这个函数使用比较有讲究
 - 输入参数：
 - projmatrix1 这个是相机1的位姿（网上用的这个说法，其实就是[R,t],一个3*4矩阵）
 - projmatrix2 相机2的位姿
 - projpoints1 这里要相机1坐标系中坐标，不能用像素坐标系中坐标，需要转换，K^-1 *(u,v,1)^T,这里没考虑畸变系数
 - projpoints2 同1
 - 输出参数：
 - point4D 其实opencv没有Point4d这个类型，所以找一个Mat放一下就好了
 - 输出了后point4D形式为（x,y,z,w）是在齐次坐标中归一化过的，故需要整体除一个w来使w为1得到真正的三维坐标
 ### 这道题也了解了一些opencv中矩阵的用法，比如问来的copyTo(M(Rect))类似于MatLab和python中M[a：b]的做法，M.row(i)和M.col(i)可以调用矩阵行列向量的引用，M.at<>(i,j)可以访问矩阵中某处值
