cmake_minimum_required(VERSION 3.10)
project(shades_and_origins)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()


file(GLOB_RECURSE ALL_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

add_executable(tests ${ALL_TEST_SOURCES})

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_executable(main
    main/main.cpp
)

add_custom_target(test_all
    COMMAND ./main
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure 
    DEPENDS main tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)