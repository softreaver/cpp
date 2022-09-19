#include <stdio.h>
#include <stdint.h>
#include <errno.h>

typedef struct DataLine {
    char bytes[4];
} DataLine;

typedef struct RawData {
    DataLine lines[32];
} RawData;

int __splitPath__(char* path, char dest[100][100]);

void bin(unsigned n) 
{ 
    unsigned i; 
    for (i = 1 << 31; i > 0; i = i / 2) 
        (n & i)? printf("1"): printf("0"); 
} 

#define INC 4

DataLine _intToRaw(uint32_t val) {
    DataLine raw;
    uint32_t data_size = sizeof(val);
    if (data_size > 8) {
        printf("Attention la donnee ne rentre pas sur une ligne de bloc. Elle sera tronquee");
        data_size = 8;
    }
    for (int i = 0; i < data_size; ++i) {
        raw.bytes[i] = (val >> ((data_size - 1 - i) * 8)) & 0xFF;
    }
    return raw;
}

uint32_t _rawToInt(const DataLine* raw) {
    int val = 0x00;
    int data_size = sizeof(val);
    if (data_size > 8) {
        printf("Attention la donnee ne rentre pas sur une ligne de bloc. Elle sera tronquee");
        data_size = 8;
    }
    for (int i = 0; i < data_size; ++i) {
        val |= (raw->bytes[i] << (data_size - 1 - i) * 8);
    }
    return val;
}

int main() {
    int64_t addr = 500, addr2 = 500;
    while (addr == addr2) {
        addr++;
        printf("==> avant = %ld\n", addr);
        bin(addr);
        printf("\n\n");

        RawData raw;
        int64_t p1 = (addr >> 32);
        int64_t p2 = addr;
        raw.lines[10] = _intToRaw((uint32_t)p1);
        raw.lines[11] = _intToRaw((uint32_t)p2);
        int shift = 56;

        shift = 56;
        addr2 = 0x00;
        for (int i = 0; i < 4; i++) {
            addr2 |= (raw.lines[10].bytes[i] << shift);
            shift -= 8;
        }
        for (int i = 0; i < 3; i++) {
            addr2 |= (raw.lines[11].bytes[i] << shift);
            shift -= 8;
        }
        addr2 |= (0x00000000000000FF & raw.lines[11].bytes[3]);

        printf("==> apres = %ld\n", addr2);
        bin(addr2);
        printf("\n\n");
    }

    return 0;
}

int __splitPath__(char* path, char dest[100][100]) {
    int index = 0, dest_index = 0, cur_index = 0, wrote = 0, count = 0;
    char c;
    while ((c = path[index]) && index + 1 < 100) {
        if (c != '/') {
            dest[dest_index][cur_index] = c;
            wrote = 1;
            cur_index++;
        } else {
            if (wrote) {
                dest[dest_index][cur_index] = '\0';
                dest_index++;
                if (cur_index > 0) count++;
                cur_index = 0;
                wrote = 0;
            }
        }
        index++;
    }
    dest[dest_index][cur_index] = '\0';

    return (wrote)? ++count : count;
}
