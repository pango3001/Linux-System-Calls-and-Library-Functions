MYDU	= mydu
MYDU_OBJ = mydu.o
OUTPUT	= $(MYDU)

.SUFFIXES: .c .o

all: $(OUTPUT)

$(MYDU): $(MYDU_OBJ)
	gcc -g -o $@ $(MYDU_OBJ)

.c.o:
	gcc -g -c $<

.PHONY: clean
clean:
	/bin/rm -f $(OUTPUT) *.o
