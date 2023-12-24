#include <iostream> 
#include <cstdio> 
#include <cstring> 
#include <cstdlib> 
#include <vector> 
#include <string>
#include <algorithm> 
using namespace std; 


struct disjoin_set{ 
  int parent[100], seniorty[100]; 
  
  int Find(int x){ 
    if (parent[x] != x)  parent[x] = Find(parent[x]); 
    return parent[x]; 
  } 
  
  void MakeSet(int vertice){ 
    parent[vertice] = vertice; 
    seniorty[vertice] = 1; 
  } 
  
  
  void Union(int x, int y){ 
    int xRoot = Find(x); 
    int yRoot = Find(y); 
    if (xRoot == yRoot) return; 
    if (seniorty[xRoot] < seniorty[yRoot]) 
      parent[xRoot] = yRoot; 
    else if (seniorty[yRoot] < seniorty[xRoot]) 
      parent[yRoot] = xRoot; 
    else{ 
      parent[yRoot] = xRoot; 
      seniorty[xRoot]++; 
    } 
  }

}; 


struct node{ 
  int x, y, l; 
  node(){} 
  node(int xx, int yy, int ll){ 
    x = xx; y = yy; l = ll; 
  } 
}; 

bool cmp1(const node &a, const node &b){  //删除花费高的，这样剩下的路就是最小花费的路
  return a.l > b.l; 
} 

bool cmp2(const node &a, const node &b){  //建最小的
  return a.l < b.l; 
} 


class CountryReorganization{ 
public: 
  int cost(char ch){ 
    if ('A' <= ch && ch <= 'Z') 
      return ch - 'A'; 
    else 
      return ch - 'a' + 26; 
  }

  int getCost(vector <string> country, vector <string> build, vector <string> destroy){ 
    vector<node> DestroyRoad, BuildRoad; 
    int n = country.size(); 
    for (int i = 0; i < n; i++) 
      for (int j = 0; j < i; j++) 
        if (country[i][j] == '1'){
            DestroyRoad.push_back(node(i, j, cost(destroy[i][j])));
        } 
        else {
            BuildRoad.push_back(node(i, j, cost(build[i][j])));
        }
           
    disjoin_set S; 
    for (int i = 0; i < n; i++) 
      S.MakeSet(i); 
    vector<node>::iterator NewSet; 
    int cost = 0; 
    sort(DestroyRoad.begin(), DestroyRoad.end(), cmp1); 
    for (NewSet = DestroyRoad.begin(); NewSet != DestroyRoad.end(); NewSet++) 
      if (S.Find(NewSet->x) != S.Find(NewSet->y)) 
        S.Union(NewSet->x, NewSet->y); 
      else 
        cost += NewSet->l; 
    sort(BuildRoad.begin(), BuildRoad.end(), cmp2); 
    for (NewSet = BuildRoad.begin(); NewSet != BuildRoad.end(); NewSet++) 
      if (S.Find(NewSet->x) != S.Find(NewSet->y)){ 
        S.Union(NewSet->x, NewSet->y); 
        cost += NewSet->l; 
      } 
    return 0; 
  } 
};


int main(){

    CountryReorganization Reorg;

    string input1, input2, input3;
    
    cin >> input1 >> input2 >> input3;

    vector<string> country, build, destroy;

    istringstream ss1(input1);
    istringstream ss2(input2);
    istringstream ss3(input3);

    string part;
    while (getline(ss1, part, ',')) {
        country.push_back(part);
    }
    while (getline(ss2, part, ',')) {
        build.push_back(part);
    }
    while (getline(ss3, part, ',')) {
        destroy.push_back(part);
    }

    int result = Reorg.getCost(country, build, destroy);

    cout << result << endl;

    return 0;
}




// Hint: All it takes is an algorithm mentioned in this course (with a slight twist). 

// The graph is undirected!


// You need to redesign the road system of an imaginary country.
// 为虚拟国家重建道路系统
// The country is composed of N cities (for simplicity numbered from 0 to N − 1).
// 国家由n各城市构成 从0到n-1
// Some pairs of cities are connected by bidirectional双向路 roads. 
// 有的城市之间是双向路


// 情况1：
// We say that there is a path between different cities A and B； 如果A和B之间有一条路
// if there exists a sequence of unique cities C1,C2,...,CM, such that C1 = A and CM = B ； 
// and for each index i < M, there is a road between cities Ci and Ci+1.
// 如果存在特殊序列的城市1-M；只要i<M，城市Ci和Ci+1之间就有一条路

// The current state of the road network is miserable.  现在的城市道路网络是混乱的
// Some pairs of cities are not connected by any path. 有些城市间完全没有路
// On the other hand, other pairs of cities are connected by multiple different paths, 有的城市间有好几条路
// and that leads to complicated traffic routing. 导致复杂的交通路段

// 前置条件：
// You want to build some new roads and destroy some of the already existing roads in the country 修新路删旧路
// so that after the reconstruction there will exist exactly one path between every pair of distinct cities. 重建后不同2城市间只要一条路
// As building new roads and destroying old ones costs a lot of money, 
// you want to minimize the total cost spent on the reconstruction. 修路和拆路都很花钱，要最小化总花费


// 要求
// You are given three two-dimensional arrays:

// • country[i][j]=1 or 0: there is an existing road between city i and j if and only if country[i][j]=1.
// i，j之间有路的条件是country[i][j]=1


// • build[i][j]: the cost for building a road between i and j. 
// The values of build[i][j] are represented using English letters. 
// A,B,...,Z represent 0,1,...,25 and a,b,...,z represent 26,27,...,51. 
// For example, if build[2][4]=b, then that means the cost for building a road between city 2 and city 4 is 27.
// 建路的花费用build[i][j]表示，用英文字母表示，A-Z表示0-25，a-z表示26-51，比如build[2][4]=b，表示2-4之间修路花费27


// • destroy[i][j]: the cost for destroying a road between i and j. 
// Again, the values are represented using English letters like the above.
// 拆路的花费用destroy[i][j]表示，用英文字母表示，A-Z表示0-25，a-z表示26-51，比如destroy[2][4]=b，表示2-4之间拆路花费27


// 任务：找到修路和拆路的最小花费
// Your task is to find and print the minimal cost needed for the road network reconstruction. 
// You don’t need to worry about invalid inputs.


// • Sample input 1: 000,000,000  ABD,BAC,DCA  ABD,BAC,DCA
// Note: 000,000,000 describes the two-dimensional array country. 
// ABD,BAC,DCA describes the two-dimensional array build. 
// ABD,BAC,DCA describes the two-dimensional array destroy.
 

// The input format is: three strings separated by spaces; 
// each string contains N parts separated by commas; each part contains N characters.
// Sample output 1: 3
// Comment: There are three cities, totally disconnected.
 
 
// • Sample input 2: 011,101,110  ABD,BAC,DCA  ABD,BAC,DCA 
// Sample output 2: 1
// Comment: Now the three cities form a connected triangle and we need to destroy one road. 
// Optimal solution is to destroy the road between the cities 0-1 (cost 1).


// • Sample input 3: (note: all inputs are on the same line. I just couldn’t fit them in one line in this pdf.) 
// 011000,101000,110000,000011,000101,000110
// ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA
// ABDFFF,BACFFF,DCAFFF,FFFABD,FFFBAC,FFFDCA

// Sample output 3: 7
// Comment: We have six cities forming two separate triangles. 
// Destroy one road in each triangle (costs 1 for each road) and then join the triangles by a new road (costs 5).


// • Sample input 4: 0 A A
// Sample output 4: 0
// Comment: One city is okay just as it is.


// • Sample input 5: 0001,0001,0001,1110 AfOj,fAcC,OcAP,jCPA AWFH,WAxU,FxAV,HUVA 
// Sample output 5: 0
// Comment: We have four cities, which are connected in such a way that there is exactly one path between each two cities.
// Thus there is nothing to reconstruct.

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>

// /* Define Edge Type Struct That Contains the Vertices Connected and it's Associated Weight */
// typedef struct edge {
// 	int v1;
// 	int v2;
// 	int weight;
// } Edge;

// /* Define Heap Type Struct Containing the Weights*/
// typedef struct heap {
// 	Edge** edges;
// 	int totalElements;
// 	int totalSize;
// } Heap;


// /* Functions Declaration */
// void checkNullPointer(void*);
// Edge* newEdge(int, int, int);
// Heap* initHeap(int);
// void printHeap(Heap*);
// void printEdge(Edge*);
// void addElement(Heap*, Edge*);
// void deleteElement(Heap**);
// void freeHeap(Heap*);
// void swap(Edge**, Edge**);
// void heapify(Heap*, int);
// void krustalAlgo(Heap**, int, int);
// void initUnionFind(int**, int**, int);
// void freeEdge(Edge*);
// int find(int, int**);
// void unionAlgo(Edge*, int**, int**);
// bool connected(Edge*, int**);
// inline static int getParent(int);
// inline static int getRightChild(int);
// inline static int getLeftChild(int);


// /* Checks if the pointer passed is null */
// void checkNullPointer(void* pointer) {
// 	if(!pointer) {
// 		fprintf(stderr, "Current Pointer is Null, Program is Exiting With Error!\n");
// 		exit(1);
// 	}
// }

// /* Create a new edge and returns a pointer to it */
// Edge* newEdge(int v1, int v2, int weight) {
	
// 	Edge* nEdge = (Edge*) malloc(sizeof(Edge));
// 	checkNullPointer((void*) nEdge);

// 	nEdge -> v1 = v1 - 1;
// 	nEdge -> v2 = v2 - 1;
// 	nEdge -> weight = weight;

// 	return nEdge;
// }

// /* Initiates a new heap struct and returns a pointer to it */
// Heap* initHeap(int totalSize) {

// 	Heap* nHeap = (Heap*) malloc(sizeof(Heap));
// 	checkNullPointer((void*) nHeap);

// 	nHeap -> edges = (Edge**) malloc(sizeof(Edge*) * totalSize);
// 	checkNullPointer((void*) nHeap -> edges);

// 	nHeap -> totalElements = 0;
// 	nHeap -> totalSize = totalSize;

// 	return nHeap;
// }

// /* Returns the value for parent node */
// inline static int getParent(int currIndex) {
// 	return (currIndex - 1) / 2;
// }

// /* Returns the value for parent node */
// inline static int getLeftChild(int currIndex) {
// 	return currIndex * 2 + 1;
// }

// /* Returns the value for parent node */
// inline static int getRightChild(int currIndex) {
// 	return currIndex * 2 + 2;
// }

// /* Swaps the pointer of two edges */
// void swap(Edge** edge1, Edge** edge2) {
// 	Edge* temp = *edge1;
// 	*edge1 = *edge2;
// 	*edge2 = temp;
// }

// /* Adds a new element to heap */
// void addElement(Heap* currHeap, Edge* currEdge) {

// 	Edge** edges = currHeap -> edges;
// 	int aux;
	
// 	if(currHeap -> totalElements == currHeap -> totalSize) {
// 		fprintf(stderr, "Heap Overflow, Please Update Heap Capacity And Try Again!\n");
// 		exit(1);
// 	}

// 	edges[currHeap -> totalElements] = currEdge;
// 	currHeap -> totalElements += 1;

// 	aux = currHeap -> totalElements - 1;
	
// 	while(aux > 0 && edges[getParent(aux)] -> weight > edges[aux] -> weight) {
// 		swap(&edges[getParent(aux)], &edges[aux]);
// 		aux = getParent(aux);
// 	}
// }

// /* Deletes The First Element From Heap, Takes The Last One and Replace it, than Sort The Tree to a Heap Again */
// void deleteElement(Heap** currHeap) {

// 	Heap* aux = *currHeap;
// 	Edge* lastElement;
	
// 	if((*currHeap) -> totalElements > 0) {

// 		lastElement = aux -> edges[aux -> totalElements - 1];

// 		swap(&aux -> edges[0], &lastElement);
// 		aux -> totalElements--;

// 		freeEdge(lastElement);
		
// 		heapify(aux, 0);
// 	}
// }

// /* Transforms An Array Into a Min Heap */
// void heapify(Heap* currHeap, int i) {

// 	int left = getLeftChild(i);
// 	int right = getRightChild(i);
// 	int smallest = i;
// 	int totalElements = currHeap -> totalElements;
// 	Edge** edges = currHeap -> edges;
	
// 	if(left < totalElements && edges[left] -> weight < edges[smallest] -> weight)
// 		smallest = left;

// 	if(right < totalElements && edges[right] -> weight < edges[smallest] -> weight)
// 		smallest = right;

// 	if(smallest != i) {
// 		swap(&edges[smallest], &edges[i]);
// 		heapify(currHeap, smallest);
// 	}
// }

// /* Prints edge info */
// void printEdge(Edge* currEdge) {
// 	printf("Connects Vertice %d to Vertice %d\n", currEdge -> v1, currEdge -> v2);
// 	printf("Weight: %d\n\n", currEdge -> weight);
// }

// /* Print Heap Info */
// void printHeap(Heap* currHeap) {

// 	int i;
	
// 	printf("Total Elements: %d\n", currHeap -> totalElements);
// 	printf("Total Size: %d\n", currHeap -> totalSize);

// 	for(i = 0; i < currHeap -> totalElements; i++)
// 		printEdge(currHeap -> edges[i]);
// }

// /* Free memory allocated for edge struct */
// void freeEdge(Edge* currEdge) {
// 	if(currEdge){
// 		free(currEdge);
// 	}
// }

// /* Free memory allocated for Heap Struct */
// void freeHeap(Heap* currHeap) {
// 	if(currHeap -> edges)
// 		free(currHeap -> edges);

// 	if(currHeap)
// 		free(currHeap);
// }

// /* Init Arrays Used in Union Find Algorithm */
// void initUnionFind(int** vertices , int** ranks, int totalVertices) {

// 	int i;
	
// 	*vertices = (int*) calloc(totalVertices, sizeof(int));
// 	*ranks = (int*) calloc(totalVertices, sizeof(int));

// 	checkNullPointer((void*) *vertices);
// 	checkNullPointer((void*) *ranks);

// 	for(i = 0; i < totalVertices; i++) {
// 		(*vertices)[i] = i;
// 		(*ranks)[i] = 1;
// 	}
	
// }

// /* UnionFind Core Operation, Find the Root Vertice Given Any Other Vertice */
// int find(int root, int** vertices) {

// 	/* Find Root Vertice and do Path Compression Recursivilly */
// 	if(root != (*vertices)[root])
// 		(*vertices)[root] = find((*vertices)[root], vertices);
	
// 	return (*vertices)[root];
// }

// /* UnionFind Core Operation, Connects Sets of Vertices Together*/
// void unionAlgo(Edge* currEdge, int** vertices, int** ranks) {

// 	int root1 = find(currEdge -> v1, vertices);
// 	int root2 = find(currEdge -> v2, vertices);

// 	if((*ranks)[root1] < (*ranks)[root2])
// 		(*vertices)[root1] = root2;
// 	else if((*ranks)[root1] > (*ranks)[root2])
// 		(*vertices)[root2] = root1;
//     else {
// 		(*vertices)[root1] = root2;
// 		(*ranks)[root1] += 1;		
// 	}
// }


// /* Returns if Two Vertices are Already Connected */
// bool connected(Edge* currEdge, int** vertices) {
// 	int u = currEdge -> v1;
// 	int v = currEdge -> v2;
	
// 	return (find(u, vertices) == find(v, vertices));
// }

// /* Implement Krustal Algorithm and Prints The Sum of The Minimun Spanning Tree */
// void krustalAlgo(Heap** currHeap, int totalVertices, int totalEdges) {

// 	int sum = 0, i;
// 	int* vertices = NULL, *ranks = NULL;
// 	Heap* aux = *currHeap;

// 	//printf("Total Vertices: %d\n", totalVertices);
	
// 	initUnionFind(&vertices, &ranks, totalVertices);

// 	for(i = 0; i < totalEdges; i++) {

// 		//printf("Is Connected To MST? %c\n", (connected(aux -> edges[0], &vertices)) ? 's' : 'n');
// 		//printEdge(aux -> edges[i]);
		
// 		if(connected(aux -> edges[0], &vertices)){
// 			deleteElement(currHeap);
// 			continue;
// 		}

// 		//printEdge(aux -> edges[i]);
		
// 		unionAlgo(aux -> edges[0], &vertices, &ranks);
// 		sum += aux -> edges[0] -> weight;
		
// 		deleteElement(currHeap);

// 		/* All Vertices are Connected */
// 		if(ranks[find(0, &vertices)] == totalVertices){
// 			printf("All Nodes Are Connected!\n");
// 			break;
// 		}
// 	}

// 	/*for(int i =0; i < totalVertices; i++)
// 	  printf("Vertice %d: %d\nRank %d: %d\n\n", i, vertices[i], i, ranks[i]);*/

// 	printf("%d\n", sum);

// 	free(vertices);
// 	free(ranks);
// }


// int main(int argc, char* argv[]) {

// 	int totalEdges, totalVertices;
// 	int u, v, w, cont = 0;
// 	Heap* currHeap;
// 	Edge* currEdge;
	
// 	scanf("%d %d", &totalVertices, &totalEdges);

// 	currHeap = initHeap(totalEdges);
	
// 	while(cont < totalEdges &&!feof(stdin)) {
// 		scanf("%d %d %d", &u, &v, &w);
// 		currEdge = newEdge(u, v, w);
// 		addElement(currHeap, currEdge);
// 		cont++;
// 		currEdge = NULL;
// 	}

// 	//printHeap(currHeap);
	
// 	krustalAlgo(&currHeap, totalVertices, totalEdges);

// 	//printHeap(currHeap);
// 	freeHeap(currHeap);
	
// 	return 0;
// }




