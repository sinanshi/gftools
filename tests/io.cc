#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() 
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include <hapfile.h>
using namespace std;


TEST_CASE("Read hapFile") {
  auto hf = hapFile("/data/mallard/not-backed-up/shi/ref_hap_chr20/HRC.r1-1.GRCh37.chr20.shapeit3.mac5.aa.genotypes.hap.gz", 
      "/data/mallard/not-backed-up/shi/ref_hap_chr20/HRC.r1-1.GRCh37.chr20.shapeit3.mac5.aa.genotypes.legend.gz", 
      "/data/mallard/not-backed-up/shi/ref_hap_chr20/HRC.r1-1.GRCh37.chr20.shapeit3.mac5.aa.genotypes.samples");
  hf.readSample();
  CHECK(hf.sample_size() == 32470);
  hf.readLegend(); 
  CHECK(hf.n_snp() == 884983);

  hf.read(); 
}
