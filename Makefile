.PHONY: all configure build prog tests run-main run-tests clean

all: build

configure:
	cmake -B build

build: configure
	cmake --build build

prog: configure
	cmake --build build --target main

tests: configure
	cmake --build build --target tests

run-main: prog
	./build/main

run-tests: tests
	cd build && ctest --verbose

clean:
	rm -rf build
