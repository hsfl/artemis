
set(CUBESAT_DEVICE_SRC	I2CDevice.cpp
                        SPIDevice.cpp
                        UARTDevice.cpp
                        OPT3001.cpp
                        ADT7311.cpp
                        PyCubed.cpp
                        GPIO.cpp)


add_library(CubesatDevices STATIC ${CUBESAT_DEVICE_SRC})
target_link_libraries(CubesatDevices ${COSMOS_LIBS})
