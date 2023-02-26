# opencv_stl_forwarder
Improve performance of stl algorithms when using opencv matrices.

#Description
STL algorithms aren't going along very well with opencv matrices. The matrix iterators in opencv are very poorly performing, because they keep track of jumps in the memory layout to support submatrices. 
The solution that this library offers is to use template meta programming and a single run-time check to see if opencv iterators have to be used (because the matrix is not contiguous) or if iterators can be replaced by pointers, making the algorithm often around an order of magnitude more performant.

#Deployment
This library is header only except the tests and benchmarks.

#Build and test on ubuntu
To build and run tests use

$ git submodule init && git submodule udpate
$ mkdir build && cd build && cmake -DOPENCV_STL_FORWARDER_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release .. && make -j

and run the unit tests and benchmarks:
$ ./unit_test && ./benchmarks

to see the gain in performance over cv iterator based stl algorithms.
