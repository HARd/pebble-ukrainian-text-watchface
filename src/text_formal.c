#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "text_formal.h"


void append_string(char* output, const char* string, bool add_space) {
    strcat(output, string);
    if (add_space) {
        strcat(output, " ");
    }
}

void strip_trailing_space(char* buffer) {
    size_t buffer_length = strlen(buffer);
    buffer[buffer_length - 1] = '\0';
    buffer[buffer_length] = 0;
}

void say_formal(char* hours_buffer, char* minutes_buffer, int hours, int minutes) {
    memset(hours_buffer, 0, TIME_BUFFER_SIZE / 2);
    memset(minutes_buffer, 0, TIME_BUFFER_SIZE);

    hours = hours % 12;
    append_string(hours_buffer, HOURS_NOMINATIVE[hours], true);

    if (minutes <= 9) {
        append_string(minutes_buffer, MINUTES_NOMINATIVE_ONES[0], true);
        append_string(minutes_buffer, MINUTES_NOMINATIVE_ONES[minutes], true);
    } else {
        if (minutes > 9 && minutes < 20) {
            minutes = minutes % 10;
            append_string(minutes_buffer, MINUTES_NOMINATIVE_TEENS[minutes], true);
        }
        else {
            int minutes_ones = minutes % 10;
            int minutes_tens = (minutes - minutes_ones) / 10;
            append_string(minutes_buffer, MINUTES_NOMINATIVE_TENS[minutes_tens], true);
            if (minutes_ones > 0) {
                append_string(minutes_buffer, MINUTES_NOMINATIVE_ONES[minutes_ones], true);
            }
        }
    }

    strip_trailing_space(hours_buffer);
    strip_trailing_space(minutes_buffer);
}