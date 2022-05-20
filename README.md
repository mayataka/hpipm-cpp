# hpipm-cpp: A C++ wrapper for [hpipm](https://github.com/giaf/hpipm)

A C++ wrapper for [hpipm](https://github.com/giaf/hpipm), a high-performance interior-point method (IPM) solver for structured quadratic programming (QP) arising in optimal control (OC) and model predictive control (MPC).
This wrapper provides an interface of hpipm using STL and Eigen. 

## Requirements
1. [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page)
2. [blasfeo](https://github.com/giaf/blasfeo)
3. [hpipm](https://github.com/giaf/hpipm)


Eigen3 can be installed by the following command:
```
sudo apt install libeigen3-dev
```


blasfeo can be installed by the following commands (they are almost same as the `install_blasfeo.sh`):
```
git clone https://github.com/giaf/blasfeo
cd blasfeo 
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBLASFEO_EXAMPLES=OFF 
make -j4
sudo make install -j
echo export LD_LIBRARY_PATH=/opt/blasfeo/lib:$LD_LIBRARY_PATH >> ~/.bashrc
```


hpipm can be installed by the following commands (they are almost same as the `install_hpipm.sh`):
```
git clone https://github.com/giaf/hpipm
cd hpipm
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DHPIPM_TESTING=OFF
make -j4
sudo make install -j
echo export LD_LIBRARY_PATH=/opt/hpipm/lib:$LD_LIBRARY_PATH >> ~/.bashrc
```

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
#include "hpipm-cpp/ocp_qp_dim.hpp"
#include "hpipm-cpp/ocp_qp.hpp"
#include "hpipm-cpp/ocp_qp_ipm_arg.hpp"
#include "hpipm-cpp/ocp_qp_ipm.hpp"

hpipm::ocp_qp_dim dim;
dim.N = ... // set dims
dim.nx.push_back(...)  // set dims
... 
dim.createHpipmData(); // this creates hpipm's QP-dim object.

hpipm::ocp_qp qp; 
qp.A.push_back(Eigen::MatrixXd::...) // set QP datas by Eigen objects
... 
qp.createHpipmData(dim); // this creates hpipm's QP-data object.

hpipm::ipm_arg ipm_arg; 
ipm_arg.ipm_arg.mode = ... // set the IPM solver settings
... 
ipm_arg.createHpipmData(dim); // this creates hpipm's the IPM solver-settings object.

hpipm::ocp_qp_sol sol;
sol.createHpipmData(dim); // this creates hpipm's QP-solution object.

hpipm::ocp_qp_ipm ipm;
ipm.createHpipmData(dim, arg); // this creates hpipm's IPM-solver object.
const auto res = ipm.solve(qp, sol, arg); // solve the QP

sol.from_hpipm(dim); // retrieve the QP-solution as Eigen's object from hpipm's object.
for (int i=0; i<=dim.N; ++i) {
  std::cout << "x[" << i << "]: " << sol.x[i].transpose() << std::endl;  
  std::cout << "u[" << i << "]: " << sol.u[i].transpose() << std::endl;
}
```