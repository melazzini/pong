enable_testing()

find_package(GTest REQUIRED)

find_package(GLM REQUIRED)

find_package(SDL2 REQUIRED)

add_executable(cpptest TestMovable.cpp TestRectangularGeometry.cpp TestBox.cpp TestInteractionManager.cpp 
    ../src/Renderer.cpp ../src/Window.cpp ../src/InteractionManager.cpp ../src/EventManager.cpp TestRenderer.cpp TestWindow.cpp TestEventManager.cpp)

target_include_directories(cpptest PRIVATE ${GLM_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS})

target_link_libraries(cpptest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock pthread ${SDL2_LIBRARIES})

add_test(AllTests cpptest)
