add_executable(GameTests GameTests.cpp)
add_test(NAME GameTests COMMAND GameTests)

target_include_directories(GameTests PRIVATE ${CMAKE_SOURCE_DIR}/monopoly_ai/game_elements)

target_link_libraries(GameTests sfml-graphics sfml-window sfml-system)
