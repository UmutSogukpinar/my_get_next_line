#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

// char    *get_next_line(int fd)
// {
//     int static current_line = 0;

//     if (ft_get_indent(current_line, fd) > 0)
//     {

//     }
//     return (NULL);
// }

int    ft_get_indent(int wanted_line, int fd)
{
    char       c;
    int     current_line;

    current_line = 0;
    while (current_line < wanted_line)
    {
        if (read(fd, &c, 1) <= 0)
            return  (-1);
        if (c == '\n')
            current_line++;
    }
    return (1);
}



// int main() {
//     char buffer[123];
//     char buffer2[123];

//     int fd = open("deneme.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Dosya açılamadı");
//         return 1;
//     }

//     // İlk satırı atla
//     if (ft_get_indent(1, fd) == -1) {
//         perror("Satır bulunamadı");
//         close(fd);
//         return 1;
//     }

//     // İlk okuma işlemi
//     ssize_t bytesRead = read(fd, buffer, 8);
//     if (bytesRead <= 0) {
//         perror("Okuma hatası");
//         close(fd);
//         return 1;
//     }
//     printf("bytesread is : %d\n", bytesRead);
//     buffer[4] = '\0'; // Sonlandırma karakteri ekle

//     // İkinci satırı atla
//     if (ft_get_indent(1, fd) == -1) { // wanted_line parametresi düzeltilmeli
//         perror("Satır bulunamadı");
//         close(fd);
//         return 1;
//     }

//     // İkinci okuma işlemi
//     bytesRead = read(fd, buffer2, 8);
//     if (bytesRead <= 0) {
//         perror("Okuma hatası");
//         close(fd);
//         return 1;
//     }
//     buffer2[6] = '\0'; // Sonlandırma karakteri ekle

//     close(fd);

//     // Okunan verileri ekrana yazdır
//     printf("1. satırdan sonraki 8 karakter: %s\n", buffer);
//     printf("2. satırdan sonraki 8 karakter: %s\n", buffer2);

//     return 0;
// }