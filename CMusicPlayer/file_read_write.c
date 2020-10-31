#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "terminal_user_input.c"
#include <stdlib.h>
#include <string.h>


typedef enum { Pop, Classic, Rock, Metal, Country } genre;


typedef struct
{
  my_string trackName;
  my_string trackLocation;
} track;


typedef struct
{
  my_string albumName;
  my_string artistName;
  my_string  albumGenre;
  int numberOfTracks;
  track albumTracks[14];
} album;

int numberOfAlbums;
album* albumArray;
genre myGenre;



void ReadLinesFromFiles()
{

  int a;
  int b;
  FILE *myFile;

  
  myFile = fopen("mytestfile.dat", "r");
  if ( myFile == NULL )
  {
    printf("Unable to open music data.");
    exit(EXIT_FAILURE);
  }



  fscanf(myFile, "%d ", &numberOfAlbums);
  albumArray = malloc(numberOfAlbums * sizeof(album));

  

  for (a = 0; a < numberOfAlbums; a++)
  {
    
    fscanf(myFile, "%255[^\n]\n", albumArray[a].albumName.str);
    fscanf(myFile, "%255[^\n]\n", albumArray[a].artistName.str);
    fscanf(myFile, "%255[^\n]\n", albumArray[a].albumGenre.str);
    fscanf(myFile, "%d\n", &albumArray[a].numberOfTracks);
    

    for (b = 0; b < albumArray[a].numberOfTracks; b++)
    {
      fscanf(myFile, "%255[^\n]\n", albumArray[a].albumTracks[b].trackName.str);
      fscanf(myFile, "%255[^\n]\n", albumArray[a].albumTracks[b].trackLocation.str);
    }
 
  }

  printf("File read successfully\n");
  printf("******************\n");

}



void PrintLinesToTerminal()
{
	int a;
	int b;


	printf("\n");
	printf("******************\n");
	printf("The number of albums is: %d\n", numberOfAlbums);
	printf("******************\n");

	for (a = 0; a < numberOfAlbums; a++)
	{
    	printf("Album name is: %s\n", albumArray[a].albumName.str);
    	printf("Artists name is: %s\n", albumArray[a].artistName.str);
    	printf("The genre is: %s\n", albumArray[a].albumGenre.str);
    	printf("The number of tracks is: %d\n", albumArray[a].numberOfTracks);

    	for (b = 0; b < albumArray[a].numberOfTracks; b++)
    	{
    		printf("Name of track is: %s\n", albumArray[a].albumTracks[b].trackName.str);
      		printf("Location of track is: %s\n", albumArray[a].albumTracks[b].trackLocation.str);
    	}

    	printf("******************\n");
    	printf("\n");
	}
}



void PlayTrack()
{
	int selectedTrack;
	int selectedAlbum;


	printf("\n");
	printf("******************\n");

	selectedAlbum = read_integer_range("Please enter the album number you want to play: ", 1, numberOfAlbums);
	printf("\nYou have selected the album: %s", albumArray[selectedAlbum -1].albumName.str);
	printf("\n");
	selectedTrack = read_integer_range("Please enter the track number you want to play: ", 1, albumArray[selectedAlbum -1].numberOfTracks);
	printf("\n");
	printf("You have selected the track: %s", albumArray[selectedAlbum -1].albumTracks[selectedTrack -1].trackName.str);
	printf(". From the album: %s", albumArray[selectedAlbum -1].albumName.str);
	printf("\nNow Playing...");
	printf("\n******************");
	printf("\n");
}



void AlbumEdit()
{
	int selectedAlbum;
	int edit;
  int genreNumber;


	printf("\n");
	printf("******************\n");

	selectedAlbum = read_integer_range("Please enter the number of the album you want to edit: ", 1, numberOfAlbums);
	printf("\nYou have selected the album: %s", albumArray[selectedAlbum -1].albumName.str);
	printf("\n");

	edit = -1;
	while (edit !=3)
	{
		printf("1. Change Album Name\n");
    	printf("2. Change Album Genre\n");
    	printf("3. Back to Main Menu\n");

    	edit = read_integer_range("Enter menu number: ", 1, 3);

		if (edit == 1) {
			albumArray[selectedAlbum -1].albumName = read_string("Please enter a new name for the selected album: ");
			printf("\nAlbum has been updated");
			printf("\n");
		}
		if (edit == 2) {
			genreNumber = read_integer_range("Please select the number genre you want: 1 = Pop, 2 = Classic, 3 = Rock, 4 = Metal, 5 = Country: ", 1, 5);
      if (genreNumber == 1) {
        myGenre = Pop;
      }
      if (genreNumber == 2) {
        myGenre = Classic;
      }
      if (genreNumber == 3) {
        myGenre = Rock;
      }
      if (genreNumber == 4) {
        myGenre = Metal;
      }
      if (genreNumber == 5) {
        myGenre = Country;
      }


      if (myGenre == Pop) {
        strncpy(albumArray[selectedAlbum -1].albumGenre.str, "Pop", 4);
      }
      if (myGenre == Classic) {
        strncpy(albumArray[selectedAlbum -1].albumGenre.str, "Classic", 9);
      }
      if (myGenre == Rock) {
        strncpy(albumArray[selectedAlbum -1].albumGenre.str, "Rock", 5);
      }
      if (myGenre == Metal) {
        strncpy(albumArray[selectedAlbum -1].albumGenre.str, "Metal", 6);
      }
      if (myGenre == Country) {
        strncpy(albumArray[selectedAlbum -1].albumGenre.str, "Country", 9);
      }
      
   
			printf("\nAlbum has been updated");
			printf("\n");
		}
	}
}



void main()
{
  int Selected;


  Selected = -1;
  while (Selected != 5)
    {
    printf("1. Read in Albums\n");
    printf("2. Display Albums\n");
    printf("3. Select an Album to play\n");
    printf("4. Update an existing Album\n");
    printf("5. Exit the application\n");

    Selected = read_integer_range("Enter menu number: ", 1, 5);

    if (Selected == 1) {
        ReadLinesFromFiles();
    }
      
    if (Selected == 2) {
        PrintLinesToTerminal();
    }
      
    if (Selected == 3) {
      PlayTrack();
    }
      
    if (Selected == 4) {
      AlbumEdit();
    }
    
    }
}