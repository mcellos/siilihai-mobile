#include <QGuiApplication>

#include <QQmlComponent>
#include <QDebug>
#include <QFile>
#include "qtquick2applicationviewer.h"
#include "siilihaimobile.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    qDebug() << Q_FUNC_INFO << "started";
    QGuiApplication app(argc, argv);
    qDebug() << Q_FUNC_INFO << "QGuiApplication created";
    QCoreApplication::setOrganizationName("Siilihai");
    QCoreApplication::setOrganizationDomain("siilihai.com");
    QCoreApplication::setApplicationName("Siilihai-mobile");

    QtQuick2ApplicationViewer viewer;
    qDebug() << Q_FUNC_INFO << "QtQuick2ApplicationViewer created";
    SiilihaiMobile shm(0, &viewer);
    qDebug() << Q_FUNC_INFO << "SiilihaiMobile created";

    app.setQuitOnLastWindowClosed(false);

    // Find the main.qml to use..
#ifdef Q_OS_ANDROID
    // Android is a bit special.. it loads QML *REALLY* slow so we need a loading screen:
    viewer.setMainQmlFile("qml/siilihai-mobile-nocomponents/LoadingScreen.qml");
    qDebug() << Q_FUNC_INFO << "Loading..";
    viewer.showFullScreen();
    app.processEvents();
    // On android the file.exists() returns false, although this works:
    viewer.setMainQmlFile("qml/siilihai-mobile-nocomponents/main.qml");
    qDebug() << Q_FUNC_INFO << "setMainQmlFile done";
#else
    // Search from a few known paths
    QStringList mainFileAlternatives;
    mainFileAlternatives << "../siilihai-mobile/qml/siilihai-mobile-nocomponents/main.qml"
                         << "qml/siilihai-mobile-nocomponents/main.qml"
                         << "/usr/share/harbour-siilihai-mobile/qml/siilihai-mobile-nocomponents/main.qml";

    QFile mainQml;
    foreach(QString fileName, mainFileAlternatives) {
        mainQml.setFileName(fileName);
        qDebug() << Q_FUNC_INFO << "File " << fileName << (mainQml.exists() ? " exists, using it" : " does not exist");
        if(mainQml.exists()) {
            viewer.setMainQmlFile(fileName);
            break;
        }
    }
    if(!mainQml.exists()) {
        qDebug() << Q_FUNC_INFO << "Cannot open main.qml!";
        return -1;
    }
#endif

#ifdef FULLSCREEN
    viewer.showFullScreen();
#else
    viewer.resize(540, 960);
    viewer.show();
#endif

    shm.setContextProperties(); // Root ctx may change when loading, so redo this
    qDebug() << Q_FUNC_INFO << "ctx props set";
    qDebug() << Q_FUNC_INFO << "viewer open";

    // This works on Sailfish, but not on desktop
    app.connect(&viewer, SIGNAL(closing(QQuickCloseEvent*)), &shm, SLOT(haltSiilihai()));

    shm.launchSiilihai(false);
    int ret = app.exec();
    // Ugly hack to make sure Siilihai quits graceously after swipe close
    qDebug() << Q_FUNC_INFO << "exec() exited";
    viewer.setSource(QUrl("")); // Otherwise things may crash
    viewer.hide();
    if(!shm.isHaltRequested()) {
        qDebug() << Q_FUNC_INFO << "halt NOT requested yet - forcing halt. This will probably crash on Sailfish";
        shm.haltSiilihai();
        app.exec(); // Re-start Qt main loop
        qDebug() << Q_FUNC_INFO << "Second main loop run exited - all should be good now.";
    } else {
        qDebug() << Q_FUNC_INFO << "Halt ok";
    }
    return ret;
}
