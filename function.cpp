//
//  function.cpp
//  SRC_Face_Detector
//
//  Created by 盛晟 on 15/12/1.
//  Copyright © 2015年 盛晟. All rights reserved.
//

#include "function.hpp"

bool MatConvertToColumVector(cv::Mat &in, cv::Mat &out)
{
    if (in.rows < 1 || in.cols < 1)
        return false;
    
    
    int rows = in.cols * in.rows;
    int cols = 1;
    
    cv::Mat tmp(rows, cols, in.type(), in.data);
    tmp.copyTo(out);
    
    
    
    return true;
}

bool ColumVectorSum(cv::Mat &in, cv::Mat &out, int type)
{
    if (in.cols != 1) {
        std::cerr<<"列向量求和错误，请输入正确列向量!"<<std::endl;
        return false;
    }
    
    for (int i = 0; i != in.rows; ++i) {
        
    }
    
    return true;
}

bool ColumVectorConvertToMat(cv::Mat& in, cv::Mat& out, int rows, int cols)
{
    if (in.cols != 1) {
        std::cerr<<"请输入正确向量"<<std::endl;
        return false;
    }
    
    cv::Mat tmp(rows, cols, in.type(), in.data);
    tmp.copyTo(out);
    
    return true;
}
