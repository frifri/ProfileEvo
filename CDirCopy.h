#ifndef __CDIRCOPY_H__
#define __CDIRCOPY_H__

#include <QtCore>
#include <QtGui>

class CDirCopy : public QObject
{
	Q_OBJECT
	
public:
	int launch();
	int launch2007();
	
	inline void setSource(QString srcDir) { m_src = srcDir; }
	inline void setTarget(QString tarDir) { m_tar = tarDir; }
	
	// Pour le nom du dossier
	QString m_date;
	
private:
	QString m_src;
	QString m_tar;
	
	void recursiveCopy(QDir srcN, QDir tarN);
};

#endif //__CDIRCOPY_H__
