#include "AppStyle.h"

#include <QApplication>
#include <QFont>
#include <QStyleFactory>

void AppStyle::apply(QApplication& app)
{
    app.setStyle(QStyleFactory::create("Fusion"));
    app.setFont(QFont("Segoe UI", 10));

    app.setStyleSheet(R"(
        QWidget {
            font-family: "Segoe UI";
            font-size: 10pt;
            color: #1F2937;
            background-color: #F6F7F9;
        }

        QMainWindow {
            background-color: #F6F7F9;
        }

        QLabel {
            background: transparent;
        }

        QListWidget {
            background-color: #111827;
            color: #E5E7EB;
            border: none;
            padding: 8px;
        }

        QListWidget::item {
            padding: 12px 10px;
            margin: 2px;
            border-radius: 6px;
        }

        QListWidget::item:selected {
            background-color: #2563EB;
            color: white;
        }

        QListWidget::item:hover {
            background-color: #374151;
        }

        QLineEdit,
        QComboBox,
        QSpinBox,
        QDoubleSpinBox,
        QDateEdit {
            background-color: #FFFFFF;
            border: 1px solid #D1D5DB;
            border-radius: 6px;
            padding: 6px 8px;
            min-height: 24px;
        }

        QLineEdit:focus,
        QComboBox:focus,
        QSpinBox:focus,
        QDoubleSpinBox:focus,
        QDateEdit:focus {
            border: 1px solid #2563EB;
        }

        QPushButton {
            background-color: #2563EB;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 7px 12px;
            min-height: 26px;
        }

        QPushButton:hover {
            background-color: #1D4ED8;
        }

        QPushButton:pressed {
            background-color: #1E40AF;
        }

        QPushButton:disabled {
            background-color: #9CA3AF;
        }

        QPushButton[danger="true"] {
            background-color: #DC2626;
        }

        QPushButton[danger="true"]:hover {
            background-color: #B91C1C;
        }

        QPushButton[secondary="true"] {
            background-color: #FFFFFF;
            color: #1F2937;
            border: 1px solid #D1D5DB;
        }

        QPushButton[secondary="true"]:hover {
            background-color: #F3F4F6;
        }

        QTableWidget,
        QTableView {
            background-color: #FFFFFF;
            alternate-background-color: #F9FAFB;
            gridline-color: #E5E7EB;
            border: 1px solid #D1D5DB;
            border-radius: 6px;
            selection-background-color: #DBEAFE;
            selection-color: #1F2937;
        }

        QHeaderView::section {
            background-color: #E5E7EB;
            color: #1F2937;
            padding: 8px;
            border: none;
            border-right: 1px solid #D1D5DB;
            font-weight: bold;
        }

        QGroupBox {
            background-color: #FFFFFF;
            border: 1px solid #D1D5DB;
            border-radius: 8px;
            margin-top: 14px;
            padding: 10px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 4px;
            color: #374151;
            font-weight: bold;
        }

        QFrame#card {
            background-color: #FFFFFF;
            border: 1px solid #E5E7EB;
            border-radius: 10px;
        }

        QMessageBox {
            background-color: #F6F7F9;
        }
    )");
}