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
    "п’ять",
    "шість",
    "сім",
    "вісім",
    "дев’ять"
};

static const char *const MINUTES_NOMINATIVE_TEENS[] = {
    "десять",
    "одинадцять",
    "дванадцять",
    "тринадцять",
    "чотирнадцять",
    "п’ятнадцять",
    "шістнадцять",
    "сімнадцять",
    "вісімнадцять",
    "дев’ятнадцять",
};

static const char *const MINUTES_NOMINATIVE_TENS[] = {
    "", // нульові
    "", // десятки
    "двадцять",
    "тридцять",
    "сорок",
    "п’ятдесят",
};

void append_string(char* output, const char* string, bool add_space);
void say_formal(char* buffer, const size_t buffer_size, int hours, int minutes);