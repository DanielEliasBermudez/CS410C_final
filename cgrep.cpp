#include <iostream>
#include <string>
#include <sstream>
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
         << "-A <NUM>\n"
         << "\tshow <NUM> lines after each match\n"
         << "-B <NUM>\n"
         << "\tshow <NUM> lines before each match\n"
         << "-h\n"
         << "\tdisplay this help message"
         << endl;
    exit(0);
}

int main(int argc, char **argv)
{
    int numberOfLinesAfter;
    int numberOfLinesBefore;

    bool doneParsingOptions = false;
    int patternIndex = 1;

    for (int i = 1; i < argc; ++i)
    {
        if (!doneParsingOptions)
        {
            string option(argv[i]);
            if (!strncmp(&option[0], "-", 1))
            {
                if (option == "-A")
                {
                    stringstream ss(argv[++i]);
                    ss >> numberOfLinesAfter;
                }
                else if (option == "-B")
                {
                    stringstream ss(argv[++i]);
                    ss >> numberOfLinesBefore;
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
        string pattern(argv[patternIndex]);
        string path(argv[patternIndex + 1]);
    }
    else if ((argc - patternIndex) == 1)
    {
        string pattern(argv[patternIndex]);
        string path(".");
    }
    else
    {
        displayHelpMessage();
    }
}