cmake_minimum_required(VERSION 3.5)

project(dspeed VERSION 0.1 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )


set(PROJECT_SOURCES main.cpp temporary_file.hpp temporary_file.cpp Test.hpp Test.cpp)


add_executable(dspeed ${PROJECT_SOURCES} )



target_link_libraries( dspeed LINK_PUBLIC ${Boost_LIBRARIES} )
