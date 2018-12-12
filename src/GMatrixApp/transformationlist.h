#ifndef TRANSFORMATIONLIST_H
#define TRANSFORMATIONLIST_H

#include <QAbstractListModel>
#include "transformation.h"
#include <QString>
#include <cstring>      //  For memory copy

/**
 * @brief Class that stores a list of transformations that can be graphically represented
 * by a ListView widget. Internally, transformations data is stored within a QVector.
 */
class TransformationList : public QAbstractListModel
{
    Q_OBJECT
    Q_DISABLE_COPY(TransformationList)

  protected:
    /// Vector of transformations
    QVector <Transformation> transformations;
    /// Number of transformations already shown in the view.
    int fetchedRowCount = 0;

  public:
    TransformationList (QObject * parent = nullptr);
    ~TransformationList ();

    /**
     * @brief Append a transformation to the list.
     * @param Transformation to be appended.
     */
    inline void append (Transformation & trans)
    {
        transformations.append(trans);
        this->fetchMore(QModelIndex());
    }

    /**
     * @brief Returns the amount of transformations in the list.
     */
    inline int size () const
    {
        return transformations.size();
    }

    /**
     * @brief Gets the data for transformations codified in an integer array.
     * @param transformations Pointer in which the transformations array will be put.
     * @param noOfTransformations Integer in which the number of transformations will be put.
     */
    void getDataForTransformation(int * & transformations, int & noOfTransformations) const;

    /**
     * @brief Clears all of the data in the object.
     */
    void clear ();

    /**
     * @brief For model-view control. Returns the amount of transformations already shown.
     */
    virtual int rowCount (const QModelIndex &parent) const override;

    /**
     * @brief For model-view control. Returns a given transformation.
     * @param index Index of the transformation to get.
     * @return String for the transformation at index.
     */
    virtual QVariant data (const QModelIndex &index, int role = Qt::DisplayRole) const override;

  protected:
    /**
     * @brief For model-view control. Indicates if transformations are yet to be shown.
     * @return True iff more transformations may be fetched.
     */
    virtual bool canFetchMore(const QModelIndex &parent) const override;

    /**
     * @brief For model-view control. Updates the view of this list.
     */
    virtual void fetchMore(const QModelIndex &parent) override;
};

#endif // TRANSFORMATIONLIST_H
