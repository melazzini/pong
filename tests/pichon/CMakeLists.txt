aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_curdir)
find_package(GTest REQUIRED)
find_package(GLM REQUIRED)
add_executable(pichontest "")
target_sources(pichontest PRIVATE ${sources_in_curdir})
target_include_directories(pichontest PRIVATE ${GLM_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/facineroso/include ${CMAKE_SOURCE_DIR}/pichon/include)
target_link_libraries(pichontest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock pthread facineroso pichon)
