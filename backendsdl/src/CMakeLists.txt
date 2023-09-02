aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} sources_in_cur_dir)
find_package(SDL2 REQUIRED)
find_package(GLM REQUIRED)
add_library(backendsdl "")
target_sources(backendsdl PRIVATE ${sources_in_cur_dir})
target_include_directories(backendsdl PRIVATE ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/facineroso/include" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_link_libraries(backendsdl PRIVATE ${SDL2_LIBRARIES})

