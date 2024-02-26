# Nolan Cyr
## CS 2300 Module 2 Open-Ended Project – Subway Shuffle: A Randomized NYC Journey Pt 2

## Summary of Program
This is a game where a player is placed into a random NYC subway station,
and the objective is to reach another randomly given station.

Upon starting the game, the player is given their current station, and the `destination station`.
With this information, the player is given a choice between traveling on the uptown or downtown tracks.
Next, the player is asked how many stations they would like to advance,
and after a valid input is given, they're notified of the station they have arrived at.

This process is repeated until either:
1. The player reaches the `destination station`, to which they win the game!
2. The player accidentally passes the `destination station`, to which they lose.

**Classes:**

| Name          | Private Variables                                                                                       | Description                                                                                                                                                                              |
|---------------|---------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Train**     | `currentLine (enum)`, `direction (enum)`, `scheduledStops`, `currentStationIndex`, `express`, `numCars` | Manages a `Train` Object and its scheduled stops, and methods to advance through `Stations`. Includes an `enum Direction`, and the overloaded method `bool advanceStation()`.            |
| **Station**   | `id`, `name`, `transfers`, `borough (enum)`                                                             | Manages a `Station` Object that holds variables corresponding to strings in a `csv` file. Includes an `enum Borough`, a `getTextForEnum` method, and an overloaded `<<` (cout) operator. |
| **SubwayMap** | `allStations<Station>`                                                                                  | Reads a `.csv` file and inserts `stop_id`, `stop_name`, `transfers`, `borough` strings into a vector of `Station` Objects.                                                               |
| **Line**      | `LineName (enum)`                                                                                       | Common class for storing all of the different train lines as enums. Supports transfer logic.                                                                                             |

**Main:**

Acts as the "Driver" for the game.
Includes input validation for all questions, which has been extensively tested.
Also prints out a vertical ladder map of each `Station` on the `1 Train` at the start of the game.

## Future Work (From Module 1) ##

Obviously, with only one line and two directions,
the game is very simple assuming you refer to the map or have expert NYC subway knowledge. 

However, if you look in the `csv` directory,
you can see I have a second `.csv` file containing `Station` data for ALL NYC subway stations.
Notice that each `Station` also has a list of transfers to other train lines that you can reach,
meaning this file holds data for a **graph of the NYC subway system**. [All Stations CSV](./csv/all_stations.csv).

I realized this thanks to CS 2250 Computability & Complexity, which taught me how graphs are two-tuple data structures.

It will be interesting to see the game played out when I add the ability to transfer to other train lines at each station.

## Module 2 Additions ##

Although I have not implemented it into the main game yet,
I have added all the necessary methods with logic for verifying, and executing a successful transfer.

- `validTransfer()`: returns true or false if the users' requested LineName is at a specified Station
- `updateScheduledStops()`: calls the `updateStopsForLine()` method in `SubwayMap` to update the current Trains' `scheduledStops`.
- `transferToLine()`: updates the current Train objects' `LineName`, and `scheduledStops`.
- `updateStopsForLine()`: builds the correct path to a given `LineName`'s scheduledStops .csv file and returns it as a vector of Stations.

I had to refactor A LOT of my code from Module 1, as it was difficult organizing, passing, and updating variables that needed to be modified to complete a transfer. The most difficult task was probably designing the most efficent way to have my classses interact with one another without a circular dependency.

## Video Demonstrations ##

**[Input Validation](https://www.youtube.com/watch?v=8oJfOjqpsMM)**
> **Note:** I set hard coded values to make the demonstration as simple and understandable as possible. In the provided code, the two `Station` Objects are chosen at random.

****

**[Transferring Lines (Debugger)](https://www.youtube.com/watch?v=O2yxH51k6xI)**

In this demonstration video,
I step through the CLion debugger
showing how all the fields we need to update in a Train object to perform a successful transfer.
1. I set up some code in `main.cpp` to test the transfer to the `TWO_TRAIN` at 14th St
2. `transferToLine()` is called with the requested transfers' `LineName` and the Train's `currentStation`
3. `validTransfer()` returns `true`, as it finds the `TWO_LINE` in 14th st's vector of `LineName`s.
4. `updateScheduledStops()` is called and builds a `SubwayMap` to be passed into the `SubwayMap` class (for `Station` file handling).
5. `updateStopsForLine()` is called in `SubwayMap` and uses the requested `LineName` enum to build the path to the correct csv file (that holds the station data to that line). The standard pattern for the file names is: 

    `{LineName(str)}_stations.csv`

6. `transferToLine()` returns `true` in main, and we can see that the current Train objects' `scheduledStops<Station>` has been updated with all of the `TWO_TRAIN` station data, and we are at the same station still.


## Grade ##

At my Summer internship, they had me document my code on a separate webpage _Confluence_ (similar to Markdown format).
I decided to do a similar thing in my README above, as I feel like the separation makes the code less cluttered and more readable.
- Main Program Complexity (30)
- Testing Program (20)
- Has-A Relationships (80)
  - **Train** has-a `Line` and has-a `vector<Station>`
  - **Station** has-a `vector<Line>`
  - **SubwayMap** has-a `vector<Station>`
- File I/O (5)

**IMPORTANT:** Thinking I was in my M2OEP repository, I created a branch when I started major refactoring for my transfer functionality. 
I was however, in my M1OEP repositry, so I ended up merging that branch to M1OEP.
I was easily able to sync my M2OEP reposirory with those changes (as it was forked from M1),
I just don't want to get points off in case there's any confusion with the commit times/dates.

Therefore, my proposed grade for this Project is: **100**
