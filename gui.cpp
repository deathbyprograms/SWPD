#include "gui.h"
#include "ui_gui.h"
#include "swpd.h"
#include <QFileDialog>
#include <QString>

//Sets up the window.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Result->hide();
}

//Deletes the window when it needs to.
MainWindow::~MainWindow()
{
    delete ui;
}

//This function is called when the "Choose a folder" button is pressed.
void MainWindow::on_Directory_clicked()
{
    //Opens up a window for the user to choose a directory to search.
    QString filename = QFileDialog::getExistingDirectory();

    //Displays that choice in the text box next to the button.
    ui->Display->setText(filename);
}

//Closes the application when the close button is pressed
void MainWindow::on_buttonBox_rejected()
{
    QApplication::quit();
}

//When the OK button is pressed
void MainWindow::on_buttonBox_accepted()
{
    //Stop the calculation if the result was already done.
    if(ui->Result->isVisible())return;

    //Takes the text that is currently in the text box as the directory to search.
    QString filename = ui->Display->text();

    //Turns the QString that the text box outputs and turns it into a C-style string.
    QByteArray ba = filename.toLatin1();
    const char *usable = (char*)calloc(filename.length()+1,1);
    usable = ba.constData();

    //Shows the result box on the window, where it had been hidden before.
    ui->Result->show();

    //Passes the directory to the backbone function and displays the answer in the result box.
    const char* answer = run(usable);
    ui->Result->setPlainText(QString::fromLatin1(answer));
}
