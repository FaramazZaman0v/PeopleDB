#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class DbManager
{
public:
    DbManager(const QString &path);
    bool addPerson(const QString &name);
    bool personExists(const QString &name);

    bool removePerson(const QString &name);
    void printAll() const;
    bool removeAll();
    ~DbManager();

private:
    QSqlDatabase m_db;
};

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr);
    void AddPerson();
    void RemovePerson();
    void RemoveAll();
    void PrintAll();
    void PersonExists();

private:
    QLineEdit *lbl;
    DbManager m_db;
};
