#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <regex>
#include <experimental/filesystem>

using namespace std;
namespace fs = experimental::filesystem;

class SearchManager
{
private:
  regex _pattern;
  string _path;

  bool isExecutable(const auto &directoryEntryPermissions);
  void scan(auto &directoryEntry);

public:
  SearchManager(string &pattern, string &path);
  void traverseFilesystem();
};
#endif
