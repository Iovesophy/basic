MAIN = basic
CMDS = bc06
OBJ = $(MAIN).c  $(CMDS).c gettoken.o eval2.o

all:    basic
basic: $(OBJ)
	cc -o basic $(OBJ) && cc -c eval2.c

$(MAIN).o:    $(MAIN).c
$(CMDS).o:    $(CMDS).c
gettoken.o:   gettoken.c gettoken.h
eval2.o:      eval2.c
