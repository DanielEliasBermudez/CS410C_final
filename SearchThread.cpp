#include "SearchThread.h"

SearchThread::SearchThread(regex &pattern, const fs::path &path, 
                           vector<string>* results, mutex* m) :
_pattern(pattern),
_path(path),
_ptrToResults(results),
_ptrToResultsMutex(m)
{
}

void SearchThread::scan(auto &directoryEntry)
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
    // Lock the results vector before adding to it
    lock_guard<mutex> guard(*_ptrToResultsMutex);
    _ptrToResults->push_back(output);
}

void SearchThread::traverseDirectory()
{
    for (auto it = fs::directory_iterator(_path);
         it != fs::directory_iterator(); ++it)
    {
        if (isExecutableFile(it) || isHidden(it))
        {
            continue;
        }
        scan(*it);
    }
}

void SearchThread::operator()()
{
    traverseDirectory();
}

bool SearchThread::isExecutableFile(const auto &directoryEntryIterator)
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

bool SearchThread::isHidden(auto &directoryEntryIterator)
{
    // Ignore hidden files
    if (!strncmp(directoryEntryIterator->path().filename().c_str(), ".", 1))
    {
        return true;
    }
    return false;
}
