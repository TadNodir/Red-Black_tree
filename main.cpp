/*************************************************
 * ADS Praktikum 2.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:



/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV"

Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/
void mainscreen_addTreeCSV(Tree*& ref)
{
    char j;
    cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
        "importieren(j / n) ? >";
    cin >> j;
    if (j == 'j')
    {
        ifstream csvread;
        csvread.open("ExportZielanalyse.csv", ios::in);
        if (!csvread.is_open())
            cout << "Fehler beim Lesen!" << endl;
        else
        {
            string name, age, postcode, income;

            while (!csvread.eof())
            {
                getline(csvread, name, ';');
                getline(csvread, age, ';');
                getline(csvread, income, ';');
                getline(csvread, postcode, '\n');
                ref->addNode(name, stoi(age), stod(income), stoi(postcode));
            }
            csvread.close();
        }
        cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
    }
}


int main()
{

    int result = Catch::Session().run();


    string name;
    unsigned int choice, age, postcode, orderId, level;
    double income;
    Tree* data = new Tree();
    Tree* tmpData = new Tree();

    cout << "=======================================" << endl;
    cout << "  ADS - ELK - Stack v1.9, by 25th Bam  " << endl;
    cout << "=======================================" << endl;
    cout << "1) Datensatz einfuegen, manuell" << endl;
    cout << "2) Datensatz einfuegen, CSV Datei" << endl;
    cout << "3) Datensatz loeschen" << endl;
    cout << "4) Suchen" << endl;
    cout << "5) Datenstruktur anzeigen" << endl;
    cout << "6) Level-Order Ausgabe" << endl;
    cout << "7) Criterion" << endl;
    cout << "8) Level-Order Ausgabe mit Niveau" << endl;
    cout << "9) Beenden" << endl;


    while (true) {
        cout << "?> ";
        while (!(cin >> choice)) {
            cout << "False input. Please try again: " << endl;
            cout << "?> ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        if (!(choice > 0 && choice < 10)) {
            cout << "Incorrect input. Please choose between 1 and 9." << endl;
        }
        switch (choice) {
        case 1:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "+ Bitte geben Sie die den Datensatz ein:" << endl;
            cout << "Name ?> "; getline(cin, name);
            cout << "Alter ?> "; cin >> age;
            cout << "Einkommen ?> ";
            cin >> income;
            cout << "PLZ ?> ";
            cin >> postcode;
            data->addNode(name, age, income, postcode);
            cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
            break;

        case 2:
            mainscreen_addTreeCSV(data);
            break;
        case 3:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
            cout << "OrderID ?> ";
            cin >> orderId;
            data->deleteNode(orderId);
            cout << "+ Eintrag wurde geloescht." << endl;
            break;
        case 4:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << "Name ?> ";
            getline(cin, name);
            cout << "+ Fundstellen:" << endl;
            data->searchNode(name);
            data->printFound(name);
            break;
        case 5:
            data->printAll();
            break;
        case 6:
            data->printLevelOrder();
            break;
        case 7:
            data->criterionStarter();
            break;
        case 8:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "+ Bitte geben Sie die Niveau ein:" << endl;
            cout << "Niveau ?> "; cin >> level;
            data->printLevelOrder(level);
            break;
        case 9:
            system("PAUSE");
            return 0;
        }
    }
}
