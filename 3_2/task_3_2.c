#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int32_t ipToUint32(const char *ip){ 
    uint32_t res = 0;
    uint8_t octet;
    char *ip_copy = strdup(ip);
    char *token = strtok(ip_copy, ".");
    for (int i = 0; i < 4; ++i){
        if (token != NULL){
            octet = (uint8_t)atoi(token);
            res = (res << 8) | octet;
            token = strtok(NULL, ".");
        }
    }
    return res;
}

int isInSubnet(uint32_t ip, uint32_t subnet, uint32_t mask){
    return (ip & mask) == (subnet & mask);
}

void printIp(uint32_t ip){
    printf("%u.%u.%u.%u\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int main(){
    char subnet_ip[20];
    char mask[20];
    int N;

    printf("Введи адрес шлюза: \n");
    scanf("%s", subnet_ip);

    printf("Введи маску: \n");
    scanf("%s", mask);

    printf("Введи N: \n");
    scanf("%d", &N);

    uint32_t subnet_ip_int = ipToUint32(subnet_ip);
    uint32_t mask_int = ipToUint32(mask);

    srand(time(NULL));

    int in_subnet = 0;

    for (int i = 1; i<= N; i++){
        uint32_t random_ip = ((uint32_t)rand()<<16) | ((uint32_t)rand());
        //printIp(random_ip);
        if(isInSubnet(random_ip, subnet_ip_int, mask_int)){
            in_subnet++;
        }
    }
    printf("Шлюз = ");
    printIp(subnet_ip_int);
    printf("Маска = ");
    printIp(mask_int);
    printf("Ip = %u\n", subnet_ip_int);
    printf("\nВ сети = %d (%.2f%%)", in_subnet, (in_subnet/(float)N)*100);

    return 0;
}