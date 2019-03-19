#include <iostream>
#include <matrix.hpp>
#include <string>
#include <utility>
#ifdef __cplusplus__
#include <cstdlib>
#else
#include <stdlib.h>
#endif
using namespace stdlib;

enum player {
  x = 1,
  o = 0
};

enum board_state {
  no_player = -1,
  player_x = 1,
  player_o = 0
};

class game_board {
  matrix<int> board_;

  public:
  game_board() :
      board_(3, 3) {
    for (auto i = 0; i < 3; i++) {
      for (auto j = 0; j < 3; j++) {
        board_[i][j] = board_state::no_player;
      }
    }
  }

  friend class game_logic;
  const array<int>& operator[](const int& index) const {
    return board_[index];
  }

  void update(int row, int column, player current_player) {
    if ((row >= 0 && row < 3) && (column >= 0 && column < 3)) {
      board_[row][column] = current_player;
    }
  }

  void render() {
    clear_screen();
    std::string space = "   ";
    int column_count = 1;
    for (auto row : board_) {
      std::cout << "|";

      for (auto column : row) {
        if (column == player::x) {
          std::cout << space << "x" << space;
        } else if (column == player::o) {
          std::cout << space << "o" << space;
        } else
          std::cout << space << " " << space;
        std::cout << "|";
      }
      if (column_count != 3) {
        std::cout << std::endl
                  << "---"
                  << "---"
                  << "---"
                  << "---"
                  << "---"
                  << "---"
                  << "---"
                  << "---";
      }

      std::cout << std::endl;
      column_count++;
    }
  }

  private:
  void clear_screen() {
    system("clear");
    // std::cout << std::string(100, '\n');
  }
};

class game_logic {

  public:
  std::pair<bool, int> check(const game_board& b) {

    // Check the rows horizontally
    for (auto row = 0; row < 3; row++) {
      if ((b[row][0] == b[row][1]) && (b[row][1] == b[row][2]) && (b[row][2] != board_state::no_player)) {
        return std::make_pair(true, b[row][0]);
      }
    }

    // Check the columns vertically
    for (auto col = 0; col < 3; col++) {
      if ((b[0][col] == b[1][col]) && (b[1][col] == b[2][col]) && (b[2][col] != board_state::no_player)) {
        return std::make_pair(true, b[0][col]);
      }
    }

    // Check the rows and columns diagnally
    if ((b[0][0] == b[1][1]) && (b[1][1] == b[2][2]) && (b[2][2] != board_state::no_player)) {
      return std::make_pair(true, b[0][0]);
    }

    if ((b[0][2] == b[1][1]) && (b[1][1] == b[2][0]) && (b[2][0] != board_state::no_player)) {
      return std::make_pair(true, b[0][2]);
    }

    return std::make_pair(false, -1);
  }
};

class game {
  private:
  game_board board_;
  game_logic logic_;
  int input_x;
  int input_y;
  bool player_x = true;

  public:
  game() {}
  void init() {
    board_.render();
    std::cout << "Enter the coordinate (x y) that you wish to make your mark" << std::endl;
    std::cout << "player " << (player_x ? "x" : "o") << " > ";
    while (true) {
      update();
      render();
    }
  }
  void update() {
    process_input();
    board_.update(input_x, input_y, (player_x ? player::x : player::o));
    auto result = logic_.check(board_);
    if (result.first == true) {
      std::cout << "player " << (result.second == player::x ? "x" : "o") << " won!" << std::endl;
      exit(0);
    }
    player_x = !player_x;
  }

  void render() {
    board_.render();
    std::cout << "player " << (player_x ? "x" : "o") << " > ";
  }

  private:
  void process_input() {
    std::cin >> input_x;
    std::cin >> input_y;
    if (input_x == -1 || input_y == -1) {
      exit(0);
    }
  }
};

int main() {
  game new_game;
  new_game.init();
  return 0;
}