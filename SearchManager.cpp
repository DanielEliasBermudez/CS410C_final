#include "SearchManager.h"

SearchManager::SearchManager(string &pattern, string &path) : _pattern(pattern),
                                                              _path(path)
{
}

void SearchManager::scan(auto &directoryEntry)
{

    map<int, string> lines;
    ifstream file;

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
    
    string output;
    // Print the file name
    if (!lines.empty())
    {
        output = directoryEntry.path();
        output += "\n";
    }

    for (auto i : lines)
    {
        output += to_string(i.first);
        output += ": ";
        output += i.second;
        output += "\n";
    }
    
    // Print a blank line between outputs
    if (!lines.empty())
    {
        output += "\n";
    }
    results.push_back(output);
}

void SearchManager::traverseFilesystem()
{
    cout << endl;

    for (auto it = fs::recursive_directory_iterator(_path); it != fs::recursive_directory_iterator(); ++it)
    {
        if (isExecutable(it->status().permissions()) || isHidden(it))
        {
            continue;
        }
        scan(*it);
    }

    for (auto i : results)
    {
        cout << i;
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

bool SearchManager::isHidden(auto &directoryEntryIterator) 
{
    // TODO figure out a way to ignore hidden directories
    /*
    // Ignore hidden directories
    if (fs::is_directory(directoryEntryIterator->status()))
    {
        cout << directoryEntryIterator->path() << endl;
        directoryEntryIterator.disable_recursion_pending();
        cout << "disabled" << endl;
        return true;
    }
    */

    // Ignore hidden files
    if (!strncmp(directoryEntryIterator->path().filename().c_str(), ".", 1))
    {
        //cout << directoryEntryIterator->path().filename().c_str() << endl;
        return true;
    }
    return false;
}
