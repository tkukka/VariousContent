md debug
g++ -DDEBUG -D_DEBUG -D_GLIBCXX_ASSERTIONS -UNDEBUG -U_NDEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O0 -g3 -ggdb -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -c -o debug\\ls_input.o ..\\ls_input.cpp
g++ -DDEBUG -D_DEBUG -D_GLIBCXX_ASSERTIONS -UNDEBUG -U_NDEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O0 -g3 -ggdb -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -c -o debug\\ls_presentation.o ..\\ls_presentation.cpp
g++ -DDEBUG -D_DEBUG -D_GLIBCXX_ASSERTIONS -UNDEBUG -U_NDEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O0 -g3 -ggdb -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -c -o debug\\ls_stack.o ..\\ls_stack.cpp
g++ -DDEBUG -D_DEBUG -D_GLIBCXX_ASSERTIONS -UNDEBUG -U_NDEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O0 -g3 -ggdb -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -c -o debug\\lukusana_main.o ..\\lukusana_main.cpp
g++ -Wl,--error-unresolved-symbols,--subsystem,console,--nxcompat -O0 -g3 -ggdb -fno-omit-frame-pointer -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -LC:\\msys64\\mingw64\\bin -o debug\\lukusana.exe debug\\ls_input.o debug\\ls_presentation.o debug\\ls_stack.o debug\\lukusana_main.o