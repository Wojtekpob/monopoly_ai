# Set the executable name
add_executable(monopoly_ai
    monopoly_ai.cc
    game_elements/Board.cc
    game_elements/Board.h
    game_elements/BoardSquare.cc
    game_elements/BoardSquare.h
    game_elements/Drawable.h
    game_elements/Dice.h
    game_elements/Dice.cc
    game_elements/Player.h
    game_elements/Player.cc
)

# Include directories for header files
target_include_directories(monopoly_ai PRIVATE ${CMAKE_SOURCE_DIR}/monopoly_ai/game_elements)

# Link SFML libraries
target_link_libraries(monopoly_ai sfml-graphics sfml-window sfml-system)

# Set compile definitions
target_compile_definitions(monopoly_ai PRIVATE "BASE_PATH=\"${PROJECT_SOURCE_DIR}/\"")
