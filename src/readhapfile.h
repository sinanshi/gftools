class hapFile {
  private:
    string path_hap, path_legend, path_sample;
  public:
    string getPath(const string ftype);
    void readHap();
    void readLegend();
    void readSample();
}
