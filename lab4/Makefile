__fake_main__: main

qlist.o: qList.c
	@echo "   gcc   qlist.o"
	@gcc -c -g -o qlist.o qList.c
qvector.o: qVector.c
	@echo "   gcc   qvector.o"
	@gcc -c -g -o qvector.o qVector.c
graph.o: graph.c
	@echo "   gcc   graph.o"
	@gcc -c -g -o graph.o graph.c
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
main: main.o qlist.o qvector.o strparse.o graph.o prompt.o format.o 
	@echo "   LD   main"
	@g++ -static -o main main.o qlist.o qvector.o strparse.o graph.o prompt.o format.o 
clean:
	@echo "  CLEAN   all files."
	-@rm qlist.o qvector.o graph.o prompt.o strparse.o main.o format.o main  || true
