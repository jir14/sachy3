# CMakeList.txt: Projekt CMake pro sachy3, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (sachy3 "sachy3.cpp" "sachy3.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sachy3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
