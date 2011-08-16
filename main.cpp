#include "ImageColorBoolModel.h"
#include "CheckBoxDelegate.h"
#include <QtGui/QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageColorBoolModel model;
	model.setColumnCount(4);
	model.setColumnType(0, ImageColorBoolModel::NameColumn);
	model.setColumnType(1, ImageColorBoolModel::ImageColumn);
	model.setColumnType(2, ImageColorBoolModel::ColorColumn);
	model.setColumnType(3, ImageColorBoolModel::BoolColumn);
	model.insertRows(0, 2);
	model.setData(model.index(0, 0), "Carl");
	model.setData(model.index(0, 1), "Carl.png");
	model.setData(model.index(0, 2), "#FF0000");
	model.setData(model.index(0, 3), true);
	
	model.setData(model.index(1, 0), "Carl");
	model.setData(model.index(1, 1), "Carl.png");
	model.setData(model.index(1, 2), "#FF0000");
	model.setData(model.index(1, 3), false);

	QTableView view;
	view.setModel(&model);
	view.setItemDelegate(new CheckBoxDelegate(QSet<int>() << 3, &view));
	view.show();
	return a.exec();
}
