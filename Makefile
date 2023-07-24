version:
	g++ -v

build:
	mkdir build
	g++ 计算器/计算器.cpp -o build/calculator

run: build
	build/calculator

clean:
	rm -r build
