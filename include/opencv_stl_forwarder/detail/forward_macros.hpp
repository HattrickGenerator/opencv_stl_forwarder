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


#define STL_FORWARD_FIRST_IT_RETURN(algorithm_name) \
    template <typename... Args, std::size_t... Is>  \
    auto _impl##algorithm_name(std::tuple<Args...> tpl, cv::detail::index_sequence<Is...>) {   \
      return std::algorithm_name(std::get<Is>(tpl)...);   \
    }   \
    \
    template <typename ReturnType,  typename beginIt, typename... Args, std::size_t... Is,  \
        cv::detail::enable_if_t<!cv::detail::is_base_of_reverse_cvit<ReturnType>::value, bool> = true>  \
    auto _impl##algorithm_name(beginIt&&, Args&& ... args) \
      -> ReturnType {   \
        return _impl##algorithm_name(cv::detail::make_tpl_replaced(std::forward<Args>(args)...),   \
            cv::detail::make_index_sequence_variadic<Args...>());   \
    }   \
    \
    /*When this is the case we need to calculate the offset to the cv iterator we want to return*/ \
    template <typename ReturnType,  typename beginIt, typename... Args, std::size_t... Is,  \
        cv::detail::enable_if_t<cv::detail::is_base_of_reverse_cvit<ReturnType>::value, bool> = true>   \
    auto _impl##algorithm_name(beginIt&& it, Args&& ... args)  \
      -> ReturnType {   \
        auto it_intermediate =_impl##algorithm_name(cv::detail::make_tpl_replaced(std::forward<Args>(args)...),    \
                cv::detail::make_index_sequence_variadic<Args...>());   \
        return it + (it_intermediate - cv::detail::get_replaced_val(std::forward<beginIt>(it)));    \
    }   \
    \
    /*Forwarding for find stl algo. Decides at runtime if the iterators are replaced with pointers or kept as cv iterators for non-contiguous matrices.*/ \
    template <typename... Args> \
    auto algorithm_name(Args&&... args)   \
        -> decltype(std::algorithm_name(std::forward<Args>(args)...)) {   \
      /*Only perform optimization if we even have opencv iterators*/ \
      if (cv::detail::__it_replacable(std::forward<Args>(args)...)) {   \
    \
          /*Find first instance of an opencv iterator (or its reverse iterator!) in the parameter pack */ \
          constexpr size_t val = cv::detail::__get_first_cv_it_index<Args...>();    \
          /*Forward tuple for accessing the begin iterator via get to the impl functions*/ \
          auto tpl_frwd = std::make_tuple(std::forward<Args>(args)...);\
          using ReturnType = decltype(std::algorithm_name(std::forward<Args>(args)...));  \
          using beginIt = decltype(std::get<val>(tpl_frwd));    \
          /*Explicitely mention templates to avoid posing constraints on ReturnType being default constructable*/   \
          return _impl##algorithm_name<ReturnType, beginIt, Args...>(std::get<val>(tpl_frwd), std::forward<Args>(args)...);    \
      } else {  \
        return std::algorithm_name(std::forward<Args>(args)...);  \
      } \
    }



#endif //OPENCV_CORE_FORWARD_MACROS_HPP
