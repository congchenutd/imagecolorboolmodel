#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QItemDelegate>
#include <QSet>

class CheckBoxDelegate : public QItemDelegate
{
public:
	CheckBoxDelegate(const QSet<int>& columns, QObject* parent = 0);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& idx) const;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& idx);
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, 
						  const QModelIndex& idx) const;

private:
	bool isBoolColumn(int column) const;

private:
	QSet<int> boolColumns;
};

#endif // CHECKBOXDELEGATE_H
