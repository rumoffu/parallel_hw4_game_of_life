MPICC	= mpicc

# uncomment to build all when make file changes
#SPECDEP=makefile

TARGETS = gameoflife

all : $(TARGETS)
	@echo Make Complete

gameoflife : gameoflife.c $(SPECDEP)
	$(MPICC) gameoflife.c -o gameoflife

clean :
	rm gameoflife
	@echo Makeclean Complete
