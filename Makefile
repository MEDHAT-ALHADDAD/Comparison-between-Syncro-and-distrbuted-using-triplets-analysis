compile: ${n}.exe
%.exe : *.cpp
	@echo "	compile -> $@ "
	g++ -g -std=c++11 -o $* input_processing.cpp $*.cpp  -fopenmp
	# g++ -lm -lcrypt -O2 -std=c++11 -pipe -o $* $*.cpp

.PHONY: run
run: main.exe
	./main
