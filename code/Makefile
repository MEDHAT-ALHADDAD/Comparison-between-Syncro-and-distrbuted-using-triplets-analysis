compile: ${n}.exe
%.exe : *.cpp
	@echo "	compile -> $@ "
	g++ -g -std=c++11 -o $* nonmap_serial.cpp sections.cpp tasks.cpp parallel.cpp serial.cpp input_processing.cpp $*.cpp  -fopenmp
	# g++ -lm -lcrypt -O2 -std=c++11 -pipe -o $* $*.cpp

.PHONY: run
run: main.exe
	./main

%.exe1 : *.cpp
	@echo "	compile -> $@ "
	g++ -g -std=c++11 -o $*  $*.cpp  -fopenmp
	# g++ -lm -lcrypt -O2 -std=c++11 -pipe -o $* $*.cpp


.PHONY: test
test: test.exe1
	./test