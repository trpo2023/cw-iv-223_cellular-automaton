CFLAGS = -Wall
CPPFLAGS = -MMD

bin/main: obj/src/main/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
obj/src/main/main.o: src/main/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
#библиотека
obj/src/Cellular_automaton/libcell.a: obj/src/Cellular_automaton/cellular_automaton.o
	ar rcs $@ $^

obj/src/Cellular_automaton/cellular_automaton.o: src/Cellular_automaton/cellular_automaton.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
        	
clean:
	rm obj/*/*/*.[oad] bin/*

.PHONY: clean
	
-include obj/src/Cellular_automaton/cellular_automaton.d 
