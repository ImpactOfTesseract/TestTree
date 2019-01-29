#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->selectItemBox->addItem("Integer");
    ui->selectItemBox->addItem("Double");
    ui->selectItemBox->addItem("Char[10]");
    ui->addItemButton->setEnabled(0);
    ui->treeWidget ->setColumnCount(2);

    QStringList header;
    header << "Value" << "Type";
    QTreeWidgetItem* header_item = new QTreeWidgetItem(header);
    ui->treeWidget->setHeaderItem(header_item);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::visualizeTree(BaseHolder* root, QTreeWidgetItem* parent){
    if(root->getChildrenSize()==0)
        return;
    else{
        for(unsigned long long i=0; i < root->getChildrenSize(); i++){
            QStringList values;
            values << QString::fromStdString(root->getChild(i)->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$")) //удаляются лишние нули и разделитель
                   << QString::fromStdString(root->getChild(i)->getType());
            QTreeWidgetItem* child = new QTreeWidgetItem(values);
            this->hash[child] = root->getChild(i);

            parent->addChild(child);
            this->visualizeTree(root->getChild(i), child);
        }
        return;
    }
}


//событие нажатия на кнопку "Добавление элемента"
void MainWindow::on_addItemButton_clicked()
{
    if(this->ui->selectItemBox->currentText()=="Integer"){   //Для типа Integer
        if(this->ui->lineEdit->hasAcceptableInput()){
            BaseHolder* newborn = new IntHolder(this->ui->lineEdit->text().toInt());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            QTreeWidgetItem* child = new QTreeWidgetItem(values);
            if(this->ui->treeWidget->currentItem()){
                this->hash.value(this->ui->treeWidget->currentItem())->appendChild(newborn);
                this->ui->treeWidget->currentItem()->addChild(child);
                this->hash[child] = newborn;
            }
        } else {
            QMessageBox msgBox;
            msgBox.setText("Input does not fit the range for integer values");
            msgBox.exec();
        }
    } else                                                  //Для типа Double
    if(this->ui->selectItemBox->currentText()=="Double"){
        if(this->ui->lineEdit->hasAcceptableInput()){
            BaseHolder* newborn = new DoubleHolder(this->ui->lineEdit->text().toDouble());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$"))              //удаляются лишние нули и разделитель
                   << QString::fromStdString(newborn->getType());
            QTreeWidgetItem* child = new QTreeWidgetItem(values);
            if(this->ui->treeWidget->currentItem()){
                this->hash.value(this->ui->treeWidget->currentItem())->appendChild(newborn);
                this->ui->treeWidget->currentItem()->addChild(child);
                this->hash[child] = newborn;
            }
        } else{
            QMessageBox msgBox;
            msgBox.setText("Input does not fit the range for double values");
            msgBox.exec();
        }
    } else
    if(this->ui->selectItemBox->currentText()=="Char[10]"){         //Для типа Char[10]
        char buffer[10] = "         ";
        for(int i = 0; i < this->ui->lineEdit->text().size(); i++ ){
            buffer[i] = this->ui->lineEdit->text()[i].toLatin1();
        }

        BaseHolder* newborn = new CharArrayHolder(buffer);
;
        QStringList values;
        values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
        QTreeWidgetItem* child = new QTreeWidgetItem(values);
        if(this->ui->treeWidget->currentItem()){
            this->hash.value(this->ui->treeWidget->currentItem())->appendChild(newborn);
            this->ui->treeWidget->currentItem()->addChild(child);
            this->hash[child] = newborn;
        }
    }
}

//при изменении значения в ItemBox изменяются настройки валидации lineEdit
void MainWindow::on_selectItemBox_currentTextChanged(const QString &arg1)
{
    if(this->ui->selectItemBox->currentText()=="Integer"){ //настройки валидации для int
        this->ui->lineEdit->setValidator(new QIntValidator(-2147483648, 2147483647, this->ui->lineEdit));
        this->ui->lineEdit->setMaxLength(11);
        this->ui->lineEdit->clear();
    } else
    if(this->ui->selectItemBox->currentText()=="Double"){  //настрйоки валидации для double
        QLocale lo(QLocale::C);
        lo.setNumberOptions(QLocale::RejectGroupSeparator);//принимать точку как разделитель

        auto val = new QDoubleValidator(-9223372036854775808.0, 9223372036854775807.0, 2, this);
        val->setLocale(lo);
        this->ui->lineEdit->setValidator(val);
        this->ui->lineEdit->setMaxLength(24);
        this->ui->lineEdit->clear();
    } else
    if(this->ui->selectItemBox->currentText()=="Char[10]"){//настройки валидации для char[10]
        this->ui->lineEdit->setValidator(nullptr);
        this->ui->lineEdit->setMaxLength(10);
        this->ui->lineEdit->clear();
    }
}

//при нажатии на элемент дерева он выбирается как текущий
void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    this->ui->treeWidget->setCurrentItem(item);
}

//при нажатии на кнопку удаления элемента текущий элемент удаляется
void MainWindow::on_removeItemButton_clicked()
{
    if(this->ui->treeWidget->currentItem() && this->ui->treeWidget->currentItem()->parent()){ //если у элемента есть родитель, значит он не корень дерева
        this->hash.value(this->ui->treeWidget->currentItem()->parent())->removeChild(this->hash.value(this->ui->treeWidget->currentItem()));
        delete this->hash.value(this->ui->treeWidget->currentItem());
        this->hash.remove(this->ui->treeWidget->currentItem());
        this->ui->treeWidget->currentItem()->parent()->takeChild(this->ui->treeWidget->currentItem()->parent()->indexOfChild(this->ui->treeWidget->currentItem()));
    } else if (this->ui->treeWidget->currentItem() && !this->ui->treeWidget->currentItem()->parent()){ //если у этого элемента нет родителя, значит он корень дерева
        delete this->hash.value(this->ui->treeWidget->currentItem());
        this->hash.remove(this->ui->treeWidget->currentItem());
        this->ui->treeWidget->takeTopLevelItem(this->ui->treeWidget->indexOfTopLevelItem(this->ui->treeWidget->currentItem()));
        if(this->ui->treeWidget->topLevelItemCount()==0){
            this->ui->addItemButton->setDisabled(1);
        }
    }
}

//добавление элемента как корень нового дерева, во много идентично с on_addItemButton_clicked()
void MainWindow::on_addAsTopButton_clicked()
{
    if(!this->ui->addItemButton->isEnabled())
        this->ui->addItemButton->setEnabled(1); //разрешать добавлять детей тогда, когда есть хотя бы один корневой элемент

    if(this->ui->selectItemBox->currentText()=="Integer"){
        if(this->ui->lineEdit->hasAcceptableInput()){
            BaseHolder* newborn = new IntHolder(this->ui->lineEdit->text().toInt());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            QTreeWidgetItem* child = new QTreeWidgetItem(values);
            this->ui->treeWidget->addTopLevelItem(child);
            this->hash[child] = newborn;
        } else {
            QMessageBox msgBox;
            msgBox.setText("Input does not fit the range for integer values");
            msgBox.exec();
        }
    } else
    if(this->ui->selectItemBox->currentText()=="Double"){
        if(this->ui->lineEdit->hasAcceptableInput()){
            BaseHolder* newborn = new DoubleHolder(this->ui->lineEdit->text().toDouble());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$")) << QString::fromStdString(newborn->getType());
            QTreeWidgetItem* child = new QTreeWidgetItem(values);
            this->ui->treeWidget->addTopLevelItem(child);
            this->hash[child] = newborn;
        } else {
            QMessageBox msgBox;
            msgBox.setText("Input does not fit the range for double values");
            msgBox.exec();
        }
    } else
    if(this->ui->selectItemBox->currentText()=="Char[10]"){
        char buffer[10] = "         ";
        for(int i = 0; i < this->ui->lineEdit->text().size(); i++ ){
            buffer[i] = this->ui->lineEdit->text()[i].toLatin1();
        }
        BaseHolder* newborn = new CharArrayHolder(buffer);
        QStringList values;
        values << QString::fromStdString(newborn->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$")) << QString::fromStdString(newborn->getType());
        QTreeWidgetItem* child = new QTreeWidgetItem(values);
        this->ui->treeWidget->addTopLevelItem(child);
        this->hash[child] = newborn;
    }
}

//кнопка сохранения дерева в файл, вызывает рекурсивный метод WriteTree, помечает корни деревьев с помощью '#'
void MainWindow::on_saveToFileButton_clicked()
{
    auto filename = QFileDialog::getSaveFileName(this, tr("Save Tree"),"",tr("*.Txt file (*.txt)"));

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    try {
        for(int i = 0; i < this->ui->treeWidget->topLevelItemCount(); i++){
            out << "#,";
            WriteTree(hash.value(this->ui->treeWidget->topLevelItem(i)), &out);
        }
    } catch (const char* message) {
        QMessageBox msgBox;
        msgBox.setText("Failed to save to file");
        msgBox.exec();
    }


    file.close();
}

//рекурсивный метод записи дерева в файл. Помечает листья дерева с помощью '!'. Записывает построчно значение вместе с типом элемента, разделяя все значимые части строки запятыми
void MainWindow::WriteTree(BaseHolder* item, QTextStream* outstream){
    if(item->getChildrenSize()==0){
        *outstream << QString::fromStdString(item->getType()) << "," << QString::fromStdString(item->getValue()) << ",!" << "\n";
    } else{
        *outstream << QString::fromStdString(item->getType()) << "," << QString::fromStdString(item->getValue()) << ",\n";
        for(unsigned long long i = 0; i < item->getChildrenSize(); i++){
            WriteTree(item->getChild(i), outstream);
        }
    }
}

//кнопка загрузки дерева из файла, вызывает рекурсивный метод LoadTree
void MainWindow::on_loadFromFileButton_clicked()
{
    for(int i = 0; i < this->ui->treeWidget->topLevelItemCount(); i++){
        delete this->hash.value(this->ui->treeWidget->topLevelItem(i));
        this->hash.take(this->ui->treeWidget->topLevelItem(i));
        this->ui->treeWidget->takeTopLevelItem(i);
    }

    this->hash.clear();

    auto filename = QFileDialog::getOpenFileName(this, tr("Open Tree"),"",tr("*.Txt file (*.txt)"));

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    try {
        while(LoadTree(nullptr, nullptr, &in));
    } catch (const char* message) {
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }

    ui->addItemButton->setEnabled(1);
    file.close();
}

//рекурсивный метод загрузки дерева из файла.
int MainWindow::LoadTree(BaseHolder* parent,QTreeWidgetItem* visparent, QTextStream *instream){
    if(instream->atEnd()){ //если достигли конца файла, возвращаем ноль и выходим из функции
        return 0;
    }

    ui->addItemButton->setEnabled(0);
    QString line = instream->readLine(); //считываем строку
    QStringList items = line.split(","); //разделяем её на подстроки с помощью запятых

    QByteArray array = line.toLocal8Bit(); //представление строки в виде массива символов
    char* buffer = array.data();           //для исключительных случаев, когда в контейнерах типа char[10]
                                           //могут попадаться символы, соответствующие разделителям ',' и '!'

    if(items[0]=="#"){                     //если первый символ - обозначение корня дерева

        BaseHolder* newborn;               //создаём контейнер для хранения
        QTreeWidgetItem* child;            //и элемент дерева
        if(items[1]=="Integer"){           //если тип - int
            newborn = new IntHolder(items[2].toInt());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            this->ui->treeWidget->addTopLevelItem(child);
            this->hash[child] = newborn;
        } else if (items[1]=="Double"){    //если тип - double
            newborn = new DoubleHolder(items[2].toDouble());
            QStringList values;
            values << QString::fromStdString(newborn->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$")) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            this->ui->treeWidget->addTopLevelItem(child);
            this->hash[child] = newborn;
        } else if (items[1]=="Char[10]"){  //если тип - char[10]
            QByteArray array = line.toLocal8Bit();
            char* buffer = array.data();
            char buffer2[10] = "         ";         //буфер для хранения конечной строки
            for(int i = 0; i<QString(buffer).size()-1; i++){ //проходим через всю считанную строку
                if (QString(buffer)[i] == ']'){              //закрывающая скобка гарантированно означает, что закончено объявление типа в строке
                    if(QString(buffer)[QString(buffer).size()-1]=='!'){    //если последний элемент в строке - '!', указатель на отсутствие детей у элемента
                        int j; int it = 0;                           //устанавливаем итератор в позицию, следующую после ',' после 'char[10]'
                        for(j = i+2; j<QString(buffer).size()-2; j++){     //считываем участок строки от установленного итератора до запятой, предшествующей указателю '!'
                            buffer2[it] = QString(buffer)[j].toLatin1();   //записываем её в конечный буфер
                            it++;
                        }
                    } else{   //если последний элемент - произвольный
                        int j = i+2; int it = 0;         //устанавливаем итератор в позицию, следующую после ',' после 'char[10]'
                        for(j = i+2; j<QString(buffer).size()-1; j++){ //считываем участок строки от установленного итератора до конца строки
                            buffer2[it] = QString(buffer)[j].toLatin1(); //записываем её в конечный буфер
                            it++;
                        }
                    }
                }
            }
            newborn = new CharArrayHolder(buffer2);
            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            this->ui->treeWidget->addTopLevelItem(child);
            this->hash[child] = newborn;
        } else{        //если получен неожиданный ввод - бросаем исключение
            throw "Failed to read the file";
        }



            if(QString(buffer)[QString(buffer).size()-1]=='!'){ //если предпоследний символ - это указатель на отсутствие детей
                return -1;             //возвращаем соответствующее значение
            } else {               //а иначе
            try {
                while(LoadTree(newborn, child, instream)); //рекурсивно вызываем функцию десериализации для текущего контейнера
            } catch (const char* message) {
                throw message;
            }
        }
        return -1;
    } else {          //для дочерних узлов выполняется тот же процесс, только контейнеры создаются и добавляются как дети, а не как TopLevelItem'ы
        BaseHolder* newborn;
        QTreeWidgetItem* child;
        if(items[0]=="Integer"){
            newborn = new IntHolder(items[1].toInt());
            parent->appendChild(newborn);
            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            visparent->addChild(child);
            this->hash[child] = newborn;
        } else if (items[0]=="Double"){
            newborn = new DoubleHolder(items[1].toDouble());
            parent->appendChild(newborn);
            QStringList values;
            values << QString::fromStdString(newborn->getValue()).remove(QRegExp("0+$")).remove(QRegExp("\\.$")) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            visparent->addChild(child);
            this->hash[child] = newborn;
        } else if (items[0]=="Char[10]"){
            QByteArray array = line.toLocal8Bit();
            char* buffer = array.data();
            char buffer2[10]= "         ";
            for(int i = 0; i<QString(buffer).size()-1; i++){
                if (QString(buffer)[i] == ']'){
                    if(QString(buffer)[QString(buffer).size()-1]=='!'){
                        int j; int it = 0;
                        for(j = i+2; j<QString(buffer).size()-2; j++){
                            buffer2[it] = QString(buffer)[j].toLatin1();
                            it++;
                        }
                    } else{
                        int j; int it = 0;
                        for(j = i+2; j<QString(buffer).size()-1; j++){
                            buffer2[it] = QString(buffer)[j].toLatin1();
                            it++;
                        }
                    }
                }
            }
            qInfo() << "hey";
            qInfo() << QString::fromStdString(parent->getValue());
            qInfo() << "ho";
            newborn = new CharArrayHolder(buffer2);
            parent->appendChild(newborn);


            QStringList values;
            values << QString::fromStdString(newborn->getValue()) << QString::fromStdString(newborn->getType());
            child = new QTreeWidgetItem(values);
            visparent->addChild(child);
            this->hash[child] = newborn;
        }

        if(QString(buffer)[QString(buffer).size()-1]=='!'){
            return -1;
        } else {
            try {
                while(LoadTree(newborn, child, instream)!=-1);
            } catch (const char* message) {
                throw message;
            }

        return -1;
        }
  }
}


