#include "Linky_Frame.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

// Open serial port on ttyAMA0
int initSerial() {
    printf("Initiating serial\n");
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        printf("open_port: Unable to open /dev/ttyAMA0 - ");
    }
    else {
        fcntl(fd, F_SETFL, 0);

        struct termios options;
        tcgetattr(fd, &options);

        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);

        tcsetattr(fd, TCSANOW, &options);
    }

    usleep(50000);

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
        printf("Start reading\n");
        ssize_t bytesRead =  read(serial, &c, 1);
        printf("Read %d bytes\n", bytesRead);
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
