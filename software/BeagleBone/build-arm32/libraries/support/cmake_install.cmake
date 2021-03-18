# Install script for directory: /home/vagrant/cosmos/source/core/libraries/support

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosSupport.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosSlip.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosTransfer.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosPrint.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosError.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosConvert.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosEphem.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosNetwork.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosNamespace.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosString.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosJson.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosCad.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosTime.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libCosmosData.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/libEnvi.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/support" TYPE FILE FILES
    "/home/vagrant/cosmos/source/core/libraries/support/configCosmos.h"
    "/home/vagrant/cosmos/source/core/libraries/support/convertdef.h"
    "/home/vagrant/cosmos/source/core/libraries/support/convertlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/cosmos-defs.h"
    "/home/vagrant/cosmos/source/core/libraries/support/cosmos-errno.h"
    "/home/vagrant/cosmos/source/core/libraries/support/datalib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/demlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/elapsedtime.h"
    "/home/vagrant/cosmos/source/core/libraries/support/envi.h"
    "/home/vagrant/cosmos/source/core/libraries/support/ephemlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/estimation_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/geomag.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jpleph.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonclass.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsondef.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonobject.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonvalue.h"
    "/home/vagrant/cosmos/source/core/libraries/support/objlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/print_utils.h"
    "/home/vagrant/cosmos/source/core/libraries/support/sliplib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/socketlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/stringlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/timelib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/timeutils.h"
    "/home/vagrant/cosmos/source/core/libraries/support/transferlib.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/support" TYPE FILE FILES "/home/vagrant/cosmos/source/core/libraries/support/json11.hpp")
endif()

