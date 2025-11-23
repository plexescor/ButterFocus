cmake_minimum_required(VERSION 3.20)
project(ViraChrono)

# ------------------------------------------
# Output directory for C++ executable
# ------------------------------------------
set(CPP_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/compiled")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CPP_OUTPUT_DIR}")

# ------------------------------------------
# C++ sources
# ------------------------------------------
file(GLOB_RECURSE SOURCES "Scripts/*.cpp")

# ------------------------------------------
# ImGui sources
# ------------------------------------------
set(IMGUI_SRC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_sdl2.cpp
    external/imgui/backends/imgui_impl_sdlrenderer2.cpp
)

# Combine all sources
list(APPEND SOURCES ${IMGUI_SRC})

# Create executable
add_executable(ViraChrono ${SOURCES})

# ------------------------------------------
# Include directories
# ------------------------------------------
target_include_directories(ViraChrono PRIVATE
    external/SDL2/include
    external/imgui
    external/imgui/backends
)

# ------------------------------------------
# SDL2 library path and linking
# ------------------------------------------
set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/external/SDL2/lib/x64")
target_link_libraries(ViraChrono
    "${SDL2_LIB_DIR}/SDL2.lib"
    "${SDL2_LIB_DIR}/SDL2main.lib"
)

# ------------------------------------------
# Copy SDL2.dll to output folder
# ------------------------------------------
# add_custom_command(TARGET ViraChrono POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     "external/SDL2/x64/SDL2.dll"
#     $<TARGET_FILE_DIR:ViraChrono>
# )

# ------------------------------------------
# C# helper paths (your original)
# ------------------------------------------
set(CS_HELPER_SRC "${CMAKE_SOURCE_DIR}/Scripts/C-Sharp/ActiveWindowHelper.cs")
set(CS_HELPER_EXE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/ActiveWindowHelper.exe")
set(CS_HELPER_TMP "${CMAKE_BINARY_DIR}/ActiveWindowHelper.cs") # temporary copy

add_custom_command(
    OUTPUT ${CS_HELPER_EXE}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CS_HELPER_SRC}" "${CS_HELPER_TMP}"
    COMMAND csc.exe /nologo /target:exe /out:${CS_HELPER_EXE} "${CS_HELPER_TMP}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CS_HELPER_TMP}"
    DEPENDS "${CS_HELPER_SRC}"
    COMMENT "Compiling C# ActiveWindowHelper.exe"
)

add_custom_target(BuildCSharpHelper ALL
    DEPENDS ${CS_HELPER_EXE}
)

add_dependencies(ViraChrono BuildCSharpHelper)
