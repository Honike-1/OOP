main:
	windres resource.rc -o resource.o
	g++ main.cpp shapes/shape.cpp shapes/point.cpp shapes/line.cpp shapes/rectangle.cpp shapes/ellipse.cpp resource.o -o app.exe -lgdi32 -mwindows
	cmd /c del resource.o
	.\app.exe