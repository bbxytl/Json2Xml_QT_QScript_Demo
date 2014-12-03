#include "qscriptjson.h"

static QString datas =
        QString("{'billcount':2,'bills':[\
         {'billID':'010101001','billname':'平整场地','billunit':'m2','decount':3,\
            'des':[{'deID':'A1-1','decont':'建筑场地挖填高度在±30cm以内的找平','dename':'平整场地','deunit':'100m2'},\
                {'deID':'A1-3','decont':'土方开挖','dename':'人工挖土方 三类土 深度在1.5m内','deunit':'100m3'},\
                {'deID':'A1-4','decont':'土方开挖','dename':'人工挖土方 四类土 深度在1.5m内','deunit':'100m3'}]},\
        {'billID':'010101005','billname':'挖淤泥、流砂','billunit':'m3','decount':1,\
            'des':[{'deID':'A1-27','decont':'挖淤泥、流砂','dename':'人工挖淤泥流砂','deunit':'100m3'}]}]}");

QScriptJson::QScriptJson(const QString &fileName)
{
    m_fileName=fileName;
    QStringList sls;
    m_mapProperty.insert("_BEGIN_","BillTable");
    sls<<"billcount"<<"bills";
    m_mapProperty.insert("BillTable",sls);
    sls.clear();
    sls<<"billID"<<"billname"<<"billunit"<<"decount"<<"des";
    m_mapProperty.insert("bills",sls);
    sls.clear();
    sls<<"deID"<<"decont"<<"dename"<<"deunit";
    m_mapProperty.insert("des",sls);
    sls.clear();
    m_mapProperty.insert("_END_","_END_");

    m_mapItems.insert("bills","BillItem");
    m_mapItems.insert("des","DesItem");

}

QScriptJson::~QScriptJson()
{

}

bool QScriptJson::write2File()
{
    QString dt=datas;
    QFile file(m_fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        dbg<<QString("打不开文件 : %1").arg (m_fileName);
        return false;
    }
    try{
        m_writer.setDevice(&file);
        m_writer.setAutoFormatting(true);
        //文档开始
        m_writer.writeStartDocument();

        QScriptEngine engine;
        QScriptValue sv = engine.evaluate("value="+dt);
        QString strBegin=m_mapProperty.value("_BEGIN_").toString();

        m_writer.writeStartElement(strBegin);
        QStringList sLsPty=m_mapProperty.value(strBegin).toStringList();
        getPropety(sv,sLsPty," ");
        getPropety(sv,sLsPty);
        m_writer.writeEndElement();
        m_writer.writeEndDocument();
    }catch(...){
         dbg<<"Error: Write to File .";
         file.close();
    }
    file.close();
}

void QScriptJson::getPropety(QScriptValue sv,QStringList sLsPty)
{
    foreach(QString element,sLsPty){
        QScriptValue sptV=sv.property(element);
        if(!sptV.isArray()){
            QString value=sptV.toString();
            m_writer.writeAttribute(element,value);
        }else{
            m_writer.writeStartElement(element);

            QScriptValueIterator it(sptV);
            while (it.hasNext()) {
                it.next();                
                if(it.flags()&&QScriptValue::SkipInEnumeration)continue;
                QString item=m_mapItems.value(element).toString();
                m_writer.writeStartElement(item);
                QStringList sLs_Child=m_mapProperty.value(element).toStringList();
                getPropety(it.value(),sLs_Child);
                m_writer.writeEndElement();
            }
            m_writer.writeEndElement();
        }
    }
}

void QScriptJson::getPropety(QScriptValue sv, QStringList sLsPty,QString space)
{
    foreach(QString str,sLsPty){
        QScriptValue sptV=sv.property(str);
        if(!sptV.isArray()){
            QString str2=sptV.toString();
            dbg<<(space+str+QString(" : ")+str2);  //如果当前属性不是一个数组，则输出其内容
        }else{
            dbg<<(space+str+QString(" [ "));
            QScriptValueIterator it(sptV);
//            dbg<<it.name()<<it.value().toString();
//            if(it.hasNext())it.next();
            while (it.hasNext()) {
                it.next();
//                dbg<<it.name()<<it.value().toString();
                if(it.flags()&&QScriptValue::SkipInEnumeration)continue;
                QStringList sLs_Child=m_mapProperty.value(str).toStringList();
                getPropety(it.value(),sLs_Child,space+"   ");
//                it.next();
            }
//            dbg<<it.name()<<it.value().toString();
            dbg<<(space+str+QString(" ] "));
        }
    }

}
