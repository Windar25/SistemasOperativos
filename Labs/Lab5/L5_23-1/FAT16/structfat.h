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
    unsigned char logicalDriveNumber;
    unsigned char reserved;
    unsigned char extended_signature;
    unsigned int serial_number;
    char volume_label[11];
    char  file_system_type[8];
    char bootstrap[448];
    unsigned short signature;
}__attribute((packed)) Fat16BootSector;