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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/support/libCosmosSupport.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/support" TYPE FILE FILES
    "/home/vagrant/cosmos/source/core/libraries/support/command_queue.h"
    "/home/vagrant/cosmos/source/core/libraries/support/configCosmos.h"
    "/home/vagrant/cosmos/source/core/libraries/support/convertdef.h"
    "/home/vagrant/cosmos/source/core/libraries/support/convertlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/cosmos-defs.h"
    "/home/vagrant/cosmos/source/core/libraries/support/cosmos-errno.h"
    "/home/vagrant/cosmos/source/core/libraries/support/datadef.h"
    "/home/vagrant/cosmos/source/core/libraries/support/datalib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/demlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/elapsedtime.h"
    "/home/vagrant/cosmos/source/core/libraries/support/ephemlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/estimation_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/event.h"
    "/home/vagrant/cosmos/source/core/libraries/support/geomag.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jpleph.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonclass.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsondef.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonlib.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonobject.h"
    "/home/vagrant/cosmos/source/core/libraries/support/jsonvalue.h"
    "/home/vagrant/cosmos/source/core/libraries/support/nrlmsise-00.h"
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

