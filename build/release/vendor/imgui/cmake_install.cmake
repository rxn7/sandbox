# Install script for directory: /home/rxn/dev/sandbox/vendor/imgui

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/rxn/dev/sandbox/build/release/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/rxn/dev/sandbox/build/release/vendor/imgui/libimgui.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/imgui" TYPE FILE FILES
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imgui.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imconfig.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imgui_internal.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imstb_rectpack.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imstb_textedit.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/imstb_truetype.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/backends/imgui_impl_glfw.h"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/backends/imgui_impl_opengl3.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/misc/fonts" TYPE FILE FILES
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/Cousine-Regular.ttf"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/DroidSans.ttf"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/Karla-Regular.ttf"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/ProggyClean.ttf"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/ProggyTiny.ttf"
    "/home/rxn/dev/sandbox/vendor/imgui/imgui/misc/fonts/Roboto-Medium.ttf"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui/ImGuiTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui/ImGuiTargets.cmake"
         "/home/rxn/dev/sandbox/build/release/vendor/imgui/CMakeFiles/Export/1c9f1db1a0c9398944d65050189647a4/ImGuiTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui/ImGuiTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui/ImGuiTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui" TYPE FILE FILES "/home/rxn/dev/sandbox/build/release/vendor/imgui/CMakeFiles/Export/1c9f1db1a0c9398944d65050189647a4/ImGuiTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui" TYPE FILE FILES "/home/rxn/dev/sandbox/build/release/vendor/imgui/CMakeFiles/Export/1c9f1db1a0c9398944d65050189647a4/ImGuiTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/imgui" TYPE FILE FILES
    "/home/rxn/dev/sandbox/build/release/vendor/imgui/generated/ImGuiConfigVersion.cmake"
    "/home/rxn/dev/sandbox/build/release/vendor/imgui/generated/ImGuiConfig.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/rxn/dev/sandbox/build/release/vendor/imgui/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
