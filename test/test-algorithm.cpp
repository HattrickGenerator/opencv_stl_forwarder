// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
#include <gtest/gtest.h>
#include "test-header.hpp"

#include <numeric>
#include <list>

namespace opencv_test { namespace {
using namespace cv;

//This opencv feature requires return type auto a C++14 feature
TEST_F(CORE_stl_forward, count_if_test)
{
    auto lambda = [](int val){return val >13 && val < 100;};

    //This test is with replacable iterators.
    EXPECT_TRUE(cv::detail::__it_replacable(mat.begin<int>(), mat.end<int>(),lambda));

    //Test replaced iterators vs. normal stl algo
    EXPECT_EQ(experimental::count_if(mat.begin<int>(), mat.end<int>(),lambda), std::count_if(mat.begin<int>(), mat.end<int>(),lambda));
    EXPECT_EQ(experimental::count_if(mat.rbegin<int>(), mat.rend<int>(),lambda), std::count_if(mat.rbegin<int>(), mat.rend<int>(),lambda));
    EXPECT_EQ(experimental::count_if(mat.begin<int>(), mat.end<int>(),lambda), std::count_if((int*)mat.begin<int>().ptr, (int*)mat.end<int>().ptr,lambda));
}

TEST_F(CORE_stl_forward, find_test)
{
    //Test replaced iterators vs. normal stl algo
    EXPECT_EQ(*experimental::find(mat_f.begin(), mat_f.end(),5),*std::find(mat_f.begin(), mat_f.end(),5));
    EXPECT_EQ(experimental::find(mat_f.begin(), mat_f.end(),5),std::find(mat_f.begin(), mat_f.end(),5));

    //Test reverse iterator vs stl algo
    EXPECT_EQ(*experimental::find(mat_f.rbegin(), mat_f.rend(),5), *std::find(mat_f.rbegin(), mat_f.rend(),5));
    EXPECT_EQ(experimental::find(mat_f.rbegin(), mat_f.rend(),5), std::find(mat_f.rbegin(), mat_f.rend(),5));

    EXPECT_EQ(*experimental::find(intVec.begin(), intVec.end(),5),*std::find(intVec.begin(), intVec.end(),5));
    EXPECT_EQ(*experimental::find(intVec.rbegin(), intVec.rend(),5),*std::find(intVec.rbegin(), intVec.rend(),5));

    std::ptrdiff_t replaced_dist = experimental::find(mat.begin<int>(), mat.end<int>(),10) - mat.begin<int>();
    std::ptrdiff_t orig_dist = std::find(mat.begin<int>(), mat.end<int>(),10) - mat.begin<int>();

    EXPECT_EQ(replaced_dist, orig_dist);
}


}} // namespace
