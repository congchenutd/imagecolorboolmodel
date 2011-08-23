#include "ImageColorBoolModel.h"
#include "ImageColorBoolDelegate.h"
#include <QtGui/QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

bool openDB(const QString& name)
{
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(name);
	return !database.open();
}

void createTables()
{
	QSqlQuery query;
	query.exec("create table Test( \
			   Name    varchar primary key, \
			   Color   varchar, \
			   Image   varchar, \
			   Online  bool, \
			   Receive bool \
			   )");
//	query.exec("insert into Test values (\"Carl\", \"FF0000\", \"Carl.png\", \"true\", \"true\")");
//	query.exec("insert into Test values (\"Mike\", \"00FF00\", \"Mike.png\", \"false\", \"false\")");
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	openDB("Test.db");
	createTables();

	QSqlTableModel model;
	model.setTable("Test");
	model.select();

	ImageColorBoolProxy proxy;
	proxy.setSourceModel(&model);
	proxy.setColumnType(0, ImageColorBoolProxy::NameColumn);
	proxy.setColumnType(1, ImageColorBoolProxy::ColorColumn);
	proxy.setColumnType(2, ImageColorBoolProxy::ImageColumn);
	proxy.setColumnType(3, ImageColorBoolProxy::BoolColumn);
	proxy.setColumnType(4, ImageColorBoolProxy::BoolColumn);
	proxy.setGrayImageBy(3);

	QTableView view;
	view.setModel(&proxy);
	view.setItemDelegate(new ImageColorBoolDelegate(&proxy));
	view.show();
	return a.exec();
}
