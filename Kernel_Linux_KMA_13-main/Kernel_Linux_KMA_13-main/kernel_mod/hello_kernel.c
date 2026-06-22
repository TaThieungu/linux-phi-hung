#include <linux/init.h>   // Chứa các macro __init và __exit
#include <linux/module.h> // Chứa các hàm cốt lõi cho module
#include <linux/kernel.h> // Chứa hàm printk()

// Cấp phép bản quyền (Bắt buộc phải có để kernel không từ chối nạp)
MODULE_LICENSE("GPL");
MODULE_AUTHOR("OS Student");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module");

// Hàm chạy khi nạp module vào nhân (insmod)
static int __init he_thong_khoi_dong(void) {
    // printk giống printf, nhưng ghi log vào dmesg của kernel.
    // KERN_INFO là mức độ log (Information)
    printk(KERN_INFO "OS_PROJECT: Module da duoc NAP vao Kernel thanh cong!\n");
    
    // Trả về 0 nghĩa là khởi tạo thành công
    return 0; 
}

// Hàm chạy khi gỡ module ra khỏi nhân (rmmod)
static void __exit he_thong_ket_thuc(void) {
    printk(KERN_INFO "OS_PROJECT: Module da duoc GO khoi Kernel. Tam biet!\n");
}

// Đăng ký 2 hàm trên với hệ thống
module_init(he_thong_khoi_dong);
module_exit(he_thong_ket_thuc);