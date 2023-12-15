#include "Linky_Frame.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// Open serial port on ttyAMA0
int initSerial() {
    printf("Initiating serial\n");
    int fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("open_port: Unable to open /dev/ttyAMA0 - ");
    }
    else {
        printf("fnctl starting\n");
        fcntl(fd, F_SETFL, 0);
        printf("fnctl done\n");
    }

    //usleep(50000);

    printf("Done Initiating serial\n");
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
        printf("%c", c);
        frame.addByte(c);
        if (frame.isComplete()) {
            break;
        }
        if (frame.isError()) {
            printf("Error\n");
            return 0;
        }
        if (frame.isEmpty()) {
            printf("Empty\n");
            return 0;
        }
    }
}
