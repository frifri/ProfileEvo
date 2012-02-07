#include "CDirCopy.h"

int CDirCopy::launch()
{
	// Vérification du dossier de départ
	QFileInfo fiSrc(m_src);
	
	if(fiSrc.isDir())
	{
		// Lance la boucle récursive
		QDir src0(m_src);
		QDir tar0(m_tar);
		recursiveCopy(src0, tar0);
	}
	
	return	EXIT_SUCCESS;
}

int CDirCopy::launch2007()
{
	QString tempOut;
	
	// recuperation de l'heure toussa
	QTime curTime = QTime::currentTime();
	m_date = curTime.toString("hhmmss");
	
	QDir base(QDir::homePath() + "/Desktop/Profils_Messagerie");
	//QDir base(QDir::homePath() + "/Bureau/Profiles_Messagerie");
	
	// Si le dossier n'a pas été créé
	if (!base.mkdir("Profils_Outlook_2007_" + m_date))
		return EXIT_FAILURE;
	
	// Creation des dossiers de traitement
	// Source
	QDir src0(m_src);
	// Target
	QDir tar0(m_tar + "Profils_Outlook_2007_" + m_date);
	
	foreach (QFileInfo fi, src0.entryInfoList())
	{
		tempOut = tar0.path() + QDir::separator() + fi.fileName();
		
		QFile::copy(fi.filePath(), tempOut);
	}
	
	return EXIT_SUCCESS;
}

void CDirCopy::recursiveCopy(QDir srcN, QDir tarN)
{
	QString tempOut;
	
	// Récupération de tous ce qui contenu dans le dossier
	foreach(QFileInfo fi, srcN.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks))
	{
		tempOut = tarN.path() + QDir::separator() + fi.fileName();
		
		// Copie tous les fichiers contenu dans srcN
		if(fi.isFile())
			QFile::copy(fi.filePath(), tempOut);
		
		// Rentre dans tous les sous dossier de srcN
		else if(fi.isDir())
		{
			QDir srcI(fi.filePath());
			QDir tarI(tempOut);
			
			// Creation du dossier de sortie si inexistant
			if(!tarI.exists())
				tarI.mkpath(tempOut);
				
			// Appel recursif
			recursiveCopy(srcI, tarI);
		}
	}
}
