cmake_minimum_required(VERSION 3.8)

if (NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

if (WIN32)
    find_package(BOOST COMPONENTS unit_test_framework REQUIRED)
else()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

if (NOT Boost_FOUND)
    message("___BOOST NOT FOUNT___")
endif()

link_directories(${Boost_LIBRARY_DIRS})

SET(FILES ${PROJECT_SOURCE_DIR}/Bulk.h)

add_executable(${PROJECT_NAME} "main.cpp" ${FILES})
add_executable(tests tests.cpp)


set_target_properties(bulk PROPERTIES
        CXX_STANDART 17
        CXX_STANDART_REQUIRED ON
if (NOT WIN32)
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
else()
)

set_target_properties(tests PROPERTIES
        COMPILE_DEFINIITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries (tests ${Boost_LIBRARIES})
target_link_libraries (bulk)

#---------------------------

install (TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT nikbar93@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
