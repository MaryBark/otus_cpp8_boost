#if(WITH_BOOST_TEST)
#    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
##    add_executable(test_version test_version.cpp)

#    set_target_properties(test_version PROPERTIES
#        CXX_STANDARD 14
#        CXX_STANDARD_REQUIRED ON
#    )

#    set_target_properties(test_version PROPERTIES
#        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#    )

#    target_link_libraries(test_version
#        ${Boost_LIBRARIES}
#        otus8_cpp_boost
#    )
#endif()


cmake_minimum_required(VERSION 3.2)

project(otus8_cpp_boost VERSION 0.0 ${PATCH_VERSION})


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

#find_package(Boost 1.70.0 COMPONENTS thread bind asio shared_ptr enable_shared_from_this scoped_ptr chrono noncopyable)

#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})
#    add_executable(${PROJECT_NAME} server.cpp Precompiled.h)
#    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

#find_package(Boost 1.40.0 COMPONENTS program_options filesystem regex REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

add_executable(otus8_cpp_boost main.cpp
    Duplikate.h Duplikate.cpp
        Hash.h Hash.cpp HashFile.h HashFile.cpp)

set_target_properties(otus8_cpp_boost PROPERTIES
        CXX_STANDART 14
        CXX_STANDART_REQUIRED ON
        COMPILE_OPTION -Wpedantic -Wall -Wextra
        )

#    file(GLOB SOURCES "${SRC_DIR}/*.cpp")
#    file(GLOB HEADERS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")

#    set(Boost_USE_STATIC_LIBS OFF)
#    set(Boost_USE_MULTITHREADED ON)
#    set(Boost_USE_STATIC_RUNTIME OFF)
#    set(BOOST_INCLUDEDIR /usr/include/boost)
#    set(BOOST_LIBRARYDIR /usr/lib)
#    find_package(Boost 1.70.0 COMPONENTS program_options filesystem regex REQUIRED)
#    include_directories(${Boost_INCLUDE_DIRS})

#    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
#    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
#    set_target_properties(${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
#    target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

install(TARGETS otus8_cpp_boost RUNTIME DESTINATION bin)

# собираем божественный DEB-пакет
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# это,чтобы на почту приходило уведомление, собралось или нет, если проект большой, то полезно)))
set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)

# тесты сделаю потом ко всем заданиям, когда до них доползу)))
# про тетсты помню, но пока не доползла(((
include(CPack)
