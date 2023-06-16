#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "AllStructs.h"
//#include "FATentry.h"


short cadCLustersLibres[1000];

void fAlmacenaEntradasFAT(short CadClusters [], int cant_clustersArch, Fat16BootSector boot, int fdD){

    short offset;
    short final = -1;
    for(int i = 0 ; i<cant_clustersArch; i++){
        offset = boot.reserved_sectors* boot.sector_size + CadClusters[i]*2;  //posicion en el cluster CadClusters[i]  de la FAT pero cada 12 bits--> 3/2 bytes
        lseek(fdD, offset, SEEK_SET);
        if( (i + 1) == cant_clustersArch) {
            write(fdD, &final , sizeof(short));
        }
        else write(fdD, &CadClusters[i+1], sizeof(short));  
    }

}


void f_AsignarClusters_para_Archivo( int fd, int fdD, Fat16BootSector boot, FatEntry entry){

    struct stat sb; //estructura para ver estado de archivo
    int cant_clustersArch, LimiteClusterArea, offsetFAT12,offset, numclustersLibres=0;
    short * ArrClustLibres, cluster, clusterContenido;

    if (fstat(fd, &sb) == -1) {  
        perror("stat");
        exit(1);
    }
    printf("File size: %lu bytes\n", sb.st_size); //tamano del archivo
    int cluster_size = boot.sector_size * boot.sectors_per_cluster;
    //printf("cluster_size %d, %d, %d", boot.sector_size, boot.sectors_per_cluster, cluster_size);
    cant_clustersArch = (sb.st_size + (cluster_size - 1))/cluster_size ;
    printf("tamano del un cluster en sectores %d \n", boot.sectors_per_cluster * boot.sector_size);
    printf("cantidad de clusters que necesita el archivo: %d \n", cant_clustersArch);

    // for(int i=0; i< (cant_clustersArch+ 1); i++){   
    //     cadCLustersLibres[i]=-1;
    // }   
   
    //ArrClustLibres = (short*)malloc(cant_clustersArch * sizeof(short));
    
    int sectoresHastaAreaData = (boot.root_dir_entries * sizeof(entry) / boot.sector_size) + boot.reserved_sectors + (boot.number_of_fats * boot.fat_size_sectors);
    int numclustersArea = (boot.total_sectors_file - sectoresHastaAreaData) / boot.sectors_per_cluster;
    LimiteClusterArea = 2 + numclustersArea -1 ;

    printf("Numero de clusters del area de datos: %d\n", numclustersArea);

    if(cant_clustersArch > numclustersArea) printf("Numero de clusters que necesita el archivo es mayor al los clusters del Area de datos.\n");
    cluster =2;
    int ini=0;
    while (1) {
        offset = (boot.reserved_sectors * boot.sector_size) + cluster*2;
        lseek(fdD, offset, SEEK_SET);
        read(fdD, &clusterContenido, sizeof(clusterContenido)); // escribo el nuevo numero de cluster
        if (numclustersLibres== cant_clustersArch || cluster>LimiteClusterArea ){ //salida para la busqueda de clusters
            if(numclustersLibres < cant_clustersArch){
                printf("El numero de cluster libres no alcanza para lo solicitado: %d\n", cant_clustersArch);
                exit(1);
            }  
            break;  
        }              
        if(clusterContenido==0){  
            numclustersLibres++; 
            printf("Numcluster[%d] clusterContenido:%d ",cluster, clusterContenido);                
            printf("numclustersLibres : %d\n", numclustersLibres);
            cadCLustersLibres[ini] = cluster;
            ini++;
            lseek(fdD, offset, SEEK_SET);
        } 
        cluster++;
    }
    printf("\ncadena: ");
    for(int i=0; i<cant_clustersArch;i++ ) printf( "%d ", cadCLustersLibres[i]);
   fAlmacenaEntradasFAT(cadCLustersLibres, cant_clustersArch, boot, fdD);
       
}


void f_escribirAreaDAtos(int fdA, int fdD, Fat16BootSector boot, FatEntry entry){

    
    //lseek(fdD, offset, SEEK_SET);


}

int main(int narg, char *argv[])
{
    Fat16BootSector boot;
    FatEntry entry;
    int fdA, fdD;

    if (narg != 3){
        printf("Usage: %s <name image disc> < nombre del archivo>\n ", argv[0]);
        exit(1);
    }
    if ((fdA = open(argv[2], O_RDONLY)) < 0) perror("No pudo abrir el archivo");

    if ((fdD = open(argv[1], O_RDONLY)) < 0){
        perror("No pudo abrir imagen de disco"); }

    if (read(fdD, &boot, sizeof(boot)) < 0){
        perror("NO pudo leer imagen de disco");
    }

    f_AsignarClusters_para_Archivo(fdA,fdD, boot, entry);
    f_escribirAreaDAtos(fdA, fdD, boot,entry );

    close(fdA);
    close(fdD);
    return 0;
}
