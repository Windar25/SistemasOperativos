/******structfat.h******/

typedef struct{
    unsigned char jmp[3];
    char oem[8];
    unsigned short sector_size;
    unsigned char sectors_per_cluster;
    unsigned short reserved_sectors;
    unsigned char number_of_fats;
    unsigned short root_dir_entries;
    unsigned short total_sectors_short;
    unsigned char media_descriptor;
    unsigned short fat_size_sectors;
    unsigned short sectors_per_track;
    unsigned short number_of_heads;
    unsigned int hidden_sectors;
    unsigned int total_sectors;
    unsigned int sector_per_FAT;
    unsigned short mirror_flags;
    unsigned short filesystem_version;
    unsigned int first_cluster;
    unsigned short filesystem_information;
    unsigned short backup_boot_sector;
    unsigned char reserved[12];
    unsigned char drive_number;
    unsigned char reserved_current_head;
    unsigned char extended_signature;
    unsigned int serial_number_partition;
    char volume_label[11];
    char filesystem_type[8];
}__attribute((packed)) Fat32BootSector;