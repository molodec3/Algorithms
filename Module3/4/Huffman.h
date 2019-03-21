//
// Created by andrey on 11/18/18.
//

#ifndef INC_4_HUFFMAN_H
#define INC_4_HUFFMAN_H

#include <iostream>

typedef unsigned char byte;

struct IInputStream {
    virtual bool Read(byte &value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};

class ConsoleInputStream : public IInputStream {
public:
    bool Read(byte &value) override {
        char c = 0;
        std::cin.get(c);
        if (std::cin.fail())
            return false;
        value = (byte)c;
        return true;
    }
};

class ConsoleOutputStream : public IOutputStream {
public:
    void Write(byte value) override {
        std::cout << (char)value;
    }
};

void Encode(IInputStream &original, IOutputStream &compressed);
void Decode(IInputStream &compressed, IOutputStream &original);

#endif //INC_4_HUFFMAN_H
