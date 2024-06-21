if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/molcpp-${PROJECT_VERSION}"
      CACHE STRING ""
  )
  set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package molcpp)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT molcpp_Development
)

install(
    TARGETS molcpp_molcpp
    EXPORT molcppTargets
    RUNTIME #
    COMPONENT molcpp_Runtime
    LIBRARY #
    COMPONENT molcpp_Runtime
    NAMELINK_COMPONENT molcpp_Development
    ARCHIVE #
    COMPONENT molcpp_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    molcpp_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE molcpp_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(molcpp_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${molcpp_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT molcpp_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${molcpp_INSTALL_CMAKEDIR}"
    COMPONENT molcpp_Development
)

install(
    EXPORT molcppTargets
    NAMESPACE molcpp::
    DESTINATION "${molcpp_INSTALL_CMAKEDIR}"
    COMPONENT molcpp_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
