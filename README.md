# fluxSIM

Loop-based SPICE simulator to solve Josephson junction array circuits (SQIFs).

## Dependencies

Fedora system install.

```bash
sudo dnf install vtk vtk-devel
sudo dnf install boost boost-devel
sudo dnf install armadillo armadillo-devel
```

### VTK Source Install

Before installing VTK, we have to install:

```bash
sudo apt-get install freeglut3-dev
```

To install VTK:

```bash
git clone git://vtk.org/VTK.git VTK

```

Create a build directory which is separate from the source.

```bash
mkdir VTK-build
cd VTK-build
ccmake /path/to/VTK
```

## Install

As a pre-requesite first install *Conan the Librarian* as follow:

```bash
pip3 install conan --user
```

To install the program first create a build directory, then cd into it and run conan to install dependencies. Finally, commpile *Magix* using cmake.

```bash
mkdir build
cd build
conan install ..
cmake ..
make
```
