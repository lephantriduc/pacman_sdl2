cmake_minimum_required(VERSION 3.28)
project(pacman)

file(GLOB Sources CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(pacman ${Sources})

# 1. Look for a SDL2 package
# 2. look for the SDL2 component and
# 3. fail if none can be found
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
find_package(SDL2_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL2_mixer)

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library,
# SDL2::SDL2-static is the static SDL library.
target_link_libraries(pacman PRIVATE SDL2::SDL2)
target_link_libraries(pacman PRIVATE SDL2_image::SDL2_image)
target_link_libraries(pacman PRIVATE SDL2_mixer::SDL2_mixer)

# Add rpath to the SDL framework path for every build
# Edit your path to your SDL framework folder on your computer here
set(LIBRARY_PATH "/Library/Frameworks")
add_custom_command(TARGET pacman
    POST_BUILD COMMAND
    ${CMAKE_INSTALL_NAME_TOOL} -add_rpath "${LIBRARY_PATH}" $<TARGET_FILE:pacman>
)

# Copy "assets" folder next to executable file for every build
add_custom_command(TARGET pacman
    POST_BUILD COMMAND
    cp -r ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}
)

set(CMAKE_CXX_STANDARD 17)
