make:
	g++ src/*.cpp -o dsc
	#add some testing
	./dsc ./test/main.ds -a ./test/program1.cpp
	g++ ./test/program1.cpp -o ./test/program1
	./test/program1

benchmark:
	@g++ src/*.cpp -o dsc
	@echo	
	@echo "With generation of Test File"
	time ./dsc ./test/main.ds -a ./test/program1.cpp -genBenchFile > /dev/null
	@echo
	@echo "Without generation of Test File"
	time ./dsc ./test/main.ds -a ./test/program1.cpp > /dev/null
	@echo 
	@echo "size of input:" 
	@wc -l < ./test/main.ds
	@echo "size of output:"
	@wc -l < ./test/program1.cpp

debug:
	g++ src/*.cpp -g -O0 -o dsc_temp
	gdb dsc_temp
	rm dsc_temp
