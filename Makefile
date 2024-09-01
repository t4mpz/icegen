ICEBERG_SRC = src/iceberg/iceberg.cpp
BOUNDS_SRC = src/bounds/PixelArea.cpp src/bounds/Content.cpp src/bounds/Viewport.cpp
RENDER_SRC = src/render/ImageRender.cpp
C_FLAGS = -O2 -Wall -Wextra
CIMG_LIBS = -lm -lpthread -lX11

test-bounds:
	echo "Compiling test_bounds.cpp"
	g++ $(C_FLAGS) -o out/tests/bounds.test.e $(ICEBERG_SRC) $(BOUNDS_SRC) tests/test_bounds.cpp 
	./out/tests/bounds.test.e

test-iceberg:
	g++ $(C_FLAGS) -o out/tests/iceberg.test.e $(ICEBERG_SRC) tests/test_iceberg.cpp 
	./out/tests/iceberg.test.e

test-alone:
	g++ $(C_FLAGS) -o out/tests/alone.e tests/test_alone.cpp
	./out/tests/alone.e

test-render:
	g++ -g $(C_FLAGS) -o out/tests/render.test.e $(ICEBERG_SRC) $(RENDER_SRC) $(BOUNDS_SRC) tests/test_render.cpp $(CIMG_LIBS)
	./out/tests/render.test.e

compile-test:
	echo "Starting base test for the Iceberg Generator"
	g++ -Wall -Wextra tests/test_iceberg.cpp -o out/tests/iceberg.test.e
	g++ -Wall -Wextra tests/test_bounds.cpp -o out/tests/bounds.test.e

main:
	g++ $(C_FLAGS) -o iceberg-generator main.cpp $(CIMG_LIBS)
	./iceberg-generator

init:
	mkdir images out out/tests
	