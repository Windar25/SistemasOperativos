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
    Fat12BootSector boot;
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
    return 0;
}