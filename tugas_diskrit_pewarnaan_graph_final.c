#include <stdio.h>

typedef struct data_vertex{
    int nomor;
    int derajat;
}info;

void welsh_powel(int vertex, int graph[][vertex], info info_graph[]){
    int terwarna = 1, get_row[vertex], warna_saat_ini = 1, warna[vertex];

    for(int i = 0; i<vertex; i++){
        get_row[i] = graph[info_graph[0].nomor - 1][i];
        warna[i] = 0;
    }

    warna[info_graph[0].nomor - 1] = warna_saat_ini;

    while(terwarna < vertex){
        for(int j = 0; j<vertex; j++){
            if(get_row[info_graph[j].nomor - 1] == 0 && warna[info_graph[j].nomor - 1] == 0){
                warna[info_graph[j].nomor - 1] = warna_saat_ini;
                terwarna++; 
                for(int k = 0; k < vertex; k++){
                    if(get_row[k] == 0)
                        get_row[k] = get_row[k] + graph[info_graph[j].nomor - 1][k];
                }
            }
        }
        warna_saat_ini++;
        for(int i = 0; i<vertex; i++)
            get_row[i] = 0; 
    }

    printf("... Hasil Akhir Pewarnaan Graph ...\n");
    printf("Nomor Vertex\tWarna\n");
    for(int i = 0; i<vertex; i++){
        printf("%d\t\t%d\n", i+1, warna[i]);
    }
    printf("Bilangan kromatik = %d", warna_saat_ini-1);
}

int main (){
    int vertex;

    //input graph
    printf("...Program Pewarnaan Graph...\n");
    printf("Ketik jumlah vertex : ");
    scanf("%d", &vertex);

    int graph[vertex][vertex];
    info info_graph[vertex];

    for(int i = 0; i<vertex; i++){
        info_graph[i].nomor = i+1;
        info_graph[i].derajat = 0;
    }

    for(int i = 0; i<vertex; i++){
        for(int j = 0; j<vertex; j++){
            if(i == j)
                graph[i][j] = 0;
            else{
                printf("Apakah vertex ke-%d dan %d terhubung (1 = terhubung) : ", i+1,j+1);
                scanf("%d", &graph[i][j]);
                if(graph[i][j] == 1)
                    info_graph[i].derajat += 1;
            }
        }
    }

    //tampilan graph
    printf("... Tampilan Matriks Ketetanggaan ...\n");
    for(int i = 0; i<vertex; i++){
        for(int j = 0; j < vertex; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    //tampilan nomor vertex dan derajat sebelum di sorting;
    printf("... Tampilan vertex sebelum di sorting ...\n");
    printf("Nomor vertex\tDerajat\n");
    for(int i = 0; i<vertex; i++){
        printf("%d\t\t%d\n", info_graph[i].nomor, info_graph[i].derajat);
    }

    //sorting
    int simpan;
    for(int i = 0; i<vertex; i++){
        for(int j = 1; j<vertex-i; j++){
            if(info_graph[j-1].derajat < info_graph[j].derajat){
                //swaping varibel
                //swap derajat
                simpan = info_graph[j-1].derajat;
                info_graph[j-1].derajat = info_graph[j].derajat;
                info_graph[j].derajat = simpan;
                //swap nomor
                info_graph[j-1].nomor = j;
                info_graph[j].nomor = j - 1;
            }
        }
    }
    
    //tampilan nomor vertex dan derajat setelah di sorting;
    printf("\n... Tampilan vertex setelah di sorting ...\n");
    printf("Nomor vertex\tDerajat\n");
    for(int i = 0; i<vertex; i++){
        printf("%d\t\t%d\n", info_graph[i].nomor, info_graph[i].derajat);
    }

    //welch powell
    welsh_powel(vertex, graph, info_graph);
}