CC := gcc
CCFLAGS := -Wall -pedantic-errors -Werror -g --std=c99
OBJDIR := obj
OBJS = $(addprefix $(OBJDIR)/, FilePositionOptions.o Options.o FileArray.o TestBlock.o FilePosition.o BlockRegister.o BlockRegistry.o Printer.o FilePositionArray.o ChildrenArray.o TestBlockTrace.o Array.o Tree.o Lexer.o Parser.o Token.o main.o)
SRC := src
TESTDIR := tests
BINDIR := bin
OUT := $(BINDIR)/tw

.PHONY: test real compilereal runreal clean setup dirs

test: clean compilereal
	./tests/out > tests/test.out
	diff tests/test.out tests/validOutput.txt

valgrind: clean compilereal
	valgrind --leak-check=full ./bin/tw tests/realTest.c tests/realTest.out.c

real: $(OUT)
	./bin/tw tests/realTest1.c tests/realTest2.c tests/realTest3.c -o tests/realTest.out.c
	vim tests/realTest.out.c

compilereal: $(OUT)
	./bin/tw tests/realTest1.c tests/realTest2.c tests/realTest3.c -o tests/realTest.out.c
	gcc tests/RLEList.c tests/RLEListHelper.c tests/realTest.out.c -Isrc -g -o tests/out

runreal: compilereal
	./tests/out

$(OUT): objs
	$(CC) $(CCFLAGS) $(OBJS) -o $@

objs: setup $(OBJS)

setup: dirs
dirs: 
	@mkdir -p $(OBJDIR) $(BINDIR) $(TESTDIR) 

$(OBJDIR)/%.o: $(SRC)/%.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUT)

