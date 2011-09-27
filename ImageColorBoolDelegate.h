#ifndef IMAGECOLORBOOLDELEGATE_H
#define IMAGECOLORBOOLDELEGATE_H

#include <QItemDelegate>
#include <QEvent>
#include <QPixmap>

class ImageColorBoolProxy;

// A delegate that makes the bool column checkable
// Must work with ImageColorBoolModel
class ImageColorBoolDelegate : public QItemDelegate
{
public:
	ImageColorBoolDelegate(ImageColorBoolProxy* m, QObject* parent = 0);
	void setCheckedImage  (const QPixmap& img) { imgChecked   = img; }
	void setUncheckedImage(const QPixmap& img) { imgUnchecked = img; }
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
	QPixmap imgChecked;
	QPixmap imgUnchecked;
};

#endif // IMAGECOLORBOOLDELEGATE_H
