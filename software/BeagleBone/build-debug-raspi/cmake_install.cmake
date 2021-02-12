# Install script for directory: /home/vagrant/artemis/software/BeagleBone/beaglebone

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
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/agent/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/support/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/math/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/physics/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/png/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/jpeg/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/zlib/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/general/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/disk/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/cpu/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/i2c/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/serial/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/device/ccsds/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/libraries/SimpleAgent/cmake_install.cmake")
  include("/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
