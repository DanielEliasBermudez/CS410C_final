#include <iostream>

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
         << endl;
}

int main(int argc, char **argv)
{
    displayHelpMessage();
}
