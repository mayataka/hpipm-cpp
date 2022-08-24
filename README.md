# hpipm-cpp: A C++ wrapper for [hpipm](https://github.com/giaf/hpipm)

A C++ wrapper for [hpipm](https://github.com/giaf/hpipm), a high-performance interior-point method (IPM) solver for structured quadratic programming (QP) arising in optimal control (OC) and model predictive control (MPC).
This wrapper provides an interface of hpipm using STL and Eigen. 

## Requirements
- [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page)

Eigen3 can be installed by the following command:
```
sudo apt install libeigen3-dev
```

Other external libraries, i.e., [blasfeo](https://github.com/giaf/blasfeo) and [hpipm](https://github.com/giaf/hpipm) are automatically installed with `hpipm-cpp`.

## Build hpipm-cpp
```
git clone https://github.com/mayataka/hpipm-cpp
cd hpipm-cpp
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release 
make -j4
sudo make install -j
```

## Usage
Link hpipm-cpp in the `CMakeLists.txt` as
```
...
find_package(hpipm-cpp REQUIRED)
target_link_libraries(
  YOUR_TARGET
  PRIVATE
  hpipm-cpp::hpipm-cpp
)
...
```
and write the source files as 
```
#include "hpipm-cpp/hpipm-cpp.hpp"

N = ...; // horion length
hpipm::OcpQpDim dim(N);
dim.nx[i] = ...  // set dims
dim.nu[i] = ...  // set dims
... 

hpipm::OcpQp qp(dim); 
qp.A[i] = Eigen::MatrixXd::... // set QP datas by Eigen 
... 

hpipm::OcpQpIpmSolverSettings ipm_solver_settings; 
ipm_solver_settings.mode = ... // set the IPM solver settings
... 

hpipm::OcpQpSolution solution(dim);
hpipm::OcpQpSolver solver(dim, ipm_solver_settings);
const auto res = solver.solve(qp, solution); // solve the QP

for (int i=0; i<=dim.N; ++i) {
  std::cout << "x[" << i << "]: " << sol.x[i].transpose() << std::endl;  
}
for (int i=0; i<dim.N; ++i) {
  std::cout << "u[" << i << "]: " << sol.u[i].transpose() << std::endl;  
}
```

For detailed formulations, please see the [documentation of hpipm](https://github.com/giaf/hpipm/blob/master/doc/guide.pdf).
The conventions follow the documentation. 
