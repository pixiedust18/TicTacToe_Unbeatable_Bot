#include <iostream>
using namespace std;

int best_zero_max = -1; //total number of times when minimum score is 0, ai player wins
int zero_max = 0;
int curr_zero_depth = 100;
int best_zero_depth = 100; //should be minimum

//int best_zero_row=0;
//int best_zero_col=0;
int zero_max_set = 0;
class Game
{
    char board[3][3];

public:
    Game()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = '_';
            }
        }
    }
    int check_hor(int, int);
    int check_vert(int, int);
    int check_diag(int, int);
    void Player1_human1st();
    void Player1_ai1st();

    void Player2();
    void display();
    int ai_play();
    int minimax(int i, int j, bool minimise, int depth);
    int win(int, int);
    int isFull()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == '_')
                    return false;
            }
        }
        return true;
    }
};
int Game::minimax(int i, int j, bool minimise, int depth)
{
    if (win(i, j))
    {
        if (minimise == true)
        {
            //cout<<" o "<<depth<<endl;;
            if (depth < curr_zero_depth)
                curr_zero_depth = depth;
            zero_max++;
            return (100 - depth);
        }
        else
        {
            //cout<<" x "<<depth<<endl;;
            return -1;
        }
    } 
    if (isFull())
    {
        if (best_zero_max < zero_max)
        {
            best_zero_max = zero_max;
            zero_max_set = 1;
            //cout<<best_zero_max<<" "<<best_zero_depth<<endl;
        }
        if (best_zero_max == zero_max)
        {
            if (best_zero_depth >= curr_zero_depth)
            {
                best_zero_depth = curr_zero_depth;
                best_zero_max = zero_max;
                zero_max_set = 1;
                //cout<<best_zero_max<<" "<<best_zero_depth<<endl;
            }
        }
        //cout<<best_zero_max<<" "<<best_zero_depth<<endl;
        return 0;
    }
    int score = 0, best_score;

    if (minimise)
        best_score = 99;
    else
        best_score = -99;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int temp_score = 0;
            if (board[i][j] == '_')
            {
                if (minimise) //next is human x
                {

                    board[i][j] = 'x';
                    score = minimax(i, j, !minimise, depth + 1);
                    board[i][j] = '_';
                    if (score < best_score)
                        best_score = score;
                }
                else
                {
                    board[i][j] = 'o';
                    score = minimax(i, j, !minimise, depth + 1);
                    board[i][j] = '_';
                    if (score > best_score)
                        best_score = score;
                }
            }
        }
    }

    return best_score;
}
int Game::ai_play()
{
    int best_row = 0, best_col = 0, best_score = -99, score = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            zero_max = 0;
            curr_zero_depth=100;
            int temp_score = 0;
            if (board[i][j] == '_')
            {
                board[i][j] = 'o';
                score = minimax(i, j, true, 0);
                board[i][j] = '_';

                
                if (score >= best_score)
                {
                    if (score == 0 && zero_max_set == 1)
                    {
                        zero_max_set = 0;
                        best_col = j;
                        best_row = i;
                        //cout<<best_zero_depth<<" "<<best_zero_max<<" ij "<<i<<" "<<j<<endl;
                        best_score = score;

                    }else if(score!=0)
                    {
                        best_score = score;
                        best_row = i;
                        best_col = j;
                    }

                    //cout<<best_score<<" ij "<<i<<" "<<j<<endl;
                }
                if (score == 0 && zero_max_set == 1)
                {
                    zero_max_set = 0;
                }
            }
        }
    }
    board[best_row][best_col] = 'o';
    best_zero_depth=100;
    best_zero_max=0;
    if (win(best_row, best_col))
        return 1;
    else
        return 0;
}

int Game::check_hor(int row, int col)
{
    char token = board[row][col];
    if (token == '_')
        return 0;
    for (int i = 0; i < 3; i++)
    {
        if (board[row][i] != token)
            return 0;
    }
    return 1;
}
int Game::check_vert(int row, int col)
{
    char token = board[row][col];
    if (token == '_')
        return 0;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][col] != token)
            return 0;
    }
    return 1;
}
int Game::check_diag(int row, int col)
{
    int flag = 1;
    char token = board[row][col];
    if (token == '_')
        return 0;
    int j = 2;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][j] != token)
        {
            flag = 0;
            break;
        }
        j--;
    }
    if (flag == 1)
        return 1;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][i] != token)
        {
            return 0;
        }
    }
    return 1;
}
void Game::display()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}
int Game::win(int row, int col)
{
    // check for vertical 4
    int play = this->check_vert(row, col);
    if (play == 1)
        return 1;

    // check for horizontal 4
    play = this->check_hor(row, col);
    if (play == 1)
        return 1;

    // check for diagonal 4
    play = this->check_diag(row, col);
    if (play == 1)
        return 1;
    else
        return 0;
}
void Game::Player2()
{
    int moves = 0;
    int row, col;
    int play = 0;

    cout << "Player 1: o" << endl;
    cout << "Player 2: x" << endl;

    while ((play == 0) && (moves <= 9))
    {
        //player 1

        cout << "Player 1's(o) move:" << endl;
        cin >> row >> col;
        if (board[row][col] != '_')
            continue;

        board[row][col] = 'o';
        this->display();

        if (win(row, col))
        {
            cout << "Player 1 wins!" << endl;
            return;
        }
        moves++;
        //player 2

        do
        {
            cout << "Player 2’s(x) move:" << endl;
            cin >> row >> col;
        } while (board[row][col] != '_');

        board[row][col] = 'x';
        this->display();
        if (win(row, col))
        {
            cout << "Player 2 wins!" << endl;
            return;
        }
        moves++;
    }

    cout << "It is a tie!\n";
}
void Game::Player1_human1st()
{
    int moves = 0;
    int row, col;
    int play = 0;

    cout << "You: x" << endl;
    cout << "AI: o" << endl;

    while ((play == 0) && (moves <= 9))
    {

        cout << "\nYour move:" << endl;
        cin >> row >> col;
        if (board[row][col] != '_')
            continue;

        board[row][col] = 'x';
        this->display();

        if (win(row, col))
        {
            cout << "You win!" << endl;
            return;
        }
        moves++;
        if (moves == 9)
            break;

        cout << "\nAI's move\n";
        int s = ai_play();
        this->display();
        if (s == 1)
        {
            cout << "AI wins!" << endl;
            return;
        }
        moves++;
    }
    cout << "It is a tie!\n";
}
void Game::Player1_ai1st()
{
    int moves = 0;
    int row, col;
    int play = 0;

    cout << "You: x" << endl;
    cout << "AI: o" << endl;

    while ((play == 0) && (moves <= 9))
    {
        cout << "\nAI's move\n";
        int s = ai_play();
        this->display();
        if (s == 1)
        {
            cout << "\nAI wins!" << endl;
            return;
        }
        moves++;
        if (moves >= 9)
            break;

        cout << "\nYour move:" << endl;
        cin >> row >> col;
        if (board[row][col] != '_')
            continue;

        board[row][col] = 'x';
        this->display();

        if (win(row, col))
        {
            cout << "\nYou win!" << endl;
            return;
        }
        moves++;
    }
    cout << "\nIt is a tie!\n";
}
int main()
{
    Game g;
    cout<<"Pick an option:\n 1) 1 Player\n 2) 2 Player\n";
    int op;
    cin>>op;

    if(op==1)
    {
        cout<<"Do you want to start first? Y/n\n";
        char ch;
        cin>>ch;
        if(ch=='Y' || ch=='y')
        {
            g.Player1_human1st();
        } else 
        {
            g.Player1_ai1st();
        }
    }else
    {
        g.Player2();
    }
    return 0;
}