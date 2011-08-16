#include "ImageColorBoolModel.h"

ImageColorBoolModel::ImageColorBoolModel(QObject* parent) 
: QStandardItemModel(parent), imageColumn(-1), imageSize(64, 64)
{}

void ImageColorBoolModel::setColumnType(int column, ColumnType type)
{
	columnTypes[column] = type;
	if(type == ImageColumn)     // remember the ONLY imageColumn
	{
		if(imageColumn != -1)
			columnTypes[imageColumn] = RegularColumn;
		imageColumn = column;
	}
}

ImageColorBoolModel::ColumnType ImageColorBoolModel::getColumnType(int column) const {
	return columnTypes.contains(column) ? columnTypes[column] : RegularColumn;
}

QVariant ImageColorBoolModel::data(const QModelIndex& idx, int role) const
{
	if(!idx.isValid())
		return QStandardItemModel::data(idx, role);

	ColumnType columnType = getColumnType(idx.column());
	if(columnType == NameColumn)        // Name
	{
		if(role == Qt::DecorationRole && imageColumn != -1)
		{
			QImage image(data(index(idx.row(), imageColumn)).toString());
			return QPixmap::fromImage(image.scaled(imageSize));
		}
	}
	else if(columnType == ColorColumn)   // Color
	{
		if(role == Qt::DecorationRole)
			return QColor(QStandardItemModel::data(idx, Qt::DisplayRole).toString());
		else if(role == Qt::DisplayRole)
			return QVariant();
	}
	else if(columnType == BoolColumn)   // Bool
	{

	}

	return QStandardItemModel::data(idx, role);
}

