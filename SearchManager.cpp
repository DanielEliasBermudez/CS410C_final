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

    for (auto it = fs::recursive_directory_iterator(_path);
         it != fs::recursive_directory_iterator(); ++it)
    {
        if (isExecutableFile(it) || isHidden(it))
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

bool SearchManager::isExecutableFile(const auto &directoryEntryIterator)
{
    auto perms = directoryEntryIterator->status().permissions();
    
    if ((fs::is_regular_file(directoryEntryIterator->status())) &&
        ((perms & fs::perms::owner_exec) != fs::perms::none ||
         (perms & fs::perms::group_exec) != fs::perms::none ||
         (perms & fs::perms::others_exec) != fs::perms::none))
    {
        return true;
    }
    return false;
}

bool SearchManager::isHidden(auto &directoryEntryIterator)
{

    // Ignore hidden files and directories
    if (!strncmp(directoryEntryIterator->path().filename().c_str(), ".", 1))
    {
        // Disable recursing through a hidden directory
        if (fs::is_directory(directoryEntryIterator->status())) 
        {
            directoryEntryIterator.disable_recursion_pending();
        }
        return true;
    }
    return false;
}
