aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_curdir)
find_package(GTest REQUIRED)
find_package(GLM REQUIRED)
add_executable(facinerosotest "")
target_sources(facinerosotest PRIVATE ${sources_in_curdir})
target_include_directories(facinerosotest PRIVATE ${GLM_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/facineroso/include)
target_link_libraries(facinerosotest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock pthread facineroso)
