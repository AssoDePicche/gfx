add_executable(Tests
  main.cpp
)

target_link_libraries(Tests PRIVATE core GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(Tests)
