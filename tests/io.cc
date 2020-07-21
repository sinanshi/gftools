#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() 
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include <hapfile.h>
using namespace std;

TEST_CASE("Read hapFile") {
  auto hf = hapFile("/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.hap.gz", 
      "/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.legend.gz", 
      "/data/mallard/not-backed-up/shi/ref_reduced/h100/h100.samples");

  vector<int> x = {63231, 63452, 65288, 65900, 68396, 69094, 70980, 74347, 76771, 90814, 91508, 91707, 92527, 96931, 101905, 102799, 118034, 119534, 126149, 126155, 126214, 126309, 126310, 127194, 127720, 129063, 134476, 138555, 139456, 139576, 139741, 144050, 153057, 164083, 165832};
  hf.read(x);
  CHECK(hf.m(0, 3) == 1);

  hf.m(0, 3) = 0;
  CHECK(hf.m.isZero(0));

  // test warnings
}
