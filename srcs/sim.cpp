/*
sim.cc

Compile:
  g++ sim.cc -std=c++11 -lpheval -O3 -o sim -IPokerHandEvaluator/cpp/include -LPokerHandEvaluator/cpp/build
  ./sim

Run: (all arguments are optional, defaults to 9 player full runouts)  
  ./sim [number of other players 1-8] [cards on the board 3-5] [top % highlighted] [number of runouts per hand]
e.g.
  ./sim 5 3 10 1000
  plays out 6 handed, just the flop, highlights the top 10% of hands, only runs 1000 simulations per hand (1M is better, but takes longer)

*/
#include <cassert>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <phevaluator/phevaluator.h>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <tuple>

using namespace phevaluator;
static std::vector<int> in;

#define ITERS 10000

const std::unordered_map<int, char> rankMap = {
    {0, '2'}, {1, '3'}, {2, '4'}, {3, '5'},  {4, '6'},  {5, '7'},  {6, '8'},
    {7, '9'}, {8, 'T'}, {9, 'J'}, {10, 'Q'}, {11, 'K'}, {12, 'A'},
};
const std::unordered_map<int, char> suitMap = {
    {0, 'C'},
    {1, 'D'},
    {2, 'H'},
    {3, 'S'},
};

int hand_strength_sim(int argc, char **argv)
{
  for (auto i = 0; i < 52; ++i) {
    in.emplace_back(i);
  }
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, 51); // define the range

  auto gen_rollout = [&](int hole0, int hole1, int other_players,
                         int cards_on_board) -> bool {
    std::vector<int> villains;
    villains.reserve(other_players * 2);
    std::vector<int> board;
    board.reserve(cards_on_board);

    std::vector<int> out;
    auto gen_card = [&]() {
      auto card = 52;
      bool valid = false;
      while (!valid) {
        card = distr(gen);
        if (card == hole0) {
          continue;
        }
        if (card == hole1) {
          continue;
        }
        bool match = false;
        for (auto v : villains) {
          if (card == v) {
            match = true;
            break;
          }
        }
        if (match) {
          continue;
        }
        for (auto v : board) {
          if (card == v) {
            match = true;
            break;
          }
        }
        if (match) {
          continue;
        }
        break;
      }
      assert(card < 52);
      assert(card >= 0);
      return card;
    };

    for (auto v = 0; v < other_players * 2; ++v) {
      villains.emplace_back(gen_card());
    }

    for (auto b = 0; b < cards_on_board; ++b) {
      board.emplace_back(gen_card());
    }

    Rank h;
    if (cards_on_board == 5) {
      h = EvaluateCards(hole0, hole1, board[0], board[1], board[2], board[3],
                        board[4]);
    } else if (cards_on_board == 4) {
      h = EvaluateCards(hole0, hole1, board[0], board[1], board[2], board[3]);
    } else if (cards_on_board == 3) {
      h = EvaluateCards(hole0, hole1, board[0], board[1], board[2]);
    } else {
      throw std::exception();
    }
    for (auto v = 0; v < other_players; ++v) {
      Rank vh;
      if (cards_on_board == 5) {
        vh = EvaluateCards(villains[v * 2], villains[v * 2 + 1], board[0],
                           board[1], board[2], board[3], board[4]);
      } else if (cards_on_board == 4) {
        vh = EvaluateCards(villains[v * 2], villains[v * 2 + 1], board[0],
                           board[1], board[2], board[3]);
      } else if (cards_on_board == 3) {
        vh = EvaluateCards(villains[v * 2], villains[v * 2 + 1], board[0],
                           board[1], board[2]);
      }
      if (vh.value() < h.value()) {
        return false;
      }
    }

    return true;
  };

  size_t iters = ITERS;
  if (argc > 4) {
    iters = std::atoi(argv[4]);
  }

  int cards_on_board = 5;
  if (argc > 2) {
    cards_on_board = std::atoi(argv[2]);
  }

  auto get_pct = [&](int h0, int h1, int num_players) {
    float wins = 0;
    for (size_t i = 0; i < iters; ++i) {
      wins += gen_rollout(h0, h1, num_players, cards_on_board);
    }
    return wins / iters;
  };

  int num_players = 8;
  if (argc > 1) {
    num_players = std::atoi(argv[1]);
  }

  int top_pct = 100;
  if (argc > 3) {
    top_pct = std::atoi(argv[3]);
  }
  std::cout << "% winning for " << num_players + 1 << " players after "
            << cards_on_board << " cards dealt (" << iters
            << " simulations per hand)" << std::flush;
  if (top_pct < 100) {
    std::cout << ", highlighting top " << top_pct << "%"
              << " of hands" << std::flush;
  }

  auto pct_to_color = [&](float pct, float mean, float stddev) {
    std::stringstream ss;
    auto diff = pct - mean;
    auto scaled_diff = std::abs(diff) / stddev;
    auto rb = std::max((int)(255 - scaled_diff / 1.5 * 255), 0);
    if (std::abs(diff) < 0.001) {
      ss << "\033[38;2;255;255;255m";
    } else if (diff < 0) {
      ss << "\033[38;2;255;" << rb << ";" << rb << "m";
    } else {
      ss << "\033[38;2;" << rb << ";255;" << rb << "m";
    }
    return ss.str();
  };

  std::cout << std::fixed;
  std::cout << std::setprecision(0);
  std::unordered_map<int, float> winning_pct;
  for (auto c0 = 12; c0 >= 0; --c0) {
    for (auto c1 = 12; c1 >= 0; --c1) {
      auto s0 = 0;
      auto s1 = 1;
      if (c0 > c1) {
        s1 = 0;
      }
      auto h0 = c0 * 4 + s0;
      auto h1 = c1 * 4 + s1;
      auto pct = get_pct(h0, h1, num_players);
      auto idx = h0 * 52 + h1;
      winning_pct[idx] = pct;
    }
    std::cout << "." << std::flush;
  }
  std::cout << "\n";

  float total = 0;
  for (auto &p : winning_pct) {
    total += p.second;
  }
  float mean = total / winning_pct.size();
  float sq_total = 0;
  for (auto &p : winning_pct) {
    auto o = (p.second - mean);
    sq_total += o * o;
  }
  float std = std::sqrt(sq_total / winning_pct.size());

  auto inTop = [&](float pct) {
    auto num_above = 0;
    for (auto &p : winning_pct) {
      if (p.second > pct) {
        num_above++;
      }
    }
    return ((float)num_above / (13 * 13) * 100) < top_pct;
  };

  for (auto c0 = 12; c0 >= 0; --c0) {
    for (auto c1 = 12; c1 >= 0; --c1) {
      auto s0 = 0;
      auto s1 = 1;
      if (c0 > c1) {
        s1 = 0;
      }
      auto h0 = c0 * 4 + s0;
      auto h1 = c1 * 4 + s1;
      auto idx = h0 * 52 + h1;
      auto pct = winning_pct.at(idx);

      if (!inTop(pct)) {
        std::cout << "\033[38;2;50;50;50m";
      }
      if (c0 > c1) {
        std::cout << rankMap.at(c0) << rankMap.at(c1) << "s ";
      } else if (c1 > c0) {
        std::cout << rankMap.at(c0) << rankMap.at(c1) << "o ";
      } else {
        std::cout << rankMap.at(c0) << rankMap.at(c1) << "  ";
      }
      std::cout << "\033[0m";

      std::cout << pct_to_color(pct, mean, std);
      std::cout << std::setfill(' ') << std::setw(2) << 100 * pct << "% ";
      std::cout << "\033[0m";
    }
    std::cout << "\n";
  }
  return 0;
}
