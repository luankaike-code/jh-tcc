#include "imageswindowbackend.h"
#include <iostream>
#include <random>

ImagesWindowBackend::ImagesWindowBackend(QObject *parent) : QObject{parent} {}

void ImagesWindowBackend::removeImageFromImagesAvailable(QString image) {
    qsizetype index = imagesAvailable.indexOf(image);
    if(index > -1) {
        imagesAvailable.removeAt(index);
    }
}

void ImagesWindowBackend::removeImageFromImagesHistorical(QString image) {
    int countRemovedImages = imagesHistorical.removeAll(image);
    setCurrentIndex(m_currentIndex-countRemovedImages);
}

void ImagesWindowBackend::removeImageFromImages(QString image) {
    qsizetype index = m_images.indexOf(image);
    if(index > -1) {
        m_images.removeAt(index);
        emit imagesChanged();
    } else {
        std::cerr << "images not contains " << image.toStdString() << std::endl;
    }
}

void ImagesWindowBackend::removeImageFromAllDatas(QString image) {
    removeImageFromImagesAvailable(image);
    removeImageFromImagesHistorical(image);
    removeImageFromImages(image);
}

void ImagesWindowBackend::setCurrentIndex(int newIndex) {
    m_currentIndex = newIndex < 0? 0 : newIndex;
    emit currentIndexChanged();
}

void ImagesWindowBackend::setCurrentImage(QString image) {
    m_currentImage = image;
    emit currentImageChanged();
}

QString ImagesWindowBackend::getRandomImageFromImagesAvailable() const {
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> getRandomNumberInRange(0, imagesAvailable.length()-1);
    int randomNumber = getRandomNumberInRange(gen);
    return imagesAvailable[randomNumber];
}

void ImagesWindowBackend::updateImagesAvailable() {
    if(imagesAvailable.isEmpty()) {
        imagesAvailable = m_images;
    }
}

void ImagesWindowBackend::nextImage() {
    setCurrentIndex(m_currentIndex+1);

    updateImagesAvailable();

    if(m_currentIndex > imagesHistorical.length()-1) {
        QString chosenImage = getRandomImageFromImagesAvailable();

        setCurrentImage(chosenImage);
        removeImageFromImagesAvailable(chosenImage);

        if(!m_currentImage.isEmpty())
            imagesHistorical.push_back(m_currentImage);
    } else {
        setCurrentImage(imagesHistorical[m_currentIndex]);
    }
}

void ImagesWindowBackend::preventImage() {
    if(m_currentIndex <= 0)
        return;
    setCurrentIndex(m_currentIndex-1);

    setCurrentImage(imagesHistorical[m_currentIndex]);
}

int ImagesWindowBackend::getCurrentIndex() const {
    return m_currentIndex;
}

QString ImagesWindowBackend::getCurrentImage() const {
    return m_currentImage;
}

QStringList ImagesWindowBackend::getImages() const {
    return m_images;
}

void ImagesWindowBackend::setImages(QStringList images) {
    if(m_images == images)
        return;

    m_images = images;
    m_currentIndex = 0;
    imagesAvailable = m_images;
    imagesHistorical.clear();
    emit imagesChanged();
}