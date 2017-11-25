#ifndef GUI_H
#define GUI_H

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
    void on_Directory_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::MainWindow *ui;
};

#endif // GUI_H
