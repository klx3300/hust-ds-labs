__fake_main__: main

linear_list.o: linear_list.c
	@echo "   gcc   linear_list.o"
	@gcc -c  -o linear_list.o linear_list.c
prompt.o: prompt.cpp
	@echo "   g++   prompt.o"
	@g++ -c  -o prompt.o prompt.cpp
strparse.o: parse_str/strparse.cpp
	@echo "   g++   strparse.o"
	@g++ -c  -o strparse.o parse_str/strparse.cpp
main.o: main.cpp
	@echo "   g++   main.o"
	@g++ -c  -o main.o main.cpp
main: main.o strparse.o linear_list.o prompt.o 
	@echo "   LD   main"
	@g++  -o main main.o strparse.o linear_list.o prompt.o 
clean:
	@echo "  CLEAN   all files."
	-@rm linear_list.o prompt.o strparse.o main.o main  || true
