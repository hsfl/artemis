
# TCS Agents
add_executable(agent_temp agent_temp.cpp)
add_executable(agent_heater agent_heater.cpp)
target_link_libraries(agent_temp ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)
target_link_libraries(agent_heater ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)


# EPS Agents
add_executable(agent_switch agent_switch.cpp)
target_link_libraries(agent_switch ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)

# ADCS Agents
add_executable(agent_sun agent_sun.cpp)
target_link_libraries(agent_sun ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)

# PyCubed Agent
add_executable(agent_pycubed agent_pycubed.cpp)
target_link_libraries(agent_pycubed ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)

# Payload (Raspberry Pi) Agent
add_executable(agent_raspi agent_raspi.cpp)
target_link_libraries(agent_raspi ${COSMOS_LIBS} ${CUBESAT_LIBS} SimpleAgent)
