# CMakeList.txt : CMake project for SDL_cmake_template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

project(SDL_cmake_template)
set(CMAKE_CXX_STANDARD 11)

# TODO: Add tests and install targets if needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(BIN_DIR ${SDL_cmake_template_SOURCE_DIR}/bin)

# This path is used by FindSDL2 module. 
# It will find include and lib folders under this directory.
# This is because find command doesn't include any path for Windows.
# So it can't find anything using default paths.
# SDL2_PATH is already expected in module file. I'm using the same variable.
IF (WIN32)
  set(SDL2_PATH "c:/Users/arbal/Downloads/SDL2-devel-2.30.9-VC/SDL2-2.30.9")
ENDIF()

find_package(SDL2 REQUIRED)

set(SOURCE_FILES "src/main.cpp")


include_directories(${SDL2_INCLUDE_DIR})

add_executable(SDL_cmake_template 
${SOURCE_FILES}
)

target_include_directories(SDL_cmake_template
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
PUBLIC ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(SDL_cmake_template 
	${SDL2_LIBRARIES}
)

install(TARGETS SDL_cmake_template RUNTIME DESTINATION ${BIN_DIR}/)
set_target_properties(SDL_cmake_template PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/debug/
	RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/release/ )

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	add_custom_command( TARGET SDL_cmake_template POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x64/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET SDL_cmake_template POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x64/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )
elseif()
	add_custom_command( TARGET SDL_cmake_template POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different 
		${SDL2_PATH}/lib/x86/SDL2.dll 
		${BIN_DIR}/debug/SDL2.dll  )
	add_custom_command( TARGET SDL_cmake_template POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${SDL2_PATH}/lib/x86/SDL2.dll
		${BIN_DIR}/debug/SDL2.dll  )
endif()