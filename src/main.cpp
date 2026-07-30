#include <QApplication>
#include <QMessageBox>
#include "db/DatabaseManager.h"
#include "ui/MainWindow.h"
#include "ui/AppStyle.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    AppStyle::apply(app);
    app.setApplicationName("Bookstore Management System");


    if (!DatabaseManager::instance().open("bookstore.db")) {
        QMessageBox::critical(nullptr, "Error",
                              "Unable to open the database. The application will exit.");
        return 1;
    }

    MainWindow w;
    w.show();
    return app.exec();
}
