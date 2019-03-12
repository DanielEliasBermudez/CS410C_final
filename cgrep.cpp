/**
 * Daniel Elias Bermudez
 * CS410: Advanced Topics in C++
 *
 * Final Project
 * Create a command line grep tool that uses multi threading.
 * Cgrep.cpp parses the command line options. It builds a SearchManager object.
 * SearchManager recursively searches the directory passed in via the arguments.
 * Every new directory encountered in the search spawns a new SearchThread thread 
 * object. Once all the threads return, the results are printed to the screen.
 */
#include <iostream>
#include <string>
#include <sstream>
#include "SearchManager.h"
using namespace std;

void displayHelpMessage()
{
    cout << "Usage: "
         << "cg [OPTIONS] PATTERN [PATH]\n\n"
         << "PATTERN\n"
         << "\tA regular expression used for searching\n"
         << "PATH\n"
         << "\tA directory to search"
         << "Option:\n"
         << "-h\n"
         << "\tdisplay this help message"
         << endl;
    exit(0);
}
/**
 * Parses the command line arguments and builds the SearchManager
 * object to handle the grepping of the files.
 */
int main(int argc, char **argv)
{
    std::string pattern;
    std::string path;

    bool doneParsingOptions = false;
    int patternIndex = 1;

    for (int i = 1; i < argc; ++i)
    {
        if (!doneParsingOptions)
        {
            string option(argv[i]);
            if (!strncmp(&option[0], "-", 1))
            {
                if (option == "-h")
                {
                    displayHelpMessage();
                    return 0;
                }
                else
                {
                    displayHelpMessage();
                }
            }
            else
            {
                doneParsingOptions = true;
                patternIndex = i;
            }
        }
    }

    if ((argc - patternIndex) == 2)
    {
        pattern = argv[patternIndex];
        path = argv[patternIndex + 1];
    }
    else if ((argc - patternIndex) == 1)
    {
        pattern = argv[patternIndex];
        path = ".";
    }
    else
    {
        displayHelpMessage();
    }

    SearchManager s(pattern, path);
    s.traverseFilesystem();
}
