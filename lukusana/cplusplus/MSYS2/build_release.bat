md release
g++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O2 -flto -fuse-linker-plugin -march=native -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -fstack-protector-strong -fstack-clash-protection -c -o release\\ls_input.o ..\\ls_input.cpp
g++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O2 -flto -fuse-linker-plugin -march=native -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -fstack-protector-strong -fstack-clash-protection -c -o release\\ls_presentation.o ..\\ls_presentation.cpp
g++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O2 -flto -fuse-linker-plugin -march=native -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -fstack-protector-strong -fstack-clash-protection -c -o release\\ls_stack.o ..\\ls_stack.cpp
g++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG -IC:\\msys64\\mingw64\\include\\c++ -std=c++17 -O2 -flto -fuse-linker-plugin -march=native -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -fstack-protector-strong -fstack-clash-protection -c -o release\\lukusana_main.o ..\\lukusana_main.cpp
g++ -Wl,--error-unresolved-symbols,-s,--subsystem,console,--nxcompat,--dynamicbase,--high-entropy-va,-e,mainCRTStartup -O2 -flto -fuse-linker-plugin -pedantic -Wall -Wextra -Wformat-security -Werror=format-security -fmessage-length=0 -fstack-protector-strong -fstack-clash-protection -LC:\\msys64\\mingw64\\bin -o release\\lukusana.exe release\\ls_input.o release\\ls_presentation.o release\\ls_stack.o release\\lukusana_main.o -lssp