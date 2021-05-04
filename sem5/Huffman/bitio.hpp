#pragma once
#include <stdio.h>
#include <string>
#include <assert.h>

using namespace std;

class bitio_in {
public:
  bitio_in(string const &name) { 
    fp = fopen(name.c_str(), "rb");
    assert(fp != nullptr);
    mask = 256; 
  }

  ~bitio_in() {
    fclose(fp);
  }

  unsigned in() {
    if (mask > 128) {
      int c = getc(fp);
      if (c == EOF) {
        eof = true;
        return 0;
      }
      buffer = c;
      mask = 2;
      return (buffer & 1) != 0;
    } else {
      unsigned retval = (buffer & mask) != 0;
      mask <<= 1;
      return retval;
    }
  }

  unsigned in(int bits) {
    unsigned ret = 0;
    for (int i = 0; i < bits; i++) {
      ret |= (in() << i);
    }
    //		printf("bitio_in(%d)=%u\n", bits, ret);
    return ret;
  }

  bool is_eof() const { return eof; }

private:
  FILE *fp;
  unsigned char buffer;
  unsigned mask;
  bool eof;
};

class bitio_out {
public:
  bitio_out(string const &name) {
    fp = fopen(name.c_str(), "wb");
    assert(fp != nullptr);
    mask = 1;
    buffer = 0;
  }
  ~bitio_out() { 
    flush(); 
    fclose(fp);
  }
  void flush() {
    //		printf("buf=%x mask=0x%x\n", buffer, mask);
    if (mask > 1) {
      putc(buffer, fp);
      buffer = 0;
    }
    mask = 1;
  }
  void out(unsigned bit) {
    //		 printf("out(%d)\n", bit);
    if (bit) {
      buffer |= mask;
    }
    mask <<= 1;
    if (mask > 128) {
      //			 printf("putc %x\n", buffer);
      putc(buffer, fp);
      buffer = 0;
      mask = 1;
    }
  }
  void out(int bits, unsigned n) {
    //		 printf("bitio_out(%d, %u)\n", bits, n);
    for (int i = 0; i < bits; i++) {
      out(n & 1);
      n >>= 1;
    }
  }

private:
  FILE *fp;
  unsigned char buffer;
  unsigned mask;
};

