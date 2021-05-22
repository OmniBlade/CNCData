#include "isextract.h"
#include "getopt.h"
#include <stdio.h>
#include <set>
#include <iostream>

void printUse()
{
    printf("\nISExtract \n\n"
        "Usage:\n"
        "  isextract -x [-d <path>] [-f <file>] <archive>\n"
        "  isextract -l <archive>\n"
        "  isextract -h | --help\n\n"
        "Options:\n"
        "  -x --extract    Extract files from an InstallShield archive.\n"
        "  -l --list       List files in a InstallShield archive.\n"
        "  -d --directory  Path to search for files or to extract files to.\n"
        "  -f --file       File to extract.\n"
        "                  Can be specified multiple times for multiple files.\n"
        "  -h --help       Displays this help.\n\n");
}

int main(int argc, char** argv)
{
    std::string mode;
    std::string filepath;
    std::string outdir = "./";
    std::set<std::string> files;
    bool extracting = false;
    bool listing = false;
    InstallShield infile;
    
    if(argc < 2) {
        printUse();
        return 0;
    }
    
    while (true) {
        static struct option long_options[] = {
            {"extract", no_argument, nullptr, 'x'},
            {"list", no_argument, nullptr, 'l'},
            {"file", required_argument, nullptr, 'f'},
            {"directory", required_argument, nullptr, 'd'},
            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0},
        };

        int this_option_optind = optind ? optind : 1;
        int option_index = 0;

        int c = getopt_long(argc, argv, "hxl?f:d:", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch (c) {
        case 'l':
            listing = true;
            break;
        case 'x':
            extracting = true;
            break;
        case 'f':
            files.insert(optarg);
            break;
        case 'd':
            outdir = optarg;
            break;
        case 'h': // fallthrough.
        case '?':
            printUse();
            return 0;
        default:
            break;
        }
    }

    filepath = argv[argc - 1];
    
    if(argc >= 4) {
        outdir = argv[3];
    }
    
    try {
        infile.open(filepath);
    } catch (const char* msg) {
        std::cout << "Error: " << msg << "\n";
        return -1;
    }
    
    if(extracting){
        if(files.empty()) {
            infile.extractAll(outdir);
        } else {
            for (auto it : files) {
                infile.extractFile(it.c_str(), outdir);
            }
        }
    } else if(listing) {
        infile.listFiles();
    }
    
    return 0;
}