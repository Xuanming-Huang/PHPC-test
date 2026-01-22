# General library configuration
# ===== OpenMP (macOS manual setup) =====
if(APPLE)
    add_library(OpenMP::OpenMP_CXX INTERFACE IMPORTED)

    set_target_properties(OpenMP::OpenMP_CXX PROPERTIES
        INTERFACE_COMPILE_OPTIONS "-Xpreprocessor;-fopenmp"
        INTERFACE_INCLUDE_DIRECTORIES "/opt/homebrew/Cellar/libomp/17.0.6/include"
        INTERFACE_LINK_LIBRARIES "/opt/homebrew/Cellar/libomp/17.0.6/lib/libomp.dylib"
    )
else()
    find_package(OpenMP REQUIRED)
endif()

# ===== C++ standard =====
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== Default build type =====
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()