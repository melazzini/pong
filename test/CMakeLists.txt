enable_testing()

find_package(GTest REQUIRED)

find_package(GLM REQUIRED)

add_executable(cpptest TestPaddle.cpp)

target_include_directories(cpptest PRIVATE ${GLM_INCLUDE_DIR})

target_link_libraries(cpptest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock pthread)

add_test(AllTests cpptest)