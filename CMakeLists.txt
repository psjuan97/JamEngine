cmake_minimum_required(VERSION 2.8)

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "JamEngine" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=gnu++11 ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

## Set our project name
project(${PROJECT_NAME})

include_directories("src")

## Use all the *.cpp files we found under this folder for the project
FILE(GLOB_RECURSE SRCS "src/*.cpp")

## Define the executable
add_executable(${PROJECT_NAME} ${SRCS})

# Detect and add SDL, Box2D and more
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Box2D REQUIRED)

find_package(tinyxml2 REQUIRED )
find_package(SDL2_mixer REQUIRED)

if(PSP)
  message(STATUS "PSP COMPILATION \n" )
  string(STRIP ${PSP_LIBRARIES} PSP_LIBRARIES)
  target_link_libraries(${PROJECT_NAME} ${PSP_LIBRARIES})
  
endif()

if(TinyXML2_FOUND)
  target_link_libraries(${PROJECT_NAME} ${TinyXML2_LIBRARIES})
endif()

if(BOX2D_FOUND)
  target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARY})
endif()

if(SDL2_FOUND)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
endif()

if(SDL2_IMAGE_FOUND)
  target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
endif()

if(SDL2_TTF_FOUND)
  target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
endif()

if(SDLMIXER_FOUND)
  target_link_libraries(${PROJECT_NAME} ${SDLMIXER_LIBRARY})
endif()
