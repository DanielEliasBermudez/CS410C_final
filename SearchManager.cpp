#include "SearchManager.h"

SearchManager::SearchManager(string &pattern, string &path) : _pattern(pattern),
                                                              _path(path)
{
}

void SearchManager::traverseFilesystem()
{
    cout << endl;
    fs::path p = _path;

    // Search for the pattern in the _path directory
    SearchThread searchThread(_pattern, p, &results, &resultsMutex);
    threads.push_back(thread(searchThread));

    for (auto it = fs::recursive_directory_iterator(_path);
         it != fs::recursive_directory_iterator(); ++it)
    {
        // Avoid executable files or hidden files/directories
        if (isExecutableFile(it) || isHidden(it))
        {
            continue;
        }
        // Launch a new thread for each directory
        if (fs::is_directory(it->status()))
        {
            //cout << it->path() << endl;
            //cout << "time to create new thread" << endl;
            SearchThread searchThread(_pattern, it->path(), &results, &resultsMutex);
            threads.push_back(thread(searchThread));
        }
    }
    for (auto &t : threads)
    {
        t.join();
    }
    // Print the results of the search
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
