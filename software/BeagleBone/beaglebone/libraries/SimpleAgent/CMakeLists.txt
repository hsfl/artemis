


set(SIMPLEAGENT_SRC
    Device.cpp
    SimpleAgent.cpp
	RemoteAgent.cpp
	Telemetry.cpp)

set(SIMPLEAGENT_HEADERS
    AgentRequest.h
    Device.h
    DeviceDetail.h
    DeviceRequest.h
    Exceptions.h
    RemoteAgent.h
    RequestHelper.h
    SimpleAgent.h
    StringTools.h
	Telemetry.h
    TimeTools.h
    Types.h
    )


add_library(SimpleAgent STATIC ${SIMPLEAGENT_SRC})
target_link_libraries(SimpleAgent ${COSMOS_LIBS})



