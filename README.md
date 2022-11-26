# hpipm-cpp: A C++ wrapper for [hpipm](https://github.com/giaf/hpipm)

A C++ wrapper for [hpipm](https://github.com/giaf/hpipm), a high-performance interior-point method (IPM) solver for structured quadratic programming (QP) arising in optimal control (OC) and model predictive control (MPC).
This wrapper provides an interface of hpipm using STL and Eigen and inspired by [control-toolbox](https://github.com/ethz-adrl/control-toolbox) and [ocs2](https://github.com/leggedrobotics/ocs2). 

## Requirements
- [Eigen3](https://eigen.tuxfamily.org/index.php?title=Main_Page)

Eigen3 can be installed by the following command:
```
sudo apt install libeigen3-dev
```

- [blasfeo](https://github.com/giaf/blasfeo) and [hpipm](https://github.com/giaf/hpipm)  

blasfeo and hpipm can be installed, e.g., via
```
git clone https://github.com/giaf/blasfeo
git clone https://github.com/giaf/hpipm
cd blasfeo && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBLASFEO_EXAMPLES=OFF 
make -j8
sudo make install -j
cd ../../hpipm && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DHPIPM_TESTING=OFF 
make -j8
sudo make install -j
```

Further, you need to set `LD_LIBRARY_PATH` as 
```
export LD_LIBRARY_PATH=/opt/blasfeo/lib:/opt/hpipm/lib:$LD_LIBRARY_PATH
```

`/opt` is the default install destination of `blasfeo` and `hpipm`. If you change it to `YOUR_DESTINATIon`, change the above scripts as
```
git clone https://github.com/giaf/blasfeo
git clone https://github.com/giaf/hpipm
cd blasfeo && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DBLASFEO_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=YOUR_DESTINATION
make -j8
sudo make install -j
cd ../../hpipm && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DHPIPM_TESTING=OFF -DCMAKE_INSTALL_PREFIX=YOUR_DESTINATION
make -j8
sudo make install -j
export LD_LIBRARY_PATH=YOUR_DESTINATION/blasfeo/lib:YOUR_DESTINATION/hpipm/lib:$LD_LIBRARY_PATH
```


## Build hpipm-cpp
```
git clone https://github.com/mayataka/hpipm-cpp
cd hpipm-cpp
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release 
make -j8
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

unsingned int N = ...; // horion length
... 

std::vector<hpipm::OcpQp> qp(N+1); 
qp[i].A = Eigen::MatrixXd::... // set QP datas by Eigen 
... 

hpipm::OcpQpIpmSolverSettings solver_settings; 
solver_settings.mode = ... // set the IPM solver settings
... 

std::vector<hpipm::OcpQpSolution> solution(N+1);
hpipm::OcpQpSolver solver(qp, solver_settings);
Eigen::VectorXd x0 = ... // initial state
const auto status = solver.solve(x0, qp, solution); // solve the QP

for (int i=0; i<=dim.N; ++i) {
  std::cout << "x[" << i << "]: " << sol[i].x.transpose() << std::endl;  
}
for (int i=0; i<dim.N; ++i) {
  std::cout << "u[" << i << "]: " << sol[i].u.transpose() << std::endl;  
}
```

For detailed formulations, please see the [documentation of hpipm](https://github.com/giaf/hpipm/blob/master/doc/guide.pdf).
The conventions follow the documentation. 
