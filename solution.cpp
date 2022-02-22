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

/*takeways
  - you are playing many rounds of the game
    starting with different combinations
  - example: ++++
    - you flipped ++++ to --++,
      - from the opponent's pointof view he/she
        is playing a game starting with --++
        that's why we implement the recursive
        calls to simulate this
      - the opponent then flipped from --++
        to ----
      - you lost as nothing left to be flipped
    - move on to the next round; you flipped
      ++++ to +--+, and it continues

  - the exit condition for the recursive calls
    is that it will eventually running out of
    things to flip guaranteed

*/

bool Solution::canWin(string s)
{
  auto visited = unordered_set<string>();
  function<bool(string)> play = [&visited, &play](string x)
  {
    /* nothing to flip */
    if (x.size() < 2)
      return false;

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
        /* you won */
        if (!oppWon)
          return true;
        /* flip them back in case you need the next round */
        x[i] = x[i + 1] = '+';
      }
    }

    /* nothing left to flip */
    return false;
  };

  return play(s);
}
