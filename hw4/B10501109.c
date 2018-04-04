#include <stdio.h>
#include <stdlib.h>
#define MAX_NUM_LINK 50
#define MAX_NUM_NODE 50

struct link{
        int ends[2];
        double cost;
};

struct node{
        int id;
        int next;
        double cost;
};

struct link links[MAX_NUM_LINK];
struct node nodes[MAX_NUM_NODE];
int num_of_link = 0;
int num_of_node = 0;



void readTopo(const char* plaintext){
	FILE* input_file = fopen(plaintext, "r");
	num_of_link = 0;
	num_of_node = 0;

        if(!input_file){
		printf("Cannot read the topo file\n");
		return;
	}

	while(!feof(input_file)){
		int dd;
                int id1;
                int id2;
		double cost;
		fscanf(input_file, "%d %d %d %lf\n", &dd, &id1, &id2, &cost);

		if(id1 > num_of_node) num_of_node = id1;
		if(id2 > num_of_node) num_of_node = id2;


		if(num_of_link < MAX_NUM_LINK){
			links[num_of_link].ends[0] = id1;
			links[num_of_link].ends[1] = id2;
			links[num_of_link].cost = cost;

			num_of_link++;
		}
		
		nodes[id1].id = id1;
		nodes[id1].next = -1;
		nodes[id1].cost = 0.0;
		nodes[id2].id = id2;
		nodes[id2].next = -1;
		nodes[id2].cost = 0.0;

	}


        fclose(input_file);
}


void print_path(int* path, int path_len){
	for(int i = 0; i < path_len; i++){
		printf("%d\t", path[i]);
	}
	printf("\n");
}


void buildAdjacencyMatrix(double **adjMatrix, int nodeCount) {
    for (int i = 1; i < nodeCount + 1; i++) {
        for (int j = 1; j < nodeCount + 1; j++)
            adjMatrix[i][j] = -1;
    }

    for (int i = 0; i < num_of_link; i++) {
        adjMatrix[links[i].ends[0]][links[i].ends[1]] = links[i].cost;
        adjMatrix[links[i].ends[1]][links[i].ends[0]] = links[i].cost;
    }
}

void performDijsktra(int srcId) {
    vector<int> Nset;
    double **adjMatrix;

    // Array
    adjMatrix = new double*[num_of_node + 1];
    for (int i = 0; i < num_of_node + 1; i++)
        adjMatrix[i] = new double[num_of_node + 1];

    buildAdjacencyMatrix(adjMatrix, num_of_node);

    // Dijsktra initial
    int searchNode = srcId, minCostNode = -1;
    double minCost = INT_MAX;
    for (int i = 1; i < num_of_node + 1; i++)
        nodes[i].cost = INT_MAX;
    nodes[srcId].cost = 0;

    // Dijsktra loop
    Nset.push_back(searchNode);
    while (true) {
        for (int i = 1; i < num_of_node + 1; i++) {
            bool existsInNset = find(Nset.begin(), Nset.end(), i) != Nset.end();
            if (existsInNset) continue;

            if (adjMatrix[searchNode][i] != -1) {
                double newCost = nodes[searchNode].cost + adjMatrix[searchNode][i];
                if (newCost < nodes[i].cost) {
                    nodes[i].cost = newCost;
                    nodes[i].next = searchNode;
                }
            }

            if (nodes[i].cost < minCost) {
                minCost = nodes[i].cost;
                minCostNode = i;
            }
        }
        if (minCostNode == -1) throw runtime_error("No route found.");
        searchNode = minCostNode;
        Nset.push_back(searchNode);
        minCostNode = -1; minCost = INT_MAX;

        if (Nset.size() == num_of_node)
            break;
    }

#ifdef DEBUG
    printf("N'= ");
    for (auto &id : Nset)
        printf("%d ", id);
    printf("\n");

    for (int i = 1; i < num_of_node + 1; i++) {
        printf("node %d: cost=%.1f, next=%d\n", nodes[i].id, nodes[i].cost, nodes[i].next);
    }
#endif

    for (int i = 0; i < num_of_node + 1; i++)
        delete [] adjMatrix[i];
    delete [] adjMatrix;
}

void generatePath(int srcId, int dstId, int path[], int *path_len) {
    int next, size = 0;

    next = path[size++] = dstId;
    while (srcId != next) {
        next = nodes[next].next;
        path[size++] = next;
    }
    *path_len = size;

    for (int i = 0; i < size / 2; i++) {
        swap(path[i], path[size - i - 1]);
    }
}

int main(int argc, char *argv[]){
	int path[MAX_NUM_NODE];
	int path_len;
	int source, destination;

	if(argc != 3){
		printf("Usage: ./routing <source> <destination>\n");
		return -1;
	}

	source = atoi(argv[1]);
	destination = atoi(argv[2]);


	readTopo("topo.txt");
	
	/* insert your code here and also you are free to define any function */

    performDijsktra(source);
    generatePath(source, destination, path, &path_len);

	print_path(path, path_len);
	
}
