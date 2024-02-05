# Nolan Cyr
## CS 2300 Module 1 Open-Ended Project – Subway Shuffle: A Randomized NYC Journey

## Summary of Program
This is a game where a player is placed into a random NYC subway station,
and the objective is to reach another random station.

Upon starting the game, the player is given their current station, and the `destination station`.
With this information, the player is given a choice between traveling on the uptown, or downtown tracks.
Next, the player is asked how many stations they would like to advance,
and after a valid input is given, the station they are now at.

This process is repeated until either:
1. The player reaches the `destination station`, to which they win the game!
2. The player accidentally passes the `destination station`, to which they lose.

Currently, I only have complete support on the `1 Train`, and plan to add the rest of the system in future modules.
The `1 Train` has 39 stations. [Link to CSV](/Users/nolancyr/Desktop/CS 2300/Module 1/M1OEP-ncyr1/csv/one_line_stations.csv).

**Classes:**

| Name          | Private Variables                                                                             | Description                                                                                                                                                                              |
|---------------|-----------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Train**     | `lineName`, `direction (enum)`, `scheduledStops`, `currentStationIndex`, `express`, `numCars` | Manages a `Train` Object and its scheduled stops, and methods to advance through `Stations`. Includes an `enum Direction`, and the overloaded method `bool advanceStation()`.            |
| **Station**   | `id`, `name`, `transfers`, `borough (enum)`                                                   | Manages a `Station` Object that holds variables corresponding to strings in a `csv` file. Includes an `enum Borough`, a `getTextForEnum` method, and an overloaded `<<` (cout) operator. |
| **SubwayMap** | `allStations<Station>`                                                                        | Reads a `.csv` file and inserts `stop_id`, `stop_name`, `transfers`, `borough` strings into a vector of `Station` Objects.                                                               |

**Main:**

Acts as the "Driver" for the game.
Includes input validation for all questions, which has been extensively tested.
Also prints out a vertical ladder map of each `Station` on the `1 Train` at the start of the game.

## Future Work ##

Obviously, with only one line and two directions,
the game is very simple assuming you refer to the map or have expert NYC subway knowledge. 

However, if you look in the `csv` directory,
you can see I have a second `.csv` file containing `Station` data for ALL NYC subway stations.
Notice that each `Station` also has a list of transfers to other train lines that you can reach,
meaning this file holds data for a **graph of the NYC subway system**. [All Stations CSV](/Users/nolancyr/Desktop/CS 2300/Module 1/M1OEP-ncyr1/csv/nyc_stations.csv).

I realized this thanks to CS 2250 Computability & Complexity, which taught me how graphs are two-tuple data structures.

It will be interesting to see the game played out when I add the ability to transfer to other train lines at each station.

## Video Demonstration ##

**[YouTube Link](https://www.youtube.com/watch?v=8oJfOjqpsMM)**
> **Note:** I set hard coded values to make the demonstration as simple and understandable as possible. In the provided code, the two `Station` Objects are chosen at random.


## Grade ##

At my Summer internship, they had me document my code on a separate webpage _Confluence_ (similar to Markdown format).
I decided to do a similar thing in my README above, as I feel like the separation makes the code less cluttered and more readable.
- 3 Classes (60)
- Main Program Complexity (40)
- 2 Enumerated Types (10)
- 1 Overloaded Operator (5)
- 1 Overloaded Method (5)

Therefore, my proposed grade for this Project is: **100**
