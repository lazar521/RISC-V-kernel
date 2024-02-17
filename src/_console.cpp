#include "../h/_console.h"


int _console::INTERRUPT_CODE = 0x0A;

_buffer* _console::inputBuffer = nullptr;
_buffer* _console::outputBuffer = nullptr;


char _console::getc() {
    _console::processInputStream();
    return inputBuffer->get();
}

void _console::putc(char c) {
    outputBuffer->put(c);
    _console::processOutputStream();
}

void _console::processInputStream() {
    char* STATUS_REG = (char*) CONSOLE_STATUS ;
    char* DATA_READ_REG = (char*) CONSOLE_RX_DATA;

    while( (*STATUS_REG & CONSOLE_RX_STATUS_BIT) && inputBuffer->hasSpace()){
        volatile char data = *DATA_READ_REG;
        _console::inputBuffer->put(data);
    }
}

void _console::processOutputStream() {
    char* STATUS_REG = (char*) CONSOLE_STATUS;
    char* DATA_SEND_REG = (char*) CONSOLE_TX_DATA;

    while( (*STATUS_REG & CONSOLE_TX_STATUS_BIT) && outputBuffer->hasElements()){
        *DATA_SEND_REG = _console::outputBuffer->get();
    }
}

void _console::initConsole() {
    _console::inputBuffer = new _buffer(1000);
    _console::outputBuffer = new _buffer(1000);
}
