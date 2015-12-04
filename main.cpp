//
//  main.cpp
//  SRC_Face_Detector
//
//  Created by 盛晟 on 15/11/30.
//  Copyright © 2015年 盛晟. All rights reserved.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Eigen/Dense"
#include "opencv2/core/eigen.hpp"

#include "function.hpp"
#include "PCA_Handle.hpp"

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    
    PCA_Handle pca("/Users/shengsheng/Desktop/img_process/code/SRC_Face_Detector/images");
    
    pca.StartWork();
}
