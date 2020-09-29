#include "gorm_options.h"
#include "gorm_error.h"
#include <getopt.h>


int GORM_GetOptions(int argc, char **argv)
{
    int c, value;
    opterr = 0;
    for(;;)
    {
        c = getopt_long(argc, argv, short_options, long_options, NULL);
        if (c == -1) 
        {
            /* no more options */
            break;
        }
        switch (c)
        {
        case 'h':
            GORM_Options::Instance()->showHelp = 1;
            break;
        case 'c':
            GORM_Options::Instance()->confFileName = optarg;
            break;
        case 'd':
            GORM_Options::Instance()->daemonize = 1;
            break;
        case 'n':
            GORM_Options::Instance()->dbname = optarg;
            break;
        default:
            cout << "gredis: invalid option -- '" << optopt << "'";
            return GORM_ERROR;
        }

    }
    return GORM_OK;
}


