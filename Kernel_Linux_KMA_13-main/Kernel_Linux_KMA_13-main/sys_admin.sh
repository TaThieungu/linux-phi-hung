#!/bin/bash

# 1. Kiểm tra xem người dùng có chạy bằng quyền root (sudo) không
if [ "$EUID" -ne 0 ]; then
  echo "LỖI: Bạn phải chạy script này với quyền quản trị!"
  echo "Hãy thử lại bằng lệnh: sudo ./sys_admin.sh"
  exit 1
fi

# Vòng lặp vô hạn để giữ menu luôn hiện cho đến khi chọn Thoát
while true; do
    echo "========================================="
    echo "    CÔNG CỤ QUẢN TRỊ HỆ THỐNG UBUNTU     "
    echo "========================================="
    echo "1. Xem thời gian & Múi giờ hiện tại"
    echo "2. Đồng bộ thời gian tự động qua mạng (NTP)"
    echo "3. Đổi múi giờ thành Việt Nam (Asia/Ho_Chi_Minh)"
    echo "4. Cài đặt một phần mềm (Tự động)"
    echo "5. Gỡ bỏ một phần mềm (Tự động)"
    echo "6. Thoát"
    echo "========================================="
    
    # Đọc lựa chọn của người dùng vào biến 'choice'
    read -p "Mời bạn chọn chức năng (1-6): " choice

    # Xử lý theo từng lựa chọn
    case $choice in
        1)
            echo -e "\n[+] THỜI GIAN HỆ THỐNG:"
            timedatectl
            ;;
        2)
            echo -e "\n[+] ĐANG BẬT ĐỒNG BỘ NTP..."
            timedatectl set-ntp true
            echo "Thành công! Thời gian sẽ tự động lấy từ Internet."
            ;;
        3)
            echo -e "\n[+] ĐANG ĐỔI MÚI GIỜ..."
            timedatectl set-timezone Asia/Ho_Chi_Minh
            echo "Thành công! Múi giờ đã chuyển thành Việt Nam."
            ;;
        4)
            echo -e "\n[+] CÀI ĐẶT PHẦN MỀM"
            read -p "Nhập tên phần mềm muốn cài (VD: htop, tree, curl): " pkg
            echo "Đang tự động cài đặt $pkg..."
            # Cờ -y giúp tự động trả lời Yes, -qq giúp ẩn bớt log rác
            apt-get update -qq
            apt-get install -y "$pkg"
            echo "Xong! Đã cài đặt $pkg."
            ;;
        5)
            echo -e "\n[+] GỠ BỎ PHẦN MỀM"
            read -p "Nhập tên phần mềm muốn gỡ (VD: htop): " pkg
            echo "Đang tự động gỡ bỏ $pkg..."
            # Cờ --purge xóa luôn file cấu hình cũ
            apt-get remove --purge -y "$pkg"
            apt-get autoremove -y
            echo "Xong! Đã gỡ bỏ sạch sẽ $pkg."
            ;;
        6)
            echo -e "\nĐã thoát chương trình. Tạm biệt!"
            break
            ;;
        *)
            echo -e "\nLựa chọn không hợp lệ. Vui lòng nhập từ 1 đến 6!"
            ;;
    esac
    echo "" # In một dòng trống cho dễ nhìn
done