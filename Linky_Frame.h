#define STX 0x02 // STX
#define ETX 0x03 // ETX
#define EOT 0x04 // EOT

#define BUFFER_SIZE 128

class Linky_Frame
{
  public:
    Linky_Frame();
    void init();
    bool isComplete();
    bool isError();
    void addByte(char byte);
    char *getFrame();

  private:
    char _frame[BUFFER_SIZE];
    int _size;
};
