#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "binarysearchtree.h"
#include <QStandardItemModel>
#include <stack>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void setAccessLevel(bool accessLevel,QString);
    QString loginPath;
    Ui::MainWindow *ui;
    void getData(QString);
    void updateTable();
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_LogoutButton_clicked();

    void on_pushButton_2_clicked();

    void on_AddUserButton_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_DeleteUserButton_clicked();

    void on_SaveButton_clicked();

    void on_changeToTreeViewBtn_clicked();

    void on_changeToTableViewBtn_clicked();

    void on_leftChildBtn_clicked();

    void on_rightChildBtn_clicked();

    void on_backBtn_clicked();

    void on_tableView_objectNameChanged(const QString &objectName);

private:
    struct clientData{
        clientData(){

        }
        clientData(QString key,QString position,int room,QString mobile,QString phone,QString info){
            this->key = key;
            this->position = position;
            this->room = room;
            this->mobile = mobile;
            this->phone = phone;
            this->info=info;
        }
        clientData(const clientData& rhs){
            key = rhs.key;
            position = rhs.position;
            room = rhs.room;
            mobile = rhs.mobile;
            phone = rhs.phone;
            info = rhs.info;
        }

        QString key;
        QString position;
        int room;
        QString mobile;
        QString phone;
        QString info;
    };
    QString pathToDataFile;
    QString accessLevel;
    BinarySearchTree<QString,clientData> bst;
    QStandardItemModel *model;
    QStandardItemModel *searchModel;
    bool isTreeView;
    node<QString,clientData>* ptr;
    stack<node<QString,clientData>*>undo;
    void updateDisplay();
    void hideButtons(bool);
    void emptyStack();
};

#endif // MAINWINDOW_H
