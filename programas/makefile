objects = fontes/data.o fontes/solvers.o fontes/qsort.o fontes/heuristics.o fontes/callback.o


all: exato heuristica


exato: $(objects) fontes/exato.c
	
	gcc $(objects) -lglpk -lm -o exato fontes/exato.c


heuristica: $(objects) fontes/heuristica.c
		
	gcc $(objects) -lglpk -lm -o heuristica fontes/heuristica.c


fontes/data.o: fontes/data.c fontes/data.h 

	cd fontes;	gcc -c data.c

fontes/solvers.o: fontes/solvers.c fontes/solvers.h 

	cd fontes;	gcc -c solvers.c
	
fontes/qsort.o: fontes/qsort.c fontes/qsort.h 

	cd fontes;	gcc -c qsort.c

fontes/heuristics.o: fontes/heuristics.c fontes/heuristics.h 

	cd fontes;	gcc -c heuristics.c
	
fontes/callback.o: fontes/callback.c fontes/callback.h 

	cd fontes;	gcc -c callback.c
	

clean:

	cd fontes;	rm *.o
	rm exato heuristica

	

glpk-install:
	
	cd ../glpk; make install

glpk-uninstall:
	
	cd ../glpk; make uninstall
