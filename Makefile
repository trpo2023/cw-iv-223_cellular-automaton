CFLAGS = -Wall
CPPFLAGS = -MMD

bin/main: obj/src/main/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lm -lncurses

test: bin/matrix_test bin/input_user_interface_test bin/graphical-output_test bin/interaction_test

bin/matrix_test: obj/src/test/matrix_test.o obj/src/test/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lm

bin/input_user_interface_test: obj/src/test/input_user_interface_tests.o obj/src/test/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^

bin/graphical-output_test:  obj/src/test/graphical-output_tests.o obj/src/test/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lncurses

bin/interaction_test: obj/src/test/interaction_tests.o obj/src/test/main.o obj/src/Cellular_automaton/libcell.a
	gcc $(CFLAGS) -o $@ $^ -lncurses

obj/src/test/matrix_test.o: test/matrix_test.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/test/input_user_interface_tests.o: test/input_user_interface_tests.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/test/graphical-output_tests.o: test/graphical-output_tests.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $< -lncurses

obj/src/test/interaction_tests.o: test/interaction_tests.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $< -lncurses
	
obj/src/test/main.o: test/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<


obj/src/main/main.o: src/main/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -O0
#библиотека
obj/src/Cellular_automaton/libcell.a: obj/src/Cellular_automaton/cellular_automaton.o obj/src/Input/input_user_interface.o obj/src/Screen/graphical-output.o obj/src/Interaction/interaction.o
	ar rcs $@ $^

obj/src/Cellular_automaton/cellular_automaton.o: src/Cellular_automaton/cellular_automaton.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -O0

obj/src/Input/input_user_interface.o: src/Input/input_user_interface.c	
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -O0

obj/src/Screen/graphical-output.o: src/Screen/graphical-output.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -lncurses -O0
	
obj/src/Interaction/interaction.o: src/Interaction/interaction.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -lncurses -O0
	
	
clean:
	rm obj/*/*/*.[oad] bin/*

.PHONY: clean
	
-include obj/src/Cellular_automaton/cellular_automaton.d obj/src/Input/input_user_interface.d obj/src/Screen/graphical-output.d obj/src/Interaction/interaction.d
