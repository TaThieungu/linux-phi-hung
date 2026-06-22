#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *reply = "HTTP/1.1 200 OK\n\nXin chao Client! Server da nhan tin hieu.\n";

    printf("=== TCP SERVER BẮT ĐẦU KHỞI ĐỘNG ===\n");

    // 1. Tạo Socket (File descriptor cho mạng)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Lỗi tạo socket");
        exit(EXIT_FAILURE);
    }

    // Cấu hình địa chỉ và Cổng (Port)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Nhận kết nối từ mọi IP
    address.sin_port = htons(PORT);       // Chuyển Port sang định dạng mạng

    // 2. Bind: Gắn socket vào đúng Cổng 8080 của hệ điều hành
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Lỗi Bind (Cổng có thể đang bận)");
        exit(EXIT_FAILURE);
    }

    // 3. Listen: Bật chế độ lắng nghe (Tối đa 3 kết nối đợi)
    if (listen(server_fd, 3) < 0) {
        perror("Lỗi Listen");
        exit(EXIT_FAILURE);
    }
    printf("[+] Đang lắng nghe kết nối tại cổng %d...\n", PORT);

    // 4. Accept: Chặn luồng thực thi, đứng đợi cho đến khi có Client kết nối
    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (client_socket < 0) {
        perror("Lỗi Accept");
        exit(EXIT_FAILURE);
    }

    // 5. Read & Write: Đọc dữ liệu từ Client và Gửi phản hồi
    read(client_socket, buffer, 1024);
    printf("[+] Đã nhận từ Client: %s\n", buffer);
    
    send(client_socket, reply, strlen(reply), 0);
    printf("[+] Đã gửi phản hồi về cho Client.\n");

    // Đóng kết nối
    close(client_socket);
    close(server_fd);
    printf("=== ĐÓNG SERVER ===\n");
    return 0;
}