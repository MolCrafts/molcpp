if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/molcore-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package molcore)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT molcore_Development
)

install(
    TARGETS molcore_molcore
    EXPORT molcoreTargets
    RUNTIME #
    COMPONENT molcore_Runtime
    LIBRARY #
    COMPONENT molcore_Runtime
    NAMELINK_COMPONENT molcore_Development
    ARCHIVE #
    COMPONENT molcore_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    molcore_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE molcore_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(molcore_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${molcore_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT molcore_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${molcore_INSTALL_CMAKEDIR}"
    COMPONENT molcore_Development
)

install(
    EXPORT molcoreTargets
    NAMESPACE molcore::
    DESTINATION "${molcore_INSTALL_CMAKEDIR}"
    COMPONENT molcore_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
