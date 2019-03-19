#ifndef TIC_TAC_TOE_GAME_LOGIC_HPP
#define TIC_TAC_TOE_GAME_LOGIC_HPP
#include "game_board.hpp"
#include <utility>
namespace tictactoe {
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

}
#endif