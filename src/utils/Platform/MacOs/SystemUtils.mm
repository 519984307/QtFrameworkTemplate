//
//  SystemUtils.m
//  Billfish
//
//  Created by luqi on 2021/1/20.
//

#import "SystemUtils.h"
#include "SystemUtilsCInterface.h"
#import <AppKit/AppKit.h>
#include <QOperatingSystemVersion>
#include <QDebug>
#include <QFileinfo>
//#include "sysutils.h"

#import "SSZipArchive.h"

//using namespace MoyeaBased;

@implementation SystemUtils
+ (NSArray*)getApplicationURLsForURL:(NSString*)filePath {
  NSURL* url = [NSURL fileURLWithPath:filePath];

  // Ask launch services for the different apps that it thinks could edit this file.
  // This is usually a more useful list than what can view the file.
  LSRolesMask roles = kLSRolesAll;
  CFArrayRef urls = LSCopyApplicationURLsForURL((__bridge CFURLRef)url, roles);
  NSArray* appUrls = CFBridgingRelease(urls);

  return appUrls;
}

QStringList getApplicationURLsForURL(const QString& filePath) {
  NSString* localPath = filePath.toNSString();
  NSArray* appUrls = [SystemUtils getApplicationURLsForURL:localPath];
  QStringList list;
  for (NSURL* url in appUrls) {
    //[appNames addObject: url.lastPathComponent];

    list.append(QString::fromNSString(url.path));
    // list.append(QString::fromNSString(displayNameAtPath));
  }

  return list;
}

QString getApplicationDisplayNameWithFilePath(const QString& filePath) {
  NSFileManager* fileManager = [[NSFileManager alloc] init];
  NSString* displayNameAtPath = [fileManager displayNameAtPath:filePath.toNSString()];
  return QString::fromNSString(displayNameAtPath);
}

void openUrlWithApplication(const QString& filePath, const QString& applicationPath) {
  NSString* path = filePath.toNSString();
  NSURL* nsfilePath = [[NSURL alloc] initFileURLWithPath:path isDirectory:false];

  NSArray* urls = [NSArray arrayWithObject:nsfilePath];
  NSURL* appPath = [[NSURL alloc] initFileURLWithPath:applicationPath.toNSString()];

  NSError* err = nil;
  [[NSWorkspace sharedWorkspace] openURLs:urls
                     withApplicationAtURL:appPath
                                  options:0
                            configuration:NULL
                                    error:&err];
  NSLog(@"%@", err);
}

void makeKeyAndOrderFront(QWidget* w) {
  //   // [NSApp ]
  //    NSView * view = ( __bridge NSView * )reinterpret_cast<void *>(w->winId());
  //    NSWindow * nsWin = [view window];
  ////    [nsWin makeKeyAndOrderFront:NSApp];
  //	    [nsWin makeKeyAndOrderFront:nil];
  [NSApp activateIgnoringOtherApps:YES];
}

void changeMainWindowStyle(QWidget* w) {
  auto current = QOperatingSystemVersion::current();
  if (current < QOperatingSystemVersion::MacOSMojave) {
    // returns true on macOS >= 10.10 and iOS >= 8.0, but false on macOS < 10.10 and iOS < 8.0
    w->setWindowTitle("Billfish");
    return;
  }

  NSView* view = (__bridge NSView*)reinterpret_cast<void*>(w->winId());
  NSWindow* nsWin = [view window];
  [nsWin setStyleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                      NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable |
                      NSWindowStyleMaskFullSizeContentView];

  nsWin.titlebarAppearsTransparent = YES;
  [nsWin setReleasedWhenClosed:false];
  //[nsWin setMovableByWindowBackground:true];
  NSString* str = [[NSString alloc] init];
  [nsWin setTitle:str];

  NSColor* color = [nsWin backgroundColor];
  if (color == nil || (![color isEqual:[NSColor clearColor]])) {
    nsWin.opaque = false;
    [nsWin setBackgroundColor:[NSColor clearColor]];
  }

//  NSButton* button = [nsWin standardWindowButton:NSWindowZoomButton];
//  [button setEnabled:NO];
}

bool folderIconExist(const QString& folderPath) {
  NSImage* sp_image = [[NSWorkspace sharedWorkspace] iconForFile:folderPath.toNSString()];

  NSImage* default_folder_image =
      [[NSWorkspace sharedWorkspace] iconForFileType:NSFileTypeForHFSTypeCode(kGenericFolderIcon)];

  NSData* sp_data = [sp_image TIFFRepresentation];
  NSData* default_folder_data = [default_folder_image TIFFRepresentation];

  if ([sp_data isEqualToData:default_folder_data]) {
    return false;
  }
  return true;
}

unsigned long long getFolderSize(const QString& folderPath) {
  unsigned long long fileSize =
      [[[NSFileManager defaultManager] attributesOfItemAtPath:folderPath.toNSString()
                                                        error:nil] fileSize];
  return fileSize;
}

unsigned long long getFreeDiskSize(const QString& folderPath) {
  unsigned long long fileSize = [[[[NSFileManager defaultManager]
      attributesOfFileSystemForPath:folderPath.toNSString()
                              error:nil] objectForKey:NSFileSystemFreeSize] longLongValue];
  return fileSize;
}

unsigned long long getTotalDiskSize(const QString& folderPath) {
  unsigned long long fileSize = [[[[NSFileManager defaultManager]
      attributesOfFileSystemForPath:folderPath.toNSString()
                              error:nil] objectForKey:NSFileSystemSize] longLongValue];
  return fileSize;
}

void setFolderIcon(const QString& imagePath, const QString& folderPath) {
  NSImage* icon = [[NSImage alloc] initWithContentsOfFile:imagePath.toNSString()];
  [[NSWorkspace sharedWorkspace] setIcon:icon forFile:folderPath.toNSString() options:0];
}

void removeFolderIcon(const QString& folderPath){
  [[NSWorkspace sharedWorkspace] setIcon:nil forFile:folderPath.toNSString() options:0];
}

static double gScreenDpiScale = 0.0;
double getScreenDpiScale() {
  if (gScreenDpiScale > 0.0) {
    return gScreenDpiScale;
  }

  NSArray<NSScreen*>* screens = [NSScreen screens];
  for (NSUInteger i = 0; i < screens.count; ++i) {
    CGFloat devicePixelRatio = [screens[i] backingScaleFactor];
    if (devicePixelRatio > gScreenDpiScale) {
      gScreenDpiScale = devicePixelRatio;
    }
  }
  return gScreenDpiScale;
}

int localizedStandardCompare(const QString& lhs, const QString& rhs) {
  return (int)([lhs.toNSString() localizedStandardCompare:rhs.toNSString()]);
}

char* getMacAppVersion() {
  NSString* major = [[[NSBundle mainBundle] infoDictionary]
      objectForKey:@"CFBundleShortVersionString"];  // major version
  NSString* build =
      [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];  // build version
  NSString* full = [NSString stringWithFormat:@"%@.%@", major, build];
  if (full != nil) {
    // return (char*)full.UTF8String;
    return (char*)[full UTF8String];
  }
  return NULL;
}

bool isApplicationAlreadyRunning() {
  NSArray<NSRunningApplication*>* array =
      [NSRunningApplication runningApplicationsWithBundleIdentifier:@"cn.billfish.Billfish"];

  if (array.count > 1) {
    //[[NSApplication sharedApplication] terminate:nil];
    [array[0] activateWithOptions:(NSApplicationActivateAllWindows |
                                   NSApplicationActivateIgnoringOtherApps)];
    return true;
  }

  return false;
}

QString GetVolumeName(const QString& folder_path) {
  // path is the path of a folder
  NSURL* url = [NSURL fileURLWithPath:folder_path.toNSString()];
  NSError* error;
  NSString* volumeName = nil;
  [url getResourceValue:&volumeName forKey:NSURLVolumeNameKey error:&error];
  if (volumeName) {
    return QString::fromNSString(volumeName);
  }
  return QString("Unknown");
}

QStringList GetOpenOpenFileNameAndDir(const QString& title, const QString& dir) {
  NSOpenPanel* openPanel = [NSOpenPanel openPanel];
  [openPanel setAllowsMultipleSelection:YES];
  [openPanel setCanChooseFiles:YES];
  [openPanel setCanChooseDirectories:YES];
//  [openPanel setTreatsFilePackagesAsDirectories:YES];
  if (!title.isEmpty()) {
    [openPanel setTitle:title.toNSString()];
  }

  if (!dir.isEmpty()) {
    QFileInfo dir_info(dir);
    if (dir_info.exists() && dir_info.isDir()) {
      NSURL* url = [[NSURL alloc] initWithString:dir.toNSString()];
      [openPanel setDirectoryURL:url];
    }
  }

  NSInteger result = [openPanel runModal];
  QStringList stringList;

  if (result == NSModalResponseOK) {
    NSArray* URLs = [openPanel URLs];
    NSLog(@"URLs == %@", URLs);
    for (NSURL* URL in URLs) {
      stringList += QString::fromNSString(URL.path);
    }
  }

  return stringList;
}

void unzipToPath(const QString& zip_path, const QString& folder_path) {
  [SSZipArchive unzipFileAtPath:zip_path.toNSString()
                  toDestination:folder_path.toNSString()];
}

void createZipFileAtPath(const QString& zip_path,
                         const QStringList& file_paths) {
  if (file_paths.count() == 0) {
    return;
  }

  if (file_paths.isEmpty()) {
    return;
  }

  NSMutableArray* result = [NSMutableArray arrayWithCapacity:file_paths.size()];
  for (int i = 0; i < file_paths.size(); ++i) {
    [result
        addObject:file_paths[i]
                      .toNSString()];  // Now leak is gone!(If the autorelease
                                       // pool is used, but I think it is)
  }
  [SSZipArchive createZipFileAtPath:zip_path.toNSString()
                   withFilesAtPaths:result];
}

int getMenubarHeightOffset() {
  auto current = QOperatingSystemVersion::current();
  if (current < QOperatingSystemVersion::MacOSMojave) {
    // returns true on macOS >= 10.10 and iOS >= 8.0, but false on macOS < 10.10
    // and iOS < 8.0
    return 22;
  }

  return 0;
}

@end
