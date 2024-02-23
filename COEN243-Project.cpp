#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <exception>
using namespace std;

//Functions for PvP game mode

//Assigns random values to an array[5]
void randList(int sum, int arr[5])
{
    default_random_engine engine(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<unsigned int> randomInt(0, 4);

    for (int i{ 0 }; i < 5; i++)
    {
        sum--;
        arr[i] = 1;
    }
    while (sum != 0)
    {
        arr[randomInt(engine)] += 1;
        sum--;
    }
}

//create a vector with a given number of elements
void create(vector<char> rows, int arr[5], int index)
{
    for (int i{ 0 }; i < arr[index]; i++)
    {
        rows.push_back('O');
        cout << rows[i] << " ";
    }
}

//displays 5 vectors based on the previous 2 functions
void display(int arr[5])
{
    for (int i{ 0 }; i < 5; i++)
    {
        char row = 'A' + i;
        vector<char> A;
        cout << endl << row << ": ";
        create(A, arr, i);
    }
    cout << endl;
}

//updates the entry of the array[5]
void remove(char row, int ntoks, int arr[5])
{
    int index = row - 'A';
    arr[index] -= ntoks;
}

//validates the user's input
bool checkRow(int arr[5], int row, int tokens)
{
    if ((row == 'A' || row == 'B' || row == 'C' || row == 'D' || row == 'E') && (tokens == 1 || tokens == 2))
    {
        if (tokens <= arr[0] || tokens <= arr[1] || tokens <= arr[2] || tokens <= arr[3] || tokens <= arr[4])
        {
            int index = row - 'A';
            if (tokens > arr[index])
            {
                return false;
            }
            else return true;
        }
        else return false;
    }
    else return false;
}

//checks to see if a user won
bool checkWin(int arr[5])
{
    if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0 && arr[3] == 0 && arr[4] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Functions for PvC game mode

//initializes a vector of type int with elements of 2^i
void createHeap(vector<int>& heap, int rows)
{
    for (int i{ 0 }; i < rows; i++)
    {
        heap.push_back(pow(2, i));
    }
}

//creates vectors of type char from the previously initialized vector of type int
void createVect(vector<int>& heap, vector<char>& tokens, int index)
{
    char row = 'A' + index;
    cout << endl << row << ": ";
    for (int i{ 0 }; i < heap[index]; i++)
    {
        tokens.push_back('O');
        cout << tokens[i] << " ";
    }
}

//prints the vectors 
void printHeap(vector<int>& heap)
{
    for (int i{ 0 }; i < heap.size(); i++)
    {
        vector<char> A;
        createVect(heap, A, i);
    }
    cout << endl;
}

// function that removes the inputed tokens from the input heap row
void remove_tokens(vector<int>& heap, char userchar, int tokens)
{
    int index = userchar - 'A';
    for (int i = 0; i < tokens; i++)
    {
        heap[index] -= 1;
    }
}

//checks the input value of the user
bool check_input(vector<int>& heaps, char userchar, int tokens)
{
    int index = userchar - 'A';
    if ((userchar == 'A' || userchar == 'B' || userchar == 'C' || userchar == 'D' || userchar == 'E' || userchar == 'F') && (tokens == 1 || tokens == 2))
    {
        if (tokens <= heaps[0] || tokens <= heaps[1] || tokens <= heaps[2] || tokens <= heaps[3] || tokens <= heaps[4])
        {
            if (tokens > heaps[index])
            {
                return false;
            }
            else return true;
        }
    }
    else return false;
}

//checks to see if all heaps have no tokens left 
bool check_vic(vector<int>& heaps)
{
    int check{ 0 };
    for (int i{ 0 }; i < heaps.size(); i++)
    {
        if (heaps[i] != 0)
        {
            check++;
        }
    }
    if (check == 0)
    {
        return false;
    }
    else return true;

}

//looks for a heap with more than a certain number of token
char seeking(vector<int>& heaps, int nrows)
{
    char row = 'A';
    for (int i = heaps.size() - 1; i >= 0; i--)
    {
        if (heaps[i] >= nrows)
        {
            row += i;
            break;
        }
    }
    return row;
}

bool check_Row(vector<int>& heaps, int nrows)
{
    for (int i = 0; i < heaps.size(); i++)
    {
        if (heaps[i] == nrows)
        {
            return true;
        }
    }
    return false;
}

int get_Rows(vector<int>& heaps, int nrows)
{
    int row = 0;
    for (int i = 0; i < heaps.size(); i++)
    {
        if (heaps[i] == nrows)
        {
            row += 1;
        }
    }
    return row;
}

char get_char(vector<int>& heaps, int nrow)
{
    char row = 'A';
    for (int i = 0; i < heaps.size(); i++)
    {
        if (heaps[i] == nrow)
        {
            row += i;
            break;
        }
    }
    return row;
}

//PC algorithm, calls remove_token function that updates heaps
void algorithm(vector<int>& heaps)
{
    //check total or sum
    int sum{ 0 };
    for (int i{ 0 }; i < heaps.size(); i++)
    {
        sum += heaps[i];
    }

    //removes tokens based on the sum being even or odd
    char letter{'A'};
    if (sum == 1)
    {
        letter = get_char(heaps, 1);
        remove_tokens(heaps, letter, 1);
        cout << "\nPC's turn: " << letter << 1 << endl;
    }
    else if (sum == 2)
    {
        if (check_Row(heaps, 2))
        {
            letter = get_char(heaps, 2);
            remove_tokens(heaps, letter, 2);
            cout << "\nPC's turn: " << letter << 2 << endl;
        }
        else
        {
            letter = get_char(heaps, 1);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
    }
    else if (sum == 3)
    {
        if (check_Row(heaps, 2))
        {
            letter = get_char(heaps, 2);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
        else
        {
            letter = get_char(heaps, 1);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
    }
    else if (sum == 5)
    {
        if (check_Row(heaps, 4))
        {
            letter = get_char(heaps, 1);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
        else if (check_Row(heaps, 3))
        {
            if (check_Row(heaps, 2))
            {
                letter = get_char(heaps, 3);
                remove_tokens(heaps, letter, 1);
                cout << "\nPC's turn: " << letter << 1 << endl;
            }
            else
            {
                letter = get_char(heaps, 2);
                remove_tokens(heaps, letter, 2);
                cout << "\nPC's turn: " << letter << 2 << endl;
            }
        }
        else if (check_Row(heaps, 2) == false)
        {
            letter = get_char(heaps, 1);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
        else if (get_Rows(heaps, 1) == 3)
        {
            letter = get_char(heaps, 3);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
        else
        {
            letter = get_char(heaps, 1);
            remove_tokens(heaps, letter, 1);
            cout << "\nPC's turn: " << letter << 1 << endl;
        }
    }
    else if (sum % 2 != 0)
    {
        letter = seeking(heaps, 2);
        remove_tokens(heaps, letter, 2);
        cout << "\nPC's turn: " << letter << 2 << endl;
    }
    else if (sum % 2 == 0)
    {
        letter = seeking(heaps, 1);
        remove_tokens(heaps, letter , 1);
        cout << "\nPC's turn: " << letter << 1 << endl;
    }
}

void PvC(vector<int>& heaps, string user)
{
    int sum{ 0 };
    for (int i{ 0 }; i < heaps.size(); i++)
    {
        sum += heaps[i];
    }

    if (sum == 0)
    {
        cout << endl;
    }
    else
    {
        char userchar;
        int t;
    startPvC:
        cout << "\n" << user << "'s turn: ";
        cin >> userchar >> t;

        try
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("\nInvalid input!\n");
            }
            else if (check_input(heaps, userchar, t) == false)
            {
                cout << "Incorrect row or number of tokens! Try again.\n";
                goto startPvC;
            }
            else
            {
                remove_tokens(heaps, userchar, t);
                printHeap(heaps);
                cout << "----------------------------------------\n";
                if (check_vic(heaps) == false)
                {
                    cout << "\nCongradulations! " << user << " wins!\n";

                }
                else
                {
                    algorithm(heaps);
                    printHeap(heaps);
                    cout << "----------------------------------------\n";
                    if (check_vic(heaps) == false)
                    {
                        cout << "\nPC wins! Better luck next time ;)\n";

                    }
                }
            }
        }
        catch (...)
        {
            cout << "\nInvalid input! Try again";
            goto startPvC;
        }
        PvC(heaps, user);
    }
}


int main()
{
    int option;
    cout << "* * * * * * * Nim Game * * * * * * *\n";
    cout << "------------------------------------\n";
Lobby:
    cout << "Game Modes:\n";
    cout << "1- PLay two players (user vs. user)" << endl
        << "2- Play one player (user vs. PC)" << endl
        << "3- Exit" << endl;
    cout << "\nSelect game mode: "; cin >> option;
    try
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Invalid input. Please enter a number (1, 2, or 3).");
        }
        else if (option < 1 || option > 3)
        {
            throw out_of_range("Invalid option. Please enter a number (1, 2, or 3).");
        }
        else
        {
            if (option == 1)
            {
                string user1, user2;
                int toks{ 0 }, user{ 1 }, t;
                int random[5]{};
                char row;

                cout << "\n* * * * * * * * * * Welcome to PvP * * * * * * * * * * *\n";
                cout << "--------------------------------------------------------\n";
                cout << "Instructions: To play your turn, you must write the heap\n";
                cout << "              (A/B/C/D/E) and the number of tokens(1/2)\n";
                cout << "--------------------------------------------------------\n";
                cout << "\nEnter Player 1's name: "; cin.ignore(); getline(cin, user1);
                cout << "Enter Player 2's name: "; getline(cin, user2);
            tokens:
                cout << "\nEnter the number of tokens (minimum 6): "; cin >> toks;
                try
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        throw invalid_argument("\nInvalid input! Enter an integer number.");
                    }
                    else if (toks < 6)
                    {
                        throw out_of_range("\nInvalid numbber of tokens! Enter a number greater than 6.");
                        goto tokens;
                    }
                    else
                    {

                        randList(toks, random);
                        display(random);

                        do
                        {
                        startPvP:
                            if (user == 3)
                            {
                                user -= 2;
                            }
                            if (user == 1)
                            {
                                cout << "\n" << user1 << "'s turn: ";
                            }
                            else
                            {
                                cout << "\n" << user2 << "'s turn: ";
                            }

                            cin >> row >> t;
                            try
                            {
                                if (cin.fail())
                                {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    throw invalid_argument("\nInvalid input! Enter an integer number.");
                                }
                                else if (checkRow(random, row, t) == false)
                                {
                                    cout << "Incorrect row or number of tokens! Try again.\n";
                                    goto startPvP;
                                }
                                else
                                {
                                    remove(row, t, random);
                                    display(random);
                                    user++;
                                }
                            }
                            catch (...)
                            {
                                cout << "\nIncorrect input! Try again\n";
                                goto startPvP;
                            }
                        } while (checkWin(random));

                        --user;
                        if (user == 1)
                        {
                            cout << "\nCongradulations! " << user1 << " wins!\n";
                        }
                        else
                        {
                            cout << "\nCongradulations! " << user2 << " wins!\n";
                        }

                        string play_again;
                        cout << "\nWould you like to play again? "; cin >> play_again;

                        if (play_again == "yes" || play_again == "Yes" || play_again == "YES")
                        {
                            cout << endl;
                            goto Lobby;
                        }
                        else if (play_again == "no" || play_again == "No" || play_again == "NO")
                        {
                            cout << "\nGame terminated. Good-bye!\n";
                        }
                    }
                }
                catch (...)
                {
                    cout << "\nInvalid input! Try again.\n";
                    goto tokens;
                }
            }
            else if (option == 2)
            {
                //user vs PC
                {
                    vector<int> heaps;
                    string user;
                    int rows, t;
                    char userchar;

                    cout << "\n* * * * * * * * * * Welcome to PvC * * * * * * * * * * *\n";
                    cout << "--------------------------------------------------------\n";
                    cout << "Instructions: To play your turn, you must write the heap\n";
                    cout << "              (A/B/C/D/E) and the number of tokens(1/2)\n";
                    cout << "--------------------------------------------------------\n";
                    cout << "\nEnter Player's name: "; cin.ignore(); getline(cin, user);
                tokensPvC:
                    cout << "Enter an integer number of heaps (max 6): "; cin >> rows;
                    try
                    {
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            throw invalid_argument("\nInvalid input! Enter an integer number.");
                        }
                        else if (rows > 6)
                        {
                            cout << "\nAre you sure you want to do that. Rows are calculated based on 2^n\n";
                            goto tokensPvC;
                        }
                        else
                        {
                            createHeap(heaps, rows);
                            printHeap(heaps);
                            PvC(heaps, user);

                        end:
                            string play_again;
                            cout << "\nWould you like to play again? "; cin >> play_again;

                            if (play_again == "yes" || play_again == "Yes" || play_again == "YES")
                            {
                                cout << endl;
                                goto Lobby;
                            }
                            else if (play_again == "no" || play_again == "No" || play_again == "NO")
                            {
                                cout << "\nGame terminated. Good-bye!\n";
                            }
                            else
                            {
                                cout << "\nYou must enter yes or no!\n";
                                goto end;
                            }
                        }
                    }
                    catch (...)
                    {
                        cout << "\nInput is not an integer! Try again.\n";
                        goto tokensPvC;
                    }
                }
            }
            else if (option == 3)
            {
                cout << "\nExiting the game. Goodbye!" << endl;
            }
        }
    }
    catch (...)
    {
        cout << "\nInvalid input! Try again.\n\n";
        goto Lobby;
    }
    return 0;
}