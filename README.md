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

