#include "QtFlieOperation.h"
#include <QDir>

QtFlieOperation * QtFlieOperation::file_operation = NULL;

QtFlieOperation::QtFlieOperation()
{
	
}


QtFlieOperation::QtFlieOperation(const QtFlieOperation&)
{

}


QtFlieOperation&QtFlieOperation::operator=(const QtFlieOperation&)
{

	return *this;
}

QtFlieOperation* QtFlieOperation::GetQtFileOperation()
{
	if (file_operation == NULL)
	{
		file_operation = new QtFlieOperation;
		return file_operation;
	}
	return file_operation;
}

QtFlieOperation::~QtFlieOperation()
{

	if (file_operation!=NULL)
	{
		delete file_operation;
		file_operation = NULL;
	}
}


void QtFlieOperation::CreateFolderWithLastDir(QString path)
{
	QDir folder;
	bool exist = folder.exists(path);
	if (exist)
	{

	}
	else
	{
		//创建文件夹
		bool ok = folder.mkdir(path);	
	}
}

void QtFlieOperation::CreateFolder(QString path)
{
	QDir folder;
	bool exist = folder.exists(path);
	if (exist)
	{

	}
	else
	{
		//创建文件夹
		bool ok = folder.mkpath(path);
	}
}

QStringList QtFlieOperation::GetFolderFilesPath(QString path)
{
	QStringList flist;
	flist.clear();
	QDir dir(path);
	if (!dir.exists())
		return flist;
	dir.setFilter(QDir::Files);
	QFileInfoList infolist = dir.entryInfoList();
	int file_count = infolist.count();
	for (int i = 0; i < file_count; i++)
	{
		QFileInfo file_info = infolist.at(i);
		QString absolute_file_path = file_info.absoluteFilePath();
		flist.append(absolute_file_path);
	}
	QDir dirA(path);
	dirA.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList infolistA = dirA.entryInfoList();
	int dir_count = infolistA.count();
	for (int i = 0; i < dir_count; i++)
	{
		QFileInfo file_infoA = infolistA.at(i);
		QString absolute_dir_path = file_infoA.absoluteFilePath();
		flist.append(absolute_dir_path);
	}
	return flist;
}
QStringList QtFlieOperation::GetFolderFilesNames(QString path)
{
	QStringList flist;
	flist.clear();
	QDir dir(path);
	if (!dir.exists())
		return flist;
	dir.setFilter(QDir::Files);
	QFileInfoList infolist = dir.entryInfoList();
	int file_count = infolist.count();
	for (int i = 0; i < file_count; i++)
	{
		QFileInfo file_info = infolist.at(i);
		QString absolute_file_name = file_info.fileName();
		flist.append(absolute_file_name);
	}
	QDir dirA(path);
	dirA.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	QFileInfoList infolistA = dirA.entryInfoList();
	int dir_count = infolistA.count();
	for (int i = 0; i < dir_count; i++)
	{
		QFileInfo file_infoA = infolistA.at(i);
		QString absolute_dir_name = file_infoA.fileName();
		flist.append(absolute_dir_name);
	}
	return flist;
}
QStringList QtFlieOperation::GetfileList(QString path, bool infile)
{
	//判断路径是否存在
	QStringList flist;
	flist.clear();
	QDir dir(path);
	if (!dir.exists())
		return flist;
	dir.setFilter(QDir::Files);
	QFileInfoList infolist = dir.entryInfoList();
	int file_count = infolist.count();
	for (int i = 0; i < file_count; i++)
	{
		QFileInfo file_info = infolist.at(i);
		QString absolute_file_path = file_info.absoluteFilePath();
		flist.append(absolute_file_path);
	}
	if (infile)
	{
		QDir dirA(path);
		dirA.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
		QFileInfoList infolistA = dirA.entryInfoList();
		int dir_count = infolistA.count();
		for (int i = 0; i < dir_count; i++)
		{
			QFileInfo file_infoA = infolistA.at(i);
			//QString suffix = file_infoA.suffix();
			QString absolute_dir_path = file_infoA.absoluteFilePath();
			flist.append(GetfileList(absolute_dir_path, infile));//
		}
	}
	return flist;
}

bool QtFlieOperation::qCopyDirectory(const QDir& fromDir, const QDir& toDir, bool bCoverIfFileExists)
{
	QDir formDir_ = fromDir;
	QDir toDir_ = toDir;
	if (!toDir_.exists())
	{
		if (!toDir_.mkdir(toDir.absolutePath()))
			return false;
	}
	QFileInfoList fileInfoList = formDir_.entryInfoList();
	foreach(QFileInfo fileInfo, fileInfoList)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue; //拷贝子目录
		if (fileInfo.isDir())
		{ //递归调用拷贝
			if (!qCopyDirectory(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName())))
				return false;
		} //拷贝子文件
		else
		{
			if (bCoverIfFileExists && toDir_.exists(fileInfo.fileName()))
			{
				toDir_.remove(fileInfo.fileName());
			}
			if (!QFile::copy(fileInfo.filePath(), toDir_.filePath(fileInfo.fileName())))
			{
				return false;
			}
		}
	}
	return true;
}

bool QtFlieOperation::copyFileToPath(QString filename, QString topath, bool coverFileIfExist)
{
	//topath.replace("\\","/");
	QString topath2 = QDir::fromNativeSeparators(topath);
	if (!QFile::exists(filename)) {
		return false;
	}
	QDir dir;
	QFileInfo file(filename);
	QString filestr = file.fileName();
	filestr = topath2 + "/" + filestr;
	bool exist = dir.exists(filestr);
	if (exist) {
		if (coverFileIfExist) {
			dir.remove(filestr);
		}
		else
			return false;
	}//end if 

	if (!QFile::copy(filename, filestr))
	{
		return false;
	}
	return true;
}


bool  QtFlieOperation::removeFolderContent(const QString &folderDir)
{
	QDir dir(folderDir);
	QFileInfoList fileList;
	QFileInfo curFile;
	if (!dir.exists()) { return false; }//文件不存，则返回false
	fileList = dir.entryInfoList(QDir::Dirs | QDir::Files
		| QDir::Readable | QDir::Writable
		| QDir::Hidden | QDir::NoDotAndDotDot
		, QDir::Name);
	while (fileList.size() > 0)
	{
		int infoNum = fileList.size();
		for (int i = infoNum - 1; i >= 0; i--)
		{
			curFile = fileList[i];
			if (curFile.isFile())//如果是文件，删除文件
			{
				QFile fileTemp(curFile.filePath());
				fileTemp.remove();
				fileList.removeAt(i);
			}
			if (curFile.isDir())//如果是文件夹
			{
				QDir dirTemp(curFile.filePath());
				QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
					| QDir::Readable | QDir::Writable
					| QDir::Hidden | QDir::NoDotAndDotDot
					, QDir::Name);
				if (fileList1.size() == 0)//下层没有文件或文件夹
				{
					dirTemp.rmdir(".");
					fileList.removeAt(i);
				}
				else//下层有文件夹或文件
				{
					for (int j = 0; j < fileList1.size(); j++)
					{
						if (!(fileList.contains(fileList1[j])))
							fileList.append(fileList1[j]);
					}
				}
			}
		}
	}
	return true;
}

bool  QtFlieOperation::QtDeleteFile(const char*path)
{
	QFile file;
	bool ok = file.remove(path);
	return ok;
}

bool  QtFlieOperation::DelDir(const QString &dirName)
{
	QDir directory(dirName);
	if (!directory.exists())
	{
		return true;
	}
	QString srcPath = QDir::toNativeSeparators(dirName);
	if (!srcPath.endsWith(QDir::separator()))
		srcPath += QDir::separator();

	QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
	bool error = false;
	for (QStringList::size_type i = 0; i != fileNames.size(); ++i)
	{
		QString filePath = srcPath + fileNames.at(i);
		QFileInfo fileInfo(filePath);
		if (fileInfo.isFile() || fileInfo.isSymLink())
		{
			QFile::setPermissions(filePath, QFile::WriteOwner);
			if (!QFile::remove(filePath))
			{
				error = true;
			}
		}
		else if (fileInfo.isDir())
		{
			if (!DelDir(filePath))
			{
				error = true;
			}
		}
	}
	if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
	{
		error = true;
	}
	return !error;
}

bool QtFlieOperation::ClearFolder(const char * DirName)
{
#ifdef _WIN32
	//  CFileFind tempFind;     //声明一个CFileFind类变量，以用来搜索  
	char szCurPath[MAX_PATH];       //用于定义搜索格式  
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName); //匹配格式为*.*,即该目录下的所有文件  
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	bool IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileA(hFile, &FindFileData); //递归搜索其他的文件  
		if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //如果不是"." ".."目录  
		{
			std::string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			std::string strTemp;
			strTemp = strFileName;
			if (IsDirectory(strFileName.c_str())) //如果是目录，则递归地调用  
			{
				printf("目录为:%s/n", strFileName.c_str());
				ClearFolder(strTemp.c_str());
			}
			else
			{
				DeleteFileA(strTemp.c_str());
			}
		}
	}
	FindClose(hFile);

	bool bRet = RemoveDirectoryA(DirName);
	if (bRet == 0) //删除目录  
	{
		printf("删除%s目录失败！/n", DirName);
		return FALSE;
	}
	return TRUE;
#endif
    
#ifdef __APPLE__
    return true;
#endif
}


bool QtFlieOperation::IsDirectory(const char *pDir)
{
  QFileInfo info(pDir);
  auto ret = false;
  if (info.exists()) {
    if (info.isDir()) {
      ret = true;
    }
  }

  return ret;

	//char szCurPath[500];
	//ZeroMemory(szCurPath, 500);
	//sprintf_s(szCurPath, 500, "%s//*", pDir);
	//WIN32_FIND_DATAA FindFileData;
	//ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));

	//HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData); /**< find first file by given path. */

	//if (hFile == INVALID_HANDLE_VALUE)
	//{
	//	FindClose(hFile);
	//	return FALSE; /** 如果不能找到第一个文件，那么没有目录 */
	//}
	//else
	//{
	//	FindClose(hFile);
	//	return TRUE;
	//}

}
