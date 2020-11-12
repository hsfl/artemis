
add_executable(gpio_test gpio_test.cpp)
target_link_libraries(gpio_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(switch_test switch_test.cpp)
target_link_libraries(switch_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(temp_test temp_test.cpp)
target_link_libraries(temp_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(sun_test sun_test.cpp)
target_link_libraries(sun_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(soh1_test soh1_test.cpp)
target_link_libraries(soh1_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(soh2_test soh2_test.cpp)
target_link_libraries(soh2_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(pycubed_test pycubed_test.cpp)
target_link_libraries(pycubed_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(simpleagent_test simpleagent_test.cpp)
target_link_libraries(simpleagent_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

add_executable(telemlog_test telemlog_test.cpp)
target_link_libraries(telemlog_test ${COSMOS_LIBS} ${CUBESAT_LIBS})

