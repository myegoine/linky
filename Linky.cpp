#include "Linky_Frame.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Open serial port on ttyAMA0
int initSerial() {
    int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("open_port: Unable to open /dev/ttyAMA0 - ");
    }
    else {
        fcntl(fd, F_SETFL, 0);
    }

    usleep(50000);

    return fd;
}

int main() {
    int serial = initSerial();
    if (serial == -1) {
        printf("No serial\n");
        return 0;
    }

    Linky_Frame frame;
    char c;
    while (1) {
        c = read(serial, &c, 1);
        frame.addByte(c);
        if (frame.isComplete()) {
            break;
        }
        if (frame.isError()) {
            printf("Error\n");
            return 0;
        }
    }
}
