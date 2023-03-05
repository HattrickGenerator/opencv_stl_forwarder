// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level
// directory of this distribution and at http://opencv.org/license.html.

#ifndef OPENCV_CORE_STL_ALGORITHM_HPP
#define OPENCV_CORE_STL_ALGORITHM_HPP


#include "opencv2/core.hpp"
#include "opencv_stl_forwarder/detail/pointer-tuple-replacer.hpp"
#include "opencv_stl_forwarder/detail/variadic-continuous-checker.hpp"
#include "opencv_stl_forwarder/detail/util.hpp"
#include "opencv_stl_forwarder/detail/forward_macros.hpp"

#include <tuple>

//This opencv feature requires return type auto a C++14 feature

namespace cv {
namespace experimental {

STL_FORWARD_NO_IT_RETURN(all_of)
STL_FORWARD_NO_IT_RETURN(any_of)
STL_FORWARD_NO_IT_RETURN(none_of)

STL_FORWARD_FIRST_IT_RETURN(find)
STL_FORWARD_FIRST_IT_RETURN(find_if)
STL_FORWARD_FIRST_IT_RETURN(find_if_not)

///@brief overload for forwarding a tuple and index sequence with cv iterators
/// replaced as pointers
template <typename... Args, std::size_t... Is>
auto _count_if_impl(std::tuple<Args...> tpl, cv::detail::index_sequence<Is...>){
  return std::count_if(std::get<Is>(tpl)...);
}

///@brief Forwarding for count_if stl algo. Decides at runtime if the iterators are replaced with pointers
/// or kept as cv iterators for non-contiguous matrices.
template <typename... Args>
auto count_if(Args&&... args)
    -> decltype(std::count_if(std::forward<Args>(args)...)) {

  if (cv::detail::__it_replacable(std::forward<Args>(args)...)) {
    return _count_if_impl(
        cv::detail::make_tpl_replaced(std::forward<Args>(args)...),
        cv::detail::make_index_sequence_variadic<Args...>());
  } else {
    return std::count_if(std::forward<Args>(args)...);
  }
}



} // namespace experimental
} // namespace cv
#endif //OPENCV_CORE_STL_ALGORITHM_HPP
