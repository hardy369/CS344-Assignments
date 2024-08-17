// user/Drawtest.c
#include "types.h"
#include "user.h"

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
    char buf[BUFFER_SIZE];
    int result;

    // Call the sys_draw system call
    result = draw(buf, sizeof(buf));

    if (result < 0) {
        printf(2, "draw failed\n");
        exit();
    }

    printf(1, "draw succeeded, %d bytes copied:\n", result);
    printf(1, "%s\n", buf);

    exit();
}

