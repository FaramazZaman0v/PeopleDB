#include "peopledb.h"
#include "./ui_peopledb.h"

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    if (!m_db.open()) {
        qDebug() << "Connection to database failed";
    } else {
        qDebug() << "Connection to database ok";
    }
}

bool DbManager::removePerson(const QString &name)
{
    bool success = false;
    if (personExists(name)) {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();
        if (!success) {
            qDebug() << "removePerson failed";
        }
    } else {
        qDebug() << "person doesn't exist";
    }
    return success;
}

void DbManager::printAll() const
{
    qDebug() << "People in db:";
    QSqlQuery query("SELECT * FROM people");
    int idName = query.record().indexOf("name");
    while (query.next()) {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool DbManager::removeAll()
{
    bool success = false;
    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM PEOPLE");
    if (removeQuery.exec()) {
        success = true;
    } else {
        qDebug() << "remove failed: " << removeQuery.lastError();
    }
    return success;
}

bool DbManager::addPerson(const QString &name)
{
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO PEOPLE (name) VALUES (:name)");
    query.bindValue(":name", name);
    if (query.exec()) {
        success = true;
    } else {
        qDebug() << "addPerson error:" << query.lastError().text();
    }
    return success;
}

bool DbManager::personExists(const QString &name)
{
    bool found = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM people WHERE name = (:name)");
    query.bindValue(":name", name);
    if (query.exec()) {
        if (query.next()) {
            found = true;
        }
    } else {
        qDebug() << "personExists error: " << query.lastError().text();
    }
    return found;
}

DbManager::~DbManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

//================================================================================

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , lbl(new QLineEdit(""))
    , m_db("/home/student-8/Desktop/C++code/DbManager/DBManager3/people.db")
{
    //quitBtn->setGeometry(50,40,75,30);

    QGridLayout *grid = new QGridLayout(this);

    QPushButton *addPBtn = new QPushButton("AddPerson", this);
    grid->addWidget(addPBtn, 1, 0);
    connect(addPBtn, &QPushButton::clicked, this, &MainWindow::AddPerson);

    QPushButton *cleanPBtn = new QPushButton("RemovePerson", this);
    grid->addWidget(cleanPBtn, 2, 0);
    connect(cleanPBtn, &QPushButton::clicked, this, &MainWindow::RemovePerson);

    QPushButton *cleanAllBtn = new QPushButton("RemoveAll", this);
    grid->addWidget(cleanAllBtn, 3, 0);
    connect(cleanAllBtn, &QPushButton::clicked, this, &MainWindow::RemoveAll);

    QPushButton *printAllBtn = new QPushButton("PrintAll", this);
    grid->addWidget(printAllBtn, 4, 0);
    connect(printAllBtn, &QPushButton::clicked, this, &MainWindow::PrintAll);

    QPushButton *pExBtn = new QPushButton("PersonExists", this);
    grid->addWidget(pExBtn, 5, 0);
    connect(pExBtn, &QPushButton::clicked, this, &MainWindow::PersonExists);

    grid->addWidget(lbl, 0, 0);

    setLayout(grid);
}

void MainWindow::AddPerson()
{
    m_db.addPerson(lbl->text());
    m_db.printAll();
}

void MainWindow::RemovePerson()
{
    m_db.removePerson(lbl->text());
    m_db.printAll();
}

void MainWindow::RemoveAll()
{
    m_db.removeAll();
    m_db.printAll();
}

void MainWindow::PrintAll()
{
    m_db.printAll();
}

void MainWindow::PersonExists()
{
    if (!m_db.personExists(lbl->text()))
        qDebug() << "personExists error";
    else
        qDebug() << "personExist";
}
