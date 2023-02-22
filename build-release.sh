CFLAGS="-Ofast -g1" CXXFLAGS="-Ofast -g1" meson setup --native-file linux-x64-clang.ini buildrelease
meson compile -C ./buildrelease