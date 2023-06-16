    #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structfat.h"

#define     SIZE_BLOCK 512
#define     OFFSET      19

#define RESERVED_SECTOR_BYTE 14
#define RESERVED_SECTOR_SIZE 2

#define SYSTEM_TYPE_BYTE 54
#define SYSTEM_TYPE_SIZE 9

unsigned int FAT_posicion;
unsigned int root_posicion;
unsigned int cluster2_sector;
unsigned int total_sectors;
unsigned int sectors_per_cluster;

Fat32BootSector boot32;
Fat16BootSector boot16;
Fat12BootSector boot12;


void leeImprimeFAT12(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries);
void leeImprimeFAT16(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries);
void leeImprimeFAT32(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries);

void imprimeFAT32(Fat32BootSector boot);
void imprimeFAT16(Fat16BootSector boot);
void imprimeFAT12(Fat12BootSector boot);

void obtiene_offset_sizeblock_num_fat(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *num_fat,
                                            int arg,char **argv,unsigned int *leftEntries);


void buscaCluster(int fd,int arg,char **argv){
    int cluster_address,n_cluster,sector,numClusters,offset;
    short cluster,cluster_anterior;
    

    cluster=(short)atoi(argv[2]);

    //sector inicial del cluster
    cluster2_sector = (root_posicion + boot12.root_dir_entries*sizeof(FatEntry))/boot12.sector_size;
    //cluster2_sector=1256;
    printf("\nCluster2 sector %d   y cluster: %d\n",cluster2_sector,cluster);
    printf("Root position: %d\n",root_posicion);
    printf("Root entries:   %d\n",boot12.root_dir_entries);
    printf("Size Entry   %d\n",sizeof(FatEntry));
    sector = (cluster-2)*boot12.sectors_per_cluster + cluster2_sector;

    numClusters = (boot12.total_sectors_short-cluster2_sector)/boot12.sectors_per_cluster;
    printf("Numero de clusters en la data area   %d\n",numClusters);
    //lseek(fd,sector*boot12.sector_size,SEEK_SET);
    //read(fd,&cluster,sizeof(cluster));
    printf("\n");
    if(cluster>=numClusters+2||cluster<2){
        printf("Se excedió el valor del cluster\n");
        exit(1);
    }else{
        cluster_anterior=cluster;
        offset=root_posicion + cluster*2;
        lseek( fd, offset, SEEK_SET );
        read(fd,&cluster,sizeof(cluster));
        if(cluster == 0) printf("El cluster %d no esta ocupado\n", cluster_anterior);
        else  printf("El cluster %d esta ocupado \n", cluster_anterior);
    }
    //if(cluster==-1)break;
    //printf("Cluster encontrado: %d \n",cluster);
}

void getQuantityClusters(int *copy_clusters){
    
}

int main(int arg,char **argv){

    FatEntry entry;
    unsigned int i,dataAreaPointer,fd,offset,size_block,num_fat,leftEntries,dp_pointer,current,num_clusters;
    short cluster;
    int copy_clusters;


    if(arg!=3){
        printf("Usage; %s <name image disc>\n",argv[0]);
        exit(1);
    }

    if((fd=open(argv[1],O_RDONLY))<0){
        perror("No pudo abrir imagen de disco");
    }
    
    Fat16BootSector boot16;
    if (read(fd, &boot16, sizeof(boot16)) < 0)
        perror("NO pudo leer imagen de disco");
    
    getQuantityClusters(&copy_clusters);

    close(fd); 

    return 0;
}

void obtiene_offset_sizeblock_num_fat(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *num_fat,int arg,char **argv,unsigned int *leftEntries)
{

    if(arg!=3){
        printf("Usage; %s <name image disc>\n",argv[0]);
        exit(1);
    }

    if((fd=open(argv[1],O_RDONLY))<0){
        perror("No pudo abrir imagen de disco");
    }

    unsigned short reserved_sectors;
    lseek(fd,RESERVED_SECTOR_BYTE,SEEK_SET);
    if(read(fd,&reserved_sectors,RESERVED_SECTOR_SIZE)<0){
        perror("No pudo leer imagen de disco");
    }

    int typeFat;

    if(reserved_sectors==1){
        char *type=(char *)malloc(SYSTEM_TYPE_SIZE);
        type[8]=0;
        lseek(fd,SYSTEM_TYPE_BYTE,SEEK_SET);
        if(read(fd,type,SYSTEM_TYPE_SIZE)<0){
            perror("No pudo leer imagen de disco");
        }
        type+=3;
        *num_fat = atoi(type);
        lseek(fd,0,SEEK_SET);
        if(*num_fat==12){
            printf("La imagen ingresada corresponde a un sistema de archivos [FAT12]\n\n");
            leeImprimeFAT12(fd,offset,size_block,leftEntries);
        }else{
            printf("La imagen ingresada corresponde a un sistema de archivos [FAT16]\n\n");
            leeImprimeFAT16(fd,offset,size_block,leftEntries);
        }
    }else{
        *num_fat=32;
        lseek(fd,0,SEEK_SET);
        printf("La imagen ingresada corresponde a un sistema de archivos [FAT32]\n\n");
        leeImprimeFAT32(fd,offset,size_block,leftEntries);
    }
    return;
}


void leeImprimeFAT12(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries){
    if(read(fd,&boot12,sizeof(boot12))<0){
        perror("No pudo leer imagen de disco");
    }
    //printf("Reserved: %3d Fat size sectors: %d  number_of_fat: %d\n",
    //boot.reserved_sectors , boot.fat_size_sectors,boot.number_of_fats);
    FAT_posicion = boot12.reserved_sectors*(boot12.sector_size);
    *offset = boot12.reserved_sectors+boot12.number_of_fats*boot12.fat_size_sectors;
    *size_block=boot12.sector_size;
    *leftEntries = boot12.root_dir_entries;
    root_posicion = (*offset) * (*size_block);
    total_sectors = boot12.total_sectors_short;
    sectors_per_cluster = boot12.sectors_per_cluster;
    imprimeFAT12(boot12);
}

void imprimeFAT12(Fat12BootSector boot){
    printf("Jump code: %x:%x:%x\n",boot.jmp[0],boot.jmp[1],boot.jmp[2]);
    printf("OEM code: %s\n",boot.oem);
    printf("sector_size: %d \n",boot.sector_size);
    printf("sectors_per_clusters: %d\n",boot.sectors_per_cluster);
    printf("reserved_sectors: %d\n",boot.reserved_sectors);
    printf("number_of_fats: %d\n",boot.number_of_fats);
    printf("root_dir_entries: %d\n",boot.root_dir_entries);
    printf("total_sector_short: %d\n",boot.total_sectors_short);
    printf("media_descriptor: %d\n",boot.media_descriptor);
    printf("fat_size_sectors: %d\n",boot.fat_size_sectors);
    printf("sectors_per_track: %d\n",boot.sectors_per_track);
    printf("number_of_heads: %d\n",boot.number_of_heads);
    printf("hidden_sectors: %d\n",boot.hidden_sectors);
    printf("boot_sector_signature: %x\n",boot.boot_sector_signature);
}

void leeImprimeFAT16(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries){
    Fat16BootSector boot;

    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }

    printf("Reserved: %3d Fat size sectors: %d  number_of_fat: %d\n",
    boot.reserved_sectors , boot.fat_size_sectors,boot.number_of_fats);
    *offset = boot.reserved_sectors + boot.fat_size_sectors*boot.number_of_fats;
    *size_block = boot.sector_size;
    *leftEntries = boot.root_dir_entries;
    //imprimeFAT16(boot);
        printf("Pos actual: %d\n",lseek(fd,0,SEEK_CUR));
    
}

void imprimeFAT16(Fat16BootSector boot){
    printf("Jump code: %x:%x:%x\n",boot.jmp[0],boot.jmp[1],boot.jmp[2]);
    printf("OEM code: %s\n",boot.oem);
    printf("sector_size: %d \n",boot.sector_size);
    printf("sectors_per_clusters: %d\n",boot.sectors_per_cluster);
    printf("reserved_sectors: %d\n",boot.reserved_sectors);
    printf("number_of_fats: %d\n",boot.number_of_fats);
    printf("root_dir_entries: %d\n",boot.root_dir_entries);
    printf("total_sector_short: %d\n",boot.total_sectors_short);
    printf("media_descriptor: %d\n",boot.media_descriptor);
    printf("fat_size_sectors: %d\n",boot.fat_size_sectors);
    printf("sectors_per_track: %d\n",boot.sectors_per_track);
    printf("number_of_heads: %d\n",boot.number_of_heads);
    printf("hidden_sectors: %d\n",boot.hidden_sectors);
    printf("total_sectors: %d\n",boot.total_sectors);
    printf("logicalDriveNumber: %x\n",boot.logicalDriveNumber);
    printf("reserved: %x\n",boot.reserved);
    printf("extendedSignature: %x\n",boot.extended_signature);
    printf("serial_number_partition: %x\n",boot.serial_number);
    printf("volumeLabel: %.11s",boot.volume_label);
    printf("file_system_type: %.8s\n",boot.file_system_type);
    //printf("bootstrap: %.448s\n",boot.bootstrap);
    printf("signature: %x \n",boot.signature);
}

void leeImprimeFAT32(unsigned int fd,unsigned int *offset,unsigned int *size_block,unsigned int *leftEntries){
    Fat32BootSector boot;

    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }
    *size_block=boot.sector_size;
    *offset =   boot.reserved_sectors+
                boot.sector_per_FAT*boot.number_of_fats;
                boot.first_cluster_root_directory*boot.sectors_per_cluster;
    (*leftEntries) = boot.total_sectors - *offset; 

    //printf("Left entries: %d\nOffset: %d\nTotal_sectors: %d\n",*offset,*leftEntries,boot.total_sectors);           
    //printf("Reserved: %3d sector_per_FAT: %d  number_of_fat: %d\n",
    //    boot.reserved_sectors , boot.sector_per_FAT,boot.number_of_fats);
    //printf("first_cluster_root_directory: %3d\nsectors_per_cluster: %d\nsize_block: %d\n\n",
    //    boot.first_cluster_root_directory , boot.sectors_per_cluster,boot.sector_size);
    imprimeFAT32(boot);


}

void imprimeFAT32(Fat32BootSector boot){
    printf("root_dir_entries: %d\n",boot.root_dir_entries);
    printf("Jump code: %x:%x:%x\n",boot.jmp[0],boot.jmp[1],boot.jmp[2]);
    printf("OEM code: %s\n",boot.oem);
    printf("sector_size: %d \n",boot.sector_size);
    printf("sectors_per_clusters: %d\n",boot.sectors_per_cluster);
    printf("reserved_sectors: %d\n",boot.reserved_sectors);
    printf("number_of_fats: %d\n",boot.number_of_fats);
    printf("root_dir_entries: %d\n",boot.root_dir_entries);
    printf("total_sector_short: %d\n",boot.total_sectors_short);
    printf("media_descriptor: %d\n",boot.media_descriptor);
    printf("fat_size_sectors: %d\n",boot.fat_size_sectors);
    printf("sectors_per_track: %d\n",boot.sectors_per_track);
    printf("number_of_heads: %d\n",boot.number_of_heads);
    printf("hidden_sectors: %d\n",boot.hidden_sectors);
    printf("total_sectors: %d\n",boot.total_sectors);
    printf("logicalDriveNumber: %x\n",boot.sector_per_FAT);
    printf("reserved: %x\n",boot.mirror_flags);
    printf("extendedSignature: %x\n",boot.filesystem_version);
    printf("filesystem_information: %x\n",boot.filesystem_information);
    printf("backup_boot_sector: %x\n",boot.backup_boot_sector);
    printf("reserved: %.12s\n",boot.reserved);
    printf("drive_number: %x\n",boot.drive_number);
    printf("reserved_current_head: %x\n",boot.reserved_current_head);
    printf("extended_signature: %x\n",boot.extended_signature);
    printf("serial_number_partition: %d\n",boot.serial_number_partition);
    printf("volume_label: %.11s\n",boot.volume_label); 
    printf("filesystem_type: %.8s\n\n",boot.filesystem_type);
}
