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
