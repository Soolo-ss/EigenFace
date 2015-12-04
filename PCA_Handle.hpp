//
//  PCA_Handle.hpp
//  SRC_Face_Detector
//
//  Created by 盛晟 on 15/12/1.
//  Copyright © 2015年 盛晟. All rights reserved.
//

#ifndef PCA_Handle_hpp
#define PCA_Handle_hpp

#include "opencv2/opencv.hpp"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class PCA_Handle{
public:
    PCA_Handle(const string &filepath);
    
    void StartWork();

    //图片向量均值化
    void Equalization(cv::Mat& in, cv::Mat& out);
    
    //输入目录，获取目录下文件名
    bool ReadDir(const string &filepath, vector<string>& filenames);
    
    //求(X.t() * X)  因为协方差阶数太大，为求简便
    void GetInverseCovarianceMatrix(cv::Mat& in, cv::Mat& out);
    
    //求矩阵特征值
    bool GetEigen(cv::Mat& in, cv::Mat& eigenvalue, cv::Mat& eigenvector);
    
    cv::PCA compressPCA(cv::Mat& input, cv::Mat& output);
private:
    cv::Mat images;
    int images_cols;                //原矩阵行列，方便恢复
    int images_rows;                //原矩阵行列，方便恢复
};


#endif /* PCA_Handle_hpp */
