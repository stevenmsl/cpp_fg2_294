#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <functional>

using namespace sol294;
using namespace std;

bool Solution::canWin(string s)
{
  auto visited = unordered_map<string, bool>(false);
  function<bool(string)> play = [&visited, &play](string x)
  {
    if (x.size() < 2)
      return false;
    if (visited.count(x))
      return visited[x];
    /* play flip games
       - flipping two positions at a time and pass
         the resulting string down to the subsequent
         recursive calls
       - once returned from the recursive calls, undo
         the flipping to get ready for the next round
       - example ++++
         - round 1 --++ -> ---- (won't win)
         - round 2 +--+ -> +--+ (win, as the opponent can't flip)
         - round 3 (don't need this as we have found the answer)
    */
    for (auto i = 0; i < x.size() - 1; i++)
    {
      if (x[i] == '+' && x[i + 1] == '+')
      {
        /* flip them! */
        x[i] = x[i + 1] = '-';
        /* opponent's turn */
        auto oppWon = play(x);
        visited[x] = !oppWon;
        /* you won */
        if (visited[x])
          return visited[x];
        /* flip them back in case you need the next round */
        x[i] = x[i + 1] = '+';
      }
    }

    /* nothing left to flip */
    visited[x] = false;

    return false;
  };

  return play(s);
}
