/**
 * Daniel Elias Bermudez
 * CS410: Advanced Topics in C++
 *
 * SearchManager Class.
 * This class recursively searches through the directory passed in at
 * construction. Every directory encountered in the search spawns a new
 * thread to search the files in that directory.
 */
#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <experimental/filesystem>
#include <vector>
#include <thread>
#include <mutex>
#include "SearchThread.h"

using namespace std;
namespace fs = experimental::filesystem;

class SearchManager
{
private:
  regex _pattern;
  string _path;
  mutex resultsMutex;
  vector<string> results;
  vector<thread> threads;

  // Returns true if a file is executable.
  bool isExecutableFile(const auto &directoryEntryIterator);
  // Returns true if a file or directory is hidden.
  bool isHidden(auto &directoryEntryIterator);

public:
  SearchManager(string &pattern, string &path);
  /* 
    Recursively searches the directory ignoring executable files and
    hidden files and directories. Every new directory spawns a new thread.
   */
  void traverseFilesystem();
};
#endif
