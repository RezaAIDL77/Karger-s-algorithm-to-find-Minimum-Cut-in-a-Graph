// Karger's algorithm to find Minimum Cut in a Graph
// Assumptions: The Graph is * undirected,
//                            * un-weighted,
//                            * connected
// Graph_Minimum_Cut:
//		Created on: Jan 1, 2019
//		Author	  : Reza Rashetnia
//		Website 	// http://rashetnia.com
//		Linkedin	// www.linkedin.com/in/rezarashetnia
//		Github  	// github.com/RezaAIDL77
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// _________________________________________________
// Structure of undirected unweighted Edge is:		|
// St: Starting point & En: Ending point			|
struct Edge		 //									|
{				 //									|
	int St, En ; //									|
};				 //									|
// _________________________________________________|
// Structure of Graph								|
struct Graph	//									|
{				//									|
//	V-> Number of vertices							|
//	E-> Number of edges								|
	int V, E ;	//									|
	// Array of edges								|
	Edge* edge;//									|
};				//									|
// _________________________________________________|
// Represent Graph for union-find					|
struct NodeC	//									|
{				//									|
	int Root ;	//									|
	int Grade ;	//									|
};				//									|
// _________________________________________________|
// Recalling										|
int find(struct NodeC subsets[], int i);//			|
void Union(struct NodeC subsets[], int x, int y);// |
// _________________________________________________|
// Karger's randomized: Monte-Carlo Randomized
int kargerMinCut(struct Graph* graph)
{
	// Get data of given graph
	int V = graph->V	;
	int E = graph->E 	;
	Edge *edge = graph->edge;

	struct NodeC *subsets = new NodeC[V];// Alloc-mem for creating V subsets

	// Create V subsets with single elements
	for (int v = 0; v < V; ++v)
	{
		subsets[v].Root = v		;
		subsets[v].Grade = 0			; // All vertices are connected
	}

	int vertices = V				; // Number of Vertices for start of contraction
	while (vertices > 2){ 			  // Contraction until to get 2

	int i = rand() % E				; // Pick a random edge

	// Find vertices (or sets) of two corners
	// of current edge
	int subset1 = find(subsets, edge[i].St);
	int subset2 = find(subsets, edge[i].En);

	// If two corners belong to same subset,
	// then no point considering this edge
	if (subset1 == subset2)
		continue;

	// Else contract the edge (or combine the
	// corners of edge into one vertex)
	else
	{
		printf("Contracting edge %d-%d\n",
				edge[i].St, edge[i].En);
		vertices--;
		Union(subsets, subset1, subset2);
	}
	}

	// Now we have two vertices (or subsets) left in
	// the contracted graph, so count the edges between
	// two components and return the count.
	int cutedges = 0;
	for (int i=0; i<E; i++)
	{
		int subset1 = find(subsets, edge[i].St);
		int subset2 = find(subsets, edge[i].En);
		if (subset1 != subset2)
		cutedges++;
	}

	return cutedges;
}
// _____________________________________________
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct NodeC subsets[], int i) // find root and make root as parent of i
{
	if (subsets[i].Root != i)
	subsets[i].Root =
			find(subsets, subsets[i].Root);

	return subsets[i].Root;
}
// _____________________________________________
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct NodeC subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// Attach smaller rank tree under root of high
	// rank tree (Union by Rank)
	if (subsets[xroot].Grade < subsets[yroot].Grade)
		subsets[xroot].Root = yroot;
	else if (subsets[xroot].Grade > subsets[yroot].Grade)
		subsets[yroot].Root = xroot;

	// If ranks are same, then make one as root and
	// increment its rank by one
	else
	{
		subsets[yroot].Root = xroot;
		subsets[xroot].Grade++;
	}
}
// _____________________________________________
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}
// ____________________________________________
// Main Function
int main()
{
	ifstream inFile   ;
		int f = 0     ; //f is vertices counter
		int c1 = 5234 ; //Length of the text input graph
		int c2 = c1/2 ; // Number of edges
		int arr[c1]   ; //1D of the input text file
		inFile.open("/Users/rezarashetnia/eclipse-workspace/Kargers_algorithm/input.txt");
		while(!inFile.eof()){
			inFile >> arr[f] ;
			f++ ;
			}
	ifstream inFile2   ;
		f = 0      ; //f is number of connection for each vertices
		int L[200] ; // List of number of connections
		inFile2.open("/Users/rezarashetnia/eclipse-workspace/Kargers_algorithm/length.txt");
		while(!inFile2.eof()){
			inFile2 >> L[f] ;
			f++ ;
			}
	int M[2517][2] = {0} ;
	int c4 = 0 ;
	int c5 = 0 ;
	int c6 = 0 ;
	for (int i1 = 0 ; i1 < 200 ; i1++){
		++c4 ;
		++c6 ;
		for (int i2 =0 ; i2 < L[i1]-1 ; i2++){
			if (c4 < arr[c6]){
				M[c5][0] = c4 ;
				M[c5][1] = arr[c6];
				++c5 ;
			}
			++c6 ;
		}
	}
	int n6 = sizeof(M)/sizeof(M[0]);

	int V = 200		; // Number of vertices in graph
	int E = n6	; // Number of edges in graph
	struct Graph* graph = createGraph(V, E);
		for (int i7 = 0 ; i7 < n6 ; i7++){
			graph->edge[i7].St = M[i7][0];
			graph->edge[i7].En = M[i7][1];
		}
		// Use a different seed value for every run.
		srand(time(NULL));
		printf("\nCut is %d\n",
			kargerMinCut(graph));
	return 0;
}
