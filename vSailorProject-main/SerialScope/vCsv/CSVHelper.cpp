#include "CSVHelper.h"

QString QuotationMark = "\"";

CSVHelper::CSVHelper(QObject *parent)
	: QObject(parent)
{


}

CSVHelper::~CSVHelper()
{
}

//��CSV�ļ��ж�ȡ����
QList<QList<QString>> CSVHelper::ReadCSVtoData(QString CSVFilePath)
{
	//����һ���ַ����������ڴ洢CSV�ļ��е�����
	QList<QList<QString>> CSVData;

	QFile CSVFile(CSVFilePath);
	if (!CSVFile.exists())
	{
		return CSVData;
	}
	//ʹ��QFile����ļ���ʹ������ʽ���ж�ȡ
	if (CSVFile.open(QIODevice::ReadOnly))
	{
		//��ʱ�ַ��������ںϲ�������������
		QString tempstring = "";
		//ʹ�������ж�ȡ����
		QTextStream stream(&CSVFile);
		//stream.setDevice(&CSVFile);
		while (!stream.atEnd())
		{
			//��ȡһ������
			QString CSVLine = stream.readLine();
			//����������ʱ�ַ����ϲ�
			if (tempstring == "")
			{
                tempstring = CSVLine;
                //���һ����׼�Ľ���
                tempstring.append(",end");
			}
			else
			{
				tempstring = tempstring + "\r\n" + CSVLine;
			}
			//�ж���ʱ�ַ����е�Ӣ�����Ÿ����Ƿ�Ϊż���������ż������˵�����ݶ�ȡ��������������򷵻�ѭ��
			if (!isEven(CountOfQuotationMark(tempstring)))
			{
				continue;
			}
			CSVData.append(ReadLineToCell(tempstring));
			tempstring = "";
		}
		CSVFile.close();
	}
	return CSVData;
}

//��һ�����ݲ�ֳɵ�Ԫ
QList<QString> CSVHelper::ReadLineToCell(QString str)
{
	//����һ��һά�ַ����飬���ڴ洢��ֺ������
	QList<QString> cell;
	//��ʱ�洢�ַ��������ڷ���
	QString tempStr = "";
	//����ַ�����Ӣ�Ķ��Ž�β��˵�������һ���յ�Ԫ�������յ�Ԫ����
	bool lastCellExist = false;
	if (str.endsWith(","))
	{
		lastCellExist = true;
	}
	//�����ַ���
	while (str.length() > 0)
	{
		//��ʾ�ַ����ж��ŵ�λ��
		int index = -1;
		//���ҵ�һ��Ӣ�Ķ��ŵ�λ��
		index = str.indexOf(',');
		//���index��Ϊ-1����˵������Ӣ�Ķ��ţ������ж�
		if (index != -1)
		{
			//���ַ������зָӢ�Ķ���ǰ�ģ���Ӣ�Ķ��ţ���ȡ�����ӵ���ʱ�ַ�����
			tempStr = tempStr + str.mid(0, index + 1);
			str = str.mid(index + 1);
			//�����ʱ�ַ����е�Ӣ�����Ÿ�����ż������˵�������Ԫ����������������������򷵻�ѭ��
			if (isEven(CountOfQuotationMark(tempStr)))
			{
				//����Ϣ���д�����������Ԫ����
				cell.append(ReadDataToCell(tempStr));
				//����ʱ�ַ������
				tempStr = "";
			}
		}
		else
		{
			cell.append(ReadDataToCell(str));
			break;
		}
	}
	if (lastCellExist)
	{
		cell.append("");
	}
	return cell;
}

//��CSV��һ����Ԫ�����ݴ�������յĵ�Ԫ���ݣ���ɾ�����������
QString CSVHelper::ReadDataToCell(QString str)
{
	//����ַ������Զ��Ž�β�ģ���ȥ���ö���
	if (str.endsWith(","))
	{
		str = str.mid(0, str.length() - 1);
	}
	//����ַ�����ͷ�ͽ�β����Ӣ�����ţ���������Ӣ�����Ŷ�ȥ��
	if (str.endsWith("\"") && str.startsWith("\""))
	{
		str = str.mid(1, str.length() - 2);
	}
	//���ڱ��洦��Ľ��
	QString cellStr = "";
	//ȥ�������Ӣ������	
	str = str.replace("\"\"", "\"");
	return str;
}

//�ж�һ�������Ƿ�Ϊż���������ż����Ϊtrue������Ϊfalse��
bool CSVHelper::isEven(int num)
{
	//��2����
	if (num % 2)
		return false;
	else
		return true;
}

//����ָ���ַ������ж��ٸ�Ӣ������
int CSVHelper::CountOfQuotationMark(QString str)
{
	//Ӣ�����ŵĸ���
	int count = 0;
	//����ַ����бȽ�
	while (str.length() > 0)
	{
		//λ�ñ�ʶ��
		int index = -1;
		//�ַ����е�һ��Ӣ�����ŵ�λ��
		index = str.indexOf(QuotationMark);
		//���λ�ñ�ʶ������-1����˵���ַ����а���Ӣ������
		if (index != -1)
		{
			//�����������Ӣ������֮ǰ���ַ�
			str = str.mid(index + 1);
			//����������һ
			count++;
		}
		else
			break;
	}
	return count;
}

//�����ݱ����csv�ļ�����������·���ļ��Ѵ��ڣ��򷵻�-1�������������г��ִ����򷵻�0������ɹ�����1
int CSVHelper::SaveCSVtoFile(QList<QList<QString>> CSVData, QString CSVFilePath)
{
	//��Ᵽ��·���ļ��Ƿ��Ѿ����ڻ���·��Ϊ�գ�������ڷ���-1
	if (CSVFilePath == "" || CSVFilePath == NULL)
		return -1;
	
	//����ļ����ڣ��򷵻�-1
	QFile CSVFile(CSVFilePath);
	if (CSVFile.exists())
	{
		return -1;
	}
	//����csv�ļ����ö�д��ʽ��
	if (CSVFile.open(QIODevice::ReadWrite))
	{
		//У������
		CSVData = CheckCSVData(CSVData);
		//���н���¼��
		for (int i = 0; i < CSVData.length(); i++)
		{
			//��һ�����ݽ��кϲ�
			QString str = CombineLine(CSVData[i]) + "\r\n";
			//д������
			CSVFile.write(str.toUtf8());			
		}
		//�ر��ļ�
		CSVFile.close();
		return 1;
	}
	return 0;
}

//�����ݽ���ת��
QString CSVHelper::TranData(QString str)
{
	//����ַ����к���Ӣ�����ţ���Ҫ����ת�壬��������Ӣ�����ű�ʾһ��Ӣ������
	str.replace("\"", "\"\"");
	//����ַ����а���Ӣ�Ķ��Ż�Ӣ�����Ż��з�����Ҫ�ַ����������Ӣ������
	if (str.contains(",") || str.contains("\r\n") || str.contains("\n") || str.contains("\""))
	{
		str = "\"" + str + "\"";
	}
	return str;
}

//�ϲ�һ������
QString CSVHelper::CombineLine(QList<QString> lineData)
{
	QString str = "";
	//��һ�������еĸ���Ԫ��ϲ�����Ԫ�����ݽ���ת�壬֮����Ӣ�Ķ��Ÿ���
	for (int i = 0; i < lineData.length(); i++)
	{
		if (str == "")
			str = TranData(lineData[i]);
		else
			str = str + "," + TranData(lineData[i]);
	}
	return str;
}

//У��csv���ݣ�csv����Ӧ������ģ������ҪУ�飬����ȱ�ٵĵ�Ԫ��""����
QList<QList<QString>> CSVHelper::CheckCSVData(QList<QList<QString>> CSVData)
{
	//Ѱ���������е�Ԫ�������
	int maxLength = 0;
	for (int i = 0; i < CSVData.length(); i++)
	{
		if (maxLength < CSVData[i].length())
			maxLength = CSVData[i].length();
	}
	//����Ԫ����
	for (int i = 0; i < CSVData.length(); i++)
	{
		if (CSVData[i].length() < maxLength)
		{
			for (int j = 0; j < maxLength - CSVData[i].length(); j++)
			{
				CSVData[i].append("");
			}
		}
	}
	return CSVData;
}
