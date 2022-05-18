#include "BFCommandLineParser.h"
#include <QCommandLineParser>
#include <QApplication>
#include <QDebug>

BFCommandLineParser::BFCommandLineParser() {}

bool BFCommandLineParser::IsSetAutoRun() {
  QStringList list = qApp->arguments();
  if (list.contains("auto")) {
    return true;
  } else {
    return false;
  }
}

QString BFCommandLineParser::GetAutoRunValue() { return "auto"; }

bool BFCommandLineParser::IsSetGreenPacketLibPath() {
  QCommandLineParser command_parser;
  command_parser.setSingleDashWordOptionMode(
      QCommandLineParser::ParseAsLongOptions);
  QCommandLineOption option("o");
  option.setValueName("lib_path");
  command_parser.addOption(option);
  command_parser.parse(qApp->arguments());
  return command_parser.isSet(option);
}

QString BFCommandLineParser::GetGreenPacketLibPath() { 
  qDebug() << "Start GetGreenPacketLibPath";
  QCommandLineParser command_parser;
  command_parser.setSingleDashWordOptionMode(
      QCommandLineParser::ParseAsLongOptions);
  QCommandLineOption option("o");
  option.setValueName("lib_path");
  command_parser.addOption(option);
  qDebug() << "arguments size" << qApp->arguments().size();
  qDebug() << qApp->arguments();
  command_parser.parse(qApp->arguments());
  QString str;
  if (command_parser.isSet(option)) {
     str = command_parser.value(option);
    qDebug() << " BFCommandLineParser::GetGreenPacketLibPath() str"
             << str;
  }

  qDebug() << "End GetGreenPacketLibPath";
  return str;
}

bool BFCommandLineParser::IsSetGreenPacketBuryPointIniPath() { 
  QCommandLineParser command_parser;
  command_parser.setSingleDashWordOptionMode(
      QCommandLineParser::ParseAsLongOptions);
  QCommandLineOption option("b");
  option.setValueName("ini_path");
  command_parser.addOption(option);
  command_parser.parse(qApp->arguments());
  return command_parser.isSet(option);
}

QString BFCommandLineParser::GetGreenPacketBuryPointIniPath() {
  QCommandLineParser command_parser;
  command_parser.setSingleDashWordOptionMode(
      QCommandLineParser::ParseAsLongOptions);
  QCommandLineOption option("b");
  option.setValueName("ini_path");
  command_parser.addOption(option);
  command_parser.parse(qApp->arguments());
  QString str;
  if (command_parser.isSet(option)) {
     str = command_parser.value(option);
    qDebug() << " BFCommandLineParser::GetGreenPacketBuryPointIniPath() str" << str;
  }
  return str;
}



BFCommandLineParser::~BFCommandLineParser() {



}
