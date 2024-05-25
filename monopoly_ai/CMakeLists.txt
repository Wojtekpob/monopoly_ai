# Set the executable name
add_executable(monopoly_ai
    monopoly_ai.cc
    game_elements/src/Board.cc
    game_elements/src/BoardSquare.cc
    game_elements/src/Dice.cc
    game_elements/src/Player.cc
    game_elements/src/Action.cc)

# Include directories for header files
target_include_directories(monopoly_ai PRIVATE ${CMAKE_SOURCE_DIR}/monopoly_ai/game_elements/include)

# Link SFML libraries
target_link_libraries(monopoly_ai sfml-graphics sfml-window sfml-system)

# Set compile definitions
target_compile_definitions(monopoly_ai PRIVATE "BASE_PATH=\"${PROJECT_SOURCE_DIR}/\"")
