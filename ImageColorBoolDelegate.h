#ifndef IMAGECOLORBOOLDELEGATE_H
#define IMAGECOLORBOOLDELEGATE_H

#include <QItemDelegate>
#include <QEvent>

class ImageColorBoolProxy;

// A delegate that makes the bool column checkable
// Must work with ImageColorBoolModel
class ImageColorBoolDelegate : public QItemDelegate
{
public:
	ImageColorBoolDelegate(ImageColorBoolProxy* m, QObject* parent = 0);
	void setEditTrigger(QEvent::Type eventType) { editTrigger = eventType; }

	// virtuals
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& idx) const;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& idx);
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, 
							const QModelIndex& idx) const;

private:
	bool isBoolColumn(int column) const;

private:
	ImageColorBoolProxy* model;
	QEvent::Type editTrigger;
};

#endif // IMAGECOLORBOOLDELEGATE_H
