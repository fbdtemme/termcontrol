cmake_minimum_required(VERSION 3.15)
project(termcontrol
        LANGUAGES CXX
        VERSION 0.2.0)


add_library(termcontrol INTERFACE)
add_library(termcontrol::termcontrol ALIAS termcontrol)

target_compile_features(termcontrol INTERFACE cxx_std_20)

include(CTest)
include(external/external.cmake)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

target_link_libraries(termcontrol
    INTERFACE
        fmt::fmt
        ctre::ctre
        gsl::gsl-lite-v1
        utf8cpp)

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()


set(termcontrol_target                  termcontrol)
set(termcontrol_cmake_install_dir       ${CMAKE_INSTALL_LIBDIR}/cmake/termcontrol)
set(termcontrol_version_config          ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
set(termcontrol_project_config          ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
set(termcontrol_project_config_template ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in)
set(termcontrol_targets_export_name     ${PROJECT_NAME}-targets)
set(termcontrol_targets_file            ${termcontrol_targets_export_name}.cmake)
set(termcontrol_include_build_dir       ${PROJECT_SOURCE_DIR}/include/)
set(termcontrol_namespace               ${PROJECT_NAME})
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        ${termcontrol_version_config}
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
        ${termcontrol_project_config_template}
        ${termcontrol_project_config}
        INSTALL_DESTINATION ${termcontrol_cmake_install_dir})


# install headers
install(DIRECTORY ${termcontrol_include_build_dir}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
# install project config file and config version file
install(FILES ${termcontrol_project_config}
        ${termcontrol_version_config}
        DESTINATION ${termcontrol_cmake_install_dir}
        )


# install targets to an export set
install(TARGETS ${termcontrol_target}
        EXPORT ${termcontrol_targets_export_name}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the export set to enable importing targets from the build tree
export(EXPORT ${termcontrol_targets_export_name}
        FILE ${termcontrol_targets_file}
        NAMESPACE ${termcontrol_namespace}::)

# Install the export set to enable importing targets from the install tree
install(EXPORT ${termcontrol_targets_export_name}
        FILE ${termcontrol_targets_file}
        NAMESPACE ${termcontrol_namespace}::
        DESTINATION ${termcontrol_cmake_install_dir})

