# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-src"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-build"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/tmp"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/src/utemplate-populate-stamp"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/src"
  "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/src/utemplate-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/src/utemplate-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/MainDic/TinyRenderer/build/_deps/utemplate-subbuild/utemplate-populate-prefix/src/utemplate-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
