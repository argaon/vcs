#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_StartButton_clicked();

    void on_CheckButton_clicked();

    void on_InfoButton_clicked();

    void on_StopButton_clicked();

    void on_cb_account_clicked(bool checked);

    void on_cb_filesystem_clicked(bool checked);

    void on_cb_network_clicked(bool checked);

    void on_cb_log_clicked(bool checked);

    void on_cb_app_clicked(bool checked);

    void on_cb_patch_clicked(bool checked);

    void chk_start();

    void reset();

private:
    Ui::MainWindow *ui;
        int p_max{0};
};

#endif // MAINWINDOW_H
