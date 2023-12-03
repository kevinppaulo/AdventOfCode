#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WRITTEN_IN_FULL_NUBERS 9

int8_t get_calibration_values(const char *s);
uint8_t contains_number_spelled(const char *s);

int main(int argc, char *argv[]) {
    FILE *file_ptr;
    char filename[] = "day_1.txt";
    char buffer[100];

    file_ptr = fopen(filename, "r");
    if(file_ptr == NULL) {
        printf("Unable to open input file");
        return EXIT_FAILURE;
    }

    uint64_t sum = 0;
    while (fgets(buffer, sizeof(buffer), file_ptr) != NULL)  {
        sum += get_calibration_values(buffer);
    }

    printf("Sum of calibration values: %ld\n", sum);

    return EXIT_SUCCESS;
}

int8_t get_calibration_values(const char *s) {
    const char *head = s;
    int8_t first = -1, last = -1;

    while (*head != '\0') {
        if(isdigit(*head)) {
            if (first < 0) {
                first = (int8_t) *head - '0';
            } else {
                last = (int8_t) *head - '0';
            }
        } else {

            uint8_t found_number = contains_number_spelled(head);
            if (found_number > 0) {
                if (first < 0) {
                    first = found_number;
                } else {
                    last = found_number;
                }
            }

        }
        head += sizeof(char);
    }

    if (last < 0) last = first;
    return first * 10 + last;
}

uint8_t contains_number_spelled(const char *s) {
    const char *spelled_numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    uint8_t offset = 0;
    
    for (uint8_t i = 0; i < WRITTEN_IN_FULL_NUBERS; i++) {
        const char *written_number = spelled_numbers[i];
        const char *head = s;
        bool match = true;

        while (match && *written_number != '\0' && *head != '\0') {
            if (*written_number != *head) {
                match = false;
            }
            written_number++;
            head++;
        }

        if(match == true){
            printf("Found number %d in string %s", i+1, s);
            return i + 1;
        } 
    }

    return 0;
}
