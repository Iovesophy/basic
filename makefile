MAIN = mbas
CMDS = bc06
OBJ = $(MAIN).c  $(CMDS).c gettoken.o

all:    mbas.exe
mbas.exe: $(OBJ)
	cc -o basic  $(OBJ)

$(MAIN).obj:    $(MAIN).c
$(CMDS).obj:    $(CMDS).c
gettoken.obj:   gettoken.c gettoken.h

