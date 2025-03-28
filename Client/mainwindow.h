#pragma once

#include <QMainWindow>
#include <QAbstractSocket>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void connect();
    void read_folder();
    void open_item(QListWidgetItem *item);
    void text_error(QString);

private:
    Ui::MainWindow *ui;
};
