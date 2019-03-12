#include "SearchManager.h"

SearchManager::SearchManager(string &pattern, string &path) : _pattern(pattern),
                                                              _path(path)
{
}

void SearchManager::traverseFilesystem()
{
    cout << endl;
    fs::path p = _path;

    SearchThread searchThread(_pattern, p, &results, &resultsMutex);

    fs::directory_entry tmpDirectoryEntry(p);

    // Check for existence to guard against a failure and unexpected program 
    // termination
    if (!fs::exists(tmpDirectoryEntry.status()))
    {
        cout << "Path does not exist" << endl;
        return;
    }
    // If the path is to a single file, we need to bypass all of the iteration
    // logic and just scan the one file. This case is not multi threaded as it 
    // does not make sense.
    if (fs::is_regular_file(tmpDirectoryEntry))
    {
        searchThread.scan(tmpDirectoryEntry);
    }
    else
    {
        // Search for the pattern in the _path directory
        threads.push_back(thread(searchThread));

        // Recursively search the directory and spawn a thread for each new directory
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
                SearchThread searchThread(_pattern, it->path(), &results, &resultsMutex);
                threads.push_back(thread(searchThread));
            }
        }
        for (auto &t : threads)
        {
            t.join();
        }
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
