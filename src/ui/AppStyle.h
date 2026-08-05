#ifndef APPSTYLE_H
#define APPSTYLE_H

class QApplication;

/*
 * AppStyle — bảng màu và style dùng chung cho toàn bộ giao diện.
 * Phụ trách: Nguyễn Phúc Lộc
 *
 * Gọi một lần trong main(). Các module không tự đặt màu/font riêng
 * để giao diện đồng nhất giữa bốn màn hình.
 */
class AppStyle
{
public:
    static void apply(QApplication& app);
};

#endif 