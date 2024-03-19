# CMakeList.txt : CMake project for GL4, include source and define
# project specific logic here.
#

# Add source to this project's executable.

# TODO: Add tests and install targets if needed.
file(GLOB_RECURSE PROJECT_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

file (GLOB_RECURSE SHADERS
	${CMAKE_CURRENT_SOURCE_DIR}/*.vert
	${CMAKE_CURRENT_SOURCE_DIR}/*.frag
	${CMAKE_CURRENT_SOURCE_DIR}/*.shader
	${CMAKE_CURRENT_SOURCE_DIR}/*.glsl
)

file (GLOB_RECURSE TEXTURES
	${CMAKE_CURRENT_SOURCE_DIR}/*.png
	${CMAKE_CURRENT_SOURCE_DIR}/*.bmp
)

file(COPY ${TEXTURES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SHADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(${EXE_NAME})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${EXE_NAME} PROPERTY CXX_STANDARD 20)
endif()

if(MSVC)
  target_compile_options(${EXE_NAME} PRIVATE /W4 /WX)
elseif(LINUX)
  target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_sources(${EXE_NAME} PRIVATE ${PROJECT_FILES})

target_include_directories(${EXE_NAME}
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
PRIVATE ${CMAKE_SOURCE_DIR}/NGL/include
PRIVATE ${DEPENDENCIES_DIR}/include)

target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME})