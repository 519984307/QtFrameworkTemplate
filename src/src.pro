TEMPLATE = subdirs
SUBDIRS += instance utils thirdparty  plugins \
    bfEventTrack \
    bfcommon bfskinmodule download interfaces
download.depends += utils bfEventTrack
bfskinmodule.depends += utils bfEventTrack
plugins.depends += utils thirdparty bfcommon bfskinmodule download bfEventTrack interfaces
instance.depends += plugins bfskinmodule bfEventTrack bfcommon

