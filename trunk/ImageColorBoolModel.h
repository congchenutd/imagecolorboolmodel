#ifndef IMAGECOLORBOOLMODEL_H
#define IMAGECOLORBOOLMODEL_H

#include <QStandardItemModel>
#include <QMap>

class ImageColorBoolModel : public QStandardItemModel
{
public:
	typedef enum {RegularColumn, NameColumn, ImageColumn, ColorColumn, BoolColumn} ColumnType;

public:
	ImageColorBoolModel(QObject* parent = 0);
	QVariant data(const QModelIndex& idx, int role = Qt::DisplayRole) const;
	void setColumnType(int column, ColumnType type);
	void setImageSize(const QSize& size) { imageSize = size; }

private:
	ColumnType getColumnType(int column) const;

private:
	QMap<int, ColumnType> columnTypes;
	int imageColumn;
	QSize imageSize;
};

#endif // IMAGECOLORBOOLMODEL_H
