#ifndef IMAGESWINDOWBACKEND_H
#define IMAGESWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

class ImagesWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QStringList images READ getImages WRITE setImages NOTIFY imagesChanged)
    Q_PROPERTY(QString currentImage READ getCurrentImage NOTIFY currentImageChanged)

    int m_currentIndex;
    QStringList m_images;
    QString m_currentImage;

    QStringList imagesAvailable;
    QStringList imagesHistorical;

    QString getRandomImageFromImagesAvailable() const;

    void removeImageFromImagesAvailable(QString image);
    void removeImageFromImagesHistorical(QString image);
    void removeImageFromImages(QString image);

    void setCurrentIndex(int newIndex);
    void setCurrentImage(QString image);

    void updateImagesAvailable();
public:
    ImagesWindowBackend(QObject *parent = nullptr);

    Q_INVOKABLE void removeImageFromAllDatas(QString image);

    Q_INVOKABLE void nextImage();
    Q_INVOKABLE void preventImage();

    int getCurrentIndex() const;

    QString getCurrentImage() const;

    QStringList getImages() const;
    void setImages(QStringList images);
signals:
    void currentIndexChanged();
    void imagesChanged();
    void currentImageChanged();
};

#endif // IMAGESWINDOWBACKEND_H