#include "transformationlist.h"

TransformationList::TransformationList(QObject * parent):
    QAbstractListModel(parent)
{}

TransformationList::~TransformationList()
{
    this->transformations.clear();
}

// New version
void TransformationList::getDataForTransformation(int * & transformations, int &noOfTransformations) const
{
    noOfTransformations = this->transformations.size();
    Transformation * trArray = new Transformation[noOfTransformations];

    // Copies every transformation, one by one
    for (int trIndex = 0; trIndex < noOfTransformations; ++trIndex)
    {
        trArray [trIndex] = this->transformations[trIndex];
    }

    transformations = (int *) trArray;
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

// New version
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
            dataStr += "Escalación por " + QString::number(trans.floatParam(1));
            break;
        case vectTranslation:
            dataStr += "Traslación por " + QString::number(trans.floatParam(1)) + " en x ";
            dataStr += "y " + QString::number(trans.floatParam(2)) + " en y";
            break;

        case matBrightness:
            dataStr += "Cambio de brillo por " + QString::number(trans.intParam(1));
            break;
        case matNegative:
            dataStr += "Cambio de colores por sus negativos.";
            break;
        case matContrast:
            dataStr += "Cambio de saturación de rojo por " + QString::number(trans.intParam(1));
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
