## Advent of Code 2023 Solutions

Each day is contained in a separate folder.
I write C++ solutions for speed (to attempt to make it on the leaderboard). I won't try to clean up these solutions; they may contain debug output and other nonsense. They can be compiled with the Makefile in each folder.

I will also try to write some cleaner solutions in other languages.
Currently I'm trying to use Haskell; these solutions can be run using `cabal run Day{X} < input` in the root directory.

Per the creator's request, problem inputs will not be uploaded.
Unless otherwise specified, programs read from standard input and print to standard output.

| Day  | Time (Part 1 / 2)    | Rank          |
|------|----------------------|---------------|
|  1   | 00:02:08 / 00:07:42  |  250 /  149   | 
|  2   | 00:07:41 / 00:10:48  |  655 /  659   |
|  3   | 00:05:58 / 00:08:53  |   49 /   26   |
|  4   | 00:03:56 / 00:06:57  |  329 /   86   |
|  5   | 00:17:53 / 00:56:07  | 1032 / 1238   |
|  6   | 00:03:11 / 00:06:50  |  102 /  354   |
|  7   | 00:14:08 / 00:28:48  |  333 /  726   |
|  8   | 00:02:53 / 00:56:12  |   35 / 4397   |
|  9   | 00:05:44 / 00:06:52  |  295 /  191   |
| 10   | 00:19:42 / 01:18:53  |  539 / 1200   |

### Day 7 (Camel Cards)

This was a pretty straightforward implementation exercise, and evaluating poker hands is a common task.
Unfortunately, I had some WAs on part 1 due to forgetting to add the full house case.

For part 2, I first thought I could separately count the number of jokers and do some casework to determine what is the best possible hand.
However, I decided this was too error-prone. Instead, I used the observation that it's always optimal to convert a J into one of your non-J cards already in your hand (modulo the case where you have 5 J's, in which case this is a five of a kind). Thus, we can generate a list of possible hands formed by replacing each J with another card.
The worst case is when we have 2 J's and 3 distinct non-J's, for a total of 9 possible hands to check.

[Actually, we don't even need to enumerate these different hands, a greedy strategy of assigning J's is always optimal.]

### Day 8 (Haunted Wasteland)

Part 1 is a quick implementation exercise.

Part 2 seems nearly intractable in the general case. After sitting for a while being confused why the problem was so hard, I looked at the inputs and discovered there were only 6 "A"-rooms, and their paths/cycles were disjoint, and only contained one "Z"-room, *and* the lengths of the cycles are equal to the distance to the "Z"-room!
Therefore the problem reduces to a CRT problem, which itself degenerates to an LCM calculation.

### Day 9 (Mirage Maintenance)

This was a pretty straightforward problem. Unfortunately my performance was hindered by my slow typing today.
I was also unsure how to handle a case where the list would become empty before we hit all zeros (e.g, `1 2`), but I eventually assumed this wouldn't be a problem and chugged on.

