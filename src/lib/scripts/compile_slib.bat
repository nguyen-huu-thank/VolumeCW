::syntax->:compile_slib.bat <.cpp> <.o> <.a>
g++ -c "%1" -o "%2" -I"A:\SFML-3.0.0\include" -I"A:\VolumeCW\src\include" -I"A:\VolumeCW\src\include\static"  -DSFML_STATIC -lwinmm
ar rcs "%3" "%2" -lwinmm