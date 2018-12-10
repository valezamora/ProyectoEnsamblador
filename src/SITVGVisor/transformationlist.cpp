#include "transformationlist.h"

TransformationList::TransformationList(QObject * parent):
    QAbstractListModel(parent)
{}

TransformationList::~TransformationList()
{
    this->transformations.clear();
}

void TransformationList::clear()
{
    beginRemoveRows(QModelIndex(), 0, transformations.size()-1);
        this->fetchedRowCount -= 1;
    endRemoveRows();

    this->transformations.clear();
    this->fetchedRowCount = 0;
}

int TransformationList::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return fetchedRowCount;
}

QVariant TransformationList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {return QVariant();}

    if ( (0 > index.row()) || (index.row() >= this->transformations.size()) )
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
    {
        QString dataStr = QString::number(index.row() + 1) + ". ";
        const Transformation & trans = this->transformations[index.row()];
        switch (trans.id) {

        case vectReflexion:
            dataStr += "Reflexión";
            break;
        case vectScaling:
            dataStr += "Escalación por " + QString::number(trans.dataOf.vScaling.scalePercent);
            break;
        case vectTranslation:
            dataStr += "Traslación por " + QString::number(trans.dataOf.vTranslation.xTranslating) + " en x ";
            dataStr += "y " + QString::number(trans.dataOf.vTranslation.yTranslating) + " en y";
            break;

        case matBrightness:
            dataStr += "Cambio de brillo por " + QString::number((int)trans.dataOf.mBrightness.brightnessChange);
            break;
        case matNegative:
            dataStr += "Cambio de colores por sus negativos.";
            break;
        case matContrast:
            dataStr += "Cambio de contraste por " + QString::number((int)trans.dataOf.mContrast.contrastChange);
            break;

        default:
            dataStr = "Transformación desconocida... Lo sentimos :(";
            break;
        }

        return dataStr;
    }

    return QVariant();
}

bool TransformationList::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->fetchedRowCount < this->transformations.size();
}

void TransformationList::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent);

    int itemsToFetch = this->transformations.size() - this->fetchedRowCount;

    if (itemsToFetch <= 0)
        return;

    int firstRow = this->fetchedRowCount;
    int lastRow = this->fetchedRowCount + itemsToFetch - 1;

    beginInsertRows(QModelIndex(), firstRow, lastRow);
    this->fetchedRowCount += itemsToFetch;
    endInsertRows();
}
