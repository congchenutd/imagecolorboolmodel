#include "CheckBoxDelegate.h"
#include <QCheckBox>
#include <QEvent>
#include <QPainter>

CheckBoxDelegate::CheckBoxDelegate(const QSet<int>& columns, QObject* parent)
	: QItemDelegate(parent), boolColumns(columns) {}

void CheckBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& idx) const
{
	if(isBoolColumn(idx.column())) {
		if(idx.data().toBool())
		{
			QPixmap tick("Tick.png");
			int width = tick.width();
			int height = tick.height();
			int x = option.rect.x() + (option.rect.width() - width) / 2;
			int y = option.rect.y() + (option.rect.height() - height) / 2;
			painter->drawPixmap(x, y, tick);
		}
	}
	else
		QItemDelegate::paint(painter, option, idx);
}

bool CheckBoxDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, 
								   const QStyleOptionViewItem& option, const QModelIndex& idx)
{
	if(isBoolColumn(idx.column()) && event->type() == QEvent::MouseButtonDblClick)
	{
		model->setData(idx, !idx.data().toBool());
		return true;
	}
	return QItemDelegate::editorEvent(event, model, option, idx);
}

bool CheckBoxDelegate::isBoolColumn(int column) const {
	return boolColumns.contains(column);
}

QWidget* CheckBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& idx) const
{
	if(isBoolColumn(idx.column()))
		return 0;
	return QItemDelegate::createEditor(parent, option, idx);
}