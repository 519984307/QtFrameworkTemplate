//
// Created by luqi on 2021/12/12.
//

#include "bftypeutils.h"
#include <QHash>
#include <QObject>

struct BFTypeInfo {
public:
    BFTypeInfo(){}
    BFTypeInfo(const QString& name_param,qint32 group_param,qint32 type_param = 0):
    name(name_param),group(group_param),type(type_param)
    {

    }
  QString name;
  qint32 group;
  qint32 type{0};  // 0x100000 : 数据类型，0x200000: 数据结构
};
static const qint32 BF_TYPEGRP_RENDER = 1;
static const qint32 BF_TYPEGRP_IMAGE = 2;
static const qint32 BF_TYPEGRP_FILE = 3;
static const qint32 BF_TYPEGRP_SOURCE = 4;
static const qint32 BF_TYPEGRP_OTHER = 5;

static const qint32 BF_TYPE_IMAGE = 0x1;
static const qint32 BF_TYPE_VIDEO = 0x2;
static const qint32 BF_TYPE_AUDIO = 0x4;
static const qint32 BF_TYPE_FONT = 0x8;
static const qint32 BF_TYPE_BUILTINIMAGE = 0x10;

#ifdef WIN32

static QHash<qint64, BFTypeInfo> s_typeMap{
    {1, {"bmp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {2, {"dib", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {3, {"rle", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {10, {"png", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {20, {"jpg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {21, {"jpeg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {22, {"jpe", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {23, {"jfif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {30, {"gif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {40, {"tif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {41, {"tiff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {50, {"ico", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {51, {"icon", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {60, {"webp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},

    {100, {"svg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
    {110, {"cdr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {120, {"psd", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {121, {"psb", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {130, {"ai", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {131, {"pdf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {132, {"eps", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {140, {"dds", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {150, {"tga", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {160, {"hdr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {170, {"heic", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {180, {"exr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {190, {"doc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {191, {"docx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {192, {"ppt", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {193, {"pptx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {194, {"xls", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {195, {"xlsx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {200, {"ttf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
    {201, {"otf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
    {202, {"ttc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
    {210, {"mp3", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {211, {"wav", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {220, {"mp4", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {221, {"mov", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {222, {"mpg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {223, {"mkv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {224, {"3g2p", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {225, {"asf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {226, {"dv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {227, {"f4v", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {228, {"m2ts", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {229, {"m4v", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {230, {"mxf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {231, {"gov", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {232, {"swf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {233, {"trp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {234, {"ts", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {235, {"vob", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {236, {"webm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {237, {"wmv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {238, {"rm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {239, {"rmvb", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},

    {300, {"icns", BF_TYPEGRP_IMAGE}},
    {310, {"base64", BF_TYPEGRP_IMAGE}},
    {320, {"obj", BF_TYPEGRP_IMAGE}},
    {330, {"3fr", BF_TYPEGRP_IMAGE}},
    {340, {"arw", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {350, {"cr2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {351, {"cr3", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {352, {"crw", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {360, {"dng", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {370, {"erf", BF_TYPEGRP_IMAGE}},
    {380, {"mrw", BF_TYPEGRP_IMAGE}},
    {390, {"nef", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {400, {"nrw", BF_TYPEGRP_IMAGE}},
    {410, {"orf", BF_TYPEGRP_IMAGE}},
    {420, {"pef", BF_TYPEGRP_IMAGE}},
    {430, {"raf", BF_TYPEGRP_IMAGE}},
    {440, {"raw", BF_TYPEGRP_IMAGE}},
    {450, {"rw2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {460, {"sr2", BF_TYPEGRP_IMAGE}},
    {470, {"srw", BF_TYPEGRP_IMAGE}},
    {480, {"x3f", BF_TYPEGRP_IMAGE}},
    {482, {"mos", BF_TYPEGRP_IMAGE}},
    {483, {"kdc", BF_TYPEGRP_IMAGE}},
    {484, {"dcr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},

    {620, {"ogg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {640, {"flv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {650, {"avi", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {660, {"flac", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {670, {"m4a", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {690, {"xmind", BF_TYPEGRP_FILE}},
    {700, {"potx", BF_TYPEGRP_FILE}},
    {710, {"txt", BF_TYPEGRP_FILE}},
    {720, {"key", BF_TYPEGRP_FILE}},
    {730, {"numbers", BF_TYPEGRP_FILE}},
    {740, {"pages", BF_TYPEGRP_FILE}},
    {750, {"ape", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {751, {"aac", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {752, {"aiff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {754, {"amr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},

    {800, {"afdesign", BF_TYPEGRP_SOURCE}},
    {810, {"afphoto", BF_TYPEGRP_SOURCE}},
    {820, {"afpub", BF_TYPEGRP_SOURCE}},
    {830, {"c4d", BF_TYPEGRP_SOURCE}},
    {840, {"clip", BF_TYPEGRP_SOURCE}},
    {850, {"dwg", BF_TYPEGRP_SOURCE}},
    {860, {"fig", BF_TYPEGRP_SOURCE}},
    {870, {"graffle", BF_TYPEGRP_SOURCE}},
    {880, {"idml", BF_TYPEGRP_SOURCE}},
    {890, {"indd", BF_TYPEGRP_SOURCE}},
    {900, {"indt", BF_TYPEGRP_SOURCE}},
    {910, {"mindnode", BF_TYPEGRP_SOURCE}},
    {920, {"pxd", BF_TYPEGRP_SOURCE}},
    {930, {"prd", BF_TYPEGRP_SOURCE}},
    {940, {"sketch", BF_TYPEGRP_SOURCE}},
    {950, {"skt", BF_TYPEGRP_SOURCE}},
    {960, {"skp", BF_TYPEGRP_SOURCE}},
    {970, {"xd", BF_TYPEGRP_SOURCE}},
    {980, {"eddx", BF_TYPEGRP_SOURCE}},
    {990, {"emmx", BF_TYPEGRP_SOURCE}},

    {1100, {"html", BF_TYPEGRP_OTHER}},
    {1110, {"woff", BF_TYPEGRP_OTHER}},
    {1120, {"zip", BF_TYPEGRP_OTHER}},

    {1200, {"psdt", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1201, {"jpf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1202, {"jpx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1203, {"jp2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1204, {"j2c", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1205, {"j2k", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1206, {"jpc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1207, {"jps", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1208, {"pcx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1209, {"pbm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1210, {"pgm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1211, {"ppm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1212, {"pnm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    //                                          {1213, {"pfm",
    //                                          BF_TYPEGRP_RENDER,
    //                                          BF_TYPE_IMAGE}},
    {1214, {"pam", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1215, {"sct", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1216, {"mpo", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1217, {"wmf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    //                                          {1218, {"mif",
    //                                          BF_TYPEGRP_RENDER,
    //                                          BF_TYPE_IMAGE}},
    {1219, {"miff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {1220, {"pdd", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},

    {3000, {"lnk", BF_TYPEGRP_OTHER}}};
#elif __APPLE__
static QHash<qint64, BFTypeInfo> s_typeMap = {{1, {"bmp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {2, {"dib", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {3, {"rle", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {10, {"png", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {20, {"jpg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {21, {"jpeg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {22, {"jpe", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {23, {"jfif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {30, {"gif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {40, {"tif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {41, {"tiff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {50, {"ico", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {51, {"icon", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {60, {"webp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},

                                             {100, {"svg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_BUILTINIMAGE}},
                                             {110, {"cdr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {120, {"psd", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {121, {"psb", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {130, {"ai", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {131, {"pdf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {132, {"eps", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {140, {"dds", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {150, {"tga", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {160, {"hdr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {170, {"heic", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {180, {"exr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {190, {"doc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {191, {"docx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {192, {"ppt", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {193, {"pptx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {194, {"xls", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {195, {"xlsx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                             {200, {"ttf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
                                             {201, {"otf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
                                             {202, {"ttc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_FONT}},
                                             {210, {"mp3", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
                                             {211, {"wav", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
                                             {220, {"mp4", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {221, {"mov", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {222, {"mpg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {223, {"mkv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {224, {"3g2p", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {225, {"asf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {226, {"dv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {227, {"f4v", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {228, {"m2ts", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {229, {"m4v", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {230, {"mxf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {231, {"gov", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {232, {"swf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {233, {"trp", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
                                             {234, {"ts", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {235, {"vob", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {236, {"webm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {237, {"wmv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {238, {"rm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {239, {"rmvb", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},

    {300, {"icns", BF_TYPEGRP_IMAGE}},
    {310, {"base64", BF_TYPEGRP_IMAGE}},
    {320, {"obj", BF_TYPEGRP_IMAGE}},
    {330, {"3fr", BF_TYPEGRP_IMAGE}},
    {340, {"arw", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {350, {"cr2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {351, {"cr3", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {352, {"crw", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {360, {"dng", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {370, {"erf", BF_TYPEGRP_IMAGE}},
    {380, {"mrw", BF_TYPEGRP_IMAGE}},
    {390, {"nef", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {400, {"nrw", BF_TYPEGRP_IMAGE}},
    {410, {"orf", BF_TYPEGRP_IMAGE}},
    {420, {"pef", BF_TYPEGRP_IMAGE}},
    {430, {"raf", BF_TYPEGRP_IMAGE}},
    {440, {"raw", BF_TYPEGRP_IMAGE}},
    {450, {"rw2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    {460, {"sr2", BF_TYPEGRP_IMAGE}},
    {470, {"srw", BF_TYPEGRP_IMAGE}},
    {480, {"x3f", BF_TYPEGRP_IMAGE}},
    {482, {"mos", BF_TYPEGRP_IMAGE}},
    {483, {"kdc", BF_TYPEGRP_IMAGE}},
    {484, {"dcr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},

    {620, {"ogg", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {640, {"flv", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {650, {"avi", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_VIDEO}},
    {660, {"flac", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {670, {"m4a", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
    {690, {"xmind", BF_TYPEGRP_FILE}},
    {700, {"potx", BF_TYPEGRP_FILE}},
    {710, {"txt", BF_TYPEGRP_FILE}},
    {720, {"key", BF_TYPEGRP_FILE}},
    {730, {"numbers", BF_TYPEGRP_FILE}},
                                             {740, {"pages", BF_TYPEGRP_FILE}},
                                             {750, {"ape", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
                                             {751, {"aac", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
                                             {752, {"aiff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},
                                             {754, {"amr", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE | BF_TYPE_AUDIO}},

                                             {800, {"afdesign", BF_TYPEGRP_SOURCE}},
                                             {810, {"afphoto", BF_TYPEGRP_SOURCE}},
                                             {820, {"afpub", BF_TYPEGRP_SOURCE}},
                                             {830, {"c4d", BF_TYPEGRP_SOURCE}},
                                             {840, {"clip", BF_TYPEGRP_SOURCE}},
                                             {850, {"dwg", BF_TYPEGRP_SOURCE}},
                                             {860, {"fig", BF_TYPEGRP_SOURCE}},
                                             {870, {"graffle", BF_TYPEGRP_SOURCE}},
                                             {880, {"idml", BF_TYPEGRP_SOURCE}},
                                             {890, {"indd", BF_TYPEGRP_SOURCE}},
                                             {900, {"indt", BF_TYPEGRP_SOURCE}},
                                             {910, {"mindnode", BF_TYPEGRP_SOURCE}},
                                             {920, {"pxd", BF_TYPEGRP_SOURCE}},
                                             {930, {"prd", BF_TYPEGRP_SOURCE}},
                                             {940, {"sketch", BF_TYPEGRP_SOURCE}},
                                             {950, {"skt", BF_TYPEGRP_SOURCE}},
                                             {960, {"skp", BF_TYPEGRP_SOURCE}},
                                             {970, {"xd", BF_TYPEGRP_SOURCE}},
                                             {980, {"eddx", BF_TYPEGRP_SOURCE}},
                                             {990, {"emmx", BF_TYPEGRP_SOURCE}},

                                             {1100, {"html", BF_TYPEGRP_OTHER}},
                                             {1110, {"woff", BF_TYPEGRP_OTHER}},
                                             {1120, {"zip", BF_TYPEGRP_OTHER}},

                                              {1200, {"psdt", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1201, {"jpf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1202, {"jpx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1203, {"jp2", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1204, {"j2c", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1205, {"j2k", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1206, {"jpc", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1207, {"jps", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1208, {"pcx", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1209, {"pbm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1210, {"pgm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1211, {"ppm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1212, {"pnm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    //                                          {1213, {"pfm", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1214, {"pam", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1215, {"sct", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1216, {"mpo", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1217, {"wmf", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
    //                                          {1218, {"mif", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1219, {"miff", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},
                                              {1220, {"pdd", BF_TYPEGRP_RENDER, BF_TYPE_IMAGE}},

                                             {3000, {"lnk", BF_TYPEGRP_OTHER}}};

#endif
bool BFTypeUtils::isVideo(qint64 tid) noexcept {
  static auto le = s_typeMap.constEnd();
  auto li = s_typeMap.constFind(tid);
  if (le != li) {
    return li.value().type & BF_TYPE_VIDEO;
  }
  return false;
}
bool BFTypeUtils::isAudio(qint64 tid) noexcept {
  static auto le = s_typeMap.constEnd();
  auto li = s_typeMap.constFind(tid);
  if (le != li) {
    return li.value().type & BF_TYPE_AUDIO;
  }
  return false;
}
bool BFTypeUtils::isSvg(qint64 tid) noexcept { return tid == 100; }
bool BFTypeUtils::isGif(qint64 tid) noexcept { return tid == 30; }

bool BFTypeUtils::isPsd(qint64 tid) noexcept
{
    return tid == 120;
}

bool BFTypeUtils::isPpt(qint64 tid) noexcept
{
    return tid == 192 || tid == 193;
}

// FIX 1005，主观上定义的qt支撑的内置图片类型，全面性是不确定的
bool BFTypeUtils::isBuiltInImageType(qint64 tid) noexcept {
  static auto le = s_typeMap.constEnd();
  auto li = s_typeMap.constFind(tid);
  if (le != li) {
    return li.value().type & BF_TYPE_BUILTINIMAGE;
  }
  return false;
}

bool BFTypeUtils::isShowBigPrivewBtn(qint64 tid) noexcept{
    static auto le = s_typeMap.constEnd();
    auto li = s_typeMap.constFind(tid);
    if (le != li) {
      return li.value().group & BF_TYPEGRP_RENDER && li.value().type & BF_TYPE_IMAGE;
    }
    return false;
}
