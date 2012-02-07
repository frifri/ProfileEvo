/*
 *  FenetrePrincipale.h
 *  ProfileSaver
 *
 *  Created by Francis Genet on 26/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HEADER_FENETREPRINCIPALE
#define HEADER_FENETREPRINCIPALE

#include <QtGui>
#include <QtCore>

class FenetrePrincipale : public QWidget
{
	Q_OBJECT

public:
	FenetrePrincipale();

private slots:
	void recProfilEx();
	void recProfilIm();
	void openGetDir();

private:
	// Widget d'onglet
	QTabWidget *m_onglets;
	// Page Export
	QWidget *m_pageExport;
	QLabel *m_bienvenueEx;
	QComboBox *m_chxLogicielEx;
	QPushButton *m_validerEx;
	QPushButton *m_quitterEx;
	// Page Import
	QWidget *m_pageImport;
	QLabel *m_bienvenueIm;
	QLineEdit *m_dossierIm;
	QPushButton *m_browseIm;
	QComboBox *m_chxLogicielIm;
	QPushButton *m_validerIm;
	QPushButton *m_quitterIm;
	
};

#endif
