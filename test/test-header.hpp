// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
#pragma once
#include <gtest/gtest.h>
#include "opencv_stl_forwarder/stl/algorithm.hpp"
#include "opencv2/core.hpp"

#include <numeric>
#include <list>

// The fixture for testing class Foo.
class CORE_stl_forward : public ::testing::Test {
 protected:

    void SetUp() override
    {
        size_t size = 13;
        mat = cv::Mat(static_cast<int>(size),static_cast<int>(size),CV_32S);
        mat_f = cv::Mat_<float>(static_cast<int>(size),static_cast<int>(size));


        intVec = std::vector<int>(size*size);
        intList = std::list<int>(size*size);

        subMat = mat(cv::Rect(2,2,7,7));
        matSub_f = mat_f(cv::Rect(2,2,7,7));

        std::iota(mat.begin<int>(), mat.end<int>(), -1);
        std::iota(mat_f.begin(), mat_f.end(), -1.0f);

        std::iota(intVec.begin(), intVec.end(), -1);
        std::iota(intList.begin(), intList.end(), -1);

        std::iota(subMat.begin(), subMat.end(), -1);
        std::iota(matSub_f.begin(), matSub_f.end(), -1.0f);
    }

    void TearDown() override
    {

    }
    cv::Mat mat;
    cv::Mat_<float> mat_f;

    std::vector<int> intVec;
    std::list<int> intList;

    cv::Mat_<int> subMat;
    cv::Mat_<float> matSub_f;
};

