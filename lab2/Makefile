__fake_main__: main

linked_list.o: linked_list.c
	@echo "   i686-w64-mingw32-gcc   linked_list.o"
	@i686-w64-mingw32-gcc -c -g -o linked_list.o linked_list.c
prompt.o: prompt.cpp
	@echo "   i686-w64-mingw32-g++   prompt.o"
	@i686-w64-mingw32-g++ -c -g -o prompt.o prompt.cpp
strparse.o: parse_str/strparse.cpp
	@echo "   i686-w64-mingw32-g++   strparse.o"
	@i686-w64-mingw32-g++ -c -g -o strparse.o parse_str/strparse.cpp
main.o: main.cpp
	@echo "   i686-w64-mingw32-g++   main.o"
	@i686-w64-mingw32-g++ -c -g -o main.o main.cpp
format.o: format/format.c
	@echo "   i686-w64-mingw32-gcc   format.o"
	@i686-w64-mingw32-gcc -c -g -o format.o format/format.c
main: main.o strparse.o linked_list.o prompt.o format.o 
	@echo "   LD   main"
	@i686-w64-mingw32-g++ -static -o main main.o strparse.o linked_list.o prompt.o format.o 
clean:
	@echo "  CLEAN   all files."
	-@rm linked_list.o prompt.o strparse.o main.o format.o main  || true
