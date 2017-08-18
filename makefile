MAIN = basic
CMDS = main
OBJ = $(MAIN).c  $(CMDS).c gettoken.o eval.o

all:    basic
basic: $(OBJ)
	cc -o basic $(OBJ)

$(MAIN).o:    $(MAIN).c
$(CMDS).o:    $(CMDS).c
gettoken.o:   gettoken.c gettoken.h
eval.o:      eval.c
