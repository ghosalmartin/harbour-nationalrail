/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QGuiApplication>
#include <QQuickView>

#include <QtQml/qqml.h>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include <FavouritesModel.h>
#include <StationsFilterModel.h>
#include <NetworkRequest.h>
#include <XMLGenerator.h>
#include <ServiceModel.h>
#include <MessagesModel.h>
#include <Database.h>
#include <PreviousCPModel.h>
#include <SubsequentCPModel.h>


int main(int argc, char *argv[])
{

    QGuiApplication *app = SailfishApp::application(argc, argv);

    app->setOrganizationName("harbour-nationalrail");
    app->setApplicationName("harbour-nationalrail");


    QDir appDir(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).back());
    QString dbName = "stationsDB.sqlite";
    QString dbFolder = "."+app->applicationName();

    if(!QFile::exists(QDir::homePath()+QDir::separator()+dbFolder+QDir::separator()+dbName)){
        QDir dir;
        dir.mkpath(QDir::homePath()+QDir::separator()+dbFolder);
        QFile::copy(appDir.path() + QDir::separator() + app->applicationName() + QDir::separator() + "data" +QDir::separator() + dbName,QDir::homePath()+QDir::separator()+dbFolder+QDir::separator()+dbName);
        qDebug() << "Database does not exist, copying...";
    }

    new Database;

    qmlRegisterType<NetworkRequest>("harbour.nationalrail.networkrequest", 1, 0, "NetworkRequest");
    qmlRegisterType<ServiceModel>("harbour.nationalrail.servicemodel", 1, 0, "ServiceModel");
    qmlRegisterType<StationsModel>("harbour.nationalrail.stationsmodel", 1, 0, "StationsModel");
    qmlRegisterType<StationsFilterModel>("harbour.nationalrail.stationsfiltermodel", 1, 0, "StationsFilterModel");
    qmlRegisterType<FavouritesModel>("harbour.nationalrail.favouritesmodel", 1, 0, "FavouritesModel");
    qmlRegisterType<MessagesModel>("harbour.nationalrail.messagesmodel", 1, 0, "MessagesModel");
    qmlRegisterType<PreviousCPModel>("harbour.nationalrail.previouscpmodel", 1, 0, "PreviousCPModel");
    qmlRegisterType<SubsequentCPModel>("harbour.nationalrail.subsequentcpmodel", 1, 0, "SubsequentCPModel");

    QQuickView *view = SailfishApp::createView();

    QString qml = QString("qml/%1.qml").arg("harbour-nationalrail");
    view->setSource(SailfishApp::pathTo(qml));
    view->show();

    return app->exec();

}

