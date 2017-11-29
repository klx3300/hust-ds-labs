__fake_main__: main

linked_list.o: linked_list.c
	@echo "   gcc   linked_list.o"
	@gcc -c  -o linked_list.o linked_list.c
prompt.o: prompt.cpp
	@echo "   g++   prompt.o"
	@g++ -c  -o prompt.o prompt.cpp
strparse.o: parse_str/strparse.cpp
	@echo "   g++   strparse.o"
	@g++ -c  -o strparse.o parse_str/strparse.cpp
main.o: main.cpp
	@echo "   g++   main.o"
	@g++ -c  -o main.o main.cpp
format.o: format/format.c
	@echo "   gcc   format.o"
	@gcc -c  -o format.o format/format.c
main: main.o strparse.o linked_list.o prompt.o format.o 
	@echo "   LD   main"
	@g++ -static -o main main.o strparse.o linked_list.o prompt.o format.o 
clean:
	@echo "  CLEAN   all files."
	-@rm linked_list.o prompt.o strparse.o main.o format.o main  || true
