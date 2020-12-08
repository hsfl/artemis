cmake_minimum_required(VERSION 2.8)
project(groundstation)



# -----------------------------------------------
# |               Compiler Options              |
# -----------------------------------------------
# Set the output directory for executables
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )


# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -Wno-invalid-offsetof")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")



# -----------------------------------------------
# |               COSMOS Options                |
# -----------------------------------------------

# Point to cosmos/source folder
set(COSMOS_SOURCE   "$ENV{HOME}/cosmos/source")
set(USE_COSMOS_FROM "SOURCE")

# Include the COSMOS CMake project
include(${COSMOS_SOURCE}/core/cmake/use_cosmos_from_source.cmake)


# Set the COSMOS libraries
set(COSMOS_LIBS
    CosmosSupport
    CosmosAgent
    CosmosDeviceGeneral
    CosmosDeviceI2C
    CosmosDeviceSerial
    CosmosDeviceCpu
    CosmosDeviceDisk
    CosmosMath
    CosmosPhysics)


# -----------------------------------------------

# Add C/C++ include directories
include_directories("./include")
include_directories("./libraries")


# Add the SimpleAgent dependency subdirectory
add_subdirectory(libraries/SimpleAgent)
set(CUBESAT_LIBS Utilities SimpleAgent)

# Add the source subdirectory
add_subdirectory(source)







