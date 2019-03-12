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

  bool isExecutableFile(const auto &directoryEntryIterator);
  bool isHidden(auto &directoryEntryIterator);

public:
  SearchManager(string &pattern, string &path);
  void traverseFilesystem();
};
#endif
