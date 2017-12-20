__fake_main__: main

binary_tree.o: binary_tree.c
	@echo "   gcc   binary_tree.o"
	@gcc -c -g -o binary_tree.o binary_tree.c
prompt.o: prompt.cpp
	@echo "   g++   prompt.o"
	@g++ -c -g -o prompt.o prompt.cpp
strparse.o: parse_str/strparse.cpp
	@echo "   g++   strparse.o"
	@g++ -c -g -o strparse.o parse_str/strparse.cpp
main.o: main.cpp
	@echo "   g++   main.o"
	@g++ -c -g -o main.o main.cpp
format.o: format/format.c
	@echo "   gcc   format.o"
	@gcc -c -g -o format.o format/format.c
main: main.o strparse.o binary_tree.o prompt.o format.o 
	@echo "   LD   main"
	@g++ -static -o main main.o strparse.o binary_tree.o prompt.o format.o 
clean:
	@echo "  CLEAN   all files."
	-@rm binary_tree.o prompt.o strparse.o main.o format.o main  || true
