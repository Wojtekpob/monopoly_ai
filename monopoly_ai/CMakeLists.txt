add_executable (
monopoly_ai
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

target_link_libraries(monopoly_ai sfml-graphics sfml-window sfml-system)
