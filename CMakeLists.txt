
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

option(BUILD_LUA_VENDORED "" OFF)

option(BUILD_SOL2_VENDORED "" ON)

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

if(BUILD_LUA_VENDORED)
    add_library(Lua)
    add_library(Lua::Lua ALIAS Lua)

    target_include_directories(Lua PUBLIC "${CMAKE_SOURCE_DIR}/vendor/lua")

    file(GLOB LUA_SOURCE
        "${CMAKE_SOURCE_DIR}/vendor/lua/*.c"   
    )

    target_sources(Lua PRIVATE ${LUA_SOURCE})

    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        target_compile_definitions(Lua PRIVATE LUA_USE_LINUX)

        target_link_libraries(Lua PRIVATE dl)
    endif()
else()
    find_package(Lua 5.4 EXACT REQUIRED)

    if(Lua_FOUND AND NOT TARGET Lua::Lua)
        add_library(Lua::Lua INTERFACE IMPORTED)

        set_target_properties(Lua::Lua PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${LUA_INCLUDE_DIR}"
            INTERFACE_LINK_LIBRARIES "${LUA_LIBRARIES}"
        )
    endif()
endif()

set(SOL2_BUILD_LUA OFF CACHE BOOL "")
set(SOL2_LUA_VERSION "5.4.8" CACHE STRING "")

if(BUILD_SOL2_VENDORED)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/sol2")
else()
    find_package(sol2 REQUIRED)
endif()

add_executable(${EXECUTABLE_NAME})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

file(GLOB_RECURSE EXECUTABLE_SOURCE CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/*.c"
    "${CMAKE_SOURCE_DIR}/source/*.cpp"
)

target_sources(${EXECUTABLE_NAME} PRIVATE ${EXECUTABLE_SOURCE})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image

    Lua::Lua

    sol2::sol2
)