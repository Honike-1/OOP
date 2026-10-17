main:
	windres resource.rc -O coff -o resource.res
	g++ main.cpp module1.cpp module1d1.cpp module1d2.cpp module2.cpp resource.res -o app.exe -mwindows -lgdi32
	cmd /c del resource.res
	./app.exe