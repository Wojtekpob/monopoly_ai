# Wymagania
- CMake - minimum 3.8
- Lista potrzebnych paczek dla Ubuntu 22.04 - mogą być one          zainstalowane przy użyciu skryptu ubuntu_install_dependencies.sh:
    - libx11-dev
    - libgl1-mesa-dev
    - libudev-dev
    - libopenal-dev
    - libvorbis-dev
    - libflac-dev
    - libxrandr-dev
    - libxcursor-dev
    - libfreetype6-dev



# Zbudowanie projektu i uruchomienie
- `./ubuntu_install_dependencies.sh` - instalacja bibliotek dla Ubuntu 22.04
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./tests/GameTests` - uruchomienie testów
- `./monopoly_ai/monopoly_ai` - uruchomienie aplikacji


# Dokumentacja doxygen:
- uruchomienie pliku `monopoly_ai/docs/html/index.html` w przegladarce
