# Dữ liệu mẫu (seed data)

Dữ liệu này được nạp tự động bởi `DatabaseManager::seedIfEmpty()` — xem `src/db/DatabaseManager.cpp`.

**Chỉ chạy khi bảng `products` còn rỗng** (lần đầu mở app), nên dữ liệu người dùng nhập sau này
không bao giờ bị ghi đè.

> Muốn nạp lại từ đầu: xoá file `bookstore.db` trong thư mục build rồi chạy lại app.
> File `.db` không được commit lên git (đã nằm trong `.gitignore`).

## Sản phẩm (10)

| ID | Loại | Tên | Giá | Tồn kho | Ghi chú |
|---:|---|---|---:|---:|---|
| 1 | BOOK | Clean Code | 250.000 | 25 | |
| 2 | BOOK | The Pragmatic Programmer | 320.000 | 18 | |
| 3 | BOOK | Design Patterns | 410.000 | 12 | |
| 4 | BOOK | How to Win Friends | 88.000 | 40 | |
| 5 | BOOK | The Alchemist | 79.000 | 4 | **sắp hết hàng** |
| 6 | MAGAZINE | National Geographic | 65.000 | 30 | số 152 |
| 7 | MAGAZINE | Forbes Vietnam | 55.000 | 3 | **sắp hết hàng** |
| 8 | STATIONERY | Thien Long TL-027 Pen | 5.000 | 200 | |
| 9 | STATIONERY | Campus Notebook 200p | 22.000 | 80 | |
| 10 | STATIONERY | Deli Stapler | 45.000 | 15 | |

Có đủ 3 lớp con của `Product` để demo tính đa hình, và 2 sản phẩm tồn kho thấp
để demo cảnh báo sắp hết hàng (dòng tô đỏ trong bảng sản phẩm).

## Khách hàng (4)

| ID | Tên | SĐT | Điểm | Hạng |
|---:|---|---|---:|---|
| 1 | Tran Thi Binh | 0901234567 | 1250 | Gold |
| 2 | Le Minh Cuong | 0912345678 | 640 | Silver |
| 3 | Pham Thu Dung | 0923456789 | 180 | Regular |
| 4 | Hoang Van Em | 0934567890 | 45 | Regular |

Đủ cả 3 hạng để demo hệ thống tích điểm.

## Đơn hàng (4 đơn, 6 dòng chi tiết)

| Đơn | Ngày | Khách | Sản phẩm | Tổng |
|---:|---|---|---|---:|
| 1 | hôm nay | Tran Thi Binh | Clean Code ×2 | 500.000 |
| 2 | hôm nay | Khách vãng lai | Pen ×5, Notebook ×2 | 69.000 |
| 3 | hôm qua | Le Minh Cuong | Design Patterns ×1 | 410.000 |
| 4 | 2 ngày trước | Pham Thu Dung | How to Win Friends ×3, National Geographic ×1 | 329.000 |

Ngày được sinh động bằng `strftime(...,'now','localtime')` nên **luôn tương đối với ngày chạy**
— bảng "Revenue by Day" ở trang Thống kê luôn có sẵn 3 ngày dữ liệu để demo.

## Số liệu Dashboard sau khi seed

- Today's Revenue: **569.000** (2 đơn hôm nay)
- Today's Orders: **2**
- Low Stock Products: **2**
- Revenue by Day: 3 dòng
- Top-Selling Products: 6 dòng
