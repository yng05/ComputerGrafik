# Install script for directory: /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/revision")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/revision")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/revision")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "tools")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/revision")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "tools")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/AUTHORS")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/LICENSE")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/codegeneration/gl.revision")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/glbinding" TYPE FILE FILES "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/glbinding-config.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glbinding-1.1.0/source/cmake_install.cmake")
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glbinding-1.1.0/docs/cmake_install.cmake")
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glbinding-1.1.0/packages/cmake_install.cmake")
  INCLUDE("/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/external/glbinding-1.1.0/codegeneration/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

