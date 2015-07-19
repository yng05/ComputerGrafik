cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
# allows access to environment variables with the name 
project (OpenGLFramework)

# include cmake package
include(ExternalProject)

#set the build type if its not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# build options
option(DYNAMIC_LINKING "Link libraries at runtime" ON)

if(DYNAMIC_LINKING)
    # glbindings
    set(OPTION_BUILD_STATIC OFF CACHE BOOL "Build static libraries" FORCE)
    # glfw
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)
else()
    set(OPTION_BUILD_STATIC ON CACHE BOOL "Build static libraries" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
endif()

# include glm headers
include_directories(external/glm-0.9.6.3)

# add glbindings
set(glbinding_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/glbinding-1.1.0/")

ExternalProject_Add(project_glbinding
 #--Configure step-------------
  SOURCE_DIR "${glbinding_DIR}"            # Source dir to be used for build
  CMAKE_ARGS 
   -DGLBINDING_STATIC:BOOL=NOT ${DYNAMIC_LINKING}
  CMAKE_CACHE_ARGS 
   -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
   -DOPTION_BUILD_STATIC:BOOL=NOT ${DYNAMIC_LINKING}
   -DOPTION_BUILD_TESTS:BOOL=OFF
 #--Build step-----------------
  BINARY_DIR "${glbinding_DIR}/build" # Specify build dir location
  # [BUILD_COMMAND cmd...]      # Command to drive the native build
  INSTALL_COMMAND ""
  TEST_BEFORE_INSTALL 0     # Add test step executed before install step
  TEST_AFTER_INSTALL 0 
)
# load include dirs and libraries
find_package(glbinding REQUIRED)
include_directories(${GLBINDING_INCLUDE_DIR})

# configure glfw building
option(GLFW_BUILD_DOCS     OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS    OFF)
option(GLFW_INSTALL        OFF)
# add glfw build system
add_subdirectory(external/glfw-3.1.1)
# include glfw headers
include_directories(external/glfw-3.1.1/include)

# output executable
add_executable(GLFramework source/main.cpp)
add_dependencies(GLFramework project_glbinding)
target_link_libraries(GLFramework glfw ${GLFW_LIBRARIES} ${GLBINDING_LIBRARIES})

# set build type dependent flags
if(UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/D NDEBUG /MD /MP /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi")
endif()

# activate C++ 11
if(NOT MSVC)
    add_definitions(-std=c++11)
    # show warnings but ignore those caused by glm  
    add_definitions(-Wall -Wno-comment -Wno-strict-aliasing)
    # force linking  with c++11 lib
    if(APPLE)
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
        add_definitions(-stdlib=libc++)
    endif()
endif()

# remove external configuration vars from cmake gui
mark_as_advanced(OPTION_BUILD_TESTS GMOCK_LIBRARY GMOCK_LIBRARY_DEBUG GTEST_LIBRARY
  GTEST_LIBRARY_DEBUG OPTION_BUILD_EXAMPLES OPTION_BUILD_TESTS
  OPTION_BUILD_TOOLS OPTION_GL_BY_STRINGS OPTION_PACK_GENERATOR OPTION_PORTABLE_INSTALL
  OPTION_STRINGS_BY_GL PYTHON INSTALL_MSVC_REDIST_FILEPATH)
mark_as_advanced(GLFW_BUILD_DOCS GLFW_BUILD_TESTS GLFW_INSTALL GLFW_BUILD_EXAMPLES
 GLFW_DOCUMENT_INTERNALS GLFW_USE_EGL GLFW_USE_MIR GLFW_USE_WAYLAND GLFW_LIBRARIES
 LIB_SUFFIX)


#if user didnt set install dir, override it and write it to the cache -> Type and description necessary,
#overwrite variable, not just write it to cache
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install" CACHE STRING "Install path prefix, prepended onto install directories." FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# installation rules, copy over binaries to bin
install(TARGETS GLFramework DESTINATION bin)
