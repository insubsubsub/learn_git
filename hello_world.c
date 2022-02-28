#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if( argc != 2)
        return (0);
    argv++;
    int fd = open(*argv, O_RDONLY);
    int read_byte;
    char buf[1024];
    while (1)
    {
        read_byte = read(fd, buf, 1024);
        if (read_byte == 0)
            break ;
        write(1, buf, read_byte);
    }
    return (0);
}