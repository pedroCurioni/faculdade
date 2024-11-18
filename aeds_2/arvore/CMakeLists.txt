# CMakeList.txt : CMake project for arvore, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (arvore "arvore.c" "arvore.h" "main.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET arvore PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
