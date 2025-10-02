 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    int id;
    char nom[50];
    char tel[20];
    char email[50];
    struct Contact* next;
} Contact;

 
void ajouterContact(Contact** head, int id, char nom[], char tel[], char email[]);
void supprimerContact(Contact** head, int id);
Contact* rechercherContact(Contact* head, char nom[]);
void afficherContacts(Contact* head);
int compterContacts(Contact* head);

 
void ajouterContact(Contact** head, int id, char nom[], char tel[], char email[]) {
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    newContact->id = id;
    strcpy(newContact->nom, nom);
    strcpy(newContact->tel, tel);
    strcpy(newContact->email, email);
    newContact->next = *head;
    *head = newContact;
}

void supprimerContact(Contact** head, int id) {
    Contact* temp = *head;
    Contact* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Contact non trouvé.\n");
        return;
    }
    if (prev == NULL) *head = temp->next;
    else prev->next = temp->next;

    free(temp);
    printf("Contact supprimé avec succès.\n");
}

Contact* rechercherContact(Contact* head, char nom[]) {
    while (head != NULL) {
        if (strcmp(head->nom, nom) == 0) return head;
        head = head->next;
    }
    return NULL;
}

void afficherContacts(Contact* head) {
    if (head == NULL) {
        printf("Aucun contact.\n");
        return;
    }
    while (head != NULL) {
        printf("ID: %d | Nom: %s | Tel: %s | Email: %s\n",
               head->id, head->nom, head->tel, head->email);
        head = head->next;
    }
    printf("NULL\n");
}

int compterContacts(Contact* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// ===== Programme principal avec menu =====
int main() {
    Contact* liste = NULL;
    int choix, id;
    char nom[50], tel[20], email[50];

    do {
        printf("\n=== Gestionnaire de Contacts ===\n");
        printf("1. Ajouter un contact\n");
        printf("2. Supprimer un contact\n");
        printf("3. Rechercher un contact\n");
        printf("4. Afficher tous les contacts\n");
        printf("5. Compter les contacts\n");
        printf("6. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("Nom: "); scanf("%s", nom);
                printf("Tel: "); scanf("%s", tel);
                printf("Email: "); scanf("%s", email);
                ajouterContact(&liste, id, nom, tel, email);
                break;

            case 2:
                printf("ID du contact à supprimer: ");
                scanf("%d", &id);
                supprimerContact(&liste, id);
                break;

            case 3:
                printf("Nom du contact à rechercher: ");
                scanf("%s", nom);
                Contact* c = rechercherContact(liste, nom);
                if (c != NULL)
                    printf("Trouvé: ID=%d | Nom=%s | Tel=%s | Email=%s\n",
                           c->id, c->nom, c->tel, c->email);
                else
                    printf("Contact non trouvé.\n");
                break;

            case 4:
                afficherContacts(liste);
                break;

            case 5:
                printf("Nombre total de contacts: %d\n", compterContacts(liste));
                break;

            case 6:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 6);

    return 0;
}

