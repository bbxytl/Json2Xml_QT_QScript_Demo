#ifndef QSCRIPTJSON_H
#define QSCRIPTJSON_H

#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include <QFile>
#include "AHeaders.h"

#include <QMap>


class QScriptJson
{
public:
   QScriptJson(const QString &fileName);
   ~QScriptJson();

   bool write2File();
private:
   void getPropety(QScriptValue sv, QStringList sLsPty);
   void getPropety(QScriptValue sv, QStringList sLsPty,QString space);
private:
   QXmlStreamWriter m_writer;
   QString m_fileName;
   QMap<QString,QVariant> m_mapProperty; //存放数据层次属性
   QMap<QString,QVariant> m_mapItems;   //节点中的子节点集

};

#endif // QSCRIPTJSON_H
