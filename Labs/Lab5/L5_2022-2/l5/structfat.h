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
    unsigned short hidden_sectors;
    char boot_code[480];
    unsigned short boot_sector_signature;
}__attribute((packed)) Fat12BootSector;

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
    unsigned char logicalDriveNumber;
    unsigned char reserved;
    unsigned char extended_signature;
    unsigned int serial_number;
    char volume_label[11];
    char  file_system_type[8];
    char bootstrap[448];
    unsigned short signature;
}__attribute((packed)) Fat16BootSector;


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
    unsigned int first_cluster_root_directory;
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


typedef struct{
    unsigned char filename[8];
    unsigned char ext[3];
    unsigned char atributes;
    unsigned char reserved[10];
    unsigned short modify_time;
    unsigned short modify_date;
    unsigned short starting_cluster;
    unsigned int file_size;
}__attribute((packed)) FatEntry;