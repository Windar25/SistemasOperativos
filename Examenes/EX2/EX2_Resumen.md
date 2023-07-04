# Algoritmos de asignacion de memoria
- First Fit
- Next Fit
- Best Fit
- Worst Fit
- Quick Fit

# File Systems

|    File System     | FAT 12 | FAT 16 | FAT 32 | EXT2  |  EXT4  |
| :----------------: | :----: | :----: | :----: | :---: | :----: |
|   Tamaño Cluster   |   a    |   a    |   a    |   a   |   a    |
| Max tamaño archivo | 4GB-1  | 4GB-1  | 4GB-1  |   a   | a  aaa |




| File System             |    FAT 12    |    FAT 16    |    FAT 32    |
| :---------------------- | :----------: | :----------: | :----------: |
| 0x0000000               | Free cluster | Free cluster | Free cluster |
| 0x00000001              |  reservado   |  reservado   |  no se usa   |
| 0x00000002 - 0x0FFFFFEF | Next cluster | Next cluster | Next cluster |
| 0x0FFFFFF0 - 0x0FFFFFF6 | Non appears  | Non appears  | Non appears  |
| 0x0FFFFFF7              | Bad cluster  | Bad cluster  | Bad cluster  |
| 0x0FFFFFF7              | Bad cluster  | Bad cluster  | Bad cluster  |
| 0x0FFFFFF7              | Bad cluster  | Bad cluster  | Bad cluster  |
| 0x0FFFFFF8 - 0x0FFFFFFF |     EOF      |     EOF      |     EOF      |
| 0x00000007              |  Only NTFS   |  Only NTFS   |  Only NTFS   |




# Directory Entry

| Attribute        | Bytes | Description                                                                                                                                 |
| ---------------- | ----- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| File name        | 0-10  | File name (8 bytes) with extension (3 bytes)                                                                                                |
| Attribute        | 11    | Bitvector. Bit 0: read-only. Bit 1: hidden. Bit 2: system file. Bit 3: volume label. Bit 4: subdirectory. Bit 5: archive. Bits 6-7: unused. |
| Reserved         | 12-21 | Reserved for future use                                                                                                                     |
| Time             | 22-23 | Time (5/6/5 bits, for hour/minutes/double seconds)                                                                                          |
| Date             | 24-25 | Date (7/4/5 bits, for year-since-1980/month/day)                                                                                            |
| Starting cluster | 26-27 | Starting cluster (0 for an empty file)                                                                                                      |
| File size        | 28-31 | File size in bytes                                                                                                                          |

