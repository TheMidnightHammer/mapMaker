# Copyright (c) 2026 MidnightHammer-code
# This source code is licensed under the MIT license
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.10)
project(voxel_Engine VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    # actual map code

    src/main.cpp
    src/ImGui.cpp
    src/system.cpp
    src/map.cpp

    # engine source
    Hammer/src/engine.cpp
    Hammer/src/utility.cpp
    Hammer/src/camera.cpp
    Hammer/src/rect.cpp
    Hammer/src/buffers.cpp
    Hammer/src/pipeline.cpp
    Hammer/src/ssbo.cpp
    Hammer/src/AsyncLogger.cpp
    Hammer/src/fontTexture.cpp
    Hammer/src/texture.cpp
    Hammer/src/fontHelper.cpp
    # Imgui source files
    Hammer/lib/imgui/imgui.cpp
    Hammer/lib/imgui/imgui_demo.cpp
    Hammer/lib/imgui/imgui_draw.cpp
    Hammer/lib/imgui/imgui_tables.cpp
    Hammer/lib/imgui/imgui_widgets.cpp
    Hammer/lib/imgui/imgui_impl_glfw.cpp
    Hammer/lib/imgui/imgui_impl_vulkan.cpp
)

find_package(Vulkan REQUIRED)
find_package(glm CONFIG REQUIRED) 
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_definitions(voxel_Engine PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_include_directories(voxel_Engine PRIVATE ../../lib/imgui)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)

if(WIN32 AND NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
    target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
    
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
endif()