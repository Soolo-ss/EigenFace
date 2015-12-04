//
//  function.hpp
//  SRC_Face_Detector
//
//  Created by 盛晟 on 15/12/1.
//  Copyright © 2015年 盛晟. All rights reserved.
//

#ifndef function_hpp
#define function_hpp

#include "opencv2/opencv.hpp"

//矩阵转化为列向量
bool MatConvertToColumVector(cv::Mat &in, cv::Mat &out);

//列向量和
bool ColumVectorSum(cv::Mat &in, cv::Mat &out);

//列向量转化为矩阵
bool ColumVectorConvertToMat(cv::Mat& in, cv::Mat& out, int rows, int cols);

#endif /* function_hpp */
