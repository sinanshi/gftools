#include <hapfile.h>
#include <iofile.h>
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


void hapFile::readLegend() {
  FileIn sf(path_legend);
  string buffer; 
  vector <string> tokens, header;
  getline(sf, buffer, '\n'); 

  while(getline(sf, buffer, '\n')) {
    futils::tokenize(buffer, tokens); 
    if (tokens.size() != 4) 
      throw(runtime_error("legend file format is not correct!"));
    loci.push_back(stoi(tokens[1]));
  }
  nSNP = loci.size();
}

void hapFile::read() {
  readSample(); 
  readLegend(); 





}
