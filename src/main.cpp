#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <queue>
#include <thread>
#include <set>

using namespace std;

class chess_board;

struct pos
{
    int x;
    int y;
};

struct action
{
    size_t queen;
    pos new_pos;
};

class chess_board
{
private:
    vector<vector<bool>> board;
    vector<pos> queens;

public:
    chess_board()
    {
        board = vector<vector<bool>>(8,vector<bool>(8, 0));
    }



    void setup_diagonal_queens()
    {
        queens.clear();
        for(int i = 0; i < board.size(); i++)
        {
            board[i][i] = 1;
            queens.push_back({i, i});
        }
    }

    vector<action> available_actions()
    {
        vector<action> ret;

        for(size_t i = 0; i < queens.size(); i++)
        {
            auto queen = queens[i];

            pos up = { queen.x, queen.y };
            while(up.y >= 0)
            {
                if(!board[up.y][up.x])
                    ret.push_back(action{ i, pos{up.x, up.y} });
                else if(board[up.y][up.x] && (up.x != queen.x || up.y != queen.y))
                    break;

                up.y--;
            }

            pos down = { queen.x, queen.y };
            while(down.y <= board.size() - 1)
            {
                if(!board[down.y][down.x])
                    ret.push_back(action{ i, pos{down.x, down.y} });
                else if(board[down.y][down.x] && (down.x != queen.x || down.y !=queen.y))
                    break;

                down.y++;
            }

            pos left = { queen.x, queen.y };
            while(left.x >= 0)
            {
                if(!board[left.y][left.x])
                    ret.push_back(action{ i, pos{left.x, left.y} });
                else if(board[left.y][left.x] && (left.x != queen.x || left.y !=queen.y))
                    break;

                left.x--;
            }

            pos right = { queen.x, queen.y };
            while(right.x <= board.size() - 1)
            {
                if(!board[right.y][right.x])
                    ret.push_back(action{ i, pos{right.x, right.y} });
                else if(board[right.y][right.x] && (right.x != queen.x || right.y !=queen.y))
                    break;

                right.x++;
            }

            pos up_left = { queen.x, queen.y };
            while(up_left.x >= 0 && up_left.y >= 0)
            {
                if(!board[up_left.y][up_left.x])
                    ret.push_back(action{ i, pos{up_left.x, up_left.y} });
                else if(board[up_left.y][up_left.x] && (up_left.x != queen.x || up_left.y !=queen.y))
                    break;

                up_left.x--;
                up_left.y--;
            }

            pos up_right = { queen.x, queen.y };
            while(up_right.x <= board.size() - 1 && up_right.y >= 0)
            {
                if(!board[up_right.y][up_right.x])
                    ret.push_back(action{ i, pos{up_right.x, up_right.y} });
                else if(board[up_right.y][up_right.x] && (up_right.x != queen.x || up_right.y !=queen.y))
                    break;

                up_right.x++;
                up_right.y--;
            }

            pos down_left = { queen.x, queen.y };
            while(down_left.x >= 0 && down_left.y <= board.size() - 1)
            {
                if(!board[down_left.y][down_left.x])
                    ret.push_back(action{ i, pos{down_left.x, down_left.y} });
                else if(board[down_left.y][down_left.x] && (down_left.x != queen.x || down_left.y !=queen.y))
                    break;

                down_left.x--;
                down_left.y++;
            }

            pos down_right = { queen.x, queen.y };
            while(down_right.x <= board.size() - 1 && down_right.y <= board.size() - 1)
            {
                if(!board[down_right.y][down_right.x])
                    ret.push_back(action{ i, pos{down_right.x, down_right.y} });
                else if(board[down_right.y][down_right.x] && (down_right.x != queen.x || down_right.y !=queen.y))
                    break;

                down_right.x++;
                down_right.y++;
            }
        }

        return ret;
    }

    int f1() // returns the number of pairs of queens that beats each other
    {
        int c = 0;

        for(size_t i = 0; i < queens.size(); i++)
        {
            auto queen = queens[i];

            pos up = { queen.x, queen.y };
            while(up.y >= 0)
            {
                if(board[up.y][up.x] && (up.x != queen.x || up.y != queen.y)) {
                    c++;
                    break;
                }

                up.y--;
            }

            pos down = { queen.x, queen.y };
            while(down.y <= board.size() - 1)
            {
                if(board[down.y][down.x] && (down.x != queen.x || down.y != queen.y)) {
                    c++;
                    break;
                }

                down.y++;
            }

            pos left = { queen.x, queen.y };
            while(left.x >= 0)
            {
                if(board[left.y][left.x] && (left.x != queen.x || left.y != queen.y)) {
                    c++;
                    break;
                }

                left.x--;
            }

            pos right = { queen.x, queen.y };
            while(right.x <= board.size() - 1)
            {
                if(board[right.y][right.x] && (right.x != queen.x || right.y != queen.y)) {
                    c++;
                    break;
                }

                right.x++;
            }

            pos up_left = { queen.x, queen.y };
            while(up_left.x >= 0 && up_left.y >= 0)
            {
                if(board[up_left.y][up_left.x] && (up_left.x != queen.x || up_left.y != queen.y)) {
                    c++;
                    break;
                }

                up_left.x--;
                up_left.y--;
            }

            pos up_right = { queen.x, queen.y };
            while(up_right.x <= board.size() - 1 && up_right.y >= 0)
            {
                if(board[up_right.y][up_right.x] && (up_right.x != queen.x || up_right.y != queen.y)) {
                    c++;
                    break;
                }

                up_right.x++;
                up_right.y--;
            }

            pos down_left = { queen.x, queen.y };
            while(down_left.x >= 0 && down_left.y <= board.size() - 1)
            {
                if(board[down_left.y][down_left.x] && (down_left.x != queen.x || down_left.y != queen.y)) {
                    c++;
                    break;
                }

                down_left.x--;
                down_left.y++;
            }

            pos down_right = { queen.x, queen.y };
            while(down_right.x <= board.size() - 1 && down_right.y <= board.size() - 1)
            {
                if(board[down_right.y][down_right.x] && (down_right.x != queen.x || down_right.y != queen.y)) {
                    c++;
                    break;
                }

                down_right.x++;
                down_right.y++;
            }
        }

        return c/2;
    }

    void move(size_t queen, pos new_pos)
    {
        pos old = {queens[queen].x, queens[queen].y};

        board[old.y][old.x] = false;
        board[new_pos.y][new_pos.x] = true;
        queens[queen] = new_pos;
    }

    vector<vector<bool>> get_board() const
    {
        return board;
    }

    void set_board(vector<vector<bool>> board)
    {
        queens.clear();
        for(size_t i = 0; i < board.size(); i++)
        {
            for(size_t j = 0; j < board.size(); j++)
            {
                this->board[i][j] = board[i][j];
                if(board[i][j])
                {
                    queens.push_back(pos{int(j), int(i)});
                }
            }
        }
    }

    vector<pos> get_available_pos()
    {
        vector<pos> ret;

        for(int y = 0; y < board.size(); y++)
        {
            for(int x = 0; x < board[y].size(); x++)
            {
                if(!board[y][x])
                    ret.push_back({x, y});
            }
        }

        return ret;
    }

    void print()
    {
        for(const auto& raw : board)
        {
            for(const auto& item : raw)
                cout << item << " ";
            cout << endl;
        }
    }

    int already_put_queens()
    {
        int c = 0;

        for(const auto& raw : board)
        {
            for(const auto& item : raw)
            {
                if(item)
                    c++;
            }
        }

        return c++;
    }

    void operator=(const chess_board& other)
    {
        //board = other.board;
        board = vector<vector<bool>>(other.board.size(), vector<bool>(other.board.size(), 0));
        for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board.size(); j++)
            {
                board[i][j] = other.board[i][j];
            }
        }
        queens = other.queens;
    }
};

struct a_star_node
{
    chess_board cb;
    action act;
    int path;
};

bool operator==(const chess_board& cb1, const chess_board& cb2)
{
    bool ret = true;

    for(int i = 0; i < cb1.get_board().size(); i++)
    {
        ret &= (cb1.get_board()[i] == cb2.get_board()[i]);
    }

    return ret;
}

bool operator==(const action& a1, const action& a2)
{
    bool ret = true;

    ret &= (a1.queen == a2.queen);
    ret &= (a1.new_pos.x == a2.new_pos.x);
    ret &= (a1.new_pos.y == a2.new_pos.y);

    return ret;
}

bool operator==(const a_star_node& a1, const a_star_node& a2)
{
    bool ret = true;

    ret &= (a1.cb == a2.cb);
    ret &= (a1.path == a2.path);
    ret &= (a1.act == a2.act);

    return ret;
}

bool operator<(const a_star_node& a1, const a_star_node& a2)
{
    return a1.path<a2.path;
}

class eight_queens_solver
{
public:
    int bfs_counter;
    int a_star_couter;

    chess_board local;

    void shuffle(chess_board& board, int iterations)
    {
        for(int i = 0; i < iterations; i++)
        {
            auto acts = board.available_actions();
            auto act = acts[rand() % acts.size()];
            board.move(act.queen, act.new_pos);
        }
    }

    chess_board bfs_solve_for(chess_board board)
    {
        queue<chess_board> states;
        queue<action> actions;
        bfs_counter = 0;

        if(is_valid(board.get_board()))
            return board;

        auto temp_actions = board.available_actions();
        for(const auto& act : temp_actions)
        {
            chess_board b;
            b = board;
            states.push(b);
            actions.push(act);
        }

        while(!actions.empty() && !states.empty())
        {
            auto next_act = actions.front();
            auto state = states.front();

            actions.pop();
            states.pop();

            state.move(next_act.queen, next_act.new_pos);

            if(is_valid(state.get_board()))
                return state;

            bfs_counter++;

            auto new_actions = state.available_actions();
            for(const auto& act : new_actions)
            {
                chess_board b;
                b = state;
                states.push(b);
                actions.push(act);
            }
        }

        return chess_board();
    }

    chess_board a_star_for(chess_board start)
    {
        a_star_couter = 0;
        vector<a_star_node> closed;
        vector<a_star_node> opened;

        if(is_valid(start.get_board()))
            return start;

        auto available_actions = start.available_actions();
        for(const auto& act : available_actions)
        {
            chess_board temp;
            temp = start;
            temp.move(act.queen, act.new_pos);
            int path = temp.f1();
            opened.push_back({temp, act, path});
        }

        while (!opened.empty())
        {
            auto min_p = std::min_element(opened.begin(), opened.end());
            auto min_val = *min_p;
            opened.erase(min_p);
            closed.push_back(min_val);

            if(std::find(closed.begin(), closed.end(), min_val) == closed.end())
                continue;

            if(is_valid(min_val.cb.get_board()))
                return min_val.cb;

            a_star_couter++;

            auto available_actions = min_val.cb.available_actions();
            for(const auto& act : available_actions)
            {
                chess_board temp;
                temp = min_val.cb;
                temp.move(act.queen, act.new_pos);
                int path = min_val.path + temp.f1();
                opened.push_back({temp, act, path});
            }
        }

        return chess_board();
    }
private:
    string out_delimeter = "===============";

    bool is_valid(vector<vector<bool>> matrix)
    {
        bool ret = true;

        ret &= is_valid_horizontal(matrix);
        ret &= is_valid_vertical(matrix);
        ret &= is_valid_diagonal(matrix);
        ret &= is_valid_back_diagonal(matrix);

        return ret;
    }

    bool is_valid_horizontal(vector<vector<bool>> matrix)
    {
        bool ret = true;

        for(auto& raw : matrix)
        {
            auto sum = accumulate(raw.begin(), raw.end(), 0);
            ret &= (sum <= 1);
        }

        return ret;
    }

    bool is_valid_vertical(vector<vector<bool>> matrix)
    {
        bool ret = true;

        for(int i = 0; i < matrix[0].size(); i++)
        {
            int sum = vertical_sum(matrix, i);
            ret &= (sum <= 1);
        }

        return ret;
    }

    bool is_valid_diagonal(vector<vector<bool>> matrix) // it is '/'
    {
        bool ret = true;

        for(int i = 0; i < matrix.size()*2 - 1; i++)
        {
            int sum = diagonal_sum(matrix, i);
            ret &= (sum <= 1);
        }

        return ret;
    }

    bool is_valid_back_diagonal(vector<vector<bool>> matrix) // it is '\'
    {
        bool ret = true;

        for(int i = 0; i < matrix.size()*2 - 1; i++)
        {
            int sum = back_diagonal_sum(matrix, i);
            ret &= (sum <= 1);
        }

        return ret;
    }

    int vertical_sum(vector<vector<bool>> matrix, int index)
    {
        int sum = 0;

        for(int i = 0; i < matrix.size(); i++)
            sum += matrix[i][index];

        return sum;
    }

    int diagonal_sum(vector<vector<bool>> matrix, int index)
    {
        int sum = 0;
        pos pos = {0, 0};

        if(index <= matrix.size()-1)
        {
            index = matrix.size() - 1 - index;
            pos = {0, index};
        }
        else
        {
            index = index - (matrix.size() - 1);
            pos = {index, 0};
        }

        while(pos.x < matrix.size() && pos.y < matrix.size())
        {
            sum += matrix[pos.y][pos.x];
            pos.x += 1;
            pos.y += 1;
        }

        return sum;
    }

    int back_diagonal_sum(vector<vector<bool>> matrix, int index)
    {
        int sum = 0;
        pos pos = {0, 0};

        if(index <= matrix.size()-1)
        {
            index = index;
            pos = {index, 0};
        }
        else
        {
            index = index - (matrix.size() - 1);
            pos = {(int)matrix.size()-1, index};
        }

        while(pos.x >= 0 && pos.y < matrix.size())
        {
            sum += matrix[pos.y][pos.x];
            pos.x -= 1;
            pos.y += 1;
        }

        return sum;
    }
};

void bfs_test(int steps_to_shuffle = 2)
{
    chess_board cb;
    cb.set_board({
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0}
    });
    eight_queens_solver eqs;
    eqs.shuffle(cb, steps_to_shuffle);

    auto bfs_res = eqs.bfs_solve_for(cb);

    cout << "!!!!!SOURCE!!!!!" << endl;
    cb.print();

    cout << "!!!!!SOLVED!!!!!" << endl;
    bfs_res.print();

    cout << "steps to solve with BFS: " << eqs.bfs_counter << endl; 
}

void a_star_test(int steps_to_shuffle)
{
    chess_board cb;
    cb.set_board({
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0}
    });

    eight_queens_solver eqs;
    eqs.shuffle(cb, steps_to_shuffle);

    auto a_star_res = eqs.a_star_for(cb);

    cout << "!!!!!SOURCE!!!!!" << endl;
    cb.print();

    cout << "!!!!!SOLVED!!!!!" << endl;
    a_star_res.print();

    cout << "steps to solve with A*: " << eqs.a_star_couter << endl;
}

int main()
{
    srand(time(0));

    int max_steps = 3;
    for (int i = 1; i <= max_steps; i++)
    {
        bfs_test(i);
        a_star_test(i);
    }
}
