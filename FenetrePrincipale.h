/*
* Copyright 2009 - 2012 Francis Genet.
*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
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
