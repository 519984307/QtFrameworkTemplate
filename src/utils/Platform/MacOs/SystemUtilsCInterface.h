//
//  SystemUtilsCInterface.h
//  Billfish
//
//  Created by luqi on 2021/1/20.
//

#ifndef SystemUtilsCInterface_h
#define SystemUtilsCInterface_h
#include <QString>
#include <QStringList>
#include <QWidget>

#ifdef __APPLE__
QStringList getApplicationURLsForURL(const QString & filePath);
QString getApplicationDisplayNameWithFilePath(const QString & filePath);
void openUrlWithApplication(const QString& filePath,const QString& applicationPath);
//
//[self.window makeKeyAndOrderFront:nil
void makeKeyAndOrderFront(QWidget* w);

void changeMainWindowStyle(QWidget* w);

bool folderIconExist(const QString& folderPath);

void setFolderIcon(const QString& imagePath,const QString& folderPath);

void removeFolderIcon(const QString& folderPath);

double getScreenDpiScale();

int localizedStandardCompare(const QString& lhs, const QString& rhs);

unsigned long long getFolderSize(const QString& folderPath);

unsigned long long getFreeDiskSize(const QString& folderPath);

unsigned long long getTotalDiskSize(const QString& folderPath);

char* getMacAppVersion();

bool isApplicationAlreadyRunning();

QString GetVolumeName(const QString& folder_path);

QStringList GetOpenOpenFileNameAndDir(const QString& title = QString(),
                                      const QString& dir = QString());

void unzipToPath(const QString& zip_path, const QString& folder_path);

void createZipFileAtPath(const QString& zip_path,
                         const QStringList& file_paths);

int getMenubarHeightOffset();

#endif

#endif /* SystemUtilsCInterface_h */
