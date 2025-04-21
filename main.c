/*
NAME: Lana Mahmoud Ali Musaffer
Dr. Radi Jarrar
SECTION: 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_CITY_NAME 100
#define CITIES 15
#define MAX_WEIGHT INT_MAX

//LINKED LIST STRUCT
struct LIST {
    int index;
    char city[MAX_CITY_NAME];
    struct LIST* next;
};

//A METHOD THAT PRINTS THE MENU
void menu() {
    printf("\nPLEASE SELECT AN OPERATION: \n");
    printf("1. LOAD CITIES.\n");
    printf("2. ENTER SOURCE.\n");
    printf("3. ENTER DESTINATION.\n");
    printf("4. FIND SHORTEST PATH BETWEEN CITIES AND TOTAL DISTANCE.\n");
    printf("5. SAVE TO FILE AND EXIT.\n");
}

//CREATES NODES IN THE LINKED LIST TO SAVE THE CITIES
struct LIST* createCities(struct LIST* head, char city[], int* size) {
    struct LIST* temp = (struct LIST*)malloc(sizeof(struct LIST));
    strcpy(temp->city, city);
    temp->next = NULL;

    if (head == NULL) { //LINKED LIST IS EMPTY
        head = temp;
        temp->index = 0;
    }

    else {  //LINKED LIST IS NOT EMPTY
        struct LIST* p = head;
        int index = 1;
        while (p->next != NULL) {
            if (strcmp(p->city, city) == 0) { //CHECK IF THE CITY IS EXISTS IN THE LINKED LIST
                free(temp); //REMOVE DUPLICATED CITIES
                return head;
            }
            p = p->next;
            index++;
        }
        if (strcmp(p->city, city) == 0) {
            free(temp);
            return head;
        }
        p->next = temp;
        temp->index = index;
    }
    (*size)++; //KEEP TRAKING THE NUMBER OF CITIES
    return head;
}

//A METHOD THAT READS THE FILE AND CONSTRUCT IT INTO LINKED LIST
struct LIST* createListFromFile(struct LIST* head, char filename[], int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR IN OPENING THE FILE.\n");
        return head;
    }

    char line[MAX_CITY_NAME * 2]; //READ TWO CITIES IN EACH LINE
    while (fgets(line, sizeof(line), file) != NULL) {
        char city1[MAX_CITY_NAME], city2[MAX_CITY_NAME];
        int distance;
        sscanf(line, "%s %s %d", city1, city2, &distance);
        head = createCities(head, city1, size);
        head = createCities(head, city2, size);
    }
    fclose(file);
    return head;
}

//A METHOD TO PRINT THE LINKED LIST
void printList(struct LIST* head) {
    struct LIST* p = head;
    while (p != NULL) {
        printf("%d %s\n", p->index, p->city);
        p = p->next;
    }
}

// A METHOD THAT FIND THE INDEX OF EACH CITY
int getCityIndex(struct LIST* head, char city[]) {
    struct LIST* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->city, city) == 0) {
            return temp->index;
        }
        temp = temp->next;
    }
    printf("CITY NOT FOUND!\n");
    return -1;
}

// A METHOD THAT FIND THE NAME OF EACH CITY
const char* getCityName(struct LIST* head, int index) {
    struct LIST* temp = head;
    while (temp != NULL) {
        if (temp->index == index) {
            return temp->city;
        }
        temp = temp->next;
    }
    return "Unknown";
}

///////////////////////////////////////////////DIJKESTRA////////////////////////////////////////////////

//A METHOD TO FIND THE CITY WITH MINIMUM DISTANCE FROM THE SOURCE CITY
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < CITIES; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

//A METHOD FOR PRINTING THE SHORTEST PATH FROM THE SOURCE CITY TO THE DESTINATION
void printSolution(int dist[], int parent[], int src, int dest, struct LIST* head) {
    printf("DIJKSTRA'S PATH: ");
    int j = dest;
    while (j != src) {
        printf("%s <- ", getCityName(head, j));
        j = parent[j];
    }
    printf("%s\n", getCityName(head, src));
    printf("\nTOTAL DISTANCE FROM %s TO %s IS %d.\n",
            getCityName(head, src),
            getCityName(head,dest),
            dist[dest]);
}


//A METHOD THAT FINDS THE SHORTEST PATH BETWEEN THE SOURCE AND DESTINATION CITIES
void dijkstra(int graph[CITIES][CITIES], int src, int dest, struct LIST* head) {
    int dist[CITIES], parent[CITIES];
    bool sptSet[CITIES];

    //INITIALIZE THE DISTANCE WITH MAXIMUM VALUE
    for (int i = 0; i < CITIES; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;  //THE SOURCE CITY IS INITIALIZED TO ZERO
    for (int count = 0; count < CITIES - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < CITIES; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, src, dest, head);
}

///////////////////////////////////////////////////BFS////////////////////////////////////////////////////

// DIRECTED GRAPH STRUCT USING ADJECANCY MATRIX
typedef struct Graph_t {
    int V;
    bool adj[CITIES][CITIES];
} Graph;

//METHOD FOR CREATING THE GRAPH
Graph* GraphCreate(int V)
{
    Graph* g = malloc(sizeof(Graph));
    g->V = V;

    //INITIALIZE THE ADJECANCY MATRIX WITH NO EDGES BETWEEN ANY CITIES
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = false;
        }
    }
    return g;
}

//METHOD THAT PRINTS THE FULL ROUTE OF THE SHORTEST PATH
void BFS(Graph* g, int source, int destination, int graph[CITIES][CITIES], struct LIST* head) {
    // INITIALIZE ALL CITIES AS UNVISITED
    bool visited[CITIES];
    for (int i = 0; i < CITIES; i++) {
        visited[i] = false;
    }

    // CREATING A QUEUE FOR BFS
    int queue[CITIES], front = 0, rear = 0;

    // MARK THE CURRENT CITY AS VISITED AND ENQUEUE IT
    visited[source] = true;
    queue[rear++] = source;

    //FOR KEEP TRAKING OF THE TOTAL DISTANCE
    int parent[CITIES];
    int distance[CITIES];
    for (int i = 0; i < CITIES; i++) {
        parent[i] = -1;
        distance[i] = 0;
    }

    while (front != rear) {
        int currentCity = queue[front++]; // DEQUEUE THE CITY
        if (currentCity == destination) // CHECK IF THE CURRENT CITY IS THE DESTINATION
            break;

        // GET ALL ADJACENT CITIES OF THE DEQUEUED
        for (int adjacent = 0; adjacent < CITIES; adjacent++) {
            if (graph[currentCity][adjacent] && !visited[adjacent]) {
                visited[adjacent] = true; // IF AN ADJACENT HAS NOT VISITED, THEN MARK IT AS VISITED
                queue[rear++] = adjacent; // ENQUEUE THE CITY
                parent[adjacent] = currentCity; // STORE THE PARENT INFORMATION
                distance[adjacent] = distance[currentCity] + graph[currentCity][adjacent]; // CALCULATE THE DISTANCE
            }
        }
    }

    // PRINT THE SHORTEST PATH FROM SOURCE TO DESTINATION
    int current = destination;
    printf("%s", getCityName(head, current));
    while (current != source) {
        printf(" <- %s", getCityName(head, parent[current]));
        current = parent[current];
    }
    printf("\n");

    // PRINT THE TOTAL DISTANCE
     printf("\nTOTAL DISTANCE FROM %s TO %s IS %d.\n",
            getCityName(head, source),
            getCityName(head, destination),
             distance[destination]);
}
/////////////////////////////////////////////FILE///////////////////////////////////////////////
/*SAME METHODS BUT FOR SAVING IN THE FILE*/
void BFS_printToFile(Graph* g, int source, int destination, int graph[CITIES][CITIES], struct LIST* head,  FILE* file) {
    bool visited[CITIES];
    for (int i = 0; i < CITIES; i++) {
        visited[i] = false;
    }

    int queue[CITIES], front = 0, rear = 0;

    visited[source] = true;
    queue[rear++] = source;

    int parent[CITIES];
    int distance[CITIES];
    for (int i = 0; i < CITIES; i++) {
        parent[i] = -1;
        distance[i] = 0;
    }

    while (front != rear) {
        int currentCity = queue[front++];
        if (currentCity == destination)
            break;

        for (int adjacent = 0; adjacent < CITIES; adjacent++) {
            if (graph[currentCity][adjacent] && !visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
                parent[adjacent] = currentCity;
                distance[adjacent] = distance[currentCity] + graph[currentCity][adjacent];
            }
        }
    }

    int current = destination;
    fprintf(file,"%s", getCityName(head, current));
    while (current != source) {
        fprintf(file, " <- %s", getCityName(head, parent[current]));
        current = parent[current];
    }

     fprintf(file, "\nTOTAL DISTANCE FROM %s TO %s IS %d.\n",
            getCityName(head, source),
            getCityName(head, destination),
            distance[destination]);
}

void printSolutionFile(int dist[], int parent[], int src, int dest, struct LIST* head,  FILE* file) {
    fprintf(file, "DIJKSTRA'S PATH: ");
    int j = dest;
    while (j != src) {
        fprintf(file, "%s <- ", getCityName(head, j));
        j = parent[j];
    }
    fprintf(file, "%s\n", getCityName(head, src));
    fprintf(file, "TOTAL DISTANCE FROM %s TO %s IS %d.\n",
            getCityName(head, src),
            getCityName(head,dest),
            dist[dest]);
}


void dijkstraPrintToFile(int graph[CITIES][CITIES], int src, int dest, struct LIST* head, FILE* file) {
    int dist[CITIES], parent[CITIES];
    bool sptSet[CITIES];

    for (int i = 0; i < CITIES; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;
    for (int count = 0; count < CITIES - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < CITIES; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolutionFile(dist, parent, src, dest, head, file);
}
//////////////////////////////////////////////MAIN///////////////////////////////////////////////

int main() {
    struct LIST* head = NULL;  //CREATING AN EMPTY LINKED LIST
    char filename[100] = "cities.txt";
    int size = 0;  //INITIALISE THE SIZE OF THE LINKED LIST
    head = createListFromFile(head, filename, &size);
    printf("CITIES: \n");
    printList(head); //PRINTING THE CITIES WITH THEIR INDECES

    //CREATING AN ADJECANCY MATRIX GRAPH
    int graph[CITIES][CITIES];
    for (int i = 0; i < CITIES; i++) {
        for (int j = 0; j < CITIES; j++) {
            graph[i][j] = 0;
        }
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR IN OPENING THE FILE.\n");
        return 0;
    }

    //CONSTRUCT THE FILE INTO A DIRECTED GRAPH
    char line[MAX_CITY_NAME * 3];
    int city1Index, city2Index;
    while (fgets(line, sizeof(line), file) != NULL) {
        char city1[MAX_CITY_NAME], city2[MAX_CITY_NAME];
        int distance;
        sscanf(line, "%s %s %d", city1, city2, &distance);
        city1Index = getCityIndex(head, city1);
        city2Index = getCityIndex(head, city2);
        graph[city1Index][city2Index] = distance;
    }

    fclose(file);

    FILE* fileOut = fopen("shortest_distance.txt", "a");

    int choice, sourceIndex, destinationIndex;
    bool citiesLoaded = false;
    bool sourceEntered = false;
    bool destinationEntered = false;

    while(1){
        menu();
        printf("PLEASE ENTER AN OPERATION: ");
        scanf("%d", &choice);

        switch (choice) {

            //LOAD FILE
            case 1:
                printf("CITIES LOADED!\n");
                citiesLoaded = true;
                break;

            //ENTER SOURCE CITY
            case 2:
                if (citiesLoaded) {
                    char sourceCity[MAX_CITY_NAME];
                    printf("Enter the source city: ");
                    scanf("%s", sourceCity);
                    sourceIndex = getCityIndex(head, sourceCity);
                    if (sourceIndex != -1) {
                        printf("Source entered.\n");
                        sourceEntered = true;
                    }
                }
                 else
                    printf("PLEASE LOAD CITIES FIRST!\n");

                break;

            //ENTER DESTINATION CITY
            case 3:
                if (citiesLoaded) {
                    char destinationCity[MAX_CITY_NAME];
                    printf("Enter the destination city: ");
                    scanf("%s", destinationCity);
                    destinationIndex = getCityIndex(head, destinationCity);
                    if (destinationIndex != -1) {
                        printf("Destination entered.\n");
                        destinationEntered = true;
                    }
                }
                else
                    printf("PLEASE LOAD CITIES FIRST!\n");

                break;

            //BFS & DIJKESTRA ALGORITHMS
            case 4:
                if (citiesLoaded && sourceEntered && destinationEntered) {
                    printf("\n______________");
                    printf("\nBFS PATH: ");
                    Graph* g = GraphCreate(size);
                    //ITERATES OVER THE MATRIX AND ADD THE DISTANCES BETWEEN THE CITIES
                    for (int i = 0; i < CITIES; i++) {
                        for (int j = 0; j < CITIES; j++) {
                            if (graph[i][j] != 0) {
                                g->adj[i][j] = true;
                            }
                        }
                    }
                    BFS(g, sourceIndex, destinationIndex,graph, head);
                    free(g); //DESTROY THE GRAPH
                    printf("______________");
                    printf("\n");
                    dijkstra(graph, sourceIndex, destinationIndex, head);
                    printf("______________");
                } else {
                    printf("PLEASE LOAD CITIES FIRST! ENTER SOURCE & DESTINATION.\n");
                }
                break;

            //EXIT AND SAVE TO FILE
            case 5:
                fprintf(fileOut,"\nBFS PATH: ");
                Graph* g = GraphCreate(size);
                //ITERATES OVER THE MATRIX AND ADD THE DISTANCES BETWEEN THE CITIES
                for (int i = 0; i < CITIES; i++) {
                    for (int j = 0; j < CITIES; j++) {
                       if (graph[i][j] != 0) {
                            g->adj[i][j] = true;
                        }
                    }
                }
                BFS_printToFile(g, sourceIndex, destinationIndex,graph, head, fileOut);
                free(g); //DESTROY THE GRAPH
                dijkstraPrintToFile(graph, sourceIndex, destinationIndex, head, fileOut);
                printf("THANKS FOR USING MY PROGRAM! DATA HAVE BEEN LOADED TO (shortest_distance.txt) FILE.\n");
                exit(0);
            default:
                printf("INVALID OPERATION! PLEASE TRY AGAIN.\n");
        }
    }

    return 0;
}