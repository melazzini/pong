enable_testing()

find_package(GTest REQUIRED)

add_executable(cpptest TestPaddle.cpp)

target_link_libraries(cpptest GTest::gtest GTest::gtest_main GTest::gmock pthread)

add_test(AllTests cpptest)