run: compiler.exe
	./compiler.exe

compiler.exe: FORCE main.c state.c tokenizer.c parser.c
	gcc -Wall main.c state.c tokenizer.c parser.c -o compiler.exe

FORCE: