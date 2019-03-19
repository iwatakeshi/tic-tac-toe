#ifndef TIC_TAC_TOE_GAME_BOARD_HPP
#define TIC_TAC_TOE_GAME_BOARD_HPP
#include "player.hpp"
#include <matrix.hpp>

namespace tictactoe {
enum board_state {
  no_player = -1,
  player_x = 1,
  player_o = 0
};

class game_board {
  stdlib::matrix<int> board_;

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
  const stdlib::array<int>& operator[](const int& index) const {
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
} // tictactoe

#endif