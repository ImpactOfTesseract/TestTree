#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <testreeheaders.h>
#include <QString>
#include <QMainWindow>
#include <QTreeWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void visualizeTree(BaseHolder* root, QTreeWidgetItem* parent); //рекурсивный метод, присваивающий элементам QWidgetTree значения из реализованной структуры дерева
    explicit MainWindow(QWidget *parent = nullptr);
    void WriteTree(BaseHolder* item, QTextStream* outstream);      //рекурсивный метод записи дерева в текстовый файл
    int LoadTree(BaseHolder* parent,QTreeWidgetItem* visparent, QTextStream* instream);      //рекурсивный метод загрузки дерева из файла
    ~MainWindow();

private slots:
    void on_addItemButton_clicked();

    void on_selectItemBox_currentTextChanged(const QString &arg1);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_removeItemButton_clicked();

    void on_addAsTopButton_clicked();

    void on_saveToFileButton_clicked();

    void on_loadFromFileButton_clicked();

private:
    Ui::MainWindow *ui;
    QHash<QTreeWidgetItem*, BaseHolder*> hash;        //ассоциативный массив, позволяющий получать соответствующий указатель на контейнер данных из реализованной структуры дерева по указателю
};                                                    //на элемент QWidgetTree

#endif // MAINWINDOW_H
