cmake_minimum_required(VERSION 3.26.3 FATAL_ERROR)

set(PROJECT_NAME HomeworkM15)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} 
		src/main.cpp 
		src/sha1.cpp 
		src/sha1.h 
		src/chat.cpp 
		src/chat.h)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)