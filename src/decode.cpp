#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unicode/utypes.h"
#include "unicode/ustring.h"
#include "unicode/regex.h"
#include "unicode/ucnv.h"
#include "unicode/uclean.h"
#include "unicode/ucsdet.h"

using namespace icu;

const char *fileName;
int         fileLen;

char16_t *ucharBuf = nullptr;

char *charBuf = nullptr;

void charSetDetection() {
    UCharsetDetector *csd;
    //const UCharsetDetector *ucm;
    static char buffer[10] = {"abcabcabc"};
    int32_t inputLength = 10; // length of the input text
    UErrorCode status = U_ZERO_ERROR;
    ucsdet_setText(csd, buffer, inputLength, &status);
    auto ucm = ucsdet_detect(csd, &status);
}

void readFile(const char *name) {

    fileName = name;
    fileLen  = 0;


    FILE *file = fopen(name, "rb");
    if (file == nullptr) {
        fprintf(stderr, "ugrep: Could not open file \"%s\"\n", fileName);
        return;
    }
    fseek(file, 0, SEEK_END);
    int rawFileLen = ftell(file);
    fseek(file, 0, SEEK_SET);
    

    charBuf = static_cast<char*>(realloc(charBuf, rawFileLen + 1));
    int t = static_cast<int>(fread(charBuf, 1, rawFileLen, file));
    if (t != rawFileLen)  {
        fprintf(stderr, "Error reading file \"%s\"\n", fileName);
        fclose(file);
        return;
    }
    charBuf[rawFileLen]=0;
    fclose(file);

    int32_t        signatureLength;
    const char *   charDataStart = charBuf; 
    //const char   charDataStart[3] = {'\xEF', '\xBB', '\xBF'}; for test
    UErrorCode     status        = U_ZERO_ERROR;
    const char*    encoding      = ucnv_detectUnicodeSignature(
                           charDataStart, rawFileLen, &signatureLength, &status);
    
    std::cout << encoding << std::endl;
    
    if (U_FAILURE(status)) {
        fprintf(stderr, "ugrep: ICU Error \"%s\" from ucnv_detectUnicodeSignature()\n",
            u_errorName(status));
        return;
    }
    if(encoding!=nullptr ){
        charDataStart  += signatureLength;
        rawFileLen     -= signatureLength;
    }

    UConverter* conv;
    conv = ucnv_open(encoding, &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "ugrep: ICU Error \"%s\" from ucnv_open()\n", u_errorName(status));
        return;
    }

    uint32_t destCap = ucnv_toUChars(conv,
                       nullptr,
                       0,
                       charDataStart,
                       rawFileLen,
                       &status);
    if (status != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "ugrep: ucnv_toUChars: ICU Error \"%s\"\n", u_errorName(status));
        return;
    };
    
    status = U_ZERO_ERROR;
    ucharBuf = static_cast<char16_t*>(realloc(ucharBuf, (destCap + 1) * sizeof(char16_t)));
    ucnv_toUChars(conv,
        ucharBuf,
        destCap+1,
        charDataStart,
        rawFileLen,
        &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "ugrep: ucnv_toUChars: ICU Error \"%s\"\n", u_errorName(status));
        return;
    };
    ucnv_close(conv);
    
    fileLen = destCap;
}

auto main() -> int {
  readFile("test.txt");
  charSetDetection();
  return -1;
}