#include <stdio.h>
#include <stdlib.h>

void header (){
    puts(" _____                              _____             _   ");
    puts("|  _  |___ ___ ___ ___ ___ _____   |   __|___ ___ ___| |_ ");
    puts("|   __|  _| . | . |  _| .'|     |  |  |  |  _| .'| . |   |");
    puts("|__|  |_| |___|_  |_| |__,|_|_|_|  |_____|_| |__,|  _|_|_|");
    puts("              |___|                              |_|      ");
}

void menu(){
    printf("\nMenu :\n");
    printf("1. Apakah merupakan graph terhubung?\n2. Apakah merupakan graph berarah?\n3. Menghitung derajat vertex\n4. Mencari lintasan\n5. Input ulang graph\n6. Selesai\n");
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

int cek_pilih(){
    int pilih;
    printf("Ketik Pilihan :");
    scanf("%d%*c", &pilih);
    return pilih;
}

//fungsi 1
void cek_terhubung(int n, int graph[][n]){
    int jumlah = 0, func_graph[n][n];
    
    for(int i = 0; i<n; i++){           //menyalin isi graph untuk di proses
        for(int j = 0; j<n; j++){
            func_graph[i][j] = graph[i][j];
        }
    }

    for(int i = 1; i<n; i++){
        for(int j = 0; j<n; j++){
            if(func_graph[0][j] == 0 && func_graph [i][j] >= 1){ 
                func_graph[0][j] = func_graph[i][j];
            }
        }
    }

    for(int i = 0 ; i<n; i++){          //menjumlahkan baris pertama matriks
    	jumlah+=func_graph[0][i];
	}
    if(jumlah >= n) printf("Graph terhubung\n");
    else printf("Graph tidak terhubung\n");
}

//fungsi 2
int cek_berarah(int n, int graph[][n]){
    for(int i = 0; i < n; i++){         //menentukan apakah matriks simetris atau tidak
        for(int j = 0; j < n; j++){
            if(graph[i][j] != graph[j][i]) return 1; 
        }
    }
    return 0;
}

//fungsi 3
void hitung_derajat (int n, int graph [][n], int berarah){
    int titik;        

    //menentukan vertex yang derajatnya ingin dicari
    label_input_vertex:
    printf("\nVertex ke :");
    scanf("%d%*c", &titik);
    if(titik < 0 || titik > n){
        printf("Input salah, vertex tidak ditemukan");
        goto label_input_vertex;
    }

    if(berarah == 1){               //menentukan derajat vertex
        int derajat_masuk = 0, derajat_keluar = 0;

        for(int j = 0; j<n; j++){
            derajat_keluar += graph[titik-1][j];
            derajat_masuk += graph[j][titik-1];
        }
        printf("Derajat masuk dari vertex %d = %d\n", titik, derajat_masuk);
        printf("Derajat keluar dari vertex %d = %d\n", titik, derajat_keluar);
    }else{
        int derajat = 0;
        for(int j = 0; j<n; j++){
            derajat += graph[titik-1][j];
        }
        printf("Derajat dari vertex %d = %d\n", titik, derajat);
    }
}

//fungsi 4
void lintasan (int n, int graph [][n]){
    int awal, akhir, tampung[n], index_tampung = 1;

    printf("Pilih Lintasan Vertex\n");
    printf("vertex awal :");
    scanf("%d", &awal); 
    printf("vertex akhir :");
    scanf("%d%*c", &akhir); 

    tampung[0] = akhir;

    awal--;
    akhir--;

    for(int i = 0; i<n; i++){       //mencari lintasan
        if(graph[i][akhir] == 1){
            akhir = i;
            tampung[index_tampung] = i+1;
            index_tampung++;
            i = -1;   
        }

        if(akhir == awal){
            break;
        }
    }

    printf("Lintasan : ");      //mencetak lintasan yang didapat dengan kondisi reverse
    if(akhir == awal){
        for(int i = index_tampung - 1; i>= 0; i--){
            if(i == 0){
                printf(" %d\n", tampung[i]);
            }else{
                printf(" %d -", tampung[i]);
            }
        }
    }else{
        printf("(Tidak ada jalan)\n");
    }
}

int main (){
    int baris, kolom, pilih, berarah;
    char ulang;
    
    label_awal :
    system("cls");
    header();

    printf("\nInput banyak vertex :");
    scanf("%d", &baris);
    kolom = baris;

    int graph[baris][kolom];

    //input graph
    for(int i = 0; i<baris; i++){
        for(int j = 0; j<baris; j++){
            if(i != j){
                printf("Jika vertex %d dan vertex %d berhubungan ketik 1, 0 jika tidak :", i+1, j+1);
                scanf("%d", &graph[i][j]);
            }else{
                graph[i][j] = 0;
            }
        }
    }

    //cetak graph
    cetak(baris, graph);

    //menentukan pilihan menu
    menu();
    pilih = cek_pilih();

    while(pilih != 6){
        if(pilih == 1){
            cek_terhubung(baris, graph);
        }else if(pilih == 2){
            berarah = cek_berarah(baris, graph);
            if(berarah == 1) printf("Graph berarah\n");
            else printf("Graph tidak berarah\n");
        }else if(pilih == 3){
            hitung_derajat(baris, graph, cek_berarah(baris, graph));
        }else if(pilih == 4){
            lintasan(baris, graph);
        }else if(pilih == 5){
            goto label_awal;
        }else{
            system("cls");
            header();
            cetak(baris, graph);
            menu();
            printf("\nPilihan tidak tersedia\n");
        }

        //mengecek apakah program ingin di ulang
        label_cek_ulang :
        printf("Apakah anda ingin mengulang (y/n):");
        scanf("%c%*c", &ulang);

        if(ulang == 'y' || ulang == 'Y'){
            system("cls");
            header();
            cetak(baris, graph);
            menu();
            pilih = cek_pilih();
        }
        else if (ulang == 'n' || ulang == 'N') break;
        else{
            printf("Inputan salah\n");
            goto label_cek_ulang;
        }
    }
    printf("\nAkhir dari program\n");
    return 0;
}