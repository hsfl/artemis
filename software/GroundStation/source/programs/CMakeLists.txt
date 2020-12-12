
add_executable(prompt prompt.cpp)
target_link_libraries(prompt ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)

add_executable(spoofer spoofer.cpp)
target_link_libraries(spoofer ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)
