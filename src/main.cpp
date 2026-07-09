#include <QApplication>
#include <QMessageBox>
#include "db/DatabaseManager.h"
#include "ui/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Bookstore Management System");


    if (!DatabaseManager::instance().open("bookstore.db")) {
        QMessageBox::critical(nullptr, "Lỗi",
                              "Không thể mở database. Ứng dụng sẽ thoát.");
        return 1;
    }

    MainWindow w;
    w.show();
    return app.exec();
}
