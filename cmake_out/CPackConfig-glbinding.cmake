# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_ALL_INSTALL_TYPES "Full;Developer")
SET(CPACK_ARCHIVE_COMPONENT_INSTALL "ON")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMMAND "/usr/local/Cellar/cmake/2.8.12.2/bin/cpack")
SET(CPACK_COMPONENTS_ALL "dev;examples;runtime;tools")
SET(CPACK_COMPONENT_DEV_DEPENDS "runtime")
SET(CPACK_COMPONENT_DEV_DISPLAY_NAME "Headers and Libraries")
SET(CPACK_COMPONENT_DEV_INSTALL_TYPES "Developer;Full")
SET(CPACK_COMPONENT_EXAMPLES_DEPENDS "runtime")
SET(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
SET(CPACK_COMPONENT_EXAMPLES_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_RUN-TIME_INSTALL_TYPES "Developer;Full")
SET(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Run-Time (Binaries)")
SET(CPACK_COMPONENT_RUNTIME_REQUIRED "ON")
SET(CPACK_COMPONENT_TOOLS_DEPENDS "runtime")
SET(CPACK_COMPONENT_TOOLS_DISPLAY_NAME "Tools")
SET(CPACK_COMPONENT_TOOLS_INSTALL_TYPES "Full")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "daniel.limberger@hpi.de")
SET(CPACK_DEBIAN_PACKAGE_NAME "glbinding")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
SET(CPACK_DEBIAN_PACKAGE_VERSION "1.1.0")
SET(CPACK_DEB_COMPONENT_INSTALL "ON")
SET(CPACK_GENERATOR "ZIP;TGZ;DEB")
SET(CPACK_IGNORE_FILES "")
SET(CPACK_INSTALLED_DIRECTORIES "")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out;glbinding;ALL;/")
SET(CPACK_INSTALL_PREFIX "/usr/")
SET(CPACK_MODULE_PATH "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/packages/glbinding")
SET(CPACK_NSIS_DISPLAY_NAME "glbinding")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
SET(CPACK_NSIS_PACKAGE_NAME "glbinding")
SET(CPACK_OUTPUT_CONFIG_FILE "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CPackConfig-glbinding.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/README.md")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_PACKAGE_FILE_NAME "glbinding-1.1.0")
SET(CPACK_PACKAGE_ICON "")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "glbinding")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "glbinding")
SET(CPACK_PACKAGE_NAME "glbinding")
SET(CPACK_PACKAGE_RELOCATABLE "false")
SET(CPACK_PACKAGE_VENDOR "hpicgs group")
SET(CPACK_PACKAGE_VERSION "1.1.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PATH "/usr/local/Cellar/cmake/2.8.12.2/bin")
SET(CPACK_RESOURCE_FILE_LICENSE "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/LICENSE")
SET(CPACK_RESOURCE_FILE_README "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/README.md")
SET(CPACK_RESOURCE_FILE_WELCOME "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/glbinding-1.1.0/README.md")
SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
SET(CPACK_RPM_PACKAGE_DESCRIPTION "")
SET(CPACK_RPM_PACKAGE_GROUP "unknown")
SET(CPACK_RPM_PACKAGE_LICENSE "MIT")
SET(CPACK_RPM_PACKAGE_NAME "glbinding")
SET(CPACK_RPM_PACKAGE_PROVIDES "")
SET(CPACK_RPM_PACKAGE_RELEASE "1")
SET(CPACK_RPM_PACKAGE_RELOCATABLE "OFF")
SET(CPACK_RPM_PACKAGE_REQUIRES "")
SET(CPACK_RPM_PACKAGE_SUMMARY "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_RPM_PACKAGE_VENDOR "hpicgs group")
SET(CPACK_RPM_PACKAGE_VERSION "1.1.0")
SET(CPACK_SET_DESTDIR "ON")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TGZ;TBZ2;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Darwin")
SET(CPACK_TOPLEVEL_TAG "Darwin")
SET(CPACK_WIX_SIZEOF_VOID_P "8")
