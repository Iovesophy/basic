MAIN = basic
CMDS = bc06
OBJ = $(MAIN).c  $(CMDS).c gettoken.o eval.o

all:    basic
basic: $(OBJ)
	cc -o basic $(OBJ) && cc -c eval.c

$(MAIN).o:    $(MAIN).c
$(CMDS).o:    $(CMDS).c
gettoken.o:   gettoken.c gettoken.h
eval.o:      eval.c
