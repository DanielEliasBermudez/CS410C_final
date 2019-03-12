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

  bool isExecutableFile(const auto &directoryEntryIterator);
  bool isHidden(auto &directoryEntryIterator);
  void scan(auto &directoryEntry);
  void traverseDirectory();

public:
  SearchThread(regex &pattern, const fs::path &path, vector<string> *results, mutex *m);
  void operator()();
};
#endif
