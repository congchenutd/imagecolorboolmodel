#ifndef IMAGECOLORBOOLMODEL_H
#define IMAGECOLORBOOLMODEL_H

#include <QAbstractProxyModel>
#include <QMap>
#include <QSize>
#include <QSortFilterProxyModel>

// A proxy model that supports image, checkable, and color columns
class ImageColorBoolProxy : public QSortFilterProxyModel
{
public:
	typedef enum {
		RegularColumn, // plain old type
		NameColumn,    // use an image for DecorationRole
		ImageColumn,   // the path of the image
		ColorColumn,   // a color block
		BoolColumn     // checkable, work with ImageColorBoolDelegate
	} ColumnType;

public:
	ImageColorBoolProxy(QObject* parent = 0);

	virtual QVariant data(const QModelIndex& idx, int role = Qt::DisplayRole) const;

	ColumnType getColumnType(int column) const;
	void setColumnType(int column, ColumnType type);
	void setImageSize(const QSize& size) { imageSize = size; }

	// gray image by a bool column (when it's false), such as Online
	void setGrayImageBy(int boolColumn) { grayImageBy = boolColumn; }
	void setImageColumn(int column)     { imageColumn = column;     }

private:
	static QPixmap toGrayPixmap(const QImage& colorImage);

private:
	QMap<int, ColumnType> columnTypes;
	QSize imageSize;
	int imageColumn;   // the image that shows on the name column
	int grayImageBy;   // gray the image based on the value of this bool column
};

#endif // IMAGECOLORBOOLMODEL_H
