#ifndef PROJECT_H
#define PROJECT_H
#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QMap>
#include <QVariant>
#include <QDateTime>
#include <QColor>
#include <QSharedPointer>

// 素材类型
enum MaterialType
{
    eMaterialTypeNone = 0,
    eMaterialTypeVideo = 1,
    eMaterialTypeImg = 2,
    eMaterialTypeAudio = 4,
    eMaterialTypeText = 8,
    eMaterialTypeAnnotation = 16,
    eMaterialTypeAll = 0xffffffff,
};

// 文本竖直对齐枚举
enum VAlign
{
    eVAlignLeft,
    eVAlignMiddle,
    eVAlignRight
};

// 标注类型
enum AnnotationType
{
    eAnnotationTypeRectangle,
    eAnnotationTypeEllipse,
    eAnnotationTypeArrow,
    eAnnotationTypeLine,
};

// 轨道类型
enum ProjectTrackType
{
    eTrackTypeVideo = 1,
    eTrackTypeAudio = 2,
    eTrackTypeTxt = 4,
    eTrackTypeAnnot = 8,
    eTrackTypeAll = 0xffffffff,
};

// 素材元信息
//struct MaterialMetaInfo
//{
//    MaterialType    type;
//    QString         id;
//    QString         name;
//    QString         alias_name; // 别名，用于重命名存储
//    QString         path;

//    // video,img
//    // key: duration,   has_audio,  w,      h,      thumb
//    // val: qint64,     bool,       int,    int,    QPixmap

//    // audio
//    // key: duration,   author
//    // val: qint64,     QString

//    // txt
//    // key: font_size, content, text_color, border_color, background_color, bold, italic, vert_align
//    // val: float,     QString, QString,    QString,      QString,          bool, bool,   VAlign

//    // annot
//    // key: type,           border_width,   border_color
//    // val: AnnotationType, int,            QString
//    QMap<QString, QVariant> extra_info;
//};

// video,img素材
//struct MaterialVideo : public MaterialMetaInfo
//{
//    qint64  duration;
//    bool    has_audio;
//    int     w;
//    int     h;
//};

//// 音频素材
//struct MaterialAudio : public MaterialMetaInfo
//{
//    qint64  duration;
//    QString author;
//};

//// 文本素材
//struct MaterialText : public MaterialMetaInfo
//{
//    float   font_size;
//    QString content;
//    QString text_color;
//    QString border_color;
//    QString background_color;
//    bool    bold;
//    bool    italic;
//    VAlign  align;
//};

//// 标注素材
//struct MaterialAnnotation : public MaterialMetaInfo
//{
//    AnnotationType  type;
//    int             border_width;
//    QString         border_color;
//};

//// 剪辑工程所有素材信息
//struct MaterialInfo
//{
//    QVector<QSharedPointer<MaterialVideo>>      videos;
//    QVector<QSharedPointer<MaterialAudio>>      audios;
//    QVector<QSharedPointer<MaterialText>>       texts;
//    QVector<QSharedPointer<MaterialAnnotation>> annots;
//};

// 去水印片段
//struct DelogoSegment
//{
//    qint64 start;       // ms
//    qint64 duration;    // ms
//    float  lower_left_x;
//    float  lower_left_y;
//    float  upper_right_x;
//    float  upper_right_y;
//};

// 去水印轨道
//struct DelogoTrack
//{
//    QVector<QSharedPointer<DelogoSegment>> segments;
//};

struct SegmentCanvasArea
{
    float   scale_x = 1.0;            // x坐标缩放系数
    float   scale_y = 1.0;            // y坐标缩放系数
    float   transform_x = 0.0;        // 素材左上角x坐标在canvas上的位置系数，屏幕坐标系左上角为0,0 右下角为1,1
    float   transform_y = 0.0;        // 素材左上角y坐标在canvas上的位置系数，屏幕坐标系左上角为0,0 右下角为1,1
    float   rotation = 0.0;           // 选转角度
};

struct SegmentTimeArea
{
    qint64 start = 0;
    qint64 duration = 0;
};

struct SegmentCropArea
{
    // 视频，图片裁剪区域
    float   lower_left_x = 0.0;
    float   lower_left_y = 0.0;
    float   lower_right_x = 1.0;
    float   lower_right_y = 0.0;
    float   upper_left_x = 0.0;
    float   upper_left_y = 1.0;
    float   upper_right_x = 1.0;
    float   upper_right_y = 1.0;
};

// 剪辑片段信息
//struct SegmentInfo
//{
//    QString id;                 // segment id
//    QString material_id;        // 关联素材id
//    float   alpha;              // 透明度
//    bool    horizontal_flip;    // 水平翻转
//    bool    vertical_flip;      // 竖直翻转
//    float   scale_x;            // x坐标缩放系数
//    float   scale_y;            // y坐标缩放系数
//    float   transform_x;        // 素材左上角x坐标在canvas上的位置系数，屏幕坐标系左上角为0,0 右下角为1,1
//    float   transform_y;        // 素材左上角y坐标在canvas上的位置系数，屏幕坐标系左上角为0,0 右下角为1,1
//    float   rotation;           // 选转角度
//    qint64  src_start;          // 素材本身的起始时间，单位ms
//    qint64  src_duration;       // 素材本身的时长，单位ms
//    qint64  target_start;       // 素材在轨道中的起始时间，单位ms
//    qint64  target_duration;    // 素材在轨道中的时长，单位ms
//    float   volume;             // 视频，音频素材音量

//    // 视频，图片裁剪区域
//    float   lower_left_x;
//    float   lower_left_y;
//    float   lower_right_x;
//    float   lower_right_y;
//    float   upper_left_x;
//    float   upper_left_y;
//    float   upper_right_x;
//    float   upper_right_y;

//    // 去水印轨道
//    //QVector<QSharedPointer<DelogoSegment>> delogo_tracks;
//};

//// 剪辑轨道信息
//struct TrackInfo
//{
//    QString             id;
//    ProjectTrackType    type;
//    int                 z_order;    // 层级，数字越大，离我们越近，越小越远。
//                                    // 主轨道层级为-1，离我们最远。
//    //QVector<QSharedPointer<SegmentInfo>> segments;
//};

//// 剪辑工程元信息
//struct ProjectMetaInfo
//{
//    QString     cover;
//    QString     fold_path;
//    QString     id;
//    QString     json_file;
//    QString     name;
//    QString     root_path;
//    QDateTime   tm_create;
//    QDateTime   tm_modified;
//    qint64      tm_duration; // ms
//};

//// 剪辑工程信息
//class ProjectInfo : public ProjectMetaInfo
//{
//    int w;
//    int h;
//    QString ratio;              // eg: "16:9/4:4/original"
//    //MaterialInfo materials;
//    //QVector<QSharedPointer<TrackInfo>> tracks;
//};

#endif
