# set up for modules. This file should be included using
# source load_modules.sh
# if you want to use the gcc toolchain + main utilities used in the examples
source /u/sw/etc/profile
module load gcc-glibc/11
module load superlu
module load eigen
module load openblas
module load suitesparse
<<<<<<< HEAD
module load boost
=======
module load pybind11
>>>>>>> c51dda82d4a8d15d522a82586f08dab5c9a54b91
# for the example on file i/o
# module load hdf5 