
# Nolan Cyr<br padding="-10px">
****
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

## Subway Game Classes

### Train
Manages a Train object and its scheduled stops.

#### Private Variables:
| Name                                                                | Description                                                       |
|---------------------------------------------------------------------|-------------------------------------------------------------------|
| <span style="color:#C586C0">`LineName currentLine`</span>           | Current subway line of the Train.                                 |
| <span style="color:#C586C0">`Direction direction`</span>            | Direction of the Train (Queensbound, Manhattanbound, Bronxbound). |
| <span style="color:#C586C0">`vector<Station> scheduledStops`</span> | Vector of stations representing scheduled stops.                  |
| <span style="color:#C586C0">`int currentStationIndex`</span>        | Index of the current station in the scheduled stops vector.       |
| <span style="color:#C586C0">`bool express`</span>                   | Indicates whether the Train is an express train or not.           |
| <span style="color:#C586C0">`int numCars`</span>                    | Number of cars in the Train.                                      |

#### Public Methods:
| Method                                                                                             | Description                                                            |
|----------------------------------------------------------------------------------------------------|------------------------------------------------------------------------|
| <span style="color:#569CD6">`LineName getName()`</span>                                            | Retrieves the current line of the Train.                               |
| <span style="color:#569CD6">`void setName(LineName newLineName)`</span>                            | Sets the current line of the Train.                                    |
| <span style="color:#569CD6">`Direction getDirection()`</span>                                      | Retrieves the direction of the Train.                                  |
| <span style="color:#569CD6">`void setDirection(Direction newDirection)`</span>                     | Sets the direction of the Train.                                       |
| <span style="color:#569CD6">`bool transferToLine(LineName newLine, Station currentStation)`</span> | Attempts to transfer the Train to a different line at a given station. |
| <span style="color:#569CD6">`void updateScheduledStops(LineName line)`</span>                      | Updates the scheduled stops based on the specified subway line.        |
| <span style="color:#569CD6">`vector<Station> getScheduledStops()`</span>                           | Retrieves the scheduled stops of the Train.                            |
| <span style="color:#569CD6">`void addScheduledStop(Station newStop)`</span>                        | Adds a station to the scheduled stops of the Train.                    |
| <span style="color:#569CD6">`Station getCurrentStation()`</span>                                   | Retrieves the current station of the Train.                            |
| <span style="color:#569CD6">`Station getNextStation()`</span>                                      | Retrieves the next station of the Train.                               |
| <span style="color:#569CD6">`int getCurrentStationIndex()`</span>                                  | Retrieves the index of the current station.                            |
| <span style="color:#569CD6">`void setCurrentStation(int stationIndex)`</span>                      | Sets the current station of the Train using an index.                  |
| <span style="color:#569CD6">`void setCurrentStation(string stationName)`</span>                    | Sets the current station of the Train using a station name.            |
| <span style="color:#569CD6">`bool advanceStation()`</span>                                         | Advances the Train to the next station.                                |
| <span style="color:#569CD6">`bool advanceStation(int numStations)`</span>                          | Advances the Train by a specified number of stations.                  |
| <span style="color:#569CD6">`bool isExpress()`</span>                                              | Checks if the Train is an express train.                               |
| <span style="color:#569CD6">`void setExpress(bool isExpress)`</span>                               | Sets whether the Train is an express train or not.                     |
| <span style="color:#569CD6">`int getNumCars()`</span>                                              | Retrieves the number of cars in the Train.                             |
| <span style="color:#569CD6">`void setNumCars(int newNumCars)`</span>                               | Sets the number of cars in the Train.                                  |

****

### Station
Represents a subway station in the game.

#### Private Variables:
| Name                                                            | Description                                                 |
|-----------------------------------------------------------------|-------------------------------------------------------------|
| <span style="color:#C586C0">`string id`</span>                  | Identifier for the Station.                                 |
| <span style="color:#C586C0">`string name`</span>                | Name of the Station.                                        |
| <span style="color:#C586C0">`vector<LineName> transfers`</span> | List of subway lines available for transfer at the Station. |
| <span style="color:#C586C0">`Borough borough`</span>            | Borough where the Station is located.                       |

#### Public Methods:
| Method                                                                       | Description                                                               |
|------------------------------------------------------------------------------|---------------------------------------------------------------------------|
| <span style="color:#569CD6">`string getId()`</span>                          | Retrieves the ID of the Station.                                          |
| <span style="color:#569CD6">`void setId(string newId)`</span>                | Sets the ID of the Station.                                               |
| <span style="color:#569CD6">`string getName()`</span>                        | Retrieves the name of the Station.                                        |
| <span style="color:#569CD6">`void setName(string newName)`</span>            | Sets the name of the Station.                                             |
| <span style="color:#569CD6">`vector<LineName> getTransfers()`</span>         | Retrieves the list of subway lines available for transfer at the Station. |
| <span style="color:#569CD6">`void addTransfers(LineName newTransfer)`</span> | Adds a subway line to the list of available transfers at the Station.     |
| <span style="color:#569CD6">`Borough getBorough()`</span>                    | Retrieves the borough of the Station.                                     |
| <span style="color:#569CD6">`void setBorough(Borough newBorough)`</span>     | Sets the borough of the Station.                                          |
| <span style="color:#569CD6">`string getTextForEnum(int enumVal)`</span>      | Retrieves the string representation of a Borough enum value.              |

#### Friend Overloaded Operator:
| Operator                                                                                | Description                                                         |
|-----------------------------------------------------------------------------------------|---------------------------------------------------------------------|
| <span style="color:#569CD6">`ostream& operator<<(ostream& str, Station station)`</span> | Overloaded insertion operator to output Station details to ostream. |

****

### Line
Handles the different subway lines in the game.

#### Public Methods:
| Method                                                                         | Description                                                   |
|--------------------------------------------------------------------------------|---------------------------------------------------------------|
| <span style="color:#569CD6">`static string getTextForEnum(int enumVal)`</span> | Retrieves the string representation of a LineName enum value. |

****

### SubwayMap
Reads station data from a CSV file and manages subway stations.

#### Private Variables:
| Name                                             | Description                            |
|--------------------------------------------------|----------------------------------------|
| <span style="color:#C586C0">`allStations`</span> | Vector containing all subway stations. |

#### Public Methods:
| Method                                                                                                       | Description                                          |
|--------------------------------------------------------------------------------------------------------------|------------------------------------------------------|
| <span style="color:#569CD6">`void createAllStations(string filePath, vector<Station>& allStations)`</span>   | Creates all subway stations from a CSV file.         |
| <span style="color:#569CD6">`void updateStopsForLine(LineName line, vector<Station>& subwayStations)`</span> | Updates scheduled stops for a specified subway line. |

### Main

Acts as the "Driver" for the game.
Includes input validation for all questions, which has been extensively tested.

## Timeline

### Future Work (From Module 1)

Obviously, with only one line and two directions,
the game is very simple assuming you refer to the map or have expert NYC subway knowledge. 

However, if you look in the `csv` directory,
you can see I have a second `.csv` file containing `Station` data for ALL NYC subway stations.
Notice that each `Station` also has a list of transfers to other train lines that you can reach,
meaning this file holds data for a **graph of the NYC subway system**. [All Stations CSV](./csv/all_stations.csv).

I realized this thanks to CS 2250 Computability & Complexity, which taught me how graphs are two-tuple data structures.

It will be interesting to see the game played out when I add the ability to transfer to other train lines at each station.

### Module 2 Additions

Although I have not implemented it into the main game yet,
I have added all the necessary methods with logic for verifying, and executing a successful transfer.

- `validTransfer()`: returns true or false if the users' requested LineName is at a specified Station
- `updateScheduledStops()`: calls the `updateStopsForLine()` method in `SubwayMap` to update the current Trains' `scheduledStops`.
- `transferToLine()`: updates the current Train objects' `LineName`, and `scheduledStops`.
- `updateStopsForLine()`: builds the correct path to a given `LineName`'s scheduledStops .csv file and returns it as a vector of Stations.

I had to refactor A LOT of my code from Module 1, as it was difficult organizing, passing,
and updating variables that needed to be modified to complete a transfer.
A big portion of this project was designing the most efficient way
to have my classes interact with one another without any circular dependencies.

## Video Demonstrations

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
>`{LineName(str)}_stations.csv`

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
