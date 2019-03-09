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
    // string _pattern;
    regex _pattern;
    string _path;
    map<int, string> lines;

  public:
    SearchManager(string &pattern, string &path);
    void scan();
    // void traverseHierarchy(const string& path);
    void traverseHierarchy();
};
#endif
