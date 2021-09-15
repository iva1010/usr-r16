#include <stdio.h>
#include <string.h>
#include <unistd.h>

int argument_valid(int argc, char *argv[], char *ip, char *port)
{
    int opt = 0;

    if(ip == NULL)
    {
        return 2;
    }

    while((opt = getopt(argc, argv, "i:p")) != -1)
    {
        switch (opt)
        {
        case 'i':
		strncpy(ip, argv[2], strlen(argv[2]));
	case 'p':
	    	strncpy(port, argv[4], strlen(argv[4]));
		return 0;
        default:
            if(argc == 1)
            {       
                return 1; // Аргументов нет
            }
            else 
            {
                printf("Do not write the path after the key\n");
                return 2; // Неверное количество аргументов              
            }
        }
    }
    return 0;
}

