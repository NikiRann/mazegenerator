Greetings! This is my maze generator. It uses a recursive backtracking algorithm to create the perfect maze.
The mazes which this algorithm create are perfect(with no loops) and they are basically a tree. 
Every maze starts in this format: 
-----------------------------------------
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
| # # # # # # # # # # # # # # # # # # # |
|#######################################|
-----------------------------------------
constructMaze() creates this basic format.
Every ' ' is an Node in a Graph and every # (without the diagonal ones) is a possible edge.
The algorithm is simillar to DFS, because it uses stack.
Then we call createRecursivePath() to create our beautifull maze.
 