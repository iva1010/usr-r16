#include <string.h>

int all_off(char *command)
{
    char str[] = {"\x55\xaa\x00\x03\x00\x03\x02\x03"};
    strncpy(command, str, sizeof str);
    return 0;
}
