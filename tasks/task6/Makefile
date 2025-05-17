.PHONY: test build

config:
	cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

build: config
	cmake --build ./build --target task6 --config Debug

run: build task6
	./task6 0 2 1000000 2
	@echo "expected output is 4.00699"

test: build task6
	python3 -m pip install scipy
	python3 tests.py

clean:
	rm -rf build/
	rm task6
