aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_curdir)
add_library(facineroso "")
target_sources(facineroso PRIVATE ${sources_in_curdir})
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
target_include_directories(facineroso PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include" "${GLM_INCLUDE_DIR}")
