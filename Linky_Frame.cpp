#include "Linky_Frame.h"
#include <cstring>

Linky_Frame::Linky_Frame() {
    init();
}

void Linky_Frame::init() {
    memset(_frame, 0, BUFFER_SIZE);
    _size = 0;
}

bool Linky_Frame::isComplete() {
  return (_size > 0 && _frame[_size - 1] == ETX);
}

bool Linky_Frame::isError() {
  return ((_size > 0 && _frame[_size - 1] == EOT) || _size == BUFFER_SIZE);
}

bool Linky_Frame::isEmpty() {
  return (_size == 0);
}

void Linky_Frame::addByte(char byte) {
  if (_size == 0 && byte != STX) {
    return;
  }
  _frame[_size++] = byte;
}

char *Linky_Frame::getFrame() {
  return _frame;
}
