#include "Linky_Frame.h"

int main() {
    serial = initSerial();
    if (serial == -1) {
        printf("No serial\n");
        return 0;
    }

    Linky_Frame frame;
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

// Open serial port on ttyAMA0
init initSerial() {
    int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyAMA0 - ");
    }
    else {
        fcntl(fd, F_SETFL, 0);
    }

    usleep(50000);

    return fd;
}
