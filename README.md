# Application-de-la-gestion-du-stock-des-medicaments
## Language utilisé : C++
![image](https://github.com/user-attachments/assets/8bf72a67-ef9b-4680-a1d0-4782536ada90)
![image](https://github.com/user-attachments/assets/8e36526f-f47e-4fb5-aeb6-9b622353eb85)
## Description :
Cette application en C++ est conçue pour gérer les stocks de médicaments dans une pharmacie ou un hôpital. Elle permet :
- D'ajouter, modifier et supprimer des informations sur les médicaments.
- D'afficher tous les médicaments enregistrés.
- De vérifier les alertes de péremption pour éviter les médicaments expirés.
- De sauvegarder et charger les données dans un fichier CSV.
- De conserver un historique des modifications dans un fichier de log.
## Fonctionnalités :
- Ajout de médicaments : Ajoutez un nouveau médicament avec des informations telles que le nom, la catégorie, le stock, la date de péremption, etc.
- Modification des médicaments : Modifiez les informations d'un médicament existant.
- Suppression des médicaments : Supprimez un médicament du stock.
- Affichage des médicaments : Affichez une liste formatée de tous les médicaments.
- Alertes de péremption : Identifiez les médicaments dont la date de péremption est proche.
- Sauvegarde et chargement : Enregistrez et chargez les données au format CSV pour une utilisation ultérieure.
- Journalisation : Enregistrez toutes les modifications dans un fichier de log pour un suivi historique.
## Installation :
### Clonez le dépôt : 
- git clone https://github.com/votre-utilisateur/Application-de-la-gestion-du-stock-des-medicaments.git
- cd Application-de-la-gestion-du-stock-des-medicaments
### Compilez le programme : Si vous utilisez g++ :
- g++ -o gestions_medicaments main.cpp
### Exécutez le programme :
- ./gestion_medicaments
## Utilisation
Lors du lancement, l'application affiche un menu interactif. Voici un aperçu des options disponibles :
#### Ajouter un médicament :
- Fournissez des détails comme le nom, la catégorie, le stock, la date de péremption, etc.
- Un identifiant unique est généré automatiquement.
#### Afficher tous les médicaments :
- Affiche une liste bien formatée de tous les médicaments stockés.
#### Modifier un médicament :
- Sélectionnez un médicament à l'aide de son nom et de son numéro de lot, puis modifiez ses attributs.
#### Supprimer un médicament :
- Retirez un médicament en précisant son nom et son numéro de lot.
#### Vérifier les alertes de péremption :
- Identifiez rapidement les médicaments qui expirent dans les 30 jours.
#### Sauvegarder les données :
- Exportez tous les médicaments dans un fichier CSV (medicament_stock_data.csv).
#### Quitter :
- Quittez 'application en toute sécurité.

## Structure du projet :
- main.cpp : Fichier source principal contenant tout le code.
- medicament_stock_data.csv : Fichier CSV généré contenant les données des médicaments.
- log.txt : Fichier de log enregistrant toutes les modifications.
- README.md : Documentation du projet.
## Exemples de fichiers :
### Exemple de fichier CSV :
![image](https://github.com/user-attachments/assets/0f56cf1e-750f-4d39-8492-0374317fd684)
### Exemple de fichier de log :
![image](https://github.com/user-attachments/assets/cba8254c-e135-4dd6-b1ba-ef4ac260a40d)

## Licence :
Ce projet est sous licence GNU General Public License v3.0. Voir le fichier LICENSE pour plus d'informations. https://www.gnu.org/licenses/gpl-3.0.en.html

## Contribution :
Les contributions sont les bienvenues ! Suivez les étapes ci-dessous :
- Forkez le dépôt.
- Créez une branche pour vos modifications : git checkout -b ma-branche
- Faites vos modifications et effectuez un commit : git commit -m "Description des modifications"
- Poussez vos changements et créez une pull request.

## Remerciements :
Développé par BAMOUH Ayoub dans le but de simplifier la gestion des stocks de médicaments pour les petites pharmacies et hôpitaux.

## Améliorations possibles :
- Ajout d'une interface graphique.
- Prise en charge de multiples langues.
- Intégration avec des bases de données comme SQLite ou MySQL.
