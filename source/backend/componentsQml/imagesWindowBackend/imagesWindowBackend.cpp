#include "imagesWindowBackend.h"
#include "../utils/clipboard/clipboard.h"
#include <iostream>
#include <random>

ImagesWindowBackend::ImagesWindowBackend(QObject* parent) : QObject{parent} {}

void ImagesWindowBackend::removeImageFromImagesAvailable(const QString& image) {
    qsizetype index = imagesAvailable.indexOf(image);
    if(index > -1) {
        imagesAvailable.removeAt(index);
    }
}

void ImagesWindowBackend::removeImageFromImagesHistorical(const QString& image) {
    int countRemovedImages = imagesHistorical.removeAll(image);
    setCurrentIndex(m_currentIndex-countRemovedImages);
}

void ImagesWindowBackend::removeImageFromImages(const QString& image) {
    qsizetype index = m_images.indexOf(image);
    if(index > -1) {
        m_images.removeAt(index);
        emit imagesChanged();
    } else {
        std::cerr << "images not contains " << image.toStdString() << std::endl;
    }
}

void ImagesWindowBackend::removeImageFromAllDatas(const QString& image) {
    removeImageFromImagesAvailable(image);
    removeImageFromImagesHistorical(image);
    removeImageFromImages(image);
}

void ImagesWindowBackend::setCurrentIndex(const int& newIndex) {
    m_currentIndex = newIndex < 0? 0 : newIndex;
    emit currentIndexChanged();
}

void ImagesWindowBackend::setCurrentImage(const QString& image) {
    m_currentImage = image;
    emit currentImageChanged();
}

QString ImagesWindowBackend::getRandomImageFromImagesAvailable() const {
    if(imagesAvailable.isEmpty()) {
        std::cerr << "imagesAvailable is empty" << std::endl;
        return "";
    }
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
    if(!imagesHistorical.empty())
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

    else if(imagesHistorical.isEmpty()) {
        std::cerr << "imagesHistorical is empty" << std::endl;
        return;
    }

    setCurrentIndex(m_currentIndex-1);
    setCurrentImage(imagesHistorical[m_currentIndex]);
}

void ImagesWindowBackend::copyCurrentImageToClipboard() {
    Clipboard::getInstance()->copyText(m_currentImage);
}

void ImagesWindowBackend::removeCurrentImage() {
    removeImageFromAllDatas(m_currentImage);
    nextImage();
}

int ImagesWindowBackend::getCurrentIndex() const {
    return m_currentIndex;
}

const QString& ImagesWindowBackend::getCurrentImage() const {
    return m_currentImage;
}

const QStringList& ImagesWindowBackend::getImages() const {
    return m_images;
}

void ImagesWindowBackend::setImages(const QStringList& images) {
    if(m_images == images)
        return;

    m_images = images;
    m_currentIndex = 0;
    imagesAvailable = m_images;
    imagesHistorical.clear();
    emit imagesChanged();
}