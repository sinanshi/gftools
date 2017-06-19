#ifndef HAPFILE_H
#define HAPFILE_H

#include <string>
#include <unordered_map>
#include <vector>
using namespace std; 
class hapFile {
  private:
    string path_hap, path_legend, path_sample;
    unordered_map <string, vector<string>> hap_sample;
    vector<int> loci; 
    int nSMPL;
    int nSNP;

  public:
    hapFile(string ph, string pl, string ps): 
      path_hap(ph), path_legend(pl), path_sample(ps) {}; 
    string getPath(const string ftype);
    void readHap();
    void readLegend();
    void readSample();
    int sample_size() {return(nSMPL);}; 
    int n_snp() {return(nSNP);}; 
}; 

#endif
