build:
	mkdir objs
	gcc -c -o objs/glfunctions.o src/glfunctions.c
	gcc -c -o objs/helpers.o src/helpers.c
	gcc -c -o objs/pesti.o src/pesti.c
	gcc -c -o objs/list.o src/list.c
	gcc -c -o objs/culori.o src/culori.c
	gcc -c -o objs/bubbles.o src/bubbles.c
	gcc -c -o objs/nisip.o src/nisip.c
	gcc -c -o objs/run_app.o src/run_app.c
	gcc -c -o objs/main.o src/main.c
	gcc -g -o main objs/main.o objs/glfunctions.o objs/helpers.o objs/pesti.o objs/list.o objs/culori.o objs/bubbles.o objs/nisip.o objs/run_app.o -lGL -lGLU -lglut -lm

clean:
	rm -r objs
	rm main

rebuild:
	make clean
	make