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
add_executable(ViraChrono ${SOURCES})

# ------------------------------------------
# C# helper paths
# ------------------------------------------
set(CS_HELPER_SRC "${CMAKE_SOURCE_DIR}/Scripts/C-Sharp/ActiveWindowHelper.cs")
# Place C# exe in the same folder as C++ exe
set(CS_HELPER_EXE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/ActiveWindowHelper.exe")
set(CS_HELPER_TMP "${CMAKE_BINARY_DIR}/ActiveWindowHelper.cs") # temporary copy

# ------------------------------------------
# Build C# helper
# ------------------------------------------
add_custom_command(
    OUTPUT ${CS_HELPER_EXE}

    # Copy the .cs file to a temp location
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CS_HELPER_SRC}"
            "${CS_HELPER_TMP}"

    # Compile it using system's csc.exe
    COMMAND csc.exe /nologo /target:exe
            /out:${CS_HELPER_EXE}
            "${CS_HELPER_TMP}"

    # Delete temporary .cs
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CS_HELPER_TMP}"

    DEPENDS "${CS_HELPER_SRC}"
    COMMENT "Compiling C# ActiveWindowHelper.exe"
)

# ------------------------------------------
# Custom target for the helper
# ------------------------------------------
add_custom_target(BuildCSharpHelper ALL
    DEPENDS ${CS_HELPER_EXE}
)

# ------------------------------------------
# Make the main C++ project depend on the helper
# ------------------------------------------
add_dependencies(ViraChrono BuildCSharpHelper)
