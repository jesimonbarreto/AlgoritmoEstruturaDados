EXEG = tp3h
EXEBF = tp3fb

all:
	gcc tp3h.c Graph.c Heurist.c -g -O0 -o $(EXEG) -Wall -Werror
	gcc tp3bf.c Graph.c BruteF.c -g -O0 -o $(EXEBF) -Wall -Werror

clean:
	rm -rf $(EXE)
