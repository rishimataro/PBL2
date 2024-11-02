all:
	cmake -G "MinGW Makefiles" -B ./build
	cmake --build ./build
makefile:
	cmake -G "MinGW Makefiles" -B ./build
build:
	cmake --build ./build
clean:
	rmdir /s /q build
	mkdir build