/*
 *  FenetrePrincipale.cpp
 *  ProfileSaver
 *
 *  Created by Francis Genet on 26/12/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "FenetrePrincipale.h"
#include "FenetreProgression.h"
#include "CDirCopy.h"

FenetrePrincipale::FenetrePrincipale()
{
	// Creation du QTabWidget
	m_onglets = new QTabWidget(this);
	
	// Creation des pages pour le QTabWidget
	m_pageExport = new QWidget;
	m_pageImport = new QWidget;
	
		// Page d'Export
		////////////////
	
		m_bienvenueEx = new QLabel("<strong>Exportez vos profils :</strong> <br /> \
                                           Choisissez votre logiciel de messagerie. <br /> \
                                           Validez... Patientez... C'est bon !");

		m_chxLogicielEx = new QComboBox;
		// Ici ajout d'un programme pour la liste deroulante
		m_chxLogicielEx->addItem("Thunderbird");
		m_chxLogicielEx->addItem("Outlook Express");
		m_chxLogicielEx->addItem("Microsoft Office Outlook 2007");

		// On ajoute la liste deroulante dans un layout de formulaire
		QFormLayout *layChoixEx = new QFormLayout;
		layChoixEx->addRow("Logiciel : ", m_chxLogicielEx);
	
		// Les boutons 
		m_validerEx = new QPushButton("&Valider");
		m_quitterEx = new QPushButton("&Quitter");

		// On ajoute les boutons dans un layout horizontal avec un alignement Ã  droite 
		QHBoxLayout *layBoutonEx = new QHBoxLayout;
		layBoutonEx->setAlignment(Qt::AlignRight);
		layBoutonEx->addWidget(m_quitterEx);
		layBoutonEx->addWidget(m_validerEx);

		// Layout principal : un Qlabel + layout liste + layout boutons
		QVBoxLayout *layPrincipalEx = new QVBoxLayout;
		layPrincipalEx->addWidget(m_bienvenueEx);
		layPrincipalEx->addLayout(layChoixEx);
		layPrincipalEx->addLayout(layBoutonEx);

		m_pageExport->setLayout(layPrincipalEx);
	
		// Page d'Import
		////////////////
		
		m_bienvenueIm = new QLabel("<strong>Importez vos profils :</strong> <br /> \
                                           Choisissez votre logiciel de messagerie. <br /> \
                                           Selectionnez le dossier de <strong>plus haut niveau</strong> <br /> \
                                           contenant vos profils (idealement le dossier d'export <br /> \
                                           produit par ProdileEVO 0.x).<br /> \
                                           Validez... Patientez... C'est bon !<br />");
	
		m_chxLogicielIm = new QComboBox;
		// Ici ajout d'un programme pour la liste deroulante
		m_chxLogicielIm->addItem("Thunderbird");
		m_chxLogicielIm->addItem("Outlook Express");
		m_chxLogicielIm->addItem("Microsoft Office Outlook 2007");
	
		// On ajoute la liste deroulante dans un layout de formulaire
		QFormLayout *layChoixIm = new QFormLayout;
		layChoixIm->addRow("Logiciel : ", m_chxLogicielIm);
	
		// QLine affichage du chemin
		m_dossierIm = new QLineEdit;
		// ReadOnly
		m_dossierIm->setReadOnly(true);
	
		// Bouton parcourir
		m_browseIm = new QPushButton("...");
	
		// layout browse
		QHBoxLayout *layBrowse = new QHBoxLayout;
		layBrowse->addWidget(m_dossierIm);
		layBrowse->addWidget(m_browseIm);
	
		m_quitterIm = new QPushButton("&Quitter");
		m_validerIm = new QPushButton("&Valider");
	
		// layout bouton
		QHBoxLayout *layBoutonIm = new QHBoxLayout;
		layBoutonIm->setAlignment(Qt::AlignRight);
		layBoutonIm->addWidget(m_quitterIm);
		layBoutonIm->addWidget(m_validerIm);
	
		// layout principal page2
		QVBoxLayout *layPrincipalIm = new QVBoxLayout;
		layPrincipalIm->addWidget(m_bienvenueIm);
		layPrincipalIm->addLayout(layChoixIm);
		layPrincipalIm->addLayout(layBrowse);
		layPrincipalIm->addLayout(layBoutonIm);
	
		// et on ajoute le layout principal
		m_pageImport->setLayout(layPrincipalIm);
	
	m_onglets->addTab(m_pageExport, "Export");
	m_onglets->addTab(m_pageImport, "Import");
	
	// On crÃ©e le layout contenant le tab
	QHBoxLayout *layTab = new QHBoxLayout;
	layTab->addWidget(m_onglets);
	
	// On l'applique Ã  la fenetre
	setLayout(layTab);

	setWindowIcon(QIcon("icone.png"));
	// le titre de la fenetre
	setWindowTitle("ProfileEvo 0.3");
	// Set d'une hauteur minimum de fenetre.
	// Pour ne pas avoir des bouton ecrase en import
	setMinimumHeight(250);

	// Export
	connect(m_quitterEx, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(m_validerEx, SIGNAL(clicked()), this, SLOT(recProfilEx()));
	
	// Import
	connect(m_quitterIm, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(m_validerIm, SIGNAL(clicked()), this, SLOT(recProfilIm()));
	connect(m_browseIm, SIGNAL(clicked()), this, SLOT(openGetDir()));
}

void FenetrePrincipale::recProfilIm()
{
	if (m_chxLogicielIm->currentText() == "Thunderbird")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Thunderbird", this, m_dossierIm->text());
		fenProgression->exec();
	}
	else if(m_chxLogicielIm->currentText() == "Outlook Express")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Outlook Express", this, m_dossierIm->text());
		fenProgression->exec();
	}
	else if(m_chxLogicielIm->currentText() == "Microsoft Office Outlook 2007")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Microsoft Office Outlook 2007", this, m_dossierIm->text());
		fenProgression->exec();
	}
	/* Pour ajouter un logiciel, ajouter juste cette partie
	 else if(m_chxLogicielIm->currentText() == "Nom_Dans_La_Liste")
	 {
	 FenetreProgression *fenProgression = naew FenetreProgression("Nom_Dans_La_Liste", this);
	 fenProgression->exec();
	 }
	 */
	
}

void FenetrePrincipale::recProfilEx()
{
	if (m_chxLogicielEx->currentText() == "Thunderbird")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Thunderbird", this);
		fenProgression->exec();
	}
	else if(m_chxLogicielEx->currentText() == "Outlook Express")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Outlook Express", this);
		fenProgression->exec();
	}
	else if(m_chxLogicielEx->currentText() == "Microsoft Office Outlook 2007")
	{
		FenetreProgression *fenProgression = new FenetreProgression("Microsoft Office Outlook 2007", this);
		fenProgression->exec();
	}
	/* Pour ajouter un logiciel, ajouter juste cette partie
	else if(m_chxLogicielEx->currentText() == "Nom_Dans_La_Liste")
	{
		FenetreProgression *fenProgression = naew FenetreProgression("Nom_Dans_La_Liste", this);
		fenProgression->exec();
	}
	*/

}

void FenetrePrincipale::openGetDir()
{
	m_dossierIm->setText(QFileDialog::getExistingDirectory(this));
}
