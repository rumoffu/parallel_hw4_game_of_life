MPICC	= mpicc

# uncomment to build all when make file changes
#SPECDEP=makefile

TARGETS = game_of_life

all : $(TARGETS)
	@echo Make Complete

game_of_life : game_of_life.c $(SPECDEP)
	$(MPICC) game_of_life.c -o game_of_life

clean :
	rm game_of_life
	@echo Makeclean Complete
