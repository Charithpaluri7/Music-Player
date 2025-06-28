// 🎵 Music Playlist Manager using Singly Linked List in C++ with File Handling

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Node structure for each song
class song {
public:
    string name;
    song* next;

    song(string name) {
        this->name = name;
        next = nullptr;
    }
};

// Playlist class
class Playlist {
private:
    song* head;
    song* current;
    stack<song*> history;

public:
    Playlist() {
        head = nullptr;
        current = nullptr;
    }

    void addSong(string name) {
        song* newSong = new song(name);

        if (!head) {
            head = newSong;
            current = head;
        } else {
            song* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newSong;
        }
    }

    void deleteSong(string name) {
        if (!head) {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        if (head->name == name) {
            song* temp = head;
            head = head->next;
            if (current == temp) current = head;
            delete temp;
            cout << "\n Deleted song: " << name << endl;
            return;
        }

        song* curr = head;
        while (curr->next && curr->next->name != name) {
            curr = curr->next;
        }

        if (curr->next) {
            song* temp = curr->next;
            curr->next = curr->next->next;
            if (temp == current) current = curr;
            delete temp;
            cout << "\n Deleted song: " << name << endl;
        } else {
            cout << "\nSong not found in playlist.\n";
        }
    }

    void displayPlaylist() {
        if (!head) {
            cout << "\nPlaylist is empty.\n";
            return;
        }

        int count = 0;
        cout << "\n Current Playlist:\n";
        song* temp = head;
        while (temp) {
            if (temp == current)
                cout << "> " << temp->name << " (Now Playing)" << endl;
            else
                cout << "- " << temp->name << endl;
            temp = temp->next;
            count++;
        }
        cout << "\n Total number of songs: " << count << endl;
    }

    void shufflePlaylist() {
        if (!head || !head->next) return;

        vector<song*> songList;
        song* temp = head;
        while (temp) {
            songList.push_back(temp);
            temp = temp->next;
        }

        random_shuffle(songList.begin(), songList.end());

        for (size_t i = 0; i < songList.size() - 1; ++i) {
            songList[i]->next = songList[i + 1];
        }
        songList.back()->next = nullptr;
        head = songList[0];
        current = head;

        cout << "\n Playlist shuffled successfully!\n";
    }

    void playNext() {
        if (!current || !current->next) {
            cout << "\nNo more songs to play next.\n";
            return;
        }

        history.push(current);
        current = current->next;

        cout << "\n Now playing: " << current->name << endl;
    }

    void playPrevious() {
        if (history.empty()) {
            cout << "\nNo previous song available.\n";
            return;
        }

        current = history.top();
        history.pop();

        cout << "\n Now playing: " << current->name << endl;
    }

    void playCurrent() {
        if (!current) {
            cout << "\nNo song is currently playing.\n";
        } else {
            cout << "\n Currently playing: " << current->name << endl;
        }
    }

    void playSongByName(string name) {
        song* temp = head;
        stack<song*> newHistory;
        while (temp) {
            if (temp->name == name) {
                current = temp;
                history = newHistory;
                cout << "\n Now playing: " << name << endl;
                return;
            }
            newHistory.push(temp);
            temp = temp->next;
        }
        cout << "\n Song not found.\n";
    }

    void saveToFile() {
        ofstream out("playlist.txt");
        song* temp = head;
        while (temp) {
            out << temp->name << endl;
            temp = temp->next;
        }
        out.close();
        cout << "\n Playlist saved to playlist.txt\n";
    }

    void loadFromFile() {
        ifstream in("playlist.txt");
        if (!in) {
            cout << "\n Could not open playlist.txt.\n";
            return;
        }

        string songName;
        while (getline(in, songName)) {
            addSong(songName);
        }
        in.close();
        cout << "\n Playlist loaded from playlist.txt\n";
    }

    void searchSong(string name) {
        song* temp = head;
        int position = 1;
        while (temp) {
            if (temp->name == name) {
                cout << "\n Song found at position " << position << ": " << name << endl;
                return;
            }
            temp = temp->next;
            position++;
        }
        cout << "\n Song not found in playlist.\n";
    }
};

int main() {
    Playlist myPlaylist;
    int choice;
    string songName;

    do {
        cout << "\n MUSIC PLAYLIST MANAGER \n";
        cout << "1. Add Song\n2. Display Playlist\n3. Shuffle Playlist\n4. Play Next\n5. Play Previous\n6. Delete Song\n7. Play Current Song\n8. Save Playlist\n9. Load Playlist\n10. Search Song\n11. Play Song by Name\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song name: ";
                getline(cin, songName);
                myPlaylist.addSong(songName);
                break;
            case 2:
                myPlaylist.displayPlaylist();
                break;
            case 3:
                myPlaylist.shufflePlaylist();
                break;
            case 4:
                myPlaylist.playNext();
                break;
            case 5:
                myPlaylist.playPrevious();
                break;
            case 6:
                cout << "Enter song name to delete: ";
                getline(cin, songName);
                myPlaylist.deleteSong(songName);
                break;
            case 7:
                myPlaylist.playCurrent();
                break;
            case 8:
                myPlaylist.saveToFile();
                break;
            case 9:
                myPlaylist.loadFromFile();
                break;
            case 10:
                cout << "Enter song name to search: ";
                getline(cin, songName);
                myPlaylist.searchSong(songName);
                break;
            case 11:
                cout << "Enter song name to play: ";
                getline(cin, songName);
                myPlaylist.playSongByName(songName);
                break;
            case 0:
                cout << "\nGoodbye! \n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
