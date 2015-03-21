#include <string.h>
#include <stdbool.h>
#include "text_formal.h"


void append_string(char *output, const char *string, bool add_space) {
    strcat(output, string);
    if (add_space) {
        strcat(output, " ");
    }
}

void say_formal(char* output, int hours, int minutes) {
    hours = hours % 12;
    append_string(output, HOURS_NOMINATIVE[hours], true);

    if (minutes <= 9) {
        append_string(output, MINUTES_NOMINATIVE_ONES[0], true);
        append_string(output, MINUTES_NOMINATIVE_ONES[minutes], true);
    } else {
        if (minutes > 9 && minutes < 20) {
            minutes = minutes % 10;
            append_string(output, MINUTES_NOMINATIVE_TEENS[minutes], true);
        }
        else {
            int minutes_ones = minutes % 10;
            int minutes_tens = (minutes - minutes_ones) / 10;
            append_string(output, MINUTES_NOMINATIVE_TENS[minutes_tens], true);
            if (minutes_ones > 0) {
                append_string(output, MINUTES_NOMINATIVE_ONES[minutes_ones], true);
            }
        }
    }
}