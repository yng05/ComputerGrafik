# Install script for directory: /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/install")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/Debug/OpenGLFramework")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/OpenGLFramework" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/OpenGLFramework")
    EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
      -change "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/Debug/libglfw.3.dylib" "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/install/lib/libglfw.3.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/OpenGLFramework")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/OpenGLFramework")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/OpenGLFramework")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glbinding-1.1.0/cmake_install.cmake")
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glfw-3.1.1/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
