set prg=%cd%
cd ..
cd lib
echo compile AudioVolume
call scripts\compile_slib.bat src\AudioVolume.cpp obj\AudioVolume_s.o link\libAudioVolume_s.a 
call scripts\compile_slib.bat src\button.cpp obj\button_s.o link\libbutton_s.a 
call scripts\compile_slib.bat src\drbar.cpp obj\drbar_s.o link\libdrbar_s.a 
cd "%prg%"
g++ VolumeCW.cpp -o ../../app/VolumeCW -I"A:\SFML-3.0.0\include" -I"A:\VolumeCW\src\include"  -L"A:\SFML-3.0.0\lib"  ../icon/VolumeCW_ICON.o  -L"A:\VolumeCW\src\lib\link" -lole32 -luuid -lwinmm -DSFML_STATIC -pthread -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lgdi32  -lfreetype -static-libgcc -static-libstdc++ -lAudioVolume_s -lbutton_s -ldrbar_s