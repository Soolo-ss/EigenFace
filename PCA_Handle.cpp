//
//  PCA_Handle.cpp
//  SRC_Face_Detector
//
//  Created by 盛晟 on 15/12/1.
//  Copyright © 2015年 盛晟. All rights reserved.
//

#include "PCA_Handle.hpp"

#include <sstream>
#include "dirent.h"
#include "opencv2/core/eigen.hpp"

#include "function.hpp"

using cv::Scalar;

PCA_Handle::PCA_Handle(const std::string& filepath)
{
    vector<string> filenames;
    
    //读取目录下图片名
    if ((ReadDir(filepath, filenames)) == false) {
        std::cerr<<"读取文件失败"<<std::endl;
        exit(1);
    }
    
    //读取图片信息以列向量的形式存放在image中
    cv::Mat tmp;
    cv::Mat tmp_col;
    int rows = 0, cols = 0;
    
    vector<string>::iterator it = filenames.begin();
    tmp = cv::imread((filepath + "/" +(*it)), 0);
    
    cv::namedWindow("ss");
    
    cols = tmp.cols;
    rows = tmp.rows;
    images_cols = cols;
    images_rows = rows;
    
    MatConvertToColumVector(tmp, tmp_col);
    
    rows = cols * rows;
    cols = static_cast<int>(filenames.size());
    
    
    images.create(rows, cols, tmp.type());
    int i = 0;
    
    for ( ; it != filenames.end(); ++it) {
        tmp_col.copyTo(images.col(i));
//        tmp.release();
//        tmp_col.release();
        tmp = cv::imread((filepath + "/" + (*it)), 0);
        MatConvertToColumVector(tmp, tmp_col);
        ++i;
        
    }
    
    //为了精确以及后续计算特征值的需要，图片元素转换为float类型
    images.convertTo(images, CV_32FC1);
    
    if (images.cols != filenames.size()) {
        std::cerr<<"读取文件错误"<<std::endl;
        exit(1);
    }
    
}

void PCA_Handle::StartWork()
{
    cv::Mat norm_martrix;
    cv::Mat inv_cov_matrix;
    cv::Mat eigen_value;
    cv::Mat eigen_vector;
    
    Equalization(images, norm_martrix);
    
    //求得的是X.t * X
    GetInverseCovarianceMatrix(norm_martrix, inv_cov_matrix);
    
    GetEigen(inv_cov_matrix, eigen_value, eigen_vector);
    
    //转换为X*X.t的特征值
    eigen_vector = norm_martrix * eigen_vector;
    
    cv::namedWindow("ss");
    
    cv::Mat show1;
    cv::Mat show2;
    for (int i = 0; i != 10; ++i) {
        eigen_vector.col(i).copyTo(show1);
        ColumVectorConvertToMat(show1, show2, images_rows, images_cols);
        show2.convertTo(show2, CV_8UC1);
    
        cv::imshow("ss", show2);
        cv::waitKey();
    }
}


//需要判断是否是cv_32fc1或者 cv_64fc1 但是判断出错， 有待改成
void PCA_Handle::Equalization(cv::Mat& in, cv::Mat &out)
{
    if (out.empty())
        out.create(in.rows, in.cols, in.type());
    
    if (in.cols != out.cols || in.rows != out.rows) {
        std::cerr<<"归一化错误"<<std::endl;
        exit(1);
    }
    
    cv::Mat tmp_sum;

    cv::reduce(in, tmp_sum, 1, CV_REDUCE_AVG, in.type());

    //求每行减去平均值  maybe more better?
    for (int i = 0; i != in.rows; ++i) {
        float sub = tmp_sum.ptr<float>(i)[0];
        out.row(i) = in.row(i) - sub;
    }
}

bool PCA_Handle::ReadDir(const string& filepath, vector<string>& filenames)
{
    filenames.clear();
    
    DIR *dp;
    struct dirent *dirp;
    string filename;
    
    dp = opendir(filepath.c_str());
    if (dp == NULL) {
        std::cerr<<"打开目录失败"<<std::endl;
        return false;
    }
    
    while ((dirp = readdir(dp)) != NULL) {
        filename = dirp->d_name;
        
        if (filename.empty())
            break;
        
        if (filename == "." || filename == ".." ||
            filename == ".DS_Store")
            continue;
        
        filenames.push_back(filename);
    }
    
    closedir(dp);
    
    return true;
}

void PCA_Handle::GetInverseCovarianceMatrix(cv::Mat& in, cv::Mat& out)
{
    cv::Mat in_t;
    cv::Mat cov_matrix;
    float m = in.cols;
    
    in_t = in.t();
    
    //opencv只支持float，double相乘
//    if (in.type() != CV_32F || in.type() != CV_64F) {
//        std::cerr<<"计算协方差矩阵错误"<<std::endl;
//        exit(1);
//    }
    
    cov_matrix.create(in.rows, in.rows, CV_32FC1);
    cov_matrix = in_t * in;
    cov_matrix.convertTo(cov_matrix, CV_32FC1, (1/m));
    
    out = cov_matrix.clone();
}

bool PCA_Handle::GetEigen(cv::Mat& in, cv::Mat& eigenvalues, cv::Mat& eigenvectors)
{
    if (cv::eigen(in, eigenvalues, eigenvectors) == false) {
        std::cerr<<"求特征值失败"<<std::endl;
        return false;
    }
    else
        return true;
}

