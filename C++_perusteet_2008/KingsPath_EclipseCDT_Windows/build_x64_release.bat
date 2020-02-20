md Release
cd Release
md src
clang++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O3 -emit-llvm -m64 -march=native -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -flto -fvisibility=hidden -fstack-protector-strong -std=c++17 -o "src\\KingsPathApp.bc" "..\\..\\KingsPathApp.cpp" 
clang++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O3 -emit-llvm -m64 -march=native -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -flto -fvisibility=hidden -fstack-protector-strong -std=c++17 -o "src\\main.bc" "..\\..\\main.cpp" 
clang++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O3 -emit-llvm -m64 -march=native -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -flto -fvisibility=hidden -fstack-protector-strong -std=c++17 -o "src\\Board.bc" "..\\..\\Board.cpp" 
clang++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O3 -emit-llvm -m64 -march=native -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -flto -fvisibility=hidden -fstack-protector-strong -std=c++17 -o "src\\Graph.bc" "..\\..\\Graph.cpp" 
clang++ -DNDEBUG -D_NDEBUG -UDEBUG -U_DEBUG "-IC:\\workspace\\github\\llvm-project\\libcxx\\include" -O3 -emit-llvm -m64 -march=native -pedantic -Wall -c -fmessage-length=0 -Wextra -Wformat-security -Werror=format-security -flto -fvisibility=hidden -fstack-protector-strong -std=c++17 -o "src\\Node.bc" "..\\..\\Node.cpp" 
clang++ "-LC:\\workspace\\github\\llvm-project\\build\\lib\\Release" "-LC:\\LLVM-9\\lib" -Wl,/subsystem:console,/machine:x64 -fuse-ld=lld -fstack-protector-strong -o KingsPath.exe "src\\Board.bc" "src\\Graph.bc" "src\\KingsPathApp.bc" "src\\Node.bc" "src\\main.bc" -lc++ 
