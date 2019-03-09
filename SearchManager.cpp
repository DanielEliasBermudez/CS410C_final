#include "SearchManager.h"

SearchManager::SearchManager(string &pattern, string &path) : _pattern(pattern),
                                                              _path(path)
{
}

void SearchManager::scan(auto &directoryEntry)
{

    map<int, string> lines;
    ifstream file;

    //file.open(_path);
    file.open(directoryEntry.path());
    int counter = 1;
    string line;

    while (getline(file, line))
    {
        if (regex_search(line, _pattern))
        {
            lines[counter] = line;
        }
        ++counter;
    }
    file.close();

    // Print the file name
    if (!lines.empty())
    {
        cout << directoryEntry.path() << endl;
    }

    for (auto i : lines)
    {
        cout << i.first << ": " << i.second << endl;
    }

    if (!lines.empty())
    {
        cout << endl;
    }
}

void SearchManager::traverseFilesystem()
{
    cout << endl;

    for (auto it = fs::recursive_directory_iterator(_path); it != fs::recursive_directory_iterator(); ++it)
    {
        //if (isExecutable(*it)) continue;
        //if (isExecutable(fs::file_status(*it).permission())) continue;
        if (isExecutable(it->status().permissions()))
            continue;
        scan(*it);
        //cout << *it << endl;
    }
}

bool SearchManager::isExecutable(const auto &directoryEntryPermissions)
{
    if ((directoryEntryPermissions & fs::perms::owner_exec) != fs::perms::none ||
        (directoryEntryPermissions & fs::perms::group_exec) != fs::perms::none ||
        (directoryEntryPermissions & fs::perms::others_exec) != fs::perms::none)
    {
        return true;
    }
    return false;
}
