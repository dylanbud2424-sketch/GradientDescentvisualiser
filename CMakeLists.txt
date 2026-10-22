cmake_minimum_required(VERSION 3.16)
project(MyImGuiApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Automatically fetch and download GLFW from GitHub
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4  # Or your preferred stable release version
    GIT_SHALLOW    ON
)
# Disable building GLFW documentation and examples to speed up compile time
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

# 2. Configure executable target
add_executable(my_project src/main.cpp)

# 3. Add path lookups for Dear ImGui source files
target_include_directories(my_project PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends
)

# 4. Compile Dear ImGui + backends natively along with your main.cpp
target_sources(my_project PRIVATE
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_demo.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/backends/imgui_impl_glfw.cpp
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp
)

# 5. Link libraries ('glfw' target automatically handles the required header include locations)
target_link_libraries(my_project PRIVATE 
    glfw
    OpenGL::GL
)
