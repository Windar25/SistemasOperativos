#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structfat.h"


int main(int arg,char **argv){
    Fat32BootSector boot;
    int fd;

    if(arg!=2){
        printf("Usage; %s <name image disc>\n",argv[0]);
        exit(1);
    }

    if((fd=open(argv[1],O_RDONLY))<0){
        perror("No pudo abrir imagen de disco");
    }

    if(read(fd,&boot,sizeof(boot))<0){
        perror("No pudo leer imagen de disco");
    }

    boot.volume_label[10]=0;
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

    //idea, leer primeros 27 bytes, luego verificar a cual corresponde y escribir bits restantes en el respectivo bootSector
    //moverse con el seek al number of reserved sectors y diferenciar si es FAT 32 o es FAT 12 o 16, en caso sea 32,
    //volvemos al inicio y leemos todo en la estructura del FAT32, en caso sea 12 o 16, nos movemos al byte 54 y leemos la cadena correspondiente 
    //para saber que fat es, luego hacemos el seek y volvemos al inicio para leer el que corresponde
    return 0;
}