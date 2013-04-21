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
#define NEIGHBORS 8
#define UPDATE_TYPE 2
#define PRINT_TYPE 3

typedef struct dummy_packet{
        int type;
        int i;
        int j;
        int value;
} packet;

static void print_grid(int grid[N][N]);
static void send_plus(int i, int j, int ra[]);
static void recv_plus(int i, int j, int ra[]);
static void send_diag(int i, int j, int ra[]);
static void recv_diag(int i, int j, int ra[]);
static void calc_neighbors(int i, int j, int ra[]);

int proc[N][N];
int grid[N][N];
int sums[N][N];	
int num_procs, rank, to_rank, from_rank, tag;

int main(int argc, char *argv[]) {
	int toi, toj;
	int i, j, k, iter; 
	int neighbors[NEIGHBORS];
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
	tag = 123;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			to_rank = proc[i][j];
			calc_neighbors(i, j, neighbors);
			for(k = 0; k < NEIGHBORS; k++)
			{//for each neighbor
				from_rank = neighbors[k];
				if(to_rank == rank)
				{//I am responsible for updating this cell
					if(from_rank == rank)
					{//I do to/from for this neighbor's data - so no send/recv
						if(k == 0)
						{	sums[i][j] += grid[(i-1+N) % N][(j-1+N) % N];}
						else if(k == 1)
						{	sums[i][j] += grid[(i-1+N) % N][j];}
						else if(k == 2)
						{	sums[i][j] += grid[(i-1+N) % N][(j+1+N) % N];}
						else if(k == 3)
						{	sums[i][j] += grid[i][(j-1+N) % N];}
						else if(k == 4)
						{	sums[i][j] += grid[i][(j+1+N) % N];}
						else if(k == 5)
						{	sums[i][j] += grid[(i+1+N) % N][(j-1+N) % N];}
						else if(k == 6)
						{	sums[i][j] += grid[(i+1+N) % N][j];}
						else if(k == 7)
						{	sums[i][j] += grid[(i+1+N) % N][(j+1+N) % N];}
					}
					else //neighbor data must come from another proc
					{ //receive the data and process
						MPI_Recv(&temp_pack, sizeof(packet), MPI_BYTE, from_rank, tag, MPI_COMM_WORLD, &status);
						sums[i][j] += temp_pack.value; //maybe if out of synch [temp_pack.i] [temp_pack.j]
					}
				}
				else //not responsible for the cell itself
				{
					if(from_rank == rank)
					{ //I am responsible for this neighbor's data so need to send
						temp_pack.type = UPDATE_TYPE;
						temp_pack.i = i; //for cell at i
						temp_pack.j = j; //for cell at j
						if(k == 0)
						{	temp_pack.value = grid[(i-1+N) % N][(j-1+N) % N];}
						else if(k == 1)
						{	temp_pack.value = grid[(i-1+N) % N][j];}
						else if(k == 2)
						{	temp_pack.value = grid[(i-1+N) % N][(j+1+N) % N];}
						else if(k == 3)
						{	temp_pack.value = grid[i][(j-1+N) % N];}
						else if(k == 4)
						{	temp_pack.value = grid[i][(j+1+N) % N];}
						else if(k == 5)
						{	temp_pack.value = grid[(i+1+N) % N][(j-1+N) % N];}
						else if(k == 6)
						{	temp_pack.value = grid[(i+1+N) % N][j];}
						else if(k == 7)
						{	temp_pack.value = grid[(i+1+N) % N][(j+1+N) % N];}
						MPI_Ssend(&temp_pack, sizeof(packet), MPI_BYTE, to_rank, tag, MPI_COMM_WORLD);
					}
				}
			}		
		}
	}
	if(rank ==0)
	{
		printf("Iteration #%d\n", iter++);
		print_grid(sums);
	}
/*	
	temp_pack.type = 1;
	temp_pack.i = 2;
	temp_pack.j = 3;
	temp_pack.value = 4;
	to_rank = 1;
	from_rank = 0;

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
*/
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

void send_plus(int i, int j, int ra[]) {

}

void recv_plus(int i, int j, int ra[]) {

}

void send_diag(int i, int j, int ra[]) {

}

void recv_diag(int i, int j, int ra[]) {

}

void calc_neighbors(int i, int j, int ra[]) {
	
	ra[0] = proc[(i-1+N) % N][(j-1+N) % N];
	ra[1] = proc[(i-1+N) % N][j];
	ra[2] = proc[(i-1+N) % N][(j+1+N) % N];
	ra[3] = proc[i][(j-1+N) % N];
	ra[4] = proc[i][(j+1+N) % N];
	ra[5] = proc[(i+1+N) % N][(j-1+N) % N];
	ra[6] = proc[(i+1+N) % N][j];
	ra[7] = proc[(i+1+N) % N][(j+1+N) % N];
}

