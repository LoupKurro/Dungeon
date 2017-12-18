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
					(SQLCHAR*)"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=DungeonGenerator;UID=dungeon;PWD=123gen;", SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {

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

void sqlConnect::ajouteUsager(char *nom, char *prenom) {

	try
	{
		connexion();

		SQLRETURN retcode;

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
		retcode = SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, nom, 0, 0);
		retcode = SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 50, 0, nom, 0, 0);

		retcode = SQLPrepare(sqlStmtHandle, (SQLCHAR*)"INSERT INTO Usager (usagerprenom, usagernom) VALUES (?, ?)", SQL_NTS);

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

