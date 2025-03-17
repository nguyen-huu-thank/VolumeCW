::syntax->:compile_dlib.bat <.cpp> <.o> <.a> <.dll>
g++ -c  "%1" -o "%2" -DBUILD_DLL -shared -fPIC  -I"A:\SFML-3.0.0\include" -I"A:\VolumeCW\src\include" -I"A:\VolumeCW\src\include\dynamic"
g++ -shared "%2" -o "%4" -Wl,--out-implib,"%3" -lole32 -L"A:\SFML-3.0.0\lib" -lsfml-system -lsfml-window -lsfml-graphics