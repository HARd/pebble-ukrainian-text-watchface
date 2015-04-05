static const char *const HOURS_NOMINATIVE[] = {
    "дванадцята",
    "перша",
    "друга",
    "третя",
    "четверта",
    "п'ята",
    "шоста",
    "сьома",
    "восьма",
    "дев'ята",
    "десята",
    "одинадцята",
    "дванадцята"
};

static const char *const MINUTES_NOMINATIVE_ONES[] = {
    "нуль",
    "один",
    "дві",
    "три",
    "чотири",
    "п'ять",
    "шість",
    "сім",
    "вісім",
    "дев'ять"
};

static const char *const MINUTES_NOMINATIVE_TEENS[] = {
    "десять",
    "одинадцять",
    "дванадцять",
    "тринадцять",
    "чотирнадц ять",
    "п'ятнадц ять",
    "шістнадц ять",
    "сімнадц ять",
    "вісімнадц ять",
    "дев'ятнадц ять",
};

static const char *const MINUTES_NOMINATIVE_TENS[] = {
    "", // нульові
    "", // десятки
    "двадцять",
    "тридцять",
    "сорок",
    "п'ятдесят",
};

void append_string(char* output, const char* string, bool add_space);
void say_formal(char* hours_buffer, char* minutes_buffer, int hours, int minutes);