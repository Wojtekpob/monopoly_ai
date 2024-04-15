# CMakeList.txt: projekt CMake dla elementu monopoly_ai, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#






# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (monopoly_ai "monopoly_ai.cpp" "monopoly_ai.h")

target_link_libraries(monopoly_ai sfml-graphics sfml-window sfml-system)

#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-audio.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-graphics.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-network.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-system.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-window.lib)


#if (WIN32)
#    set(DLL_DIR "${CMAKE_SOURCE_DIR}/dlls")
#    file(GLOB DLL_FILES "${DLL_DIR}/*.dll")
#    foreach(DLL_FILE ${DLL_FILES})
#        # Pobierz nazwę pliku bez ścieżki
#        get_filename_component(DLL_NAME ${DLL_FILE} NAME_WE)
#       # Dodaj bibliotekę do projektu
#        add_library(${DLL_NAME} SHARED IMPORTED)
#        # Ustaw właściwy plik DLL jako importowany plik biblioteki
#        set_target_properties(${DLL_NAME} PROPERTIES IMPORTED_LOCATION "${DLL_FILE}")
#    endforeach()
#    target_link_libraries(monopoly_ai ${DLL_FILES})
#endif()


#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-main.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-audio-s.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-graphics-s.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-network-s.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-system-s.lib)
#target_link_libraries(monopoly_ai ${CMAKE_SOURCE_DIR}/library/sfml-window-s.lib)


#include_directories(${CMAKE_SOURCE_DIR}/include)

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET monopoly_ai PROPERTY CXX_STANDARD 20)
#endif()



# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
