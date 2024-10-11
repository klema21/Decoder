#include "../src/general_decoder.hpp"

int main() {

  Decoder d;

  d.Decode("../test_files/big5.txt");
  d.Decode("../test_files/iso-8859-5.txt");
  d.Decode("../test_files/koi-8r.txt");
  d.Decode("../test_files/utf-8.txt");
  d.Decode("../test_files/utf-16.txt");
  d.Decode("../test_files/utf-32.txt");
  d.Decode("../test_files/win1251.txt");
  return 0;
}