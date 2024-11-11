#include "model/analyzer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int parse_args(int argc, char *argv[], uint32_t *gateway, uint32_t *mask, int *packets_count);

int main(int argc, char *argv[]) {
    // Входные аргументы
    uint32_t gateway, mask;
    int packets_count = 0;

    if (parse_args(argc, argv, &gateway, &mask, &packets_count) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    srand((unsigned)time(NULL));


    int in_subnet_count = 0;

    for (int i = 0; i < packets_count; i++) {
        uint32_t random_ip = generate_random_ip();

        if (is_ip_in_subnet(random_ip, gateway, mask)) {
            in_subnet_count++;
        }
    }


    printf("Total packets: %d\n", packets_count);
    printf("In subnet: %d (%.2f%%)\n", in_subnet_count, (in_subnet_count * 100.0) / packets_count);

    return 0;
}


int parse_args(int argc, char *argv[], uint32_t *gateway, uint32_t *mask, int *packets_count) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <gateway IP> <subnet mask> <packets_count>\n", argv[0]);
        return 1;
    }

    *gateway = ip_to_int(argv[1]);
    *mask = ip_to_int(argv[2]);
    *packets_count = atoi(argv[3]);

    if (*packets_count <= 0) {
        fprintf(stderr, "Invalid packets count: %s\n", argv[3]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
