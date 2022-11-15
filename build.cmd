@echo off

cd bin
del /Q *.exe
cd ..

set DEFAULT_FLAGS="-lmingw32 -lgcc -lmoldname -lmingwex -lmsvcrt -ladvapi32 -lshell32 -luser32 -lkernel32 -lmingw32 -lgcc -lmoldname -lmingwex -lmsvcrt"

set LIBRARY_PATH="-LC:\MinGW\lib\gcc\x86_64-w64-mingw32\11.2.0 -LC:\MinGW\lib"

set type="static"

set OPTIMAL_FLAGS="-lmingw32 -lmsvcrt -lkernel32"

set OBJECT_FILES="C:\MinGW\lib\gcc\x86_64-w64-mingw32\11.2.0\crtbegin.o"

set COLLECT2="C:\MinGW\libexec\gcc\x86_64-w64-mingw32\11.2.0\collect2.exe"

gcc -c main.cpp -s -g -O3
gcc -Bdynamic main.o -lstdc++ -Bdynamic -s -g -O3 -lmingw32 -Bstatic -lgcc -lmoldname -lmingwex -lmsvcrt -ladvapi32 -lshell32 -luser32 -lkernel32 -lmingw32 -lgcc -lmoldname -lmingwex -lmsvcrt -o main.exe 
strip -s main.exe

copy /Y main.exe bin
del /Q *.o
del /Q *.a
del /Q *.exe

call .\bin\main.exe