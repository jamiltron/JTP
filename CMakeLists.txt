cmake_minimum_required (VERSION 3.16.3)

project(jtp)
set(NAME "jtp")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_directories(${CMAKE_SOURCE_DIR}/lib)

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
file(GLOB SOURCE "src/*.c")
add_executable(jtp ${SOURCE})
set_property(TARGET jtp PROPERTY C_STANDARD 11)


if(WIN32)
  set(LIBS glfw3 opengl32)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -W -Wall -Wextra")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  set(LIBS ${GLFW3_LIBRARY} X11 GL dl pthread Xrandr Xi m)
  set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE} -ldl")
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
  set(LIBS ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS)
endif(WIN32)

add_library(GLAD "src/glad.c")
set(LIBS ${LIBS} GLAD)
target_link_libraries(jtp ${LIBS})

include_directories(
  ${CMAKE_SOURCE_DIR}/inc
  ${CMAKE_SOURCE_DIR}/dep)

# TODO: map actual directories over, I also probably need to do some filetype dependent handling
file(GLOB RESOURCES
  "res/shaders/*.vs"
  "res/shaders/*.fs"
  "res/shaders/*.gs"
  "res/config/*.nini")
foreach(RESOURCE ${RESOURCES})
  if(WIN32)
      add_custom_command(TARGET ${NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:${NAME}>)
  elseif(UNIX AND NOT APPLE)
      file(COPY ${RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  elseif(APPLE)
      get_filename_component(RESOURCENAME ${RESOURCE} NAME)
      makeLink(${RESOURCE} ${CMAKE_CURRENT_BINARY_DIR} ${NAME})
  endif(WIN32)
endforeach(RESOURCE)
