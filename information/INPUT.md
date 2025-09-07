# INPUT

The input to the program is provided through a set of structured text files. Each file contains specific game configuration data, such as the map layout for different transportation types, initial player setup, and available tickets. These input files allow the program to initialize the Scotland Yard game environment and simulate gameplay accordingly.

<br>

## Index
- [Taxi map](#taxi-map)
- [Bus map](#bus-map)
- [Underground map](#underground-map)
- [Ferry map](#ferry-map)
- [Number of positions](#number-of-positions)
- [General starting positions](#general-starting-positions)
- [Detective tickets](#detective-tickets)
- [Mr. X tickets](#mr-x-tickets)
- [Number of players](#number-of-players)
- [Mr. X starting position](#mr-x-starting-position)
- [Detectives starting positions](#detectives-starting-positions)

---

<br>

## Taxi map
### File
```
board-data/taxi_map.txt
```
### Purpose
Construct an undirected graph that models the available taxi connections.
### Format
Each line contains two integers: the starting position and the ending position of a connection.
The values are separated by a space.

```
[origin] [destination]
```

Example:
```
1 9
2 10
134 127
```

## Bus map
### File
```
board-data/bus_map.txt
```
### Purpose
Construct an undirected graph that models the available bus connections.
### Format
Each line contains two integers: the starting position and the ending position of a connection.
The values are separated by a space.

```
[origin] [destination]
```

Example:
```
23 3
46 1
191 165
```

## Underground map
### File
```
board-data/underground_map.txt
```
### Purpose
Construct an undirected graph that models the available underground connections.
### Format
Each line contains two integers: the starting position and the ending position of a connection.
The values are separated by a space.

```
[origin] [destination]
```

Example:
```
89 13
93 79
111 153
```

## Ferry map
### File
```
board-data/ferry_map.txt
```
### Purpose
Construct an undirected graph that models the available ferry connections.
### Format
Each line contains two integers: the starting position and the ending position of a connection.
The values are separated by a space.

```
[origin] [destination]
```

Example:
```
115 157
157 115
157 194
```

## Number of positions
### File
```
board-data/num_of_positions.txt
```
### Purpose
Define the total number of locations (positions) on the map.
### Format
Single line with an integer.

```
[locations]
```

Example:
```
199
```

## General starting positions
### File
```
board-data/general_starting_positions.txt
```
### Purpose
List the possible starting positions for Mr. X and detectives.
### Format
Each line contains a single integer representing one starting position.

```
[position]
```

Example:
```
13
34
103
```

## Detective tickets
### File
```
game-data/detective_tickets.txt
```
### Purpose
Specify how many tickets each detective gets for each transportation type.
### Format
Each line contains a single integer representing the number of tickets available for a specified mode of transport.

```
[taxi tickets]
[bus tickets]
[underground tickets]
```

Example:
```
10
8
4
```

## Mr. X tickets
### File
```
game-data/mr_x_tickets.txt
```
### Purpose
Specify how many tickets Mr. X gets for each transportation type.
### Format
Each line contains a single integer representing the number of tickets available for a specified mode of transport.

```
[taxi tickets]
[bus tickets]
[underground tickets]
[black tickets]
[double move tickets]
```

Example:
```
4
3
3
5
2
```

## Number of players
###
```
game-data/num_of_players.txt
```
### Purpose
Specify how many players are participating in the current game, including Mr. X.
### Format
Single line with an integer.

```
[players]
```

Example:
```
6
```

## Mr. X starting position
### File
```
game-data/mr_x_starting_position.txt
```
### Purpose
Define the starting position of Mr. X in the current game.
### Format
Single line with an integer.

```
[position]
```

Example:
```
13
```

## Detectives starting positions
### File
```
game-data/detectives_starting_positions.txt
```
### Purpose
List the starting positions of the detectives in the current game.
### Format
Each line contains a single integer representing one starting position.

```
[position]
```

Example:
```
13
117
197
```
