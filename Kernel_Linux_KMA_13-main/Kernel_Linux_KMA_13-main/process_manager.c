#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    pid_t pid;
    int file_desc;

    printf("--- CHƯƠNG TRÌNH QUẢN LÝ TIẾN TRÌNH & FILE ---\n");

    // 1. Mở hoặc tạo một file log bằng System Call open()
    // O_CREAT: Tạo file nếu chưa có, O_WRONLY: Chỉ ghi, O_APPEND: Ghi nối đuôi
    // 0644: Cấp quyền Đọc/Ghi cho User, chỉ Đọc cho nhóm và người khác
    file_desc = open("system_monitor.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (file_desc < 0) {
        perror("Lỗi khi mở file");
        return 1;
    }

    // 2. Nhân bản tiến trình bằng System Call fork()
    pid = fork();

    if (pid < 0) {
        // Nếu fork trả về số âm -> Thất bại
        perror("Không thể tạo tiến trình con");
        return 1;
    } 
    else if (pid == 0) {
        // fork() trả về 0 -> Đây là TIẾN TRÌNH CON (Child Process)
        char *msg = "LOG: [Tiến trình CON] Đang quét hệ thống...\n";
        
        // Ghi vào file bằng System Call write() thay vì printf/fprintf thông thường
        write(file_desc, msg, strlen(msg));
        
        printf("[+] Tiến trình CON (PID: %d) vừa ghi log thành công.\n", getpid());
        exit(0); // Kết thúc tiến trình con một cách sạch sẽ
    } 
    else {
        // fork() trả về một số dương (>0) -> Đây là TIẾN TRÌNH CHA (Parent Process)
        // Số dương này chính là PID của đứa con vừa sinh ra
        
        char *msg = "LOG: [Tiến trình CHA] Đang giám sát tiến trình con...\n";
        write(file_desc, msg, strlen(msg));
        printf("[+] Tiến trình CHA (PID: %d) đang đợi con hoàn thành...\n", getpid());

        // 3. Tiến trình cha phải ĐỢI con kết thúc để tránh lỗi "Tiến trình Zombie"
        wait(NULL); 
        
        char *final_msg = "LOG: [Tiến trình CHA] Tiến trình con đã thoát. Kết thúc tác vụ.\n";
        write(file_desc, final_msg, strlen(final_msg));
        
        // Đóng file descriptor
        close(file_desc);
        printf("[+] Tiến trình CHA dọn dẹp tài nguyên và thoát.\n");
    }

    return 0;
}