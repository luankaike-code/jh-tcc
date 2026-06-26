#ifndef IMAGESWINDOWBACKEND_H
#define IMAGESWINDOWBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>

class ImagesWindowBackend : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int currentIndex READ getCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(QStringList images READ getImages WRITE setImages NOTIFY imagesChanged REQUIRED)
    Q_PROPERTY(QString currentImage READ getCurrentImage NOTIFY currentImageChanged)

    int m_currentIndex;
    QStringList m_images;
    QString m_currentImage;

    QStringList imagesAvailable;
    QStringList imagesHistorical;

    QString getRandomImageFromImagesAvailable() const;

    void removeImageFromImagesAvailable(const QString& image);
    void removeImageFromImagesHistorical(const QString& image);
    void removeImageFromImages(const QString& image);

    void setCurrentIndex(const int& newIndex);
    void setCurrentImage(const QString& image);

    void updateImagesAvailable();
public:
    ImagesWindowBackend(QObject* parent = nullptr);

    Q_INVOKABLE void removeImageFromAllDatas(const QString& image);

    Q_INVOKABLE void nextImage();
    Q_INVOKABLE void preventImage();

    Q_INVOKABLE void copyCurrentImageToClipboard();
    Q_INVOKABLE void removeCurrentImage();

    int getCurrentIndex() const;

    const QString& getCurrentImage() const;

    const QStringList& getImages() const;
    void setImages(const QStringList& images);
signals:
    void currentIndexChanged();
    void imagesChanged();
    void currentImageChanged();
};

#endif // IMAGESWINDOWBACKEND_H