cmake_minimum_required(VERSION 3.23)

project(nlohmann-reflectcpp LANGUAGES CXX)

if(NOT TARGET nlohmann_json OR NOT TARGET reflectcpp)
	message(SEND_ERROR "Could NOT find nlohmann/json or reflect-cpp targets!")
endif()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${sources})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json reflectcpp)
