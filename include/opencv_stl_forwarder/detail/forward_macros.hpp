// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level
// directory of this distribution and at http://opencv.org/license.html.
#ifndef OPENCV_CORE_FORWARD_MACROS_HPP
#define OPENCV_CORE_FORWARD_MACROS_HPP

#include "opencv2/core.hpp"
#include <tuple>
#include <type_traits>
#include <iterator>
#include "opencv_stl_forwarder/detail/util.hpp"
#include <algorithm>


#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

//Macro for stl algorithms that return a non-iterator type.
//This makes forwarding easy because we don't need to worry about pointer or cvIt return types
#define STL_FORWARD_NO_IT_RETURN(algorithm_name)  \
    template <typename... Args, std::size_t... Is>  \
    auto _impl##algorithm_name(std::tuple<Args...> tpl, cv::detail::index_sequence<Is...>){ \
      return std::algorithm_name(std::get<Is>(tpl)...); \
    } \
    template <typename... Args> \
    auto algorithm_name(Args&&... args) -> decltype(std::algorithm_name(std::forward<Args>(args)...)){  \
      if (cv::detail::__it_replacable(std::forward<Args>(args)...)) {   \
        return _impl##algorithm_name(    \
            cv::detail::make_tpl_replaced(std::forward<Args>(args)...), \
            cv::detail::make_index_sequence_variadic<Args...>());   \
      } else {  \
        return std::algorithm_name(std::forward<Args>(args)...);    \
      } \
    }



#endif //OPENCV_CORE_FORWARD_MACROS_HPP
