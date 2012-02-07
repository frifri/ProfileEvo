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

#include "FenetreProgression.h"
#include "CDirCopy.h"

FenetreProgression::FenetreProgression(QString logiciel, QWidget *parent) : QDialog(parent)
{
    m_curAction = new QLabel("Copie des fichiers de profil en cour...");
    m_curAction->setAlignment(Qt::AlignHCenter);

	m_progressBar = new QProgressBar;
	m_progressBar->setMaximum(100);
	m_progressBar->setMinimum(0);
	m_progressBar->setValue(0);
	m_progressBar->setAlignment(Qt::AlignHCenter);

	m_bouton = new QPushButton("OK");
	m_bouton->setEnabled(false);

	QVBoxLayout *layoutPrincipale = new QVBoxLayout;
	layoutPrincipale->addWidget(m_curAction);
	layoutPrincipale->addWidget(m_progressBar);
	layoutPrincipale->addWidget(m_bouton);

    setWindowTitle("Copie...");
	setWindowIcon(QIcon("icone.png"));
	setLayout(layoutPrincipale);

	m_logiciel = logiciel;

    // le timer pour permettre la creation de la fenetre
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    QWidget::connect(timer, SIGNAL(timeout()), this, SLOT(copyDir()));
    timer->start(500);

    // Le bouton OK
	QWidget::connect(m_bouton, SIGNAL(clicked()), this, SLOT(accept()));
}

FenetreProgression::FenetreProgression(QString logiciel, QWidget *parent, QString source) : QDialog(parent)
{
	m_curAction = new QLabel("Copie des fichiers de profil en cour...");
    m_curAction->setAlignment(Qt::AlignHCenter);
	
	m_progressBar = new QProgressBar;
	m_progressBar->setMaximum(100);
	m_progressBar->setMinimum(0);
	m_progressBar->setValue(0);
	m_progressBar->setAlignment(Qt::AlignHCenter);
	
	m_bouton = new QPushButton("OK");
	m_bouton->setEnabled(false);
	
	QVBoxLayout *layoutPrincipale = new QVBoxLayout;
	layoutPrincipale->addWidget(m_curAction);
	layoutPrincipale->addWidget(m_progressBar);
	layoutPrincipale->addWidget(m_bouton);
	
    setWindowTitle("Copie...");
	setWindowIcon(QIcon("icone.png"));
	setLayout(layoutPrincipale);
	
	m_logiciel = logiciel;
	m_source = source;
	
    // le timer pour permettre la creation de la fenetre
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    QWidget::connect(timer, SIGNAL(timeout()), this, SLOT(copyDirIm()));
    timer->start(500);
	
    // Le bouton OK
	QWidget::connect(m_bouton, SIGNAL(clicked()), this, SLOT(accept()));
}

int FenetreProgression::copyDirIm()
{
	m_progressBar->setValue(5);
	
    // Creation de la copie du dossier
	CDirCopy copy;
	
	m_progressBar->setValue(10);
	
	// recuperation de l'heure toussa
	QTime curTime = QTime::currentTime();
	QString strCurTime = curTime.toString("hhmmss");
	
	m_progressBar->setValue(15);
	
	// SetSource
	copy.setSource(m_source);
	
	m_progressBar->setValue(20);
	
	// setTarget
	if (m_logiciel == "Thunderbird")
		copy.setTarget(QDir::homePath() + "/Application Data/Thunderbird/Profiles");
    else if(m_logiciel == "Outlook Express")
        copy.setTarget(QDir::homePath() + "/Local Settings/Application Data/Identities");
	else if(m_logiciel == "Outlook Express")
        copy.setTarget(QDir::homePath() + "/Local Settings/Application Data/Microsoft/Outlook");
	
	m_progressBar->setValue(30);
	
	// lancement de la copie
	if (m_logiciel == "Thunderbird" || m_logiciel == "Outlook Express")
		copy.launch();
	else 
		copy.launch2007();
	
	m_progressBar->setValue(100);

	QMessageBox::information(this, "Copie...", "La copie est terminee, vous retrouverez votre messagerie comme à l'époque de la sauvegarde");

	m_bouton->setEnabled(true);
	
	return true;
}

int FenetreProgression::copyDir()
{
    m_progressBar->setValue(5);

    // Creation de la copie du dossier
	CDirCopy copy;
	
	// Creation du dossier de base si pas existant
	QDir dir(QDir::homePath() + "/Desktop/Profils_Messagerie");
	//QDir dir(QDir::homePath() + "/Bureau/Profiles_Messagerie");
	
	// Si le dossier n'existe pas
	if(!dir.exists())
	{
		QDir base(QDir::homePath() + "/Desktop");
		//QDir base(QDir::homePath() + "/Bureau");
		
		// Si le dossier n'a pas été créé
		if(!base.mkdir("Profils_Messagerie"))
		{
			QMessageBox::information(this, "Erreur !", "Une erreur est survenue lors de la création du dossier de base sur votre bureau");
			return false;
		}
	}

	m_progressBar->setValue(10);

	// recuperation de l'heure toussa
	QTime curTime = QTime::currentTime();
	QString strCurTime = curTime.toString("hhmmss");

	m_progressBar->setValue(15);

	// SetSource
	if (m_logiciel == "Thunderbird")
		copy.setSource(QDir::homePath() + "/Application Data/Thunderbird/Profiles");
    else if(m_logiciel == "Outlook Express")
        copy.setSource(QDir::homePath() + "/Local Settings/Application Data/Identities");
	else if(m_logiciel == "Outlook Express")
        copy.setSource(QDir::homePath() + "/Local Settings/Application Data/Microsoft/Outlook");

	m_progressBar->setValue(20);

	// setTarget
	if (m_logiciel == "Thunderbird")
		copy.setTarget(QDir::homePath() + "/Desktop/Profils_Messagerie/Profils_Thunderbird_" + strCurTime);
    else if(m_logiciel == "Outlook Express")
        copy.setTarget(QDir::homePath() + "/Desktop/Profils_Messagerie/Profils_Outlook_Express_" + strCurTime);
	else if(m_logiciel == "Microsoft Office Outlook 2007")
        copy.setTarget(QDir::homePath() + "/Desktop/Profils_Messagerie/");
	/*
	if (m_logiciel == "Thunderbird")
		copy.setTarget(QDir::homePath() + "/Bureau/Profils_Messagerie/Profils_Thunderbird_" + strCurTime);
    else if(m_logiciel == "Outlook Express")
        copy.setTarget(QDir::homePath() + "/Bureau/Profils_Messagerie/Profils_Outlook_Express_" + strCurTime);
	else if(m_logiciel == "Microsoft Office Outlook 2007")
        copy.setTarget(QDir::homePath() + "/Bureau/Profils_Messagerie/);
	*/
		
	m_progressBar->setValue(30);

	// lancement de la copie
	if (m_logiciel == "Thunderbird" || m_logiciel == "Outlook Express")
		copy.launch();
	else 
		copy.launch2007();

	m_progressBar->setValue(100);

	if (m_logiciel == "Thunderbird")
		QMessageBox::information(this, "Copie...", "La copie est terminee, vous trouverez votre profil sur votre bureau dans le dossier Profils_Messagerie/<strong>'Profils_Thunderbird_" + strCurTime + "'</strong>");
    else if(m_logiciel == "Outlook Express")
        QMessageBox::information(this, "Copie...", "La copie est terminee, vous trouverez votre profil sur votre bureau dans le dossier Profils_Messagerie/<strong>'Profils_Outlook_Express_" + strCurTime + "'</strong>");
	else if(m_logiciel == "Microsoft Office Outlook 2007")
        QMessageBox::information(this, "Copie...", "La copie est terminee, vous trouverez votre profil sur votre bureau dans le dossier Profils_Messagerie/<strong>'Profils_Outlook_2007_" + copy.m_date + "'</strong>");
	
	m_bouton->setEnabled(true);
	
	return true;
}
