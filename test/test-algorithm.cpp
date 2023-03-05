// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
#include <gtest/gtest.h>
#include "test-header.hpp"

#include <numeric>
#include <algorithm>
#include <list>

namespace opencv_test { namespace {
using namespace cv;

//This opencv feature requires return type auto a C++14 feature
TEST_F(CORE_stl_forward, count_if)
{
    auto lambda = [](int val){return val >13 && val < 100;};

    //This test is with replacable iterators.
    EXPECT_TRUE(cv::detail::__it_replacable(mat.begin<int>(), mat.end<int>(),lambda));

    //Test replaced iterators vs. normal stl algo
    EXPECT_EQ(experimental::count_if(mat.begin<int>(), mat.end<int>(),lambda), std::count_if(mat.begin<int>(), mat.end<int>(),lambda));
    EXPECT_EQ(experimental::count_if(mat.rbegin<int>(), mat.rend<int>(),lambda), std::count_if(mat.rbegin<int>(), mat.rend<int>(),lambda));
    EXPECT_EQ(experimental::count_if(mat.begin<int>(), mat.end<int>(),lambda), std::count_if((int*)mat.begin<int>().ptr, (int*)mat.end<int>().ptr,lambda));
}

//This opencv feature requires return type auto a C++14 feature
TEST_F(CORE_stl_forward, all_of)
{
    auto lambda = [](int val){return val >13 && val < 100;};

    //This test is with replacable iterators.
    EXPECT_TRUE(cv::detail::__it_replacable(mat.begin<int>(), mat.end<int>(),lambda));

    //Test replaced iterators vs. normal stl algo
    EXPECT_EQ(experimental::all_of(mat.begin<int>(), mat.end<int>(),lambda), std::all_of(mat.begin<int>(), mat.end<int>(),lambda));
}

TEST_F(CORE_stl_forward, find)
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

/*
TEST_F(CORE_stl_forward, transform)
{
    auto lambda = [](float val){return val*2.5;};
    //Test replaced iterators vs. normal stl algo
    auto matcpy_experimental = mat_f.clone();
    auto matcpy_stl = mat_f.clone();


    static_assert(false); //See description
    //THe issue here is, that we base ourselves on the first iterator available (the input iterator).
    //However in std::transform it depends on the position of the input iterator for the amtrix to be transformed:
    //It could be in the third, fourth, or fifth place! It would be possible to find the first cv iterator and copy it twice to a call of the algorithm.
    //Like that we would get a returned iterator that corresponds to the first value we would need to add to e.g.
    //std::transform(a.begin(), a.end(), b.begin()...) --> std::transform(a.begin(), a.begin(), b.begin())
    //would return the output iterator.


    const auto diff_stl_ptr = (std::transform((float*)mat_f.begin().ptr, (float*)mat_f.end().ptr, (float*)matcpy_experimental.begin().ptr, lambda));
    const auto diff_ptr = diff_stl_ptr - (float*)matcpy_experimental.begin().ptr;

    std::cout << "diff pointer is " << diff_stl_ptr << std::endl;
    std::cout << "addresses are : " << (const void*)mat_f.begin().ptr << "\n and " << (const void*)mat_f.end().ptr << "\n and " << (const void*)matcpy_experimental.begin().ptr<<std::endl;
    const auto diff = experimental::transform(mat_f.begin(), mat_f.end(), matcpy_experimental.begin(), lambda) - matcpy_experimental.begin();
    std::cout << typeid(experimental::transform(mat_f.begin(), mat_f.end(), matcpy_experimental.begin(), lambda)).name() << std::endl;

    const auto diff_stl = std::transform(mat_f.begin(), mat_f.end(), matcpy_experimental.begin(), lambda) - matcpy_experimental.begin();
    EXPECT_EQ(diff, diff_stl);

    EXPECT_EQ(experimental::transform(mat_f.begin(), mat_f.end(), matcpy_experimental.begin(), lambda) - matcpy_experimental.begin(), \
              std::transform(mat_f.begin(), mat_f.end(), matcpy_stl.begin(), lambda) - matcpy_stl.begin());

    //Test reverse iterator vs stl algo
    EXPECT_EQ(*experimental::transform(mat_f.rbegin(), mat_f.rend(),5), *std::transform(mat_f.rbegin(), mat_f.rend(),5));


    EXPECT_EQ(*experimental::transform(intVec.begin(), intVec.end(),5),*std::find(intVec.begin(), intVec.end(),5));


    std::ptrdiff_t replaced_dist = experimental::transform(mat.begin<int>(), mat.end<int>(),10) - mat.begin<int>();


    EXPECT_EQ(replaced_dist, orig_dist);

}
*/

}} // namespace
