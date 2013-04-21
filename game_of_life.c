/*
Kyle Wong
13.4.20
Parallel Programming
HW 4 game_of_life.c
*/

#include <stdio.h>
#include <mpi.h>

#define MAX_BUFFER 500
#define N 16

typedef struct dummy_packet{
        int type;
        int i;
        int j;
        int value;
} packet;

static void print_grid(int grid[N][N]);

int main(int argc, char *argv[]) {

  int num_procs, rank, to_rank, from_rank, tag;
	int i, j, k, iter; 
	int buffer[MAX_BUFFER];
	int proc[N][N];
	int grid[N][N];
	int sums[N][N];
	MPI_Status status;
	packet temp_pack;
	packet *ptr_pack;
	if(MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		printf("MPI_Init error\n");
	}
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	k = 0;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			grid[i][j] = 0;	
			proc[i][j] = i/(N/num_procs);
			sums[i][j] = 0;
		}
	}
	//starting glider
	grid[0][1] = 1;
	grid[1][2] = 1;
	grid[2][0] = 1;
	grid[2][1] = 1;
	grid[2][2] = 1;
	iter = 0;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			if(proc[i][j] == rank)
			{
				if((i+j) % 2 == 0) 
				{
				}
			}
		}
	}

	temp_pack.type = 1;
	temp_pack.i = 2;
	temp_pack.j = 3;
	temp_pack.value = 4;
	to_rank = 1;
	from_rank = 0;
	tag = 123;

	if(rank == 0)
	{
		MPI_Ssend(&temp_pack, sizeof(packet), MPI_BYTE, to_rank, tag, MPI_COMM_WORLD);
		iter = 1;
		printf("Printing grid iteration %d\n", iter++);
		print_grid(grid);
	}
	if(rank == 1)
	{
		MPI_Recv(&temp_pack, sizeof(packet), MPI_BYTE, from_rank, tag, MPI_COMM_WORLD, &status);
		ptr_pack = &temp_pack;
		printf("pack.i = %d\n", ptr_pack->i);
		printf("pack.j = %d\n", ptr_pack->j);
		printf("pack.value = %d\n", ptr_pack->value);
	}

	MPI_Finalize();
	return 0;
}

void print_grid(int grid[N][N]) {

	int i, j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf("%d ", grid[i][j]);
		}
		printf("\n");
	}

}
