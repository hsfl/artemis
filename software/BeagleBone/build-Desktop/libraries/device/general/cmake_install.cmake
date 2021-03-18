# Install script for directory: /home/vagrant/cosmos/source/core/libraries/device/general

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/general/libCosmosDeviceGeneral.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/device/general" TYPE FILE FILES
    "/home/vagrant/cosmos/source/core/libraries/device/general/acq_a35.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/ax25class.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/bbFctns.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/cssl_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/gige_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/gs232b_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/ic9100_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/kisslib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/kisstnc_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/kpc9612p_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/mixwtnc_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/pic_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/prkx2su_class.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/prkx2su_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/ts2000_lib.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/unixgpio.h"
    "/home/vagrant/cosmos/source/core/libraries/device/general/usrp_lib.h"
    )
endif()

