CFLAGS = -Wall
CPPFLAGS = -MMD

bin/main: obj/src/main/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lm

test: bin/matrix_test

bin/matrix_test: obj/src/test/matrix_test.o obj/src/test/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lm

obj/src/test/matrix_test.o: test/matrix_test.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/test/main.o: test/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/main/main.o: src/main/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
#библиотека
obj/src/Cellular_automaton/libcell.a: obj/src/Cellular_automaton/cellular_automaton.o obj/src/Input/input_user_interface.o
	ar rcs $@ $^

obj/src/Cellular_automaton/cellular_automaton.o: src/Cellular_automaton/cellular_automaton.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<

obj/src/Input/input_user_interface.o: src/Input/input_user_interface.c	
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
       	
clean:
	rm obj/*/*/*.[oad] bin/*

.PHONY: clean
	
-include obj/src/Cellular_automaton/cellular_automaton.d 
