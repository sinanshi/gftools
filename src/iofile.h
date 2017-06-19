#ifndef _IOFILE_H
#define _IOFILE_H

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>


#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>

using namespace std;
//! Reads input files with multiple formats including 
//! plain binary, gz, and bz2.
class FileIn : public boost::iostreams::filtering_istream {
  private:
    string file;
    ifstream fd;

  public:
    FileIn(const string filename , const bool binary = false);
    ~FileIn();
    string name();
    bool open(const string filename, const bool binary = false);
    bool readString(string &);
    void close();
};

namespace futils {
	bool isfile(string f);
	bool createfile(string f);
	string extensionFile(string & filename);
	void bool2binary(vector < bool > & v, ostream &fd);
	bool binary2bool(vector < bool > & v, istream & fd);
  int tokenize(string &, vector < string > &);
  int tokenize(string &, vector < string > &, int);
  int tokenize(string &, vector < string > &, string);
  string int2str(int n);
	string int2str(vector < int > & v);
};
#endif
