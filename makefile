enigma: main.o utils.o components.o
	g++ -Wall -g main.o utils.o components.o -o enigma

main.o: main.cpp errors.h utils.h components.h
	g++ -Wall -c main.cpp

utils.o: utils.cpp errors.h utils.h components.h
	g++ -Wall -c utils.cpp

components.o: components.cpp errors.h components.h utils.h
	g++ -Wall -c components.cpp

.PHONY: clean
clean:
	rm -rf *.o
