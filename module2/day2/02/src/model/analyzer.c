#include "model/analyzer.h"

#include <stdio.h>
#include <stdlib.h>


uint32_t ip_to_int(const char *ip) {
    if (ip == NULL) {
        fprintf(stderr, "Invalid IP address: NULL\n");
        exit(EXIT_FAILURE);
    }

    uint32_t result = 0;
    int octet = 0;
    const char *start = ip;

    for (int i = 0; i < 4; i++) {
        char *end;
        octet = strtol(start, &end, 10);

        if (octet < 0 || octet > 255) {
            fprintf(stderr, "Invalid IP address: %s\n", ip);
            exit(EXIT_FAILURE);
        }

        result = (result << 8) | octet;

        if (i < 3) {
            if (*end != '.') {
                fprintf(stderr, "Invalid IP address: %s\n", ip);
                exit(EXIT_FAILURE);
            }

            start = end + 1;
        }
    }

    return result;
}

int is_ip_in_subnet(uint32_t ip, uint32_t subnet, uint32_t mask) {
    return (ip & mask) == (subnet & mask);
}

uint32_t generate_random_ip() {
    return (rand() % 256) << 24 | (rand() % 256) << 16 | (rand() % 256) << 8 | rand() % 256;
}
