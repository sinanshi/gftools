#include <hapfile.h>
#include <iofile.h>
#include <map>

using namespace Eigen;

//! We assume that sample file has a table which contains 4 columns. 
//! sample, population, group, sex
void hapFile::readSample() {
  FileIn sf(path_sample);
  string buffer;
  vector <string> tokens, header;

  hap_sample["sample"] = vector<string>();
  hap_sample["population"] = vector<string>();
  hap_sample["group"] = vector<string>();
  hap_sample["sex"] = vector<string>();
  // Getting the header. 
  getline(sf, buffer, '\n');
  futils::tokenize(buffer, tokens);
  if (tokens[0] != "sample" || tokens[1] != "population" ||
      tokens[2] != "group" || tokens[3] != "sex")
    throw(runtime_error("sample file " + path_sample + 
          "format error."));

  while(getline(sf, buffer, '\n')) {
    futils::tokenize(buffer, tokens);
    hap_sample["sample"].push_back(tokens[0]);
    hap_sample["population"].push_back(tokens[1]);
    hap_sample["group"].push_back(tokens[2]);
    hap_sample["sex"].push_back(tokens[3]);
  }
  nSMPL = hap_sample["sample"].size(); 
}

//! Read legend file with a give name
//! \param lfname the full path of the legend file
//! \return an vector<int> which contains all the positions appeard in the 
//! legend file. 
vector<int> hapFile::readLegendFile(string lfname) {
  FileIn lf(lfname);
  string buffer; 
  vector <string> tokens, header;
  vector <int> p;
  getline(lf, buffer, '\n'); 

  while(getline(lf, buffer, '\n')) {
    futils::tokenize(buffer, tokens); 
    if (tokens.size() != 4) 
      throw(runtime_error("legend file format is not correct!"));
    p.push_back(stoi(tokens[1]));
  }
  return(p);
}

//! Load the legend file for the haplotype data object.
//! #pos_legend is updated.
//! \return 
void hapFile::readLegend() {
  auto l = readLegendFile(path_legend); 
  pos_legend = l;
}

void hapFile::read(const vector<int> & select_snp) {
  FileIn sf(path_hap);
  vector <string> tokens;
  string buffer;
  readSample();
  readLegend();

  vector<bool> pmask = subset_pmask(select_snp);

  m = Matrix<bool, Dynamic, Dynamic>(select_snp.size(), nSMPL * 2);

  int index_row = 0; // for the eigen Matrix m
  int iSNP = 0; // ith row in the hap file. 
  while (getline(sf, buffer, '\n')) {
    if (pmask[iSNP]) {
      if (futils::tokenize(buffer, tokens) != (nSMPL * 2))
        throw(runtime_error("hap file is not aligned"));
      else {
        int index_col = 0;
        for (string t : tokens) {
          //cout << index_row << ", " << index_col << endl; 
          m(index_row, index_col) = (stoi(t) == 1);
          index_col++;
        }
      }
      index_row++;
    }
    iSNP++;
  }
  pos = select_snp;
  nSNP = pos.size();
}

void hapFile::read(const string fname) {
  auto l = readLegendFile(fname);
  read(l);
}


void hapFile::read() {
  auto l = pos_legend; 
  read(l);
}

vector<bool> hapFile::subset_pmask(const vector<int>& l) {
  int miss = 0;
  vector<int> match_index; 
  map <int, int> ml;
  vector<bool> pmask(pos_legend.size()); 

  // create a map to matach the positions. 
  int index = 0; 
  for (auto i : pos_legend) {
    ml.insert(make_pair(i, index));
    index++; 
  }

  for (auto i : l) {
    auto it = ml.find(i);
    if (it != ml.end()) 
      match_index.push_back(it -> second);
    else
      miss++;
  }

  if (miss > 0) 
    cout << "[WARNING] " << miss << "positions are removed.";

  for(int i = 0; i < pmask.size(); ++i) pmask[i] = false;
  for(auto i : match_index) pmask[i] = true;

  return(pmask);
}
