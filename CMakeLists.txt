cmake_minimum_required(VERSION 3.0)
project(Raymarch)

set(VulkanSDKPath C:/VulkanSDK/1.3.261.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE DEF_FILES src/cxx/*.hpp)
file(GLOB_RECURSE SRC_FILES src/cxx/*.cpp)

file(COPY src/glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Raymarch ${DEF_FILES} ${SRC_FILES})

add_subdirectory(modules/VulkanContext)

target_link_libraries(Raymarch PUBLIC VulkanContext)
