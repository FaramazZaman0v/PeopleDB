#include <QApplication>
#include "peopledb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DbManager DbManage("/home/student-8/Desktop/C++code/DbManager/DBManager3/people.db");
    DbManage.addPerson("Timmy");
    DbManage.personExists("Timmy");
    DbManage.printAll();

    MainWindow window;
    window.resize(250, 150);
    window.setWindowTitle("TxT");
    window.show();

    return app.exec();
}
