cmake_minimum_required(VERSION 3.30)

# The toolchain file setup should ideally be in a CMakePresets.json file,
# but we'll keep it here for simplicity
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(Chess_2D VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add dependencies
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# No C++20 modules
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) 

# Chess executable
add_executable(Chess)

# Chess sources and headers
file(GLOB_RECURSE Chess_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

target_sources(Chess PRIVATE ${Chess_SOURCES})

# Chess include dirs
target_include_directories(Chess PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# Preprocessor defines
target_compile_definitions(Chess PRIVATE
    MY_TEST_DEFINE
)

# Automatically links to these libs
target_link_libraries(Chess PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    spdlog::spdlog
)

# Add directories with any random loose .dlls or .libs here
target_link_directories(Chess PRIVATE
  
)

add_custom_command(
    TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:Chess>/assets
)

# Set configuration properties for Playground
if(MSVC)
    target_compile_options(Chess PRIVATE
        /W3
        /MP # multithreaded build
        /WX # warnings as errors
        /ZI # program database for edit and continue
    )
else()
    target_compile_options(Chess PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()

# Set Chess as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Chess)

# Filters
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${Chess_SOURCES})

# Enable solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)