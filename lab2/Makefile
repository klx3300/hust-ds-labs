__fake_main__: main

linear_list.o: linear_list.c
	@echo "   i686-w64-mingw32-gcc   linear_list.o"
	@i686-w64-mingw32-gcc -c  -o linear_list.o linear_list.c
prompt.o: prompt.cpp
	@echo "   i686-w64-mingw32-g++   prompt.o"
	@i686-w64-mingw32-g++ -c  -o prompt.o prompt.cpp
strparse.o: parse_str/strparse.cpp
	@echo "   i686-w64-mingw32-g++   strparse.o"
	@i686-w64-mingw32-g++ -c  -o strparse.o parse_str/strparse.cpp
main.o: main.cpp
	@echo "   i686-w64-mingw32-g++   main.o"
	@i686-w64-mingw32-g++ -c  -o main.o main.cpp
main: main.o strparse.o linear_list.o prompt.o 
	@echo "   LD   main"
	@i686-w64-mingw32-g++ -static -o main main.o strparse.o linear_list.o prompt.o 
clean:
	@echo "  CLEAN   all files."
	-@rm linear_list.o prompt.o strparse.o main.o main  || true
