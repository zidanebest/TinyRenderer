cmake_minimum_required(VERSION 3.15)

project(TinyRenderer)

set(Application_Name "TinyRenderer")

set(DCMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_CXX_STANDARD 17)

set(RendererPath ${PROJECT_SOURCE_DIR}/source/renderer)
set(LibraryPath ${PROJECT_SOURCE_DIR}/source/third_party)

# add_subdirectory(${LibraryPath}/UGM)

file(GLOB_RECURSE _sources 
  ${RendererPath}/*.cpp
  ${RendererPath}/*.h
  ${RendererPath}/*.hpp
  # ${LibraryPath}/*.cpp
  # ${LibraryPath}/*.h
  # ${LibraryPath}/*.hpp
  # ${LibraryPath}/*.inl
  )

add_executable(${Application_Name} "")
target_sources(${Application_Name} PRIVATE
  ${_sources}
)
target_link_libraries(${Application_Name} PRIVATE

)


target_include_directories(${Application_Name}  PUBLIC
  ${RendererPath}
  
)

target_compile_definitions(${Application_Name} PRIVATE

)

