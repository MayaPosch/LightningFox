#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <sqlite3.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void syncEmail();
    void quit();
    
private:
	static bool processAccountEntries(void* data, int argc, char* argv[], char* colNames[]);
	static bool processMailEntries(void* data, int argc, char* argv[], char* colNames[]);

    Ui::MainWindow *ui;
	
	sqlite3* settings = 0;
};

#endif // MAINWINDOW_H
