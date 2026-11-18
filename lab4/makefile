main:
	windres resource.rc -o resource.o
	g++ main.cpp mainwnd.cpp editor.cpp toolbar.cpp shapes/shape.cpp shapes/point.cpp shapes/line.cpp shapes/rectangle.cpp shapes/ellipse.cpp shapes/cube.cpp shapes/dotsline.cpp resource.o -o app.exe -lgdi32 -lcomctl32 -mwindows
	cmd /c del resource.o
	.\app.exe