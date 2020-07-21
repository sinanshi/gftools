#include <iofile.h>

using namespace std;

FileIn::FileIn(string filename , bool binary) {
  if (!open(filename, binary))
    throw(runtime_error("[Error]: The input file " + filename + " cannot be found!"));
}

FileIn::~FileIn() {
  close();
}

string FileIn::name() {
  return file;
}

bool FileIn::open(string filename, bool binary) {
  file = filename;
  string ext = futils::extensionFile(filename);
  if (ext == "gz") {
    fd.open(file.c_str(), ios::in | ios::binary);
    push(boost::iostreams::gzip_decompressor());
  } else if (ext == "bz2") {
    fd.open(file.c_str(), ios::in | ios::binary);
    push(boost::iostreams::bzip2_decompressor());
  } else if (binary) {
    fd.open(file.c_str(), ios::in | ios::binary);
  } else  {
    fd.open(file.c_str());
  }
  if (fd.fail()) return false;
  push(fd);
  return true;
}

bool FileIn::readString(string & str) {
  int s;
  if (!read((char*)&s, sizeof(int))) return false;
  char  * buffer = new char [s + 1];
  if (!read(buffer, s)) return false;
  buffer[s] = '\0';
  str = string(buffer);
  delete [] buffer;
  return true;
}

void FileIn::close() {
  if (!empty()) reset();
  fd.close();
}

namespace futils {
  bool isFile(string f) {
    ifstream inp;
    inp.open(f.c_str(), ifstream::in);
    if(inp.fail()) {
      inp.clear(ios::failbit);
      inp.close();
      return false;
    }
    inp.close();
    return true;
  }

  bool createFile(string f) {
    ofstream out;
    out.open(f.c_str(), ofstream::out);
    if(out.fail()) {
      out.clear(ios::failbit);
      out.close();
      return false;
    }
    out.close();
    return true;
  }

  string extensionFile(string & filename) {
    if (filename.find_last_of(".") != string::npos)
      return filename.substr(filename.find_last_of(".") + 1);
    return "";
  }

  void bool2binary(vector < bool > & V, ostream &fd) {
    int nb = V.size();
    fd.write((char*)&nb, sizeof(int));
    int cpt_byte = 0;
    int cpt_bin = 0;
    int nb_byte = (int)ceil( (V.size() * 1.0) / 8);
    while (cpt_byte < nb_byte) {
      bitset<8> byte_bitset;
      for (int l = 0; l < 8 && cpt_bin < V.size() ; l++) {
        byte_bitset[l] = V[cpt_bin];
        cpt_bin ++;
      }
      char byte_char = (char)byte_bitset.to_ulong();
      fd.write(&byte_char, 1);
      cpt_byte++;
    }
  }

  bool binary2bool(vector < bool > & V, istream & fd) {
    int nb;
    fd.read((char*)&nb, sizeof(int));
    if (!fd) return false;
    int cpt_byte = 0;
    int cpt_bin = 0;
    int nb_byte = (int)ceil( (nb * 1.0) / 8);
    V = vector < bool >(nb);
    while (cpt_byte < nb_byte) {
      char byte_char;
      fd.read(&byte_char, 1);
      if (!fd) return false;
      bitset<8> byte_bitset = byte_char;
      for (int l = 0; l < 8 && cpt_bin < nb ; l++) {
        V[cpt_bin] = byte_bitset[l];
        cpt_bin++;
      }
      cpt_byte++;
    }
    return true;
  }

  int tokenize (string & str, vector < string > & tokens) {
    tokens.clear();
    string::size_type p_last = str.find_first_not_of(" 	", 0);
    string::size_type p_curr = str.find_first_of(" 	", p_last);
    while (string::npos != p_curr || string::npos != p_last) {
      tokens.push_back(str.substr(p_last, p_curr - p_last));
      p_last = str.find_first_not_of("	 ", p_curr);
      p_curr = str.find_first_of("	 ", p_last);
    }
    if (tokens.back()[tokens.back().size()-1] == '\r')
      tokens.back() = tokens.back().substr(0, tokens.back().size()-1);
    return tokens.size();
  }

  int tokenize(string & str, vector < string > & tokens, int n_max_tokens) {
    tokens.clear();
    string::size_type p_last = str.find_first_not_of(" 	", 0);
    string::size_type p_curr = str.find_first_of(" 	", p_last);
    while ((string::npos != p_curr || string::npos != p_last) && tokens.size() < n_max_tokens) {
      tokens.push_back(str.substr(p_last, p_curr - p_last));
      p_last = str.find_first_not_of("	 ", p_curr);
      p_curr = str.find_first_of("	 ", p_last);
    }
    return tokens.size();
  }

  int tokenize (string & str, vector < string > & tokens, string sep) {
    tokens.clear();
    string::size_type p_last = str.find_first_not_of(sep, 0);
    string::size_type p_curr = str.find_first_of(sep, p_last);
    while (string::npos != p_curr || string::npos != p_last) {
      tokens.push_back(str.substr(p_last, p_curr - p_last));
      p_last = str.find_first_not_of(sep, p_curr);
      p_curr = str.find_first_of(sep, p_last);
    }
    if (tokens.back()[tokens.back().size()-1] == '\r')
      tokens.back() = tokens.back().substr(0, tokens.back().size()-1);
    return tokens.size();
  }

  string int2str(int n) {
    ostringstream s2( stringstream::out );
    s2 << n;
    return s2.str();
  }

  string int2str(vector < int > & v) {
    ostringstream s2( stringstream::out );
    for (int l = 0 ; l < v.size() ; l++) {
      if (v[l] < 0) s2 << "-";
      else s2 << v[l] ;
    }
    return s2.str();
  }
};
