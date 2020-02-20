md Debug
cd Debug
md src
clang++ -DDEBUG -D_DEBUG -UNDEBUG -U_NDEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O0 -emit-llvm -m64 -g3 -glldb -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -std=c++17 -o "src\\ls_input.bc" "..\\ls_input.cpp" 
clang++ -DDEBUG -D_DEBUG -UNDEBUG -U_NDEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O0 -emit-llvm -m64 -g3 -glldb -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -std=c++17 -o "src\\ls_presentation.bc" "..\\ls_presentation.cpp" 
clang++ -DDEBUG -D_DEBUG -UNDEBUG -U_NDEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O0 -emit-llvm -m64 -g3 -glldb -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -std=c++17 -o "src\\ls_stack.bc" "..\\ls_stack.cpp" 
clang++ -DDEBUG -D_DEBUG -UNDEBUG -U_NDEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O0 -emit-llvm -m64 -g3 -glldb -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -std=c++17 -o "src\\lukusana_main.bc" "..\\lukusana_main.cpp" 
clang++ "-LC:\\workspace\\github\\llvm-project\\build\\lib\\Debug" "-LC:\\LLVM-9\\lib" -Wl,/subsystem:console,/machine:x64,/debug:full -fuse-ld=lld -o lukusana.exe "src\\ls_input.bc" "src\\ls_presentation.bc" "src\\ls_stack.bc" "src\\lukusana_main.bc" -lc++