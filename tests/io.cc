#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() 
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include <hapfile.h>
using namespace std;

TEST_CASE("Read hapFile") {
  auto hf = hapFile("/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.hap.gz", 
      "/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.legend.gz", 
      "/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.samples");

  vector<int> x = {60828, 61044};
  hf.read(x);
  CHECK(hf.m(0, 3) == 1);

  hf.m(0, 3) = 0;
  CHECK(hf.m.isZero(0));

  // test warnings
}
