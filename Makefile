all:
	cmake -G "MinGW Makefiles" -B ./build
	cmake --build ./build
makefile:
	cmake -G "MinGW Makefiles" -B ./build
build:
	cmake --build ./build
# debug:
# 	cmake -DCMAKE_BUILD_TYPE=Debug ./build
# 	cmake --build ./build --config Debug
clean:
	rmdir /s /q build
	mkdir build