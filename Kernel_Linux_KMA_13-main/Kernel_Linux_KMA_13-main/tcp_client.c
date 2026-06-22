#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Toi la Client. Chuc Server mot ngay tot lanh!";
    char buffer[1024] = {0};

    printf("=== TCP CLIENT ===\n");

    // 1. Tạo Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nLỗi tạo Socket \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Chuyển đổi địa chỉ IPv4 từ Text sang Binary (Gọi vào localhost)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nĐịa chỉ không hợp lệ \n");
        return -1;
    }

    // 2. Connect: Bắt tay (3-way handshake) với Server
    printf("[+] Đang cố gắng kết nối tới 127.0.0.1:%d...\n", PORT);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nKết nối thất bại. Server đã bật chưa?\n");
        return -1;
    }

    // 3. Gửi và Nhận dữ liệu
    send(sock, message, strlen(message), 0);
    printf("[+] Đã gửi tin nhắn đi.\n");
    
    read(sock, buffer, 1024);
    printf("[+] Phản hồi từ Server:\n%s\n", buffer);

    close(sock);
    return 0;
}