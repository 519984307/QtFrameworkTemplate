#pragma once
#include <stdio.h>
#include<QStringList>
#include <QDir>
#include "utilsexport.h"
#ifdef _WIN32
#include <windows.h>
#endif

class UTILS_EXPORT QtFlieOperation {
public:
	static QtFlieOperation* GetQtFileOperation();
	~QtFlieOperation();

	/***************创建文件夹********************/
	void CreateFolderWithLastDir(QString path);//必须要有文件名上一级的目录才可创建
	void CreateFolder(QString path);//不需要要有文件名上一级的目录，自动创建一系列文件夹

	/***************获取文件夹信息操作***************/
	QStringList GetFolderFilesPath(QString path);   //得出下一级文件夹和文件的路径集合(只是下一级); (已测)
	QStringList GetFolderFilesNames(QString path); ////得出下一级文件夹和文件的名字集合（只是下一级)(已测);
	QStringList GetfileList(QString path, bool infile = false);//得出下一级文件的路径集合（infile=true遍历所有下一级文件，false只是下一级)(已测);

	/****************复制操作**********************/
	bool qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists = false);//将fromDir下一级的文件和文件夹拷贝到toDir，bool值表示是否覆盖

	//拷贝文件到指定路径要加后缀，只能拷贝文件，coverFileIfExist控制是否覆盖
	//toDir是要拷贝到的目录
	bool copyFileToPath(QString filename, QString toDir, bool coverFileIfExist = false);

	/*******************删除操作********************/
	bool removeFolderContent(const QString &folderDir);//删除一个文件夹下所有子东西，本身不删(已测)
	bool QtDeleteFile(const char*);  //只能删除单个文件，非文件夹，要加文件后缀(已测)
	bool DelDir(const QString &path);  //删除一个文件夹包括里面所有东西(已测)
	bool ClearFolder(const char *DirName); //删除文件夹 同DelDir类似,windowsAPI用法


	/*******************判断文件夹是否存在********************/
	bool IsDirectory(const char *pDir);
private:
	QtFlieOperation();
	QtFlieOperation(const QtFlieOperation&);
	QtFlieOperation&operator=(const QtFlieOperation&);
	static QtFlieOperation *file_operation;
};

