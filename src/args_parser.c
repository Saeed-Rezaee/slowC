/***** args_parser.c *****
* Author : flekystyley
* Date   : 31.1.2019
* Brief  : parsing command line arguments for slowC
**************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "args_parser.h"

void init_args(Arguments *args)
{
    args->help = false;
    args->content_length = 1000*1000;
    args->dial_worker_count = 10;
    args->ramp_up_interval = 10;
    args->sleep_interval = 10*10;
    args->test_duration = 0;
    args->target_host = "127.0.0.1";
    args->target_port = 80;
}

void print_usage(const char *program)
{
    printf("Example Usage: %s -c contentLength [-d dialWorkerCount]\n", program);
}

void print_help(const char *program)
{
    print_usage(program);
    printf(
    "Available options:\n"
    " -H - help command\n"
    " -c - content length.\n"
    " -d - dial worker count.\n"
    " -r - rampup interval.\n"
    " -s - sleep interval.\n"
    " -t - test duration.\n"
    " -h - target host.\n"
    " -p - target port.\n"
    );
}

void parse(int argc, char const *argv[], Arguments *args)
{
    int opt;
    while ((opt = getopt(argc, (char *const*)argv, "Hc:d:r:s:t:h:p:")) != -1) {
        switch (opt) {
        case 'H':
            print_help(argv[0]);
            break;
        case 'c':
            args->content_length = atoi(optarg);
            break;
        case 'd':
            args->dial_worker_count = atoi(optarg);
            break;
        case 'r':
            args->ramp_up_interval = atoi(optarg);
            break;
        case 's':
            args->sleep_interval = atoi(optarg);
            break;
        case 't':
            args->test_duration = atoi(optarg);
            break;
        case 'h':
            args->target_host = optarg;
        case 'p':
            args->target_port = atoi(optarg);
        default:
            printf("ERROR: Unknown arguments passed\n");
            print_usage(argv[0]);
            exit(2);
        }
    }
}
