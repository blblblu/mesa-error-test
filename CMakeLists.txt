cmake_minimum_required(VERSION 3.8)
project(framebuffer_mesa_test)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

function(set_policy POL VAL)

    if(POLICY ${POL})
        cmake_policy(SET ${POL} ${VAL})
    endif()

endfunction(set_policy)
set_policy(CMP0028 NEW) # ENABLE CMP0028: Double colon in target name means ALIAS or IMPORTED target.

find_package(GLFW REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLFW_INCLUDE_NONE")

find_package(globjects REQUIRED)
find_package(glbinding REQUIRED)

add_executable(framebuffer_mesa_test main.cpp)

target_include_directories(framebuffer_mesa_test
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/source/include

    ${GLFW_INCLUDE_DIR}
)

target_link_libraries(framebuffer_mesa_test
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${DEFAULT_LINKER_OPTIONS}

    ${GLFW_LIBRARIES}
    globjects::globjects
)
