/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 18th 2017
File : sqlConnect.cpp
Goal : Object controlling databsse connection
**********************************************************/

#include "sqlConnect.h"

void sqlConnect::connexion()
{
	
		//Initialisations
		sqlConnHandle = NULL;
		sqlStmtHandle = NULL;

		try
		{
			//Allocations
			if (!((SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle)) || (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0)) || (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle)))) {
				//Affichage
				cout << "Tentative de connexion";
				cout << "\n";

				//Connexion au SQL Server
				switch (SQLDriverConnect(sqlConnHandle, NULL,
					(SQLCHAR*)"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=DungeonGenerator;UID=sa;PWD==user123;", SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {

				case SQL_SUCCESS:
					cout << "Connexion reussi";
					cout << "\n";


					break;
				case SQL_SUCCESS_WITH_INFO:
					cout << "Connexion reussi";
					cout << "\n";

					break;
				case SQL_INVALID_HANDLE:
					throw string("Erreur de connexion");

				case SQL_ERROR:
					throw string("Erreur de connexion");
				default:
					throw string("Erreur");
					break;
				}

				//Si la connexion est impossible
				if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
					throw string("Connexion impossible");
			}
		}
		catch (string const& e)
		{
			cout << e << "\n";
			deconnexion();

			cout << "\n Appuyer sur Retour pour fermer ...";
			getchar();
			exit(1);
		}

	}

void sqlConnect::deconnexion()
{
	cout << "Deconnexion ..." << "\n";

	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}


void sqlConnect::ajouteUsager(char *nom) {
	
	try
	{
		connexion();

		SQLRETURN retcode;

		retcode = SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 100, 0, nom, 0, 0);

		retcode = SQLPrepare(sqlStmtHandle, (SQLCHAR*)"EXEC ajouterJoueur ?", SQL_NTS);

		retcode = SQLExecute(sqlStmtHandle);

		if (SQL_SUCCESS != retcode) {
			throw string("Erreur dans la requ�te");
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";

		deconnexion();

		getchar();
		exit(1);
	}

	deconnexion();
}

int sqlConnect::nbMap(char * nom)
{

	try
	{
		connexion();


		SQLRETURN retcode;

		retcode = SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 100, 0, nom, 0, 0);
		//S'il y a un probl�me avec la requ�te on quitte l'application sinon on affiche le r�sultat
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)"SELECT dbo.nbMap(?)", SQL_NTS)) {
			throw string("Erreur dans la requ�te");
		}
		else {
			//D�clarer les variables d'affichage

			SQLCHAR nbMap[SQL_RESULT_LEN];
			SQLINTEGER ptrnbMap;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_CHAR, nbMap, SQL_RESULT_LEN, &ptrnbMap);

			if (SQL_SUCCESS != retcode) {
				throw string("Erreur dans la requ�te");
			}

				//Afficher le r�sultat d'une requ�te			
				cout << nom << "  " << nbMap << endl;
			}
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";
		deconnexion();
	}

	deconnexion();
}

void sqlConnect::ajouterMap(char * nom, mapInfo info)
{
	try
	{
		connexion();

		SQLRETURN retcode;
		char * path = (char*)info.linkMap.c_str();
		SQLINTEGER dimX = info.dimX;
		SQLINTEGER dimY = info.dimY;
		SQLINTEGER plX = info.player.getPosX();
		SQLINTEGER plY = info.player.getPosY();

		
		/*
		Param�tre SQLBindParameter:
		- Handler de la requ�te
		- No du param�tre (commence � 1)
		- Est-ce un param�tre de type Input ou Output
		- Quel est le type de la variable en C++
		- Quel est le type de la variable en SQL
		- Quelle est la taille de la colonne dans la BD
		- Nombre de d�cimal
		- Quelle variable ou donn�es (pointeur)
		- Longueur du buffer
		- Pointeur du buffer
		*/
		retcode = SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 100, 0, nom, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 255, 0, path, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 4, 0, &dimX, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 4, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 4, 0, &dimY, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 5, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 4, 0, &plX, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 6, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 4, 0, &plY, 0, 0);

		retcode = SQLPrepare(sqlStmtHandle, (SQLCHAR*)"EXEC ajouterMap ?,?,?,?,?,?", SQL_NTS);

		retcode = SQLExecute(sqlStmtHandle);

		if (SQL_SUCCESS != retcode) {
			throw string("Erreur dans la requ�te");
		}
	}
	catch (string const& e)
	{
		cout << e << "\n";

		deconnexion();

		getchar();
		exit(1);
	}
	deconnexion();
}

mapInfo sqlConnect::chargerMap(int id)
{
	//doc_map VARCHAR(255), nb_line INT, nb_col INT, pos_j_x INT, pos_j_y INT

	mapInfo info;
	try
	{
		connexion();
		

		//S'il y a un probl�me avec la requ�te on quitte l'application sinon on affiche le r�sultat
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)"SELECT doc_map, nb_line, nb_col, pos_j_x, pos_j_y FROM tblMap WHERE map_id = id", SQL_NTS)) {
			throw string("Erreur dans la requ�te");
		}
		else {
			//D�clarer les variables d'affichage
			SQLCHAR path[SQL_RESULT_LEN];
			SQLINTEGER dimX[SQL_RESULT_LEN], dimY[SQL_RESULT_LEN], plX[SQL_RESULT_LEN], plY[SQL_RESULT_LEN];
			SQLINTEGER ptrPath, ptrDimX, ptrDimY, ptrPlX, ptrPlY;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_CHAR, path, SQL_RESULT_LEN, &ptrPath);
				SQLGetData(sqlStmtHandle, 2, SQL_INTEGER, dimX, SQL_RESULT_LEN, &ptrDimX);
				SQLGetData(sqlStmtHandle, 3, SQL_INTEGER, dimY, SQL_RESULT_LEN, &ptrDimY);
				SQLGetData(sqlStmtHandle, 4, SQL_INTEGER, plX, SQL_RESULT_LEN, &ptrPlX);
				SQLGetData(sqlStmtHandle, 5, SQL_INTEGER, plY, SQL_RESULT_LEN, &ptrPlY);
			}

			info.linkMap.assign((char*)path);
			info.dimX = (int)dimX;
			info.dimY = (int)dimY;
			info.player.setPosX((int)plX);
			info.player.setPosY((int)plY);

		}
	}
	catch (string const& e)
	{
		cout << e << "\n";

		info.linkMap.assign("");
		info.dimX = 0;
		info.dimY = 0;
		info.player.setPosX(0);
		info.player.setPosY(0);

		deconnexion();
	}
	deconnexion();
	return info;
}

int sqlConnect::nextMapId()
{

	try
	{
		connexion();
		SQLINTEGER nextId[SQL_RESULT_LEN];
		SQLINTEGER ptrNextId;

		//S'il y a un probl�me avec la requ�te on quitte l'application sinon on affiche le r�sultat
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)"SELECT MAX(id_map) FROM tblMap", SQL_NTS)) {
			throw string("Erreur dans la requ�te");
		}
		else {
			//D�clarer les variables d'affichage

			//SQLINTEGER nextId[SQL_RESULT_LEN];
			//SQLINTEGER ptrNextId;

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
				SQLGetData(sqlStmtHandle, 1, SQL_INTEGER, nextId, SQL_RESULT_LEN, &ptrNextId);
			}
			cout << nextId << endl;
		}
	}
	

	catch (string const& e)
	{
		cout << e << "\n";
		deconnexion();
	}
	deconnexion();
}

