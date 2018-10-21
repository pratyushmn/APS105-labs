#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list
typedef struct node {
    char* artist ;
    char* songName ;
    char* genre ;
    struct node* nextNode ;
} Node;

// Declarations of linked list functions
Node* newNode(char* song, char* artist, char* genre, Node* nextNode);
Node* insertNewSong (Node* head, char* songInsert, char* artistInsert, char* genreInsert);
Node* deleteSong (Node* head, char* songDelete);
void searchSong (Node* head, char* songName);
void printLibrary(Node* head);


// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser (char prompt[ ], char s[ ], int arraySize);
void songNameDuplicate (char songName[ ]);
void songNameFound (char songName[ ]);
void songNameNotFound (char songName[ ]);
void songNameDeleted (char songName[ ] );
void artistFound (char artist[ ]);
void artistNotFound (char artist[ ]);
void printMusicLibraryEmpty (void);
void printMusicLibraryTitle (void);

const int MAX_LENGTH = 1024;

int main (void) 
{
    // Declare the head of the linked list.
    Node* head = NULL;
    // Announce the start of the program
    printf( "Personal Music Library.\n\n" );
    printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
         "P (print), Q (quit).\n" );
    
    char response;
    char input [MAX_LENGTH + 1];
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]) ;

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            char* promptName = "Song name";
            char* promptArtist = "Artist";
            char* promptGenre = "Genre";
            char* songName = (char*) malloc((MAX_LENGTH + 1)*sizeof(char));
            char* artist = (char*) malloc((MAX_LENGTH + 1)*sizeof(char));
            char* genre = (char*) malloc((MAX_LENGTH + 1)*sizeof(char));
            inputStringFromUser(promptName, songName, MAX_LENGTH);
            inputStringFromUser(promptArtist, artist, MAX_LENGTH);
            inputStringFromUser(promptGenre, genre, MAX_LENGTH);
            
            head = insertNewSong(head, songName, artist, genre);
        }
        else if( response == 'D' ) {
            // Delete a song from the list.

            char *prompt = "\nEnter the name of the song to be deleted" ;
            char songToDelete[MAX_LENGTH+1];
            inputStringFromUser(prompt, songToDelete, MAX_LENGTH);
            head = deleteSong(head, songToDelete);

        }
        else if( response == 'S' ) {
            // Search for a song by its name.

            char *prompt = "\nEnter the name of the song to search for" ;
            char songToSearch[MAX_LENGTH + 1];
            inputStringFromUser(prompt, songToSearch, MAX_LENGTH);
            searchSong(head, songToSearch);

        }
        else if( response == 'P' ) {
            // Print the music library.
            printLibrary(head);

        }
        else if( response == 'Q' ) {
            ; // do nothing
        }
        else {
            // do this if no command matched 
            printf( "\nInvalid command.\n" ) ;
        }
    } while (response != 'Q');
  
    // Delete the entire linked list.
    while (head != NULL) {
        Node* secondNode = head -> nextNode;
        songNameDeleted(head -> songName);
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        head = secondNode;
    }
    // Print the linked list to confirm deletion.
    printLibrary(head);
    return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser (char prompt[ ], char s[ ], int maxStrLength)
{
    int i = 0;
    char c;
    
    printf("%s --> ", prompt);
    while(i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c ;
    s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate(char songName[ ]) 
{
    printf( "\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound(char songName[ ]) 
{
    printf( "\nThe song name '%s' was found in the music library.\n",
           songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound(char songName[ ]) 
{
    printf( "\nThe song name '%s' was not found in the music library.\n",
           songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted(char songName[ ]) 
{
    printf( "\nDeleting a song with name '%s' from the music library.\n",
           songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) 
{
    printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) 
{
    printf( "\nMy Personal Music Library: \n" ) ;
}


// Function to create a new node
Node* newNode(char* song, char* artist, char* genre, Node* nextNode)
{
    Node* new = (Node*) malloc(sizeof(Node));;
    if (new != NULL) {
        new -> nextNode = nextNode;
        new -> songName = song;
        new -> artist = artist;
        new -> genre = genre;
    }
    return new;
}

// Function to insert a new song in alphabetical order
Node* insertNewSong (Node* head, char* songInsert, char* artistInsert, char* genreInsert)
{
    Node* current = head;
    if (head == NULL || strcmp(songInsert, head -> songName) < 0) {
        return newNode(songInsert, artistInsert, genreInsert, head);
    } else {
        while (current -> nextNode != NULL && strcmp(current -> nextNode -> songName, songInsert) < 0) {
            current = current -> nextNode;
        }
        if (current -> nextNode == NULL) {
            current -> nextNode = newNode(songInsert, artistInsert, genreInsert, NULL);
            return head;
        } else if (strcmp(current -> nextNode -> songName, songInsert) == 0) {
            songNameDuplicate(songInsert);
            return head;
        } else {
            current -> nextNode = newNode(songInsert, artistInsert, genreInsert, current -> nextNode);
            return head;
        }
    }
}

// Function to delete a song
Node* deleteSong (Node* head, char* songDelete)
{
    Node* current = head;
    if (head == NULL) {
        printMusicLibraryEmpty();
        return head;
    } else if (strcmp(head -> songName, songDelete) == 0) {
        Node* newHead = head -> nextNode;
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        free(head);
        songNameDeleted(songDelete);
        return newHead;
    } else {
        while (current -> nextNode != NULL && strcmp(current -> nextNode -> songName, songDelete) != 0) {
            current = current -> nextNode;
        }
        if (current -> nextNode == NULL) {
            songNameNotFound(songDelete);
            return head;
        } else {
            Node* tempLink = current -> nextNode;
            free(current -> nextNode -> songName);
            free(current -> nextNode -> artist);
            free(current -> nextNode -> genre);
            current -> nextNode = current -> nextNode -> nextNode;
            free(tempLink);
            songNameDeleted(songDelete);
            return head;
        }
    }
}

// Function to search for a song
void searchSong (Node* head, char* songName)
{
    Node* current = head;
    if (head == NULL) {
        printMusicLibraryEmpty();
        return;
    } else if (strcmp(head -> songName, songName) == 0) {
        songNameFound(songName);
        printf("\n%s\n", head -> songName);
        printf("%s\n", head -> artist);
        printf("%s\n", head -> genre);
        return;
    } else {
        while(current -> nextNode != NULL && strcmp(current -> nextNode -> songName, songName) != 0) {
            current = current -> nextNode;
        }
        if (current -> nextNode == NULL) {
            songNameNotFound(songName);
            return;
        } else {
            songNameFound(songName);
            printf("\n%s\n", current -> nextNode -> songName);
            printf("%s\n", current -> nextNode -> artist);
            printf("%s\n", current -> nextNode -> genre);
            return;            
        }
    }
}

// Function to print the music library
void printLibrary(Node* head)
{
    if (head == NULL) {
        printMusicLibraryEmpty();
        return;
    } else {
        printMusicLibraryTitle();
        Node* current = head;
        while(current != NULL) {
            printf("\n%s\n", current -> songName);
            printf("%s\n", current -> artist);
            printf("%s\n", current -> genre);
            current = current -> nextNode;
        }
        return;
    }
}