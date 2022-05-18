TEMPLATE = subdirs
SUBDIRS += instance utils thirdparty  plugins \
    bfcommon bfskinmodule download interfaces
download.depends += utils 
bfskinmodule.depends += utils 
plugins.depends += utils thirdparty bfcommon bfskinmodule download  interfaces
instance.depends += plugins bfskinmodule  bfcommon

