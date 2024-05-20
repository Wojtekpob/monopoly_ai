add_executable (monopoly_ai monopoly_ai.cc game_elements/Board.cc game_elements/Board.h game_elements/BoardSquare.cc game_elements/BoardSquare.h game_elements/Drawable.h)

target_link_libraries(monopoly_ai sfml-graphics sfml-window sfml-system)
