#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structfat12.h"
#include "structfat16.h"
#include "structfat32.h"

#define RESERVED_SECTOR_BYTE 14
#define RESERVED_SECTOR_SIZE 2

#define SYSTEM_TYPE_BYTE 54
#define SYSTEM_TYPE_SIZE 9

void leeImprimeFAT12(int fd);
void leeImprimeFAT16(int fd);
void leeImprimeFAT32(int fd);
void readingImage(int arg,char **argv);

int main(int arg,char **argv){

    void readingImage(arg,argv);
    
    return 0;
}

void leeImprimeFAT12(int fd){
    Fat12BootSector boot;
    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }
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
    close(fd);
}

void leeImprimeFAT16(int fd){
    Fat16BootSector boot;
    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }

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
    printf("bootstrap: %.448s\n",boot.bootstrap);
    printf("signature: %x \n",boot.signature);
    close(fd);
}

void leeImprimeFAT32(int fd){
    Fat32BootSector boot;

    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }

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
    printf("first_cluster: %x\n",boot.first_cluster);
    printf("filesystem_information: %x\n",boot.filesystem_information);
    printf("backup_boot_sector: %x\n",boot.backup_boot_sector);
    printf("reserved: %.12s\n",boot.reserved);
    printf("drive_number: %x\n",boot.drive_number);
    printf("reserved_current_head: %x\n",boot.reserved_current_head);
    printf("extended_signature: %x\n",boot.extended_signature);
    printf("serial_number_partition: %d\n",boot.serial_number_partition);
    printf("volume_label: %.11s\n",boot.volume_label);
    printf("filesystem_type: %.8s\n",boot.filesystem_type);

    close(fd);
}

void readingImage(int arg,char **argv){
    Fat12BootSector boot;
    int fd;

    if(arg!=2){
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
        typeFat = atoi(type);
        //printf("%d\n",typeFat,type);
        lseek(fd,0,SEEK_SET);
        if(typeFat==12){
            printf("La imagen ingresada corresponde a un sistema de archivos [FAT12]\n\n");
            leeImprimeFAT12(fd);
        }else{
            printf("La imagen ingresada corresponde a un sistema de archivos [FAT16]\n\n");
            leeImprimeFAT16(fd);
        }
    }else{
        typeFat=32;
        lseek(fd,0,SEEK_SET);
        printf("La imagen ingresada corresponde a un sistema de archivos [FAT32]\n\n");
        leeImprimeFAT32(fd);
    }
    close(fd);
}