#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QPushButton>

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

    void upperletter();
    void resizeEvent(QResizeEvent *);
    bool event(QEvent * e);
    void list();
    void fontchange(QString event);

private:
    void cursorend();
    void justsave();
    void saveas();
    void openas();
    void filesname(QFile * file);
    QListWidgetItem * open;
    QListWidgetItem * save;
    QListWidgetItem * savedoc;
    QString savefile;
    QString filename;
    QFileInfo fileInfo;
    bool saved;
    bool game;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
