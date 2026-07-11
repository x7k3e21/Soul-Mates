
cmake_minimum_required(VERSION 4.2)

include("${CMAKE_SOURCE_DIR}/cmake/ApplicationInfo.cmake")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

project(${APPLICATION_NAME}
    VERSION ${APPLICATION_VERSION}
    HOMEPAGE_URL ${APPLICATION_HOMEPAGE_URL}
)

option(BUILD_SDL3_VENDORED "" OFF)
option(BUILD_SDL3_IMAGE_VENDORED "" OFF)

if(BUILD_SDL3_VENDORED)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/SDL" EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 REQUIRED)
endif()

if(BUILD_SDL3_IMAGE_VENDORED)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/SDL_image" EXCLUDE_FROM_ALL)
else()
    find_package(SDL3_image REQUIRED)
endif()

add_executable(${EXECUTABLE_NAME})

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE EXECUTABLE_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.c"
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
)

target_sources(${EXECUTABLE_NAME} PRIVATE ${EXECUTABLE_SOURCE})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
)