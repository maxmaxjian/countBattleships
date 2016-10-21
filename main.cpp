#include <iostream>
#include <vector>
#include <stack>
#include <iterator>

class solution {
  public:
    int countBattleships(std::vector<std::vector<char>> & board) {
        using std::vector;
        using std::pair;
        vector<vector<pair<size_t,size_t>>> ships;
        vector<vector<int>> visited(board.size(), vector<int>(board[0].size()));
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                if (board[i][j] == 'x' && visited[i][j] == 0) {
                    visited[i][j] = 1;
                    auto ship = getShip(board, std::make_pair(i,j), visited);
                    ships.push_back(ship);
                    for (auto p : ship) {
                        std::cout << "(" << p.first << "," << p.second << ")";
                        visited[p.first][p.second] = 1;
                    }
                    std::cout << std::endl;
                }
            }
        }

        return ships.size();
    }

  private:
    std::vector<std::pair<size_t,size_t>> getShip(std::vector<std::vector<char>> & board, const std::pair<size_t,size_t> & begin, const std::vector<std::vector<int>> & visited) {
        using pos = std::pair<size_t,size_t>;
        using std::vector;
        
        vector<pos> ship;
        std::stack<std::pair<pos,vector<vector<int>>>> st;
        st.push(std::make_pair(begin, visited));
        while (!st.empty()) {
            vector<pos> vec;
            std::stack<std::pair<pos,vector<vector<int>>>> temp;
            while (!st.empty()) {
                auto curr = st.top();
                st.pop();
                vec.push_back(curr.first);
                auto next = getNext(board, curr.first, curr.second);
                for (auto nx : next) {
                    auto cpy = curr.second;
                    cpy[nx.first][nx.second] = 1;
                    temp.push(std::make_pair(nx, cpy));
                }
            }
            std::copy(vec.begin(), vec.end(), std::inserter(ship, ship.end()));
            st = temp;
        }
        
        return ship;
    }

    std::vector<std::pair<size_t,size_t>> getNext(std::vector<std::vector<char>> & board, const std::pair<size_t,size_t> & p, const std::vector<std::vector<int>> & visited) {
        using std::vector;
        using std::pair;
        vector<pair<size_t,size_t>> next;
        if (p.first > 0 && visited[p.first-1][p.second] == 0 && board[p.first-1][p.second] == 'x')
            next.push_back(std::make_pair(p.first-1,p.second));
        if (p.first < board.size()-1 && visited[p.first+1][p.second] == 0 && board[p.first+1][p.second] == 'x')
            next.push_back(std::make_pair(p.first+1,p.second));
        if (p.second > 0 && visited[p.first][p.second-1] == 0 && board[p.first][p.second-1] == 'x')
            next.push_back(std::make_pair(p.first,p.second-1));
        if (p.second < board[0].size()-1 && visited[p.first][p.second+1] == 0 && board[p.first][p.second+1] == 'x')
            next.push_back(std::make_pair(p.first,p.second+1));
        return next;
    }
};

int main() {
    std::vector<std::vector<char>> board{
        {'x','.','.','x'},
        {'.','x','.','x'},
        {'.','x','.','x'}
    };

    solution soln;
    int numShips = soln.countBattleships(board);
    std::cout << "The total number of battleships is:\n"
              << numShips << std::endl;
}
