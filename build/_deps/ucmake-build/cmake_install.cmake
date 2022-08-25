# Install script for directory: C:/MainDic/TinyRenderer/build/_deps/ucmake-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Ubpa")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/EMPTY/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/01_CPM/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/02_cpp20/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/03_lib/gen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/03_lib/use/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/gen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/use_c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/use_c_dynamicload/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/use_c_staticlload/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/use_dynamicload/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/04_dll/use_staticload/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/classic/gen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/classic/use_c_dynamic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/classic/use_c_static/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/classic/use_static/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/virtual/gen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/virtual/use_c_dynamic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/virtual/use_c_static/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/virtual/use_dynamic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/05_dll_class/virtual/use_static/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/06_static_shared/gen/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/06_static_shared/use_shared/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/MainDic/TinyRenderer/build/_deps/ucmake-build/src/test/06_static_shared/use_static/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/UCMake_0_6_4/cmake" TYPE FILE FILES
    "C:/MainDic/TinyRenderer/build/_deps/ucmake-build/UCMakeConfig.cmake"
    "C:/MainDic/TinyRenderer/build/_deps/ucmake-build/UCMakeConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/UCMake_0_6_4" TYPE DIRECTORY FILES "C:/MainDic/TinyRenderer/build/_deps/ucmake-src/cmake")
endif()

