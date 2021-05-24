#include <stdio.h>

void Union(int parent[], int i, int j){
    parent[i] = j;
}

int find(int parent[], int i){
    while(parent[i] != i)
        i = parent[i];
    return i;
}

void kruskalAlgorithm(int V, int graph[][V]){
    int bobot_minimum = 0;
    int parent[V];

    for(int i = 0; i<V; i++)
        parent[i] = i;
    
    for(int count_edge = 0; count_edge < V-1; count_edge++){
        int min = 999, a = -1, b = -1;
        for(int i = 0; i<V; i++){
            for(int j = 0; j<V; j++){
                if(find(parent, i) != find(parent, j) && graph[i][j] < min){
                    min = graph[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        Union(parent, find(parent, a), find(parent, b));
        printf("%d --- %d, bobot = %d\n", a, b, min);
        bobot_minimum += min;
    }

    printf("Minimum Bobot Spanning Tree : %d", bobot_minimum);
}

int main (){
    //V = banyaknya vertex
    int V;

    printf("Ketik jumlah vertex : ");
    scanf("%d", &V);

    int graph[V][V];
   
    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++){
            graph[i][j] = -1;
        }
    }
    
    //Input graph
    for(int i = 0; i<V; i++){
        printf("\n");
        for(int j = 0; j<V; j++){
            if(i == j)
                graph[i][j] = 0;
            else if(graph[i][j] == -1){
                printf("-> Ketik bobot edge (%d, %d) ketik 999 jika vertex tidak terhubung :", i, j);
                scanf("%d", &graph[i][j]);
                graph[j][i] = graph[i][j];
            }
        }
    }

    //Mencetak graph
    for(int i = 0; i<V; i++){
        for(int j = 0; j<V; j++){
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
    printf("Berikut merupakan edge yang merupakan minimum spanning tree :\n");
    kruskalAlgorithm(V, graph);
    return 0;
}