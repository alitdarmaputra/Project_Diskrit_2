/*
    Nama Kelompok 2:
    - Stephania Getrudis Inaconta Sadipun   (2008561043)
    - I Made Alit Darma Putra               (2008561045)
    - I Dewa Made Candra Wiguna Marcelino   (2008561048)
    - Maharani Putri Suari                  (2008561058)
    Jurusan/Kelas : Informatika/C

    Informasi Program:
    - Program merupakan program menentukan graph euler serta lintasan atau circuit euler dengan algoritma fleury.
    - Dibuat menggunakan sistem operasi Windows, akan ada beberapa syntax yang tidak jalan jika
      program di jalankan pada sistem operasi berbeda.
*/

#include <stdio.h>
#include <stdlib.h>

void title(){
    printf(".######.##.....######.##..##.#####..##..##.........####..##......####...####..#####..######.######.##..##.##...##.\n");
    printf(".##.....##.....##.....##..##.##..##..####.........##..##.##.....##.....##..##.##..##...##.....##...##..##.###.###.\n");
    printf(".####...##.....####...##..##.#####....##..........######.##.....##.###.##..##.#####....##.....##...######.##.#.##.\n");
    printf(".##.....##.....##.....##..##.##..##...##..........##..##.##.....##..##.##..##.##..##...##.....##...##..##.##...##.\n");
    printf(".##.....######.######..####..##..##...##..........##..##.######..####...####..##..##.######...##...##..##.##...##.\n");
    printf("..................................................................................................................\n\n");
}

void cetak(int n, int graph[][n]){
    printf("\nGraph :\n");
    for(int i = 0; i < n; i++){         //mencetak matriks
        for(int j = 0; j < n; j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void hitung_derajat(int vertex, int graph[][vertex], int derajat[]){
    int sum = 0;
    for(int i = 0; i < vertex; i++){
        for(int j = 0; j<vertex; j++){
            sum+=graph[i][j];
        }
        derajat[i] = sum;
        sum = 0;
    }
}

int cek_terhubung(int n, int graph[][n]){
    int jumlah = 0, func_graph[n][n];
    
    for(int i = 0; i<n; i++){           //menyalin isi graph untuk di proses
        for(int j = 0; j<n; j++){
            func_graph[i][j] = graph[i][j];
        }
    }

    for(int i = 1; i<n; i++){
        for(int j = 0; j<n; j++){
            if(func_graph[0][j] == 0 && func_graph [i][j] == 1){ 
                func_graph[0][j] = func_graph[i][j];
            }
        }
    }

    for(int i = 0 ; i<n; i++){          //menjumlahkan baris pertama matriks
    	jumlah+=func_graph[0][i];
	}
    if(jumlah == n) return 1;
    else return 0;
}

int isEularian(int vertex, int graph[][vertex], int derajat[]){
    //Mengecek apakah semua vertex terhubung
    if(cek_terhubung(vertex, graph) == 0)
        return 0;
    
    //Menghitung banyaknya vertex dengan derajat ganjil
    int ganjil = 0;
    for(int i = 0; i<vertex; i++)
        if(derajat[i] % 2 == 1) ganjil++;
    
    if(ganjil > 2)
        return 0;
    
    return (ganjil == 0)? 2:1;
}

int dfsCount(int vertex, int graph[][vertex], int prev, int visited[]){
    visited[prev] = 1;
    int count = 1;

    for(int i = 0; i<vertex; i++){
        if(graph[prev][i] == 1 && !visited[i]){
            count+= dfsCount(vertex, graph, i, visited);
        }
    }
    return count;
}

void removeEdge(int vertex, int graph[][vertex], int prev, int next){
    graph[prev][next] = graph[next][prev] = 0;
}

void addEdge(int vertex, int graph[][vertex], int prev, int next){
    graph[prev][next] = graph[next][prev] = 1;
}

int isValidNext(int vertex, int graph[][vertex], int prev, int next){
    int count = 0;
    int visited[vertex];
    for(int i = 0; i<vertex; i++){
        visited[i] = 0;
        if(graph[prev][i] == 1)
            count++;
    }

    if(count == 0)
        return 0;
    else if(count == 1)
        return 1;
    
    int count1 = dfsCount(vertex, graph, prev, visited);
    removeEdge(vertex, graph, prev, next);

    for(int i = 0; i<vertex; i++){
        visited[i] = 0;
    }

    int count2 = dfsCount(vertex, graph, prev, visited);
    addEdge(vertex, graph, prev, next);

    return (count1 > count2)? 0:1;
}

void find_jalan(int vertex, int graph [][vertex], int prev){
    for(int i = 0; i<vertex; i++){
        if(graph[prev][i] == 1 && isValidNext(vertex, graph, prev, i)){
            printf("%d - %d  ", prev + 1, i + 1);
            removeEdge(vertex, graph, prev, i);
            find_jalan(vertex, graph, i);
        }
    }
}

int main (){
    char ulang = 'y';
    int vertex, choose_now = 1, vertex_now = 0,sum = 0;

    do{
        system("cls");
        title();
        printf("Ketik banyaknya vertex: ");
        scanf("%d%*c", &vertex);

        int graph[vertex][vertex], derajat[vertex];

        //Input graph
        for(int i = 0; i<vertex; i++){
            for(int j = 0; j<vertex; j++){
                if(i != j){
                    printf("Jika vertex %d dan vertex %d berhubungan ketik 1, 0 jika tidak :", i+1, j+1);
                    scanf("%d%*c", &graph[i][j]);
                }else{
                    graph[i][j] = 0;
                }
            }
        }

        cetak(vertex, graph);

        //Menghitung derajat vertex
        hitung_derajat(vertex, graph, derajat);

        //Mengecek jenis graph dengan sifat-sifat yang ada
        int cek = isEularian(vertex, graph, derajat);
        if(cek == 0){
            printf("\nGraph merupakan graph non-euler\n");
        }else{ 
            if(cek == 1){
                printf("\nGraph merupakan graph semi-euler\n");
            }else{
                printf("\nGraph merupakan graph euler\n");
            }

            int start = 0;

            //Mencari vertex dengan derajat ganjil petama
            for(int i = 0; i<vertex; i++){
                if(derajat[i] % 2 == 1){
                    start = i; 
                    break;
                } 
            }

            printf("Edge yang dipilih : ");
            find_jalan(vertex, graph, start);
        }

        printf("\n\nApakah anda ingin mengulang (y/n) :");
        scanf("%c%*c", &ulang);
    }while(ulang == 'y' || ulang == 'Y');
    printf("\n\nAkhir dari program\n");
    return 0;
}