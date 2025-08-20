cmake_minimum_required(VERSION 3.15)
project(mapper)

find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3-shared)

add_executable(mapper WIN32 mapper.c)
target_link_libraries(mapper PRIVATE SDL3::SDL3)

# On Windows, copy SDL3.dll to the build directory
if(WIN32)
    add_custom_command(
        TARGET mapper POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:mapper>
        VERBATIM
    )
endif()
