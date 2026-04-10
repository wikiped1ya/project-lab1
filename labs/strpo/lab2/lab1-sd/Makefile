build:
	mkdir -p build

build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp

build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp build/rect.o
	g++ -g -Isrc -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o

test-rect: build/test_rect_basic_methods.out
	./build/test_rect_basic_methods.out

build/test_rect_properties.out: tests/test_rect_properties.cpp build/rect.o
	mkdir -p build
	g++ -g -Isrc -o build/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o

test-properties: build/test_rect_properties.out
	./build/test_rect_properties.out

build/test_rect_operations.out: tests/test_rect_operations.cpp build/rect.o
	mkdir -p build
	g++ -g -Isrc -o build/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o

test-operations: build/test_rect_operations.out
	./build/test_rect_operations.out

build/test_bounding_rect.out: tests/test_bounding_rect.cpp build/rect.o
	mkdir -p build
	g++ -g -Isrc -o build/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o

test-bounding: build/test_bounding_rect.out
	./build/test_bounding_rect.out

test: test-rect test-properties test-operations test-bounding
	@echo "Все тесты пройдены успешно"

build/my_string.o: src/my_string.cpp src/my_string.hpp
	g++ -g -c -o build/my_string.o src/my_string.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp

build/text_wrapper.o: src/text_wrapper.cpp src/text_wrapper.hpp
	g++ -g -c -o build/text_wrapper.o src/text_wrapper.cpp

build/leaks.out: build/rect.o build/my_string.o build/barrel.o build/matrix.o build/text_wrapper.o src/main.cpp
	g++ -g -fsanitize=address -o build/leaks.out src/main.cpp build/rect.o build/my_string.o build/barrel.o build/matrix.o build/text_wrapper.o

leaks: build/leaks.out input.txt
	./build/leaks.out < input.txt

input.txt:
	echo "1 2 3 4" > input.txt
	echo "This text is needed to test the assignment in the program. It is very-very-very-very-very-very-very-very-very-very-very-very-very-very-very-very-very-very-very long" >> input.txt

build/debug.out: build/rect.o build/my_string.o build/barrel.o build/matrix.o build/text_wrapper.o src/main.cpp
	g++ -g -o build/debug.out src/main.cpp build/rect.o build/my_string.o build/barrel.o build/matrix.o build/text_wrapper.o

debug.out: src/main.cpp src/rect.cpp src/barrel.cpp src/matrix.cpp src/my_string.cpp src/text_wrapper.cpp
	g++ -g -o debug.out main.cpp rect.cpp barrel.cpp matrix.cpp my_string.cpp text_wrapper.cpp

debug: build/debug.out
	gdb build/debug.out

clean:
	rm -f build/*.o build/debug.out build/leaks.out input.txt
