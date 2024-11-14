#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYLISTS 10
#define MAX_SONGS 100

typedef struct
{
    char title[100];
    char artist[100];
} Song;

typedef struct
{
    char name[100];
    Song songs[MAX_SONGS];
    int songCount;
} Playlist;

Playlist playlists[MAX_PLAYLISTS];
int playlistCount = 0;

void playSong(const char* songName)
{
    printf("Now playing: %s\n", songName);
}

void addSongToPlaylist(Playlist* playlist, const Song* song)
{
    if (playlist->songCount < MAX_SONGS)
    {
        playlist->songs[playlist->songCount] = *song;
        playlist->songCount++;
    }
    else
        printf("Playlist is full. Cannot add more songs.\n");
}

void displayPlaylist(const Playlist* playlist)
{
    printf("Songs in the playlist '%s':\n", playlist->name);
    for (int i = 0; i < playlist->songCount; i++)
    {
        printf("%d. %s by %s\n", i + 1, playlist->songs[i].title, playlist->songs[i].artist);
    }
}

void createNewPlaylist()
{
    if (playlistCount < MAX_PLAYLISTS)
    {
        Playlist newPlaylist;
        printf("Enter the name of the new playlist: ");
        scanf(" %[^\n]", newPlaylist.name);
        newPlaylist.songCount = 0;
        playlists[playlistCount] = newPlaylist;
        playlistCount++;
    }
    else
        printf("You have reached the maximum number of playlists.\n");
}

int main()
{
    system("COLOR 3F");
    Song song;
    int choice;

    printf("=====================================\n");
    printf("             Music Player            \n");
    printf("=====================================\n");
    printf("=====================================\n");
    printf("<<      <         ||        >      >>\n");
    printf("=====================================\n");
    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Play\n");
        printf("2. Pause\n");
        printf("3. Create a new playlist\n");
        printf("4. Add a Song to a playlist\n");
        printf("5. Delete a Song From a Playlist\n");
        printf("6. Display Songs in a playlist\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            if (playlistCount > 0)
            {
                printf("Select a playlist to play a song:\n");
                for (int i = 0; i < playlistCount; i++)
                {
                    printf("%d. %s\n", i + 1, playlists[i].name);
                }
                int selectedPlaylist, selectedSong = 0;
                printf("Enter the number of the playlist: ");
                scanf("%d", &selectedPlaylist);
                if (selectedPlaylist >= 1 && selectedPlaylist <= playlistCount)
                {
                    Playlist* playlist = &playlists[selectedPlaylist - 1];
                    if (playlist->songCount > 0)
                    {
                        printf("Select a song to play:\n");
                        for (int i = 0; i < playlist->songCount; i++)
                        {
                            printf("%d. %s by %s\n", i + 1, playlist->songs[i].title, playlist->songs[i].artist);
                        }
                        printf("Enter the number of the song: ");
                        scanf("%d", &selectedSong);
                        if (selectedSong >= 1 && selectedSong <= playlist->songCount)
                        {
                            playSong(playlist->songs[selectedSong - 1].title);
                        }
                        else
                        {
                            printf("Invalid song number.\n");
                        }
                    }
                    else
                    {
                        printf("Selected playlist is empty.\n");
                    }

                    while(1)
                    {
                        printf("\n1.Play Next Song \n2.Play Previous Song \n3.Go Back to Menu\n");
                        printf("Enter Your Choice: ");
                        int play;
                        scanf("%d", &play);
                        if (play == 1)
                        {
                            if (selectedSong >= 1 && selectedSong < playlist->songCount)
                            {
                                selectedSong++;
                                playSong(playlist->songs[selectedSong-1].title);
                            }
                            else
                            {
                                printf("No more songs in the playlist.\n");
                            }
                        }
                        else if (play == 2)
                        {
                            if (selectedSong > 0)
                            {
                                selectedSong--;
                                playSong(playlist->songs[selectedSong-1].title);
                            }
                            else
                            {
                                printf("No previous songs in the playlist.\n");
                            }
                        }
                        else if (play == 3)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    printf("Invalid playlist number.\n");
                }
            }
            else
                printf("No playlists available. Create a new playlist first.\n");
            break;
        case 2:
            if (playlistCount > 0)
            {
                printf("Music Paused...\n");
            }
            else
                printf("No playlists available. Create a new playlist first.\n");
            break;
        case 3:
            createNewPlaylist();
            break;
        case 4:
            printf("Enter the title of the song: ");
            scanf(" %[^\n]", song.title);
            printf("Enter the artist of the song: ");
            scanf(" %[^\n]", song.artist);
            printf("1. Create a new playlist for the song\n");
            printf("2. Add to an existing playlist\n");
            int addChoice;
            printf("Enter your choice: ");
            scanf("%d", &addChoice);

            if (addChoice == 1)
            {
                createNewPlaylist();
                addSongToPlaylist(&playlists[playlistCount - 1], &song);
            }
            else if (addChoice == 2)
            {
                if (playlistCount > 0)
                {
                    printf("Select a playlist to add the song:\n");
                    for (int i = 0; i < playlistCount; i++)
                    {
                        printf("%d. %s\n", i + 1, playlists[i].name);
                    }
                    int selectedPlaylist;
                    printf("Enter the number of the playlist: ");
                    scanf("%d", &selectedPlaylist);
                    if (selectedPlaylist >= 1 && selectedPlaylist <= playlistCount)
                    {
                        addSongToPlaylist(&playlists[selectedPlaylist - 1], &song);
                    }
                    else
                        printf("Invalid playlist number.\n");
                }
                else
                    printf("No playlists available. Create a new playlist first.\n");
            }
            break;
        case 5:
            if (playlistCount > 0)
            {
                printf("Select a playlist to delete a song from:\n");
                for (int i = 0; i < playlistCount; i++)
                {
                    printf("%d. %s\n", i + 1, playlists[i].name);
                }
                int selectedPlaylist;
                printf("Enter the number of the playlist: ");
                scanf("%d", &selectedPlaylist);
                if (selectedPlaylist >= 1 && selectedPlaylist <= playlistCount)
                {
                    Playlist* playlist = &playlists[selectedPlaylist - 1];
                    if (playlist->songCount > 0)
                    {
                        printf("Select a song to delete:\n");
                        for (int i = 0; i < playlist->songCount; i++)
                        {
                            printf("%d. %s by %s\n", i + 1, playlist->songs[i].title, playlist->songs[i].artist);
                        }
                        int selectedSong;
                        printf("Enter the number of the song: ");
                        scanf("%d", &selectedSong);
                        if (selectedSong >= 1 && selectedSong <= playlist->songCount)
                        {
                            // Delete the selected song from the playlist
                            for (int i = selectedSong - 1; i < playlist->songCount - 1; i++)
                            {
                                playlist->songs[i] = playlist->songs[i + 1];
                            }
                            playlist->songCount--;
                        }
                        else
                        {
                            printf("Invalid song number.\n");
                        }
                    }
                    else
                    {
                        printf("Selected playlist is empty.\n");
                    }
                }
                else
                {
                    printf("Invalid playlist number.\n");
                }
            }
            else
                printf("No playlists available. Create a new playlist first.\n");
            break;
        case 6:
            if (playlistCount > 0)
            {
                printf("Select a playlist to display songs:\n");
                for (int i = 0; i < playlistCount; i++)
                {
                    printf("%d. %s\n", i + 1, playlists[i].name);
                }
                int selectedPlaylist;
                printf("Enter the number of the playlist: ");
                scanf("%d", &selectedPlaylist);
                if (selectedPlaylist >= 1 && selectedPlaylist <= playlistCount)
                {
                    displayPlaylist(&playlists[selectedPlaylist - 1]);
                }
                else
                    printf("Invalid playlist number.\n");
            }
            else
                printf("No playlists available. Create a new playlist first.\n");
            break;
        case 0:
            printf("Thanks for Using! \nGoodbye :)\n");
            exit(0);
            break;
        default:
            printf("Invalid Choice. Please Try Again.\n");
        }
    }
    return 0;
}

