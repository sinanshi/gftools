#ifndef HAPFILE_H
#define HAPFILE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen; 
class hapFile {
  private:
    string path_hap, path_legend, path_sample;
    //! The full path of a file which contains a selected
    //! subset of positions that the reader needs to read.
    //! The file must have the same format as a legend file.
    string path_mask; 
    unordered_map <string, vector<string>> hap_sample;
    vector<int> pos_legend; //!< loci appeared in the legend
    int nSMPL; //! number of samples in the current object.
    int nSNP; //! number of SNPs in the current object.

    vector<bool> subset_position(string fname); 
    vector<int> readLegendFile(string lfname);
    vector<bool> subset_pmask(const vector<int>& l);
  public:
    hapFile(string ph, string pl, string ps): 
      path_hap(ph), path_legend(pl), path_sample(ps) {};


    vector<int> pos; //! loci found in the current object. 

    void read();
    void read(const vector<int> & select_snp);
    void read(const string fname); 


    void readLegend(); 
    void readSample();

    int sample_size() {return(nSMPL);}; 
    int n_snp() {return(nSNP);};
    Matrix<int, Dynamic, Dynamic> m; 
};

#endif
