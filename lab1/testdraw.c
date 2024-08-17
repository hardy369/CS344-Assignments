
#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char *argv[]) {
    char buf[256];
    int result;

    result = draw(buf, sizeof(buf));

    if (result < 0) {
        printf(1, "draw failed\n");
        exit();
    }

    printf(1, "draw succeeded, %d bytes copied:\n", result);
    printf(1, "%s\n", buf);

    exit();
}

