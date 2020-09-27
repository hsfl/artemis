cmake_minimum_required(VERSION 2.8)
project(beaglebone)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )




# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -Wno-invalid-offsetof")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# -----------------------------------------------
# Point to cosmos/source folder
set(COSMOS_SOURCE   "$ENV{HOME}/cosmos/source")
set(USE_COSMOS_FROM "SOURCE")


include(${COSMOS_SOURCE}/core/cmake/use_cosmos_from_source.cmake)


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
include_directories("./include")
include_directories("./libraries")





add_subdirectory(libraries/SimpleAgent)
set(CUBESAT_LIBS CubesatDevices SimpleAgent)

add_subdirectory(source)







# ============================== Agents ==============================

## TCS Agents
#add_executable(agent_temp agents/agent_temp.cpp)
#add_executable(agent_heater agents/agent_heater.cpp)
#target_link_libraries(agent_temp ${COSMOS_LIBS} ${CUBESAT_LIBS})
#target_link_libraries(agent_heater ${COSMOS_LIBS} ${CUBESAT_LIBS})


## EPS Agents
#add_executable(agent_switch agents/agent_switch.cpp)
#target_link_libraries(agent_switch ${COSMOS_LIBS} ${CUBESAT_LIBS})

## ADCS Agents
#add_executable(agent_sun agents/agent_sun.cpp)
#target_link_libraries(agent_sun ${COSMOS_LIBS} ${CUBESAT_LIBS})

## PyCubed Agent
#add_executable(agent_pycubed agents/agent_pycubed.cpp)
#target_link_libraries(agent_pycubed ${COSMOS_LIBS} ${CUBESAT_LIBS})

## Payload (Raspberry Pi) Agent
#add_executable(agent_raspi agents/agent_raspi.cpp)
#target_link_libraries(agent_raspi ${COSMOS_LIBS} ${CUBESAT_LIBS})


# ==================================== Tests ====================================
#add_executable(device_test tests/device_test.cpp device/I2CDevice.cpp)
#target_link_libraries(device_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(gpio_test tests/gpio_test.cpp)
#target_link_libraries(gpio_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(switch_test tests/switch_test.cpp)
#target_link_libraries(switch_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(temp_test tests/temp_test.cpp)
#target_link_libraries(temp_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(sun_test tests/sun_test.cpp)
#target_link_libraries(sun_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(soh1_test tests/soh1_test.cpp)
#target_link_libraries(soh1_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(soh2_test tests/soh2_test.cpp)
#target_link_libraries(soh2_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(pycubed_test tests/pycubed_test.cpp)
#target_link_libraries(pycubed_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

#add_executable(simpleagent_test tests/simpleagent_test.cpp)
#target_link_libraries(simpleagent_test ${COSMOS_LIBS} ${CUBESAT_LIBS})


# ==================================== Simulations ====================================
#add_executable(propagator simulation/propagator.cpp)
#target_link_libraries(propagator ${COSMOS_LIBS} ${CUBESAT_LIBS})

