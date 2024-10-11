#pragma once

#include "icu_decoder_impl.hpp"

class Decoder {
public:

  void Decode(const char * path) {
    decoder.Decode(path);
  }
private:
  ICU_Decoder_Impl decoder;
};