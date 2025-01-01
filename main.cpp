/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * Created by: BAMOUH Ayoub
 */

// Inclusion des bibliothèques standard nécessaires
#include <iostream>  // Pour les entrées et sorties standard
#include <fstream>   // Pour la manipulation des fichiers
#include <vector>    // Pour l'utilisation des conteneurs vector
#include <string>    // Pour manipuler des chaînes de caractères
#include <ctime>     // Pour gérer la date et l'heure
#include <iomanip>   // Pour le formatage des sorties
#include <limits>    // Pour gérer les limites des entrées utilisateur
#include <sstream>   // Pour manipuler les flux de chaînes
#include <windows.h> // Inclure cette bibliothèque pour manipuler les couleurs de la console

using namespace std;

// Fonction pour afficher la bannière d'introduction
void displayBanner() {
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "| Created by : Mr. BAMOUH Ayoub                                       |" << endl;
    cout << "| Date       : 01/01/2025                                             |" << endl;
    cout << "| Application for handling Medicines Spare in your Pharmacy or        |" << endl;
    cout << "| Hospital for beginners and small businesses                         |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;
}

void displayGPLNotice() {
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "| This program is licensed under the GNU General Public License (GPL).|" << endl;
    cout << "| See https://www.gnu.org/licenses/gpl-3.0.en.html for details.       |" << endl;
    cout << "+---------------------------------------------------------------------+" << endl;
}

// Fonction pour changer la couleur de la sortie de la console
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Récupérer le handle de la console
    SetConsoleTextAttribute(hConsole, color);  // Changer la couleur de texte
}

// Définition de la classe Medicament
class Medicament {
private:
    string name;               // Nom du médicament
    string category;           // Catégorie du médicament
    int stockLevel;            // Niveau de stock disponible
    string expirationDate;     // Date de péremption du médicament
    string lotNumber;          // Numéro de lot
    string manufacturer;       // Fabricant du médicament
    string usageInstructions;  // Instructions d'utilisation
    string id;                 // Identifiant unique pour chaque médicament

public:
    // Constructeur pour initialiser un médicament avec ses attributs
    Medicament(string n, string c, int s, string e, string l, string m, string u, string i)
        : name(n), category(c), stockLevel(s), expirationDate(e), lotNumber(l), manufacturer(m), usageInstructions(u), id(i) {}

    // Accesseurs pour obtenir les informations sur le médicament
    string getName() const { return name; }
    string getCategory() const { return category; }
    int getStockLevel() const { return stockLevel; }
    string getExpirationDate() const { return expirationDate; }
    string getLotNumber() const { return lotNumber; }
    string getManufacturer() const { return manufacturer; }
    string getUsageInstructions() const { return usageInstructions; }
    string getId() const { return id; }

    // Affichage des informations du médicament dans un format structuré
    void display() const {
        cout << "| " << left << setw(15) << id
             << "    | " << left << setw(20) << name
             << " | " << left << setw(15) << category
             << "    | " << left << setw(6) << stockLevel
             << "| " << left << setw(12) << expirationDate
             << "       | " << left << setw(10) << lotNumber
             << " | " << left << setw(15) << manufacturer
             << " | " << left << setw(25) << usageInstructions
             << "|\n";
        cout << "+---------------------+----------------------+--------------------+-------+--------------------+------------+-----------------+--------------------------+\n";
    }

    // Vérifier si la date de péremption est proche (moins de 30 jours)
    bool isExpiringSoon() const {
        time_t now = time(0);                // Obtenir la date et l'heure actuelles
        tm *ltm = localtime(&now);           // Convertir en structure tm

        int currentYear = 1900 + ltm->tm_year;  // Année actuelle
        int currentMonth = 1 + ltm->tm_mon;    // Mois actuel
        int currentDay = ltm->tm_mday;        // Jour actuel

        int expYear, expMonth, expDay;
        sscanf(expirationDate.c_str(), "%d-%d-%d", &expYear, &expMonth, &expDay);  // Extraire la date d'expiration

        int diffDays = (expYear - currentYear) * 365 + (expMonth - currentMonth) * 30 + (expDay - currentDay);
        return diffDays <= 30 && diffDays >= 0;  // Retourne vrai si la péremption est proche
    }
};

// Fonction pour générer un identifiant unique pour chaque médicament
string generateId(int index, int year) {
    stringstream id;
    id << "YOBA-" << year << "-" << setw(6) << setfill('0') << index;  // Formater l'ID unique
    return id.str();
}

// Fonction pour sauvegarder les données dans un fichier CSV
void saveToFile(const vector<Medicament>& medicaments) {
    ofstream file("medicament_stock_data.csv");  // Ouvrir un fichier en mode écriture
    file << "ID,Nom,Categorie,Stock,Date_Peremption,Numero_Lot,Fabricant,Instructions_Utilisation\n";  // En-tête
    for (const auto& medicament : medicaments) {
        file << medicament.getId() << ","
             << medicament.getName() << ","
             << medicament.getCategory() << ","
             << medicament.getStockLevel() << ","
             << medicament.getExpirationDate() << ","
             << medicament.getLotNumber() << ","
             << medicament.getManufacturer() << ","
             << medicament.getUsageInstructions() << "\n";  // Ajouter les données
    }
    file.close();  // Fermer le fichier
}

// Fonction pour charger les données depuis le fichier CSV
vector<Medicament> loadFromFile() {
    vector<Medicament> medicaments;  // Conteneur pour stocker les médicaments
    ifstream file("medicament_stock_data.csv");  // Ouvrir le fichier CSV en mode lecture
    if (file.is_open()) {
        string name, category, expirationDate, lotNumber, manufacturer, usageInstructions, id;
        int stockLevel;

        string header;
        getline(file, header);  // Lire l'en-tête

        while (getline(file, id, ',') &&
               getline(file, name, ',') &&
               getline(file, category, ',') &&
               file >> stockLevel &&
               file.ignore() &&
               getline(file, expirationDate, ',') &&
               getline(file, lotNumber, ',') &&
               getline(file, manufacturer, ',') &&
               getline(file, usageInstructions)) {
            medicaments.push_back(Medicament(name, category, stockLevel, expirationDate, lotNumber, manufacturer, usageInstructions, id));  // Ajouter un médicament
        }
        file.close();  // Fermer le fichier
    }
    return medicaments;
}

// Fonction pour écrire dans le fichier de log
void logChange(const string& action, const Medicament& oldMedicament, const Medicament& newMedicament) {
    ofstream logFile("log.txt", ios_base::app);  // Ouvrir en mode ajout
    if (logFile.is_open()) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char timeStr[100];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", ltm);

        logFile << "Action: " << action << "\n";
        logFile << "Date/Heure: " << timeStr << "\n";
        logFile << "ID: " << oldMedicament.getId() << "\n";

        // Log des anciennes valeurs
        logFile << "Anciennes Valeurs:\n";
        logFile << "Nom: " << oldMedicament.getName() << "\n";
        logFile << "Categorie: " << oldMedicament.getCategory() << "\n";
        logFile << "Stock: " << oldMedicament.getStockLevel() << "\n";
        logFile << "Date de Péremption: " << oldMedicament.getExpirationDate() << "\n";
        logFile << "Numéro de Lot: " << oldMedicament.getLotNumber() << "\n";
        logFile << "Fabricant: " << oldMedicament.getManufacturer() << "\n";
        logFile << "Instructions: " << oldMedicament.getUsageInstructions() << "\n";

        // Log des nouvelles valeurs
        logFile << "Nouvelles Valeurs:\n";
        logFile << "Nom: " << newMedicament.getName() << "\n";
        logFile << "Categorie: " << newMedicament.getCategory() << "\n";
        logFile << "Stock: " << newMedicament.getStockLevel() << "\n";
        logFile << "Date de Péremption: " << newMedicament.getExpirationDate() << "\n";
        logFile << "Numéro de Lot: " << newMedicament.getLotNumber() << "\n";
        logFile << "Fabricant: " << newMedicament.getManufacturer() << "\n";
        logFile << "Instructions: " << newMedicament.getUsageInstructions() << "\n";
        logFile << "-----------------------------------\n";
        logFile.close();
    }
}

// Fonction pour modifier un médicament
void modifierMedicament(vector<Medicament>& medicaments) {
    string name, lotNumber;
    cout << "Entrez le nom du medicament a modifier: ";
    cin.ignore();
    getline(cin, name);
    cout << "Entrez le numero de lot du medicament a modifier: ";
    getline(cin, lotNumber);
    bool found = false;

    for (auto& medicament : medicaments) {
        if (medicament.getName() == name && medicament.getLotNumber() == lotNumber) {
            found = true;
            string newName, newCategory, newExpirationDate, newLotNumber, newManufacturer, newUsageInstructions;
            int newStockLevel;

            cout << "Modifier le nom (actuel: " << medicament.getName() << "): ";
            getline(cin, newName);
            cout << "Modifier la categorie (actuelle: " << medicament.getCategory() << "): ";
            getline(cin, newCategory);
            cout << "Modifier le stock (actuel: " << medicament.getStockLevel() << "): ";
            cin >> newStockLevel;
            cout << "Modifier la date de péremption (actuelle: " << medicament.getExpirationDate() << "): ";
            cin >> newExpirationDate;
            cout << "Modifier le numero de lot (actuel: " << medicament.getLotNumber() << "): ";
            cin >> newLotNumber;
            cout << "Modifier le fabricant (actuel: " << medicament.getManufacturer() << "): ";
            cin.ignore();
            getline(cin, newManufacturer);
            cout << "Modifier les instructions (actuelles: " << medicament.getUsageInstructions() << "): ";
            getline(cin, newUsageInstructions);

            Medicament oldMedicament = medicament;  // Sauvegarder l'ancien état
            medicament = Medicament(newName, newCategory, newStockLevel, newExpirationDate, newLotNumber, newManufacturer, newUsageInstructions, medicament.getId());

            // Log de la modification
            logChange("Modification", oldMedicament, medicament);
            break;
        }
    }

    if (!found) {
        cout << "Aucun medicament trouve avec ce nom et ce numero de lot.\n";
    }
}

// Fonction pour supprimer un médicament
void supprimerMedicament(vector<Medicament>& medicaments) {
    string name, lotNumber;
    cout << "Entrez le nom du medicament a supprimer: ";
    cin.ignore();
    getline(cin, name);
    cout << "Entrez le numero de lot du medicament a supprimer: ";
    getline(cin, lotNumber);
    bool found = false;

    for (auto it = medicaments.begin(); it != medicaments.end(); ++it) {
        if (it->getName() == name && it->getLotNumber() == lotNumber) {
            found = true;
            Medicament deletedMedicament = *it;  // Sauvegarder l'état avant la suppression
            medicaments.erase(it);

            // Log de la suppression
            logChange("Suppression", deletedMedicament, deletedMedicament);  // Supprimer mais loguer l'ancien état
            break;
        }
    }

    if (!found) {
        cout << "Aucun medicament trouve avec ce nom et ce numero de lot.\n";
    }
}

int main() {
    setColor(12);
    displayGPLNotice();
    // Appel de la bannière au début de l'exécution
    displayBanner();

    setColor(7);

    cout << "\nBienvenue dans l'application de gestion de pharmacie !\n" << endl;

    vector<Medicament> medicaments = loadFromFile(); // Charger les médicaments existants depuis le fichier
    int choice;

    do {
        // Affichage du menu pour l'utilisateur
        setColor(10);  // Commencer à afficher en vert
        cout << "+---------------------------------------------------------------------+\n";
        cout << "| Menu de gestion des medicaments:                                    |\n";
        cout << "| 1. Ajouter un medicament                                            |\n";
        cout << "| 2. Afficher tous les medicaments                                    |\n";
        cout << "| 3. Modifier un medicament                                           |\n";
        cout << "| 4. Supprimer un medicament                                          |\n";
        cout << "| 5. Verifier les alertes de peremption                               |\n";
        cout << "| 6. Sauvegarder les donnees (format .CSV)                            |\n";
        cout << "| 7. Quitter                                                          |\n";
        cout << "+---------------------------------------------------------------------+\n";
        setColor(7);  // Réinitialiser la couleur pour le texte suivant
        cout << "Choisissez une option: ";
        cin >> choice;

        // Déplacer les variables hors du switch
        bool hasExpiringSoon = false; // Initialisation globale pour éviter l'erreur

        switch (choice) {
            case 1: {
                // Ajouter un médicament
                string name, category, expirationDate, lotNumber, manufacturer, usageInstructions;
                int stockLevel;
                int year = 2025;  // Assume the year is 2025 for the unique ID
                cout << "Nom du medicament (ex: Paracetamol 500mg): ";
                cin.ignore();
                getline(cin, name);
                cout << "Categorie du medicament (ex: Analgesique, Antibiotique): ";
                getline(cin, category);
                cout << "Niveau de stock (ex: 100): ";
                cin >> stockLevel;
                cout << "Date de peremption (format: YYYY-MM-DD): ";
                cin >> expirationDate;
                cout << "Numero de lot (ex: A12345): ";
                cin >> lotNumber;
                cout << "Fabricant (ex: Sanofi, Pfizer): ";
                cin.ignore();
                getline(cin, manufacturer);
                cout << "Instructions d'utilisation (ex: Prendre 1 comprime toutes les 4 heures): ";
                getline(cin, usageInstructions);

                string id = generateId(medicaments.size() + 1, year);

                bool isDuplicate = false;
                for (const auto& medicament : medicaments) {
                    if (medicament.getName() == name && medicament.getLotNumber() == lotNumber) {
                        isDuplicate = true;
                        break;
                    }
                }
                if (isDuplicate) {
                    cout << "Un medicament avec ce nom et ce numero de lot existe deja.\n";
                    cout << "Voulez-vous quand meme ajouter ce medicament (oui/non) ? ";
                    string response;
                    cin >> response;
                    if (response == "oui") {
                        medicaments.push_back(Medicament(name, category, stockLevel, expirationDate, lotNumber, manufacturer, usageInstructions, id));
                    }
                } else {
                    medicaments.push_back(Medicament(name, category, stockLevel, expirationDate, lotNumber, manufacturer, usageInstructions, id));
                }
                break;
            }
            case 2:
                // Afficher les medicaments
                setColor(6);
                cout << "+---------------------+----------------------+--------------------+-------+--------------------+------------+-----------------+--------------------------+\n";
                cout << "| ID                  | Nom                  | Categorie          | Stock | Date_Peremption    | Numero_Lot | Fabricant       | Instructions_Utilisation |\n";
                cout << "+---------------------+----------------------+--------------------+-------+--------------------+------------+-----------------+--------------------------+\n";
                setColor(7);
                for (const auto& medicament : medicaments) {
                    medicament.display();
                }
                break;
            case 3:
                // Modifier un médicament
                setColor(3);
                modifierMedicament(medicaments);
                setColor(7);
                break;
            case 4:
                // Supprimer un médicament
                setColor(12);
                supprimerMedicament(medicaments);
                setColor(7);
                break;
            case 5:
                // Vérifier les alertes de péremption
                hasExpiringSoon = false;
                for (const auto & medicament : medicaments) {
                    if (medicament.isExpiringSoon()) {
                        setColor(4);
                        cout << "Alerte: Le medicament '" << medicament.getName() << "' (ID: " << medicament.getId() << ") expire bientot le : " << medicament.getExpirationDate() << "\n";
                        setColor(7);
                        hasExpiringSoon = true;
                    }
                }
                if (!hasExpiringSoon) {
                    setColor(14);
                    cout << "Aucun medicament n'expire dans moins de 30 jours.\n";
                    setColor(7);
                }
                break;
            case 6:
                // Sauvegarder les données
                setColor(9);
                saveToFile(medicaments);
                cout << "Donnees sauvegardees avec succes dans medicament_stock_data.csv!\n";
                setColor(7);
                break;
            case 7:
                // Quitter
                cout << "Merci d'avoir utilise le programme.\n";
                break;
            default:
                cout << "Choix invalide, veuillez reessayer.\n";
        }
    } while (choice != 7);

    return 0;
}
