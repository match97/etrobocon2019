/**
 *  @file   Instructions.cpp
 *  @brief  ブロックビンゴに使用するクラス
 *  @author Oiwane
 */
#include "Instructions.h"

Instructions::Instructions()
{
  mp['a'] = Order::ENTER_BINGO_AREA_L4;
  mp['b'] = Order::ENTER_BINGO_AREA_L6;
  mp['c'] = Order::STRAIGHT;
  mp['d'] = Order::SPIN_RIGHT;
  mp['e'] = Order::SPIN_LEFT;
  mp['f'] = Order::SPIN180;
  mp['g'] = Order::PUT;

  mp['h'] = Order::STRAIGHT_DETOUR_RIGHT;
  mp['i'] = Order::STRAIGHT_DETOUR_LEFT;
  mp['j'] = Order::TURN_RIGHT90_EXIST_BLOCK;
  mp['k'] = Order::TURN_RIGHT90_UNEXIST_BLOCK;
  mp['l'] = Order::TURN_LEFT90_EXIST_BLOCK;
  mp['m'] = Order::TURN_LEFT90_UNEXIST_BLOCK;
  mp['n'] = Order::TURN180;
  mp['o'] = Order::TURN180_DETOUR_RIGHT;
  mp['p'] = Order::TURN180_DETOUR_LEFT;

  mp['q'] = Order::SPIN_RIGHT45;
  mp['r'] = Order::SPIN_LEFT45;
  mp['s'] = Order::SPIN_RIGHT135;
  mp['t'] = Order::SPIN_LEFT135;
  mp['u'] = Order::MOVE_NODE;
  mp['v'] = Order::MOVE_DIAGONAL;
}

Order Instructions::translate(char key)
{
  decltype(mp)::iterator it = mp.find(key);

  return it->second;
}