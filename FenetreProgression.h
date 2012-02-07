/*
 *  FenetreProgression.h
 *  ProfileSaver
 *
 *  Created by Francis Genet on 27/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HEADER_FENETREPROGRESSION
#define HEADER_FENETREPROGRESSION

#include <QtGui>
#include <QtCore>

class FenetreProgression : public QDialog
{
    Q_OBJECT

public:
	FenetreProgression(QString logiciel, QWidget *parent);
	FenetreProgression(QString logiciel, QWidget *parent, QString source);

private slots:
    int copyDir();
	int copyDirIm();

private:
    QString m_logiciel;
	QString m_source;
	QProgressBar *m_progressBar;
	QLabel *m_curAction;
	QPushButton *m_bouton;
};

#endif
