#ifndef TIC_TAC_TOE_GAME_HPP
#define TIC_TAC_TOE_GAME_HPP
#include "game_board.hpp"
#include "game_logic.hpp"
#include "player.hpp"
#include <iostream>
#include <stdlib.h>

namespace tictactoe {
class game {
  private:
  game_board board_;
  game_logic logic_;
  int input_x;
  int input_y;
  bool player_x = true;

  public:
  game() {}
  void start() {
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
} // tictactoe

#endif