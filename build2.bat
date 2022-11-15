cd bin
del /Q *.exe
cd ..

g++ *.cpp -o AlarmClock.exe -lstdc++ -Bdynamic -std=c++17 -s 
strip AlarmClock.exe

copy /Y AlarmClock.exe bin
del /Q *.o
del /Q *.a
del /Q *.exe

call .\bin\AlarmClock.exe