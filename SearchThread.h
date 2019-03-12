/**
 * Daniel Elias Bermudez
 * CS410: Advanced Topics in C++
 *
 * SearchThread Class.
 * This class is a callable object that is launched as a thread from SearchManager.
 * It searches through the directory passed in at construction. It stores
 * the results in the results vector in SearchManager.
 */
#ifndef SEARCHTHREAD_H
#define SEARCHTHREAD_H
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <regex>
#include <experimental/filesystem>
#include <vector>
#include <mutex>

using namespace std;
namespace fs = experimental::filesystem;

class SearchThread
{
private:
  regex _pattern;
  string _path;
  vector<string> *_ptrToResults;
  mutex *_ptrToResultsMutex;

  // Returns true if a file is executable.
  bool isExecutableFile(const auto &directoryEntryIterator);
  // Returns true if the directory entry is a hidden file.
  bool isHidden(auto &directoryEntryIterator);
  /* 
    Searches the directory ignoring executable files and
    hidden files and directories.
   */
  void traverseDirectory();

public:
  SearchThread(regex &pattern, const fs::path &path, vector<string> *results, mutex *m);
  // Makes this class callable. This enables it to be called in a thread as a functor.
  void operator()();
  /*
    Iterates over a file looking for the regex. Once done searching,
    the results are added to the results vector from the search manager. 
  */
  //void scan(auto &directoryEntry);
  void scan(const fs::directory_entry &directoryEntry);
};
#endif
