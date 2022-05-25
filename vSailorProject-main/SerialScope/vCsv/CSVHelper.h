#pragma once

#include <QObject>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>

class CSVHelper : public QObject
{
	Q_OBJECT

public:
	CSVHelper(QObject *parent);
	~CSVHelper();
	
	static QList<QList<QString>> ReadCSVtoData(QString CSVFilePath);
	static int SaveCSVtoFile(QList<QList<QString>> CSVData, QString CSVFilePath);
	
	
private:
	
	static int CountOfQuotationMark(QString str);//�����ַ�����Ӣ�����ŵĸ���
	static bool isEven(int num);//����num�Ƿ�Ϊż��
	static QList<QString> ReadLineToCell(QString str);//��CSV�ļ���һ�����ݷֽ⵽��Ԫ����
	static QString ReadDataToCell(QString str);//��CSV��һ����Ԫ�����ݴ�������յĵ�Ԫ���ݣ���ɾ�����������

	static QList<QList<QString>> CheckCSVData(QList<QList<QString>> CSVData);//У��csv����
	static QString CombineLine(QList<QString> lineData);//�ϲ�һ������
	static QString TranData(QString str);//�����ݽ���ת��
};
