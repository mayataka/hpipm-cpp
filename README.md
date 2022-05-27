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
target_include_directories(
  YOUR_TARGET
  PRIVATE
  ${hpipm-cpp_INCLUDE_DIR}
)
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

hpipm::OcpQpDim dim;
dim.N = ... // set dims
dim.nx.push_back(...)  // set dims
... 
dim.createHpipmData(); // this creates hpipm's QP-dim object.

hpipm::OcpQp qp; 
qp.A.push_back(Eigen::MatrixXd::...) // set QP datas by Eigen objects
... 
qp.createHpipmData(dim); // this creates hpipm's QP-data object.

hpipm::OcpQpIpmSolverSettings ipm_arg; 
ipm_arg.ipm_arg.mode = ... // set the IPM solver settings
... 
ipm_arg.createHpipmData(dim); // this creates hpipm's the IPM solver-settings object.

hpipm::OcpQpSolution sol;
sol.createHpipmData(dim); // this creates hpipm's QP-solution object.

hpipm::OcpQpSolver solver;
solver.createHpipmData(dim, arg); // this creates hpipm's IPM-solver object.
const auto res = solver.solve(qp, sol, arg); // solve the QP

sol.getSolutionFromHpipm(dim); // retrieve the QP-solution as Eigen's object from hpipm's object.
for (int i=0; i<=dim.N; ++i) {
  std::cout << "x[" << i << "]: " << sol.x[i].transpose() << std::endl;  
}
for (int i=0; i<dim.N; ++i) {
  std::cout << "u[" << i << "]: " << sol.u[i].transpose() << std::endl;  
}
```

For detailed formulations, please see the [documentation of hpipm](https://github.com/giaf/hpipm/blob/master/doc/guide.pdf).
The data objects of hpipm::QcpQp follow the convention of that documentation. 
