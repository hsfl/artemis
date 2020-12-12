
add_executable(agent_ground agent_ground.cpp)
target_link_libraries(agent_ground ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)
