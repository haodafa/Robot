#ifndef QMLOBJECTLISTMODEL_H
#define QMLOBJECTLISTMODEL_H

#include <QAbstractListModel>

class QmlObjectListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QmlObjectListModel(QObject* parent = NULL);
    QmlObjectListModel(const QmlObjectListModel &objectList);
    ~QmlObjectListModel();

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QList<QObject*> objectlist READ getObjectList NOTIFY listChanged)
    Q_PROPERTY(bool dirty READ dirty WRITE setDirty NOTIFY dirtyChanged)

    Q_INVOKABLE QObject* getIndexValue(int index);

    int count(void) const;

    bool dirty(void) const;
    void setDirty(bool dirty);

    void append(QObject* object);
    QObjectList swapObjectList(const QObjectList& newlist);
    void clear(void);
    QObject* removeAt(int i);
    QObject* removeOne(QObject* object);
    void insert(int i, QObject* object);
    QObject* operator[](int i);
    const QObject* operator[](int i) const;
    bool contains(QObject* object);
    int indexOf(QObject* object);
    QObject* value(int index);

    void deleteListAndContents(void);

    void clearAndDeleteContents(void);

    QList<QObject*> getObjectList();

signals:
    void countChanged(int count);
    void dirtyChanged(bool dirtyChanged);

    void listChanged();

private slots:
    void _childDirtyChanged(bool dirty);

private:
    // Overrides from QAbstractListModel
    virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual QHash<int, QByteArray> roleNames(void) const;
    virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    QList<QObject*> m_listObject;

    bool _dirty;
    bool _skipDirtyFirstItem;

    static const int ObjectRole;
    static const int TextRole;
};

#endif

