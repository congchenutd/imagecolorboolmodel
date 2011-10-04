#include "ImageColorBoolDelegate.h"
#include "ImageColorBoolProxy.h"
#include <QEvent>
#include <QPainter>

ImageColorBoolDelegate::ImageColorBoolDelegate(ImageColorBoolProxy* m, QObject* parent)
: QItemDelegate(parent), model(m), editTrigger(QEvent::MouseButtonDblClick) {}

void ImageColorBoolDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, 
								   const QModelIndex& idx) const
{
	if(isBoolColumn(idx.column()))
	{
		if(option.state & QStyle::State_Selected)  // selection shadow
			painter->fillRect(option.rect, option.palette.highlight());

		const QPixmap& pixmap = idx.data().toBool() ? imgChecked : imgUnchecked;
		int width  = pixmap.width();
		int height = pixmap.height();
		int x = option.rect.x() + (option.rect.width()  - width)  / 2;  // center of the cell
		int y = option.rect.y() + (option.rect.height() - height) / 2;
		painter->drawPixmap(x, y, pixmap);
	}
	else
		QItemDelegate::paint(painter, option, idx);
}

bool ImageColorBoolDelegate::editorEvent(QEvent* event, QAbstractItemModel*, 
								   const QStyleOptionViewItem& option, const QModelIndex& idx)
{
	if(isBoolColumn(idx.column()) && event->type() == editTrigger)
	{
		model->setData(idx, !idx.data().toBool());   // flip the value
		model->submit();
		return true;   // true means successful? failed to find the document
	}
	return QItemDelegate::editorEvent(event, model, option, idx);
}

bool ImageColorBoolDelegate::isBoolColumn(int column) const {
	return model->getColumnType(column) == ImageColorBoolProxy::BoolColumn;
}

QWidget* ImageColorBoolDelegate::createEditor(QWidget* parent, 
											  const QStyleOptionViewItem& option, 
											  const QModelIndex& idx) const {
	return isBoolColumn(idx.column()) ? 0    // disable the original editor
			: QItemDelegate::createEditor(parent, option, idx);
}
