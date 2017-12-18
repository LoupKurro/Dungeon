#pragma once

#include <iostream>
#include <string>

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

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
};

