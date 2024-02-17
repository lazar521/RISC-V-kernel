#ifndef KOPIJA_PROJECT_BASE__CONSOLE_H
#define KOPIJA_PROJECT_BASE__CONSOLE_H

#include "printFucntions.h"
#include "../lib/hw.h"
#include"_buffer.h"

class _buffer;

class _console {
public:
    static int INTERRUPT_CODE;

    static char getc();
    static void putc (char c);

    static void processInputStream();
    static void processOutputStream();

    static void initConsole();
private:
    static _buffer* inputBuffer;
    static _buffer* outputBuffer;
};







#endif //KOPIJA_PROJECT_BASE__CONSOLE_H
