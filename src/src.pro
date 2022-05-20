#工程集
TEMPLATE = subdirs
#继续去下面几个子目录名字中读取pro文件生成工程
SUBDIRS += instance utils thirdparty  plugins bfcommon bfskinmodule download interfaces
#子项的依赖关系
download.depends += utils
bfskinmodule.depends += utils
plugins.depends += utils thirdparty bfcommon bfskinmodule download  interfaces
instance.depends += plugins bfskinmodule  bfcommon