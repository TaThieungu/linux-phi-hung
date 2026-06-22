#!/bin/bash

# 1. Khai báo thư mục cần dọn dẹp (Lấy thư mục hiện tại làm ví dụ)
TARGET_DIR="/home/nguyentung/os_project/test_folder"

# Tạo một thư mục test và một vài file rác để test thử
mkdir -p "$TARGET_DIR"
touch "$TARGET_DIR/baocao.txt" "$TARGET_DIR/anh1.jpg" "$TARGET_DIR/system.log" "$TARGET_DIR/note.txt"

echo "Đang tiến hành dọn dẹp thư mục: $TARGET_DIR"

# 2. Vòng lặp duyệt qua tất cả các file trong thư mục
for FILE in "$TARGET_DIR"/*; do
    
    # Kiểm tra xem nó có đúng là một file không (bỏ qua thư mục)
    if [ -f "$FILE" ]; then
        
        # 3. Trích xuất đuôi file (Extension)
        # Lệnh ${FILE##*.} sẽ cắt bỏ mọi thứ trước dấu chấm cuối cùng
        EXT="${FILE##*.}"
        
        # 4. Tạo thư mục tương ứng với đuôi file (nếu chưa có)
        # Cờ -p giúp không báo lỗi nếu thư mục đã tồn tại
        mkdir -p "$TARGET_DIR/$EXT"
        
        # 5. Di chuyển file vào thư mục mới
        mv "$FILE" "$TARGET_DIR/$EXT/"
        
        echo "Đã chuyển $FILE -> Thư mục $EXT/"
    fi
done

echo "Hoàn tất dọn dẹp!"