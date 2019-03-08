#include "SearchManager.h"

SearchManager::SearchManager(string &pattern, string &path) : _pattern(pattern),
                                                              _path(path)
{
}
void SearchManager::scan()
{

    ifstream file;
    // file.open("testDir/file1");
    file.open(_path);
    int counter = 1;
    string line;
    // regex pattern("thread");
    // regex pattern(_pattern);
    while (getline(file, line))
    {
        if (regex_search(line, _pattern))
        {
            lines[counter] = line;
        }
        ++counter;
    }
    for (auto i : lines)
    {
        cout << i.first << ": " << i.second << endl;
    }
    file.close();
}