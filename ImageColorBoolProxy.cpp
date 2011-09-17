#include "ImageColorBoolProxy.h"
#include <QPixmap>

//////////////////////////////////////////////////////////////////////////
ImageColorBoolProxy::ImageColorBoolProxy(QObject* parent)
: QSortFilterProxyModel(parent), imageColumn(-1), imageSize(64, 64)
{}

void ImageColorBoolProxy::setColumnType(int column, ColumnType type) {
	columnTypes[column] = type;
}

ImageColorBoolProxy::ColumnType ImageColorBoolProxy::getColumnType(int column) const {
	return columnTypes.contains(column) ? columnTypes[column] : RegularColumn;
}

QVariant ImageColorBoolProxy::data(const QModelIndex& idx, int role) const
{
	if(!idx.isValid())
		return QVariant();

	ColumnType columnType = getColumnType(idx.column());
	if(columnType == NameColumn && imageColumn != -1)
	{
		bool gray = grayImageBy > -1 ? 
			!QSortFilterProxyModel::data(index(idx.row(), grayImageBy)).toBool() : false;
		if(role == Qt::DecorationRole)
		{
			// get the image from the image column
			QString fileName = QSortFilterProxyModel::data(index(idx.row(), imageColumn)).toString();
			QImage image = QImage(fileName).scaled(imageSize);

			// gray the image by the bool column
			return gray ? toGrayPixmap(image) : QPixmap::fromImage(image);
		}
		else if(role == Qt::ForegroundRole) {   // gray the text
			return gray ? QColor(Qt::gray) : QSortFilterProxyModel::data(idx, role);
		}
	}
	else if(columnType == ColorColumn) {
		if(role == Qt::BackgroundColorRole)
			return QColor(QSortFilterProxyModel::data(idx, Qt::DisplayRole).toString());
		else if(role == Qt::DisplayRole)   // hide the text
			return QVariant();
	}

	return QSortFilterProxyModel::data(idx, role);
}

// make a gray image by copy-pasting every pixel from the original image
QPixmap ImageColorBoolProxy::toGrayPixmap(const QImage& colorImage)
{
	int width  = colorImage.width();
	int height = colorImage.height();
	QImage grayImage(width, height, QImage::Format_RGB32);
	for(int i=0; i<width; ++i)
		for(int j=0; j<height; ++j)
		{
			int pixel = colorImage.pixel(i, j);
			int alpha = qAlpha(pixel);
			if(alpha == 0)   // make transparent pixel white
				grayImage.setPixel(i, j, qRgb(255, 255, 255));
			else
			{
				int gray = qGray(pixel);
				grayImage.setPixel(i, j, qRgb(gray, gray, gray));
			}
		}
		return QPixmap::fromImage(grayImage);
}