# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-src"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-build"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/tmp"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/src/ucmake-populate-stamp"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/src"
  "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/src/ucmake-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/src/ucmake-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/MainDic/TinyRenderer/build/_deps/ucmake-subbuild/ucmake-populate-prefix/src/ucmake-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
