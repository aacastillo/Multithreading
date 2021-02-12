SRC = presidential_debate.c
OBJ = presidential_debate.o
PROG = presidential_debate

$(PROG): $(OBJ)
	gcc -pthread  $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
