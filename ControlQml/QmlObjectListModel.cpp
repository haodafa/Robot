#include "QmlObjectListModel.h"

#include <QDebug>
#include <QQmlEngine>

const int QmlObjectListModel::ObjectRole = Qt::UserRole;
const int QmlObjectListModel::TextRole = Qt::UserRole + 1;

QmlObjectListModel::QmlObjectListModel(QObject* parent)
    : QAbstractListModel(parent)
    , _dirty(false)
    , _skipDirtyFirstItem(false)
{

}

QmlObjectListModel::~QmlObjectListModel()
{

}

QObject* QmlObjectListModel::getIndexValue(int index)
{
    return m_listObject[index];
}

int QmlObjectListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    return m_listObject.count();
}

QVariant QmlObjectListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= m_listObject.count()) {
        return QVariant();
    }

    if (role == ObjectRole) {
        return QVariant::fromValue(m_listObject[index.row()]);
    } else if (role == TextRole) {
        return QVariant::fromValue(m_listObject[index.row()]->objectName());
    } else {
        return QVariant();
    }
}

QHash<int, QByteArray> QmlObjectListModel::roleNames(void) const
{
    QHash<int, QByteArray> hash;

    hash[ObjectRole] = "object";
    hash[TextRole] = "text";

    return hash;
}

bool QmlObjectListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == ObjectRole) {
        m_listObject.replace(index.row(), value.value<QObject*>());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

bool QmlObjectListModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    Q_UNUSED(parent);

    if (position < 0 || position > m_listObject.count() + 1) {
        qWarning() << "Invalid position position:count" << position << m_listObject.count();
    }

    beginInsertRows(QModelIndex(), position, position + rows - 1);
    endInsertRows();

    emit countChanged(count());

    return true;
}

bool QmlObjectListModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    Q_UNUSED(parent);

    if (position < 0 || position >= m_listObject.count()) {
        qWarning() << "Invalid position position:count" << position << m_listObject.count();
    } else if (position + rows > m_listObject.count()) {
        qWarning() << "Invalid rows position:rows:count" << position << rows << m_listObject.count();
    }

    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for (int row=0; row<rows; row++) {
        // FIXME: Need to figure our correct memory management for here
        //_objectList[position]->deleteLater();
        m_listObject.removeAt(position);
    }

    endRemoveRows();

    emit countChanged(count());

    return true;
}

QObject* QmlObjectListModel::operator[](int index)
{
    return m_listObject[index];
}

const QObject* QmlObjectListModel::operator[](int index) const
{
    return m_listObject[index];
}

void QmlObjectListModel::clear(void)
{
    while (rowCount()) {
        removeAt(0);
    }
}

QObject* QmlObjectListModel::removeAt(int i)
{
    QObject* removedObject = m_listObject[i];

    // Look for a dirtyChanged signal on the object
    if (m_listObject[i]->metaObject()->indexOfSignal(QMetaObject::normalizedSignature("dirtyChanged(bool)")) != -1) {
        if (!_skipDirtyFirstItem || i != 0) {
            QObject::disconnect(m_listObject[i], SIGNAL(dirtyChanged(bool)), this, SLOT(_childDirtyChanged(bool)));
        }
    }

    removeRows(i, 1);

    emit listChanged();
    setDirty(true);

    return removedObject;
}


QObject* QmlObjectListModel::removeOne(QObject* object)
{
    return removeAt(indexOf(object));
}


void QmlObjectListModel::insert(int i, QObject* object)
{
    if (i < 0 || i > m_listObject.count()) {
        qWarning() << "Invalid index index:count" << i << m_listObject.count();
    }

    QQmlEngine::setObjectOwnership(object, QQmlEngine::CppOwnership);

    // Look for a dirtyChanged signal on the object
    if (object->metaObject()->indexOfSignal(QMetaObject::normalizedSignature("dirtyChanged(bool)")) != -1) {
        if (!_skipDirtyFirstItem || i != 0) {
            QObject::connect(object, SIGNAL(dirtyChanged(bool)), this, SLOT(_childDirtyChanged(bool)));
        }
    }

    m_listObject.insert(i, object);
    insertRows(i, 1);

    emit listChanged();

    setDirty(true);
}


bool QmlObjectListModel::contains(QObject* object)
{
    return m_listObject.indexOf(object) != -1;
}


int QmlObjectListModel::indexOf(QObject* object)
{
    return m_listObject.indexOf(object);
}


QObject* QmlObjectListModel::value(int index)
{
    return m_listObject[index];
}


void QmlObjectListModel::append(QObject* object)
{
    insert(m_listObject.count(), object);
}


QObjectList QmlObjectListModel::swapObjectList(const QObjectList& newlist)
{
    QObjectList oldlist(m_listObject);
    beginResetModel();
    m_listObject = newlist;
    endResetModel();

    emit countChanged(count());
    emit listChanged();

    return oldlist;
}

int QmlObjectListModel::count(void) const
{
    return rowCount();
}


bool QmlObjectListModel::dirty(void) const
{
    return _dirty;
}


void QmlObjectListModel::setDirty(bool dirty)
{
    if (_dirty != dirty) {
        _dirty = dirty;
        if (!dirty) {
            // Need to clear dirty from all children
            foreach(QObject* object, m_listObject) {
                if (object->property("dirty").isValid()) {
                    object->setProperty("dirty", false);
                }
            }
        }
        emit dirtyChanged(_dirty);
    }
}

void QmlObjectListModel::_childDirtyChanged(bool dirty)
{
    _dirty |= dirty;
    // We want to emit dirtyChanged even if the actual value of _dirty didn't change. It can be a useful
    // signal to know when a child has changed dirty state
    emit dirtyChanged(_dirty);
}

void QmlObjectListModel::deleteListAndContents(void)
{
    for (int i=0; i<m_listObject.count(); i++) {
        m_listObject[i]->deleteLater();
    }
    deleteLater();
}

void QmlObjectListModel::clearAndDeleteContents(void)
{
    for (int i=0; i<m_listObject.count(); i++) {
        m_listObject[i]->deleteLater();
    }
    clear();
}


QList<QObject*> QmlObjectListModel::getObjectList()
{
    return m_listObject;
}

