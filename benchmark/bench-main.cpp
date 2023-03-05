#include <gtest/gtest.h>
#include "opencv_stl_forwarder/stl/algorithm.hpp"
#include "opencv2/core.hpp"
#include <numeric>
#include <list>

#include <benchmark/benchmark.h>

constexpr size_t size = 20;
cv::Mat setupMatrixInt()
{
    cv::Mat mat;
    mat = cv::Mat(static_cast<int>(size),static_cast<int>(size),CV_32S);
    std::iota(mat.begin<int>(), mat.end<int>(), -1);
    return mat;
}


cv::Mat_<float> setupMatrixFloat()
{
    cv::Mat_<float> mat_f;
    mat_f = cv::Mat_<float>(static_cast<int>(size),static_cast<int>(size));
   std::iota(mat_f.begin(), mat_f.end(), -1.0f);
    return mat_f;
}

static void count_if_experimental(benchmark::State& state) {
  // Perform setup here
  const cv::Mat_<float> mat = setupMatrixFloat();
  auto lambda = [](int val){return val >13 && val < 100;};
  for (auto _ : state) {
    // This code gets timed
    const auto val = cv::experimental::count_if(mat.begin(), mat.end(),lambda);
    benchmark::DoNotOptimize(val);
  }
}

static void count_if_stl_pointer(benchmark::State& state) {
  // Perform setup here
  const cv::Mat_<float> mat = setupMatrixFloat();
  auto lambda = [](int val){return val >13 && val < 100;};
  for (auto _ : state) {
    // This code gets timed
    const auto val = std::count_if((float*)mat.begin().ptr, (float*)mat.end().ptr,lambda);
    benchmark::DoNotOptimize(val);
  }
}

static void count_if_stl_iterator(benchmark::State& state) {
  // Perform setup here
  const cv::Mat_<float> mat = setupMatrixFloat();
  auto lambda = [](int val){return val >13 && val < 100;};
  for (auto _ : state) {
    // This code gets timed
    const auto val = std::count_if(mat.begin(), mat.end(),lambda);
    benchmark::DoNotOptimize(val);
  }
}

static void find_experimental(benchmark::State& state) {
  // Perform setup here
  const cv::Mat mat = setupMatrixInt();
  for (auto _ : state) {
    // This code gets timed
    const auto val = *cv::experimental::find(mat.begin<int>(), mat.end<int>(),16);
    benchmark::DoNotOptimize(val);
  }
}

static void find_stl_pointer(benchmark::State& state) {
  // Perform setup here
  const cv::Mat mat = setupMatrixInt();
  for (auto _ : state) {
    // This code gets timed
    const auto val = *std::find((int*)mat.begin<int>().ptr, (int*)mat.end<int>().ptr,16);
    benchmark::DoNotOptimize(val);
  }
}

static void find_stl_iterator(benchmark::State& state) {
  // Perform setup here
  const cv::Mat mat = setupMatrixInt();
  for (auto _ : state) {
    // This code gets timed
    const auto val = *std::find(mat.begin<int>(), mat.end<int>(),16);
    benchmark::DoNotOptimize(val);
  }
}

// Register the function as a benchmark
//BENCHMARK(count_if_experimental);
//BENCHMARK(count_if_stl_pointer);
//BENCHMARK(count_if_stl_iterator);

// Register the function as a benchmark
BENCHMARK(find_experimental);
BENCHMARK(find_stl_pointer);
BENCHMARK(find_stl_iterator);


// Run the benchmark
BENCHMARK_MAIN();
