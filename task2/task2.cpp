#include <iostream>
#include <ctime>
#include <thread>
#include <queue>
#include <chrono>

/* 
 * Bogdan Vaneev
 * Innopolis University
 * 1/30/2016
 */

#define N         (1000)
#define N_THREADS (5)

// we will keep graph in adjacency matrix
int ** generate_graph(int n_vertices, int max_path_length = 100);

// selects minimum between a and b
inline int min(int a, int b);

// print graph
void print(int ** G);

// main work
void fw(int** G, int start, int end);

// deallocate memory for graph
void free_graph(int **G);


int main()
{
	int ** G = generate_graph(N);			  // graph for parallel version
	int ** Gseq = new int*[N];			  // and it's copy for single thread version
	// deep copy graph
	for (int i = 0; i < N;i++)
	{
		Gseq[i] = new int[N];
		for (int j = 0; j < N; j++)
			Gseq[i][j] = G[i][j];
	}


	std::chrono::time_point<std::chrono::system_clock> tstart, tend;

	tstart = std::chrono::system_clock::now();
	// PARALLEL VERSION
	std::queue<std::thread*> threads;
	int start = 0;
	int step = N / N_THREADS;
	for (int i = 0; i < N_THREADS; i++)
	{
		step = i == N_THREADS - 1 ? (N - N_THREADS*step) + step: step;
		std::thread *th = new std::thread(fw, G, start, start + step);
		threads.push(th);
		start += step;
	}

	while(!threads.empty())
	{
		std::thread* th = threads.front();
		th->join();
		delete th;
		threads.pop();
	}

	tend = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_parallel = tend - tstart;

	std::cout << "Parallel version with " << N_THREADS << " threads finished in " << elapsed_parallel.count() << " seconds.\n";

	// SINGLE THREAD VERSION
	tstart = std::chrono::system_clock::now();
	fw(Gseq, 0, N);
	tend = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_sequential = tend - tstart;

	std::cout << "Single thread version finished in " << elapsed_sequential.count() << " seconds.\n";

	free_graph(G);
	free_graph(Gseq);

	system("pause");

	return 0;
}


int ** generate_graph(int n_vertices, int max_path_length)
{
	int ** graph = new int*[n_vertices];
	srand(time(NULL));
	for (int i = 0; i < n_vertices; i++)
	{
		graph[i] = new int[n_vertices];
		for (int j = 0; j < n_vertices; j++)
			graph[i][j] = rand() % max_path_length;
	}

	// diagonal elements must be 0 (path length from x to x)
	for (int i = 0; i < n_vertices; i++)
		graph[i][i] = 0;

	return graph;
}


inline int min(int a, int b)
{
	return a > b ? b : a;
}


void print_graph(int ** G)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << G[i][j] << "\t";
		std::cout << "\n";
	}
}


void fw(int** G, int start, int end)
{
	for (int k = 0; k < N; k++)
		for (int i = start; i < end; i++)
			for (int j = 0; j < N; j++)
				G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}


void free_graph(int **G)
{
	for (int i = 0; i < N; i++)
		delete[]G[i];
	delete []G;
}
