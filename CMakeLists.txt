cmake_minimum_required(VERSION "4.3")
project(Aurora LANGUAGES CXX C VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

option(BUILD_CLI "Build  Aurora Console Runtime Interface" ON)

add_subdirectory(vendor/luau)

add_library(aurora STATIC
    
)

target_include_directories(aurora PUBLIC
        src
        ${CMAKE_SOURCE_DIR}/vendor/luau/Ast/include
        ${CMAKE_SOURCE_DIR}/vendor/luau/Bytecode/include
        ${CMAKE_SOURCE_DIR}/vendor/luau/Common/include
        ${CMAKE_SOURCE_DIR}/vendor/luau/Compiler/include
        ${CMAKE_SOURCE_DIR}/vendor/luau/VM/include
)


target_link_libraries(aurora PRIVATE
    luau
)

if(BUILD_CLI)
    add_executable(aurora_cli
        
    )

    target_include_directories(aurora_cli PRIVATE
        src
    )

    target_link_libraries(aurora_cli PRIVATE
        aurora
    )
endif()