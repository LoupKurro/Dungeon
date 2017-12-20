/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 18th 2017
File : sqlConnect.h
Goal : Object controlling databsse connection
**********************************************************/


#pragma once

#include <iostream>
#include <string>

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "mapInfo.h"

using namespace std;

class sqlConnect
{
private:
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

	//Variable SQL
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	
	void connexion();
	void deconnexion();
	
	void ajouteUsager(char *nom);
	int nbMap(char *nom);
	void ajouterMap(char *nom, mapInfo info);
	mapInfo chargerMap(int id);

	int nextMapId();
};

