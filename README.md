## Advent of Code 2023 Solutions

Each day is contained in a separate folder.
I write C++ solutions for speed (to attempt to make it on the leaderboard). I won't try to clean up these solutions; they may contain debug output and other nonsense. They can be compiled with the Makefile in each folder.

(Note: I use `g++-13` as my compiler; you can change this by updating the `CC` variable in the Makefile.
 Note that I use the `<bits/stdc++.h>` header which is not available with all C++ compilers.)

I will also try to write some cleaner solutions in other languages.
Currently I'm trying to use Haskell; these solutions can be run using `cabal run Day{X} < input` in the root directory.

Per the creator's request, problem inputs will not be uploaded.
Unless otherwise specified, programs read from standard input and print to standard output.

| Day  | Time (Part 1 / 2)    | Rank          |
|------|----------------------|---------------|
|  1   | 00:02:08 / 00:07:42  |  250 /   149  | 
|  2   | 00:07:41 / 00:10:48  |  655 /   659  |
|  3   | 00:05:58 / 00:08:53  |   49 /    26  |
|  4   | 00:03:56 / 00:06:57  |  329 /    86  |
|  5   | 00:17:53 / 00:56:07  | 1032 /  1238  |
|  6   | 00:03:11 / 00:06:50  |  102 /   354  |
|  7   | 00:14:08 / 00:28:48  |  333 /   726  |
|  8   | 00:02:53 / 00:56:12  |   35 /  4397  |
|  9   | 00:05:44 / 00:06:52  |  295 /   191  |
| 10   | 00:19:42 / 01:18:53  |  539 /  1200  |
| 11   | 00:20:03 / 00:25:35  | 2098 /  1611  |
| 12   | 00:07:28 / 00:23:23  |   71 /   107  |
| 13   | 00:11:08 / 00:34:54  |  216 /  1275  |
| 14   | 00:02:08 / 00:07:42  |   91 /    27  |
| 15   | 00:04:41 / 00:15:53  | 1051 /   461  |
| 16   | 00:13:36 / 00:16:40  |  202 /   145  |
| 17   | 00:12:29 / 00:20:38  |   76 /   113  |
| 18   | 00:17:10 / 01:35:08  |  585 /  1988  |
| 19   | 00:28:14 / 01:03:55  | 1456 / 10557  |
| 20   | 00:26:14 / 01:10:31  |  147 /   564  |
| 21   | 00:04:26 / 02:49:16  |   77 /  1273  |
| 22   | 00:18:51 / 00:23:52  |   70 /    41  |
| 23   | 00:28:24 / 01:24:22  | 1106 /   883  |
| 24   | 00:15:43 / 01:22:42  |   93 /   283  |
| 25   | 00:22:54 / 00:22:58  |  435 /   376  |

Total points: 470

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

### Day 11 (Cosmic Expansion)

For some reason, I decided the best way to approach part 1 was to literally add rows and columns to the grid (perhaps influenced by the previous day's problem).
Then, I started to code a BFS instead of just computing the Manhattan distances directly.
When I got to part 2, I realized the intended solution was far simpler than what I did, so I rewrote my code to use the intended method.
This was a pretty easy one, but I wasn't thinking straight and missed the simple and obvious way to do it.

### Day 12 (Hot Springs)

I recognized that this could be solved with a DP, but for part 1 I saw that the strings were at most length 20 or so and figured a brute force approach would be faster to code.
For part 2, we have to do a DP with a state that store information like the current positions in the string/list of runs, and also the length of our current run.
The bounds are pretty loose, so anything along these lines should easily pass (for instance, I initially had an extra state signalling whether the previous character was a # or not.)

### Day 13 (Point of Incidence)

This was a pretty easy problem that I managed to bungle due to poor reading comprehension/silly mistakes.
First, I didn't understand how to summarize the answer--I thought we were asked to just count the number of column / row reflections, instead of assuming that there would be a unique column / row reflection.

Second, I didn't catch the uniqueness guarantees for part 2. Apparently, there exists a unique square such that if we flip it, there is a unique new reflection line (however, the old reflection line *may or may not* still exist).

Overall, the problem is not bad, but I wasn't expecting some of these odd constraints and skipped/misread them on my first pass through.

### Day 14 (Parabolic Reflector Dish)

Another 2d grid problem...this one was mostly just following directions and trying not to misread what is the new weird summary statistic to output.
Really not much to say about this one, I placed surprisingly high on part 2 despite getting WA initially and having to wait a minute to submit again.
Advent of Code seems to quite like these cycle detection problems, where I am particularly prone to off-by-one errors.

### Day 16 (The Floor Will Be Lava)

Another day yet ANOTHER 2d grid problem. When I looked at the input I immediately knew it was either some plinko simulation/mirror simulation.
This is just a straightforward BFS.
I wasn't fast enough to rank in the top 100, but I didn't make any major mistakes, just implementation was a bit slow.
I conjectured that I didn't actually need to check that the initial direction was facing the correct way. This turned out to be true, thought I'm not immediately sure why this is the case.

### Day 17 (Clumsy Crucible)

This year is just all grid problems, apparently.
This is a plain single-source shortest paths problem (there was a very similar one last year, iirc).
The main decision I made was whether to use my normal Dijkstra's template, which would require me to map my state pairs to indices, or adapt it to return a multidimensional distance array. I decided on the latter.
I was a bit annoyed that I made multiple different off-by-one errors; initially, I missed the condition that the first square *doesn't* count towards the total, and in part 2, my answer was off by one because I didn't realize the first square also doesn't count towards your current direction streak (which I also misread on part 1, but apparently didn't affect my answer).

### Day 20 (Pulse Propagation)

For some reason I had a very difficult time understanding the problem statement and had to read the same paragraph multiple times.
As it turns out, I completely misunderstood the order of the pulses, which are supposed to be processed in a BFS-style rather than DFS.
Somehow, this did not affect my answer for part 1, but this did bungle some of my cycle calculations (but only two of them, for some reason).

### Day 22 (Sand Slabs)
A 3-dimensional problem that is not too bad.
We can simulate the falling bricks by processing them in increasing order of z.
A brick is the sole supporter of another brick if the former is the only brick at the z-coordinate right below the latter that is in the latters (x, y) rectangle.
For part 2, we need to construct a directed graph of all supporting bricks and run topsort.

### Day 25 (Snowverload)

A surprisingly simple graph problem to end the year.
I didn't realize this was a min cut problem at all.
Instead, I brute forced removing two edges and checked if the resulting graph is not biconnected (has a bridge).
This took a few minutes to run, but coupled with a couple silly bugs, I didn't complete it nearly close enough for the leaderboard.
For fun I implemented a min-cut solution using Karger's algorithm.
