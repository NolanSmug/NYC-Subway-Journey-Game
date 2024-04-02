
# Nolan Cyr
## Subway Shuffle: A Randomized NYC Journey

### Summary of Program

This program is a text-based game set in the New York City subway system.
The player's goal is
to navigate from a randomly assigned `starting station` to another randomly assigned `destination station`.
Here's how the game steps flow:

1. **Initialization**:
    - The player is given a random `starting station` and a random `destination station` within the subway system.
    - They are prompted to choose a subway line to board from the available transfer options at their `starting station`.
    - Once a line is chosen, they select a direction (e.g., `Queens-bound` or `Brooklyn-bound`) to start traveling.

2. **Gameplay**:
    - At each station or stop, the program displays information such as the `current line`, `direction`, `current station`, and `available transfer lines`.
    - The player is presented with the options below:
   ```text
       1. Enter a number to advance a specific number of stations (or leave blank to advance one station).
       2. Enter 't' to transfer to a different line.
       3. Enter 'c' to change the direction of travel.
       4. Enter 'd' to display information about the destination station.
        
       >_
   ```

3. **Game Loop**:
    - The game continues until the player reaches the `destination station`.
   >There is no losing condition; the game runs until the player successfully reaches the destination.

4. **Challenge Mode**:
    - Optionally, the player can choose to play in `Challenge Mode`, where they are presented with specific challenges to complete.
    - `Challenges` involve traveling from one `predetermined station` to another, each ranging in `difficulty (1-3)`.

****

## Classes

### Train
Manages a `Train` object and its scheduled stops.

#### Private Variables:
| Name                             | Description                                                 |
|----------------------------------|-------------------------------------------------------------|
| `LineName currentLine`           | Current subway line of the Train.                           |
| `Direction direction`            | Direction of the Train (`UPTOWN`, `DOWNTOWN`).              |
| `string uptownLabel`             | Label in string format for the uptown-bound track           |
| `string downtownLabel`           | Label in string format for the downtown-bound track         |
| `vector<Station> scheduledStops` | Vector of stations representing scheduled stops.            |
| `int currentStationIndex`        | Index of the current station in the scheduled stops vector. |
| `bool express`                   | Indicates whether the Train is an express train or not.     |
| `int numCars`                    | Number of cars in the Train.                                |

#### Public Methods:
| Method                                                          | Description                                                            |
|-----------------------------------------------------------------|------------------------------------------------------------------------|
| `LineName getLine()`                                            | Gets the current line of the Train.                                    |
| `void setLine(LineName newLineName)`                            | Sets the current line of the Train.                                    |
| `Direction getDirection()`                                      | Gets the direction of the Train.                                       |
| `void setDirection(Direction newDirection)`                     | Sets the direction of the Train.                                       |
| `bool transferToLine(LineName newLine, Station currentStation)` | Attempts to transfer the Train to a different line at a given station. |
| `void updateScheduledStops(LineName line)`                      | Updates the scheduled stops based on a specified subway line.          |
| `vector<Station> getScheduledStops()`                           | Gets the scheduled stops of the Train.                                 |
| `void addScheduledStop(Station newStop)`                        | Adds a Station to the scheduled stops of the Train.                    |
| `Station getCurrentStation()`                                   | Gets the current station of the Train.                                 |
| `Station getNextStation()`                                      | Gets the next station of the Train.                                    |
| `int getCurrentStationIndex()`                                  | Gets the index of the Train's current station.                         |
| `void setCurrentStation(int stationIndex)`                      | Sets the current station of the Train using an index.                  |
| `void setCurrentStation(string stationName)`                    | Sets the current station of the Train using a station name.            |
| `bool advanceStation()`                                         | Advances the Train to the next station.                                |
| `bool advanceStation(int numStations)`                          | Advances the Train by a specified number of stations.                  |
| `bool isExpress()`                                              | Checks if the Train is an express train.                               |
| `void setExpress(bool isExpress)`                               | Sets whether the Train is express or not.                              |
| `int getNumCars()`                                              | Gets the number of cars on the Train.                                  |
| `void setNumCars(int newNumCars)`                               | Sets the number of cars on the Train.                                  |

****

### Station
Represents a subway station in the game.

#### Private Variables:
| Name                         | Description                                                 |
|------------------------------|-------------------------------------------------------------|
| `string id`                  | ID Number for the Station.                                  |
| `string name`                | Name of the Station.                                        |
| `vector<LineName> transfers` | List of subway lines available for transfer at the Station. |
| `Borough borough`            | Borough where the Station is located.                       |

#### Public Methods:
| Method                                    | Description                                                            |
|-------------------------------------------|------------------------------------------------------------------------|
| `string getId()`                          | Gets the ID of the Station.                                            |
| `void setId(string newId)`                | Sets the ID of the Station.                                            |
| `string getName()`                        | Gets the name of the Station.                                          |
| `void setName(string newName)`            | Sets the name of the Station.                                          |
| `vector<LineName> getTransfers()`         | Gets the list of subway lines available to transfer to at the Station. |
| `void addTransfers(LineName newTransfer)` | Adds a subway line to the list of available transfers at the Station.  |
| `Borough getBorough()`                    | Gets the borough of the Station.                                       |
| `void setBorough(Borough newBorough)`     | Sets the borough of the Station.                                       |
| `string getTextForEnum(int enumVal)`      | Gets the string representation of a Borough enum value.                |

#### Friend Overloaded Operators:
| Operator                                                  | Description                                                    |
|-----------------------------------------------------------|----------------------------------------------------------------|
| `ostream& operator<<(ostream& str, Station station)`      | Overloaded insertion operator (toString() for a Station).      |
| `bool operator==(const Station &lhs, const Station &rhs)` | Overloaded equality operator to compare two Station objects.   |
| `bool operator!=(const Station &lhs, const Station &rhs)` | Overloaded inequality operator to compare two Station objects. |


****

### Line  
Handles the different subway lines in the game.

#### Public Methods:  
| Method                                              | Description                                                          |
|-----------------------------------------------------|----------------------------------------------------------------------|
| `static string getTextForEnum(int enumVal)`         | Gets the string representation of a LineName enum.                   |
| `static string getIDTextForEnum(int enumVal)`       | Gets the ID representation of a LineName enum.                       |
| `static LineName stringToLineEnum(string& lineStr)` | Gets a LineName enum of a string representation for a LineName enum. |

****

### SubwayMap  
Reads station data from a CSV file and manages subway stations.

#### Private Variables:  
| Name           | Description                                        |
|----------------|----------------------------------------------------|
| `allStations`  | Vector containing the SubwayMap's subway stations. |

#### Public Methods:  
| Method                                                                    | Description                                                     |
|---------------------------------------------------------------------------|-----------------------------------------------------------------|
| `void createStations(string filePath, vector<Station>& allStations)`      | Loads all subway station objects into a vector from a CSV file. |
| `void updateStopsForLine(LineName line, vector<Station>& subwayStations)` | Updates the scheduled stops for a specified subway line.        |

****

### Challenge
Manages a `Challenge` object representing a specific Train journey challenge.

#### Private Variables:
| Name                         | Description                            |
|------------------------------|----------------------------------------|
| `LineName startLine`         | Starting subway line of the Challenge. |
| `Station startStation`       | Starting station of the Challenge.     |
| `Station destinationStation` | Destination station of the Challenge.  |
| `int difficulty`             | Difficulty level of the Challenge.     |

#### Public Methods:
| Method                                                      | Description                                              |
|-------------------------------------------------------------|----------------------------------------------------------|
| `LineName getStartLine()`                                   | Gets the starting subway line of the Challenge.          |
| `void setStartLine(LineName startLine)`                     | Sets the starting subway line of the Challenge.          |
| `Station getStartStation()`                                 | Gets the starting station of the Challenge.              |
| `void setStartStation(Station newStartStation)`             | Sets the starting station of the Challenge.              |
| `Station getDestinationStation()`                           | Gets the destination station of the Challenge.           |
| `void setDestinationStation(Station newDestinationStation)` | Sets the destination station of the Challenge.           |
| `int getDifficulty()`                                       | Gets the difficulty level of the Challenge.              |
| `void setDifficulty(int difficulty)`                        | Sets the difficulty level of the Challenge.              |
| `vector<Challenge> initializeAllChallenges()`               | Initializes a collection of all challenges for the game. |

****

### JourneyManager
Manages a `JourneyManager` object responsible for handling journey-related functionalities in the game.

#### Private Variables:
| Name                          | Description                                                     |
|-------------------------------|-----------------------------------------------------------------|
| `vector<Station> allStations` | Vector containing all stations in the subway system.            |
| `Station startingStation`     | Starting station of the journey.                                |
| `Station destinationStation`  | Destination station of the journey.                             |

#### Public Methods:
| Method                                                      | Description                                                       |
|-------------------------------------------------------------|-------------------------------------------------------------------|
| `Station getStartingStation()`                              | Gets the starting station of the journey.                         |
| `void setStartingStation(Station newStartingStation)`       | Sets the starting station of the journey.                         |
| `void setStartingStation(string newStartingStation)`        | Sets the starting station of the journey using a station name.    |
| `Station getDestinationStation()`                           | Gets the destination station of the journey.                      |
| `void setDestinationStation(Station newDestinationStation)` | Sets the destination station of the journey.                      |
| `void setDestinationStation(string newDestinationStation)`  | Sets the destination station of the journey using a station name. |
| `vector<Station> getAllStations()`                          | Gets all the stations in the subway system.                       |
| `Station& getRandomStation()`                               | Gets a random station from the subway system.                     |

****

### Main Class

The `main` function serves as the entry point for the `NYC Subway Journey Game Application`.
It manages the gameplay loop, user input handling, and `GameState` management.

#### GameState Struct:

The `GameState` struct encapsulates the current state of the game (it's in the name),
including the `starting line`, `starting station`, `destination station`, and `current stations`.

```c++
struct GameState {
    LineName startingLine;
    Station startingStation;
    Station destinationStation;
    vector<Station> currentStations;
    bool isFirstTurn;

    void resetGameState(JourneyManager& journeyManager); // if user wants to re-shuffle their stations
};
```

| Function                        | Description                                                                                                                                               |
|---------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
| `main`                          | Entry point of the application. It sets up the game environment, initializes the `Train`, `JourneyManager`, and `GameState`, and enters the game loop.    |
| `handleUserInput`               | Handles user input during the game. It interprets user commands to advance the train, change direction, transfer to another line, or display information. |
| `displayCurrentStationInfo`     | Displays information about the current station, including the line and direction of the train.                                                            |
| `handleAdvanceOneStation`       | Handles the command to advance the train by one station.                                                                                                  |
| `handleTransfer`                | Handles the command to transfer to another line at the current station.                                                                                   |
| `handleChangeDirection`         | Handles the command to change the direction of the train.                                                                                                 |
| `handleAdvanceMultipleStations` | Handles the command to advance the train by multiple stations specified by the user.                                                                      |
| `handleLastStop`                | Handles the situation when the train reaches the last stop on its current line. It prompts the user to switch direction and continue the journey.         |
| `getRandomStation`              | Generates a random station index within the specified range.                                                                                              |
| `handleNewDirection`            | Prompts the user to choose a new direction for the train when transferring to another line.                                                               |
| `askUserToTransfer`             | Prompts the user to choose a line for transferring at the current station.                                                                                |
| `handleStartingLine`            | Prompts the user to choose a train line to wait for at the current station.                                                                               |
| `initializeTrain`               | Initializes the train with the starting line, current station, and destination station based on the game state.                                           |
| `printTransferLines`            | Prints the available transfer lines at a station.                                                                                                         |
| `selectChallenge`               | Prompts the user to select a challenge for the game in Challenge Mode. It initializes the game state based on the selected challenge.                     |


****



## Timeline

### Future Work (From Module 1):

Obviously, with only one line and two directions,
the game is very simple assuming you refer to the map or have expert NYC subway knowledge. 

However, if you look in the `csv` directory,
you can see I have a second `.csv` file containing `Station` data for ALL NYC subway stations.
Notice that each `Station` also has a list of transfers to other train lines that you can reach,
meaning this file holds data for a **graph of the NYC subway system**. [All Stations CSV](./csv/all_stations.csv).

I realized this thanks to CS 2250 Computability & Complexity, which taught me how graphs are two-tuple data structures.

It will be interesting to see the game played out when I add the ability to transfer to other train lines at each station.

****

### Module 2 Additions:

Although I have not implemented it into the main game yet,
I have added all the necessary methods with logic for verifying and executing a successful transfer.

- `validTransfer()`: returns true or false if the users' requested LineName is at a specified Station
- `updateScheduledStops()`: calls the `updateStopsForLine()` method in `SubwayMap` to update the current Trains' `scheduledStops`.
- `transferToLine()`: updates the current Train objects' `LineName`, and `scheduledStops`.
- `updateStopsForLine()`: builds the correct path to a given `LineName`'s scheduledStops .csv file and returns it as a vector of Stations.

I had to refactor A LOT of my code from Module 1, as it was difficult organizing, passing,
and updating variables that needed to be modified to complete a transfer.
A big portion of this project was designing the most efficient way
to have my classes interact with one another without any circular dependencies.

#### Input Validation has been implemented for all prompts to the user.

****

### Module 3 Additions:

In Module 3, I have fully integrated the ability for the user to transfer between subway lines during gameplay. This involved several key additions and changes to the codebase:

#### Main Game Loop

`main` has been updated to handle user input for transferring lines, changing directions, and advancing stations.
The `handleUserInput` function serves as the central hub for processing user commands during each turn.

```cpp
bool handleUserInput(Train &train, string &uptownLabel, string &downtownLabel) {
   //        ...
   //    print options (see above)
   //        ...
    
    if (input.empty()) {    // advance 1 station
        return handleAdvanceOneStation(train);
    }
    else if (tolower(input[0]) == 't' && input.length() == 1) {    // transfer
        return handleTransfer(train);
    }
    else if (tolower(input[0]) == 'c' && input.length() == 1) {    // change direction
        return handleChangeDirection(train);
    }
    else if (tolower(input[0]) == 'd' && input.length() == 1) {    // reprint destination station
        cout << "Destination Station:\n" << destinationStation;
    }
    else if (input[0] == '0' && input.length() == 1) {             // code secret (cheat code)
        printAllStations(train);
    }
    else {  // advance input(int) stations
     return handleAdvanceMultipleStations(train, input);
    }
}
```

The `handleTransfer()` function prompts the user
to choose a transfer line from the current station's available transfers,
and updates the train's line and scheduled stops accordingly.

#### Integration of Python Code
To enhance the functionality of the project and incorporate additional features,
Python code was integrated into the system.
My Python scripts [csv_maker.py](csv/csv_maker.py) and [csv_reverser.py](csv/csv_reverser.py) use
[all_stations.csv](csv/all_stations.csv) to separate each subway lines' `scheduledStops` into individual csv files
(see the [csv directory](csv)).

```python
import csv

train_stations = {}

# Open the CSV file containing all station data
with open('./csv/all_stations.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)

    # Iterate through each row in the CSV
    for row in reader:
        # Extract the stop_id and transfers from the current row
        stop_id = row['stop_id']
        transfers = row['transfers'].split(',')

        # Iterate through each transfer
        for line in transfers:
            # Split the transfer line into individual characters
            for char in line.split():
                # Check if the character represents a subway line
                if char in train_stations:
                    # Append the current row to the list of stations associated with that subway line
                    train_stations[char].append(row)
```

Once the data is parsed, the Python script:
1. organizes the station information based on subway lines and available transfers.
2. constructs a `dictionary` where each key represents a subway line
   and the corresponding `value` is a list of stations associated with that line.
   - Each CSV file is named based on the corresponding subway line `"1_train_stations.csv", "2_train_stations.csv",...`
```python
stations = {
    "1_train_stations": ["StationA", "StationB", "StationC",...], 
    "2_train_stations": ["StationA", "StationC", "StationD",...],
    "3_train_stations": ["StationX", "StationY", "StationZ",...],
    ...
}
```

3. lastly, `csv_reverser.py` ensures that the csv files follow the correct order our `advanceStation()` logic is written.

This organization facilitates easy access to station data for each subway line,
enabling efficient retrieval and manipulation when needed.

#### Updating Scheduled Stops
The `SubwayMap` class now includes the `updateStopsForLine()` method,
which builds the scheduled stops for a given subway line
by reading the corresponding line-specific CSV file.

```c++
void SubwayMap::createStations(LineName line, vector<Station>& subwayStations) {
    string filePath = "./csv/";
    
    if (line == NULL_TRAIN) {
        filePath += "all_stations.csv";
    } 
    else {
        filePath += Line::getIDTextForEnum(line) + "_train_stations.csv";
    }
    createStations(filePath, subwayStations);
}

void SubwayMap::updateStopsForLine(LineName line, vector<Station>& subwayStations) {
    subwayStations.clear();
    createStations(line, subwayStations);
}
```

#### User Experience Improvements
The current station information, including the train line, direction, and station details, is displayed after each user action.
When a transfer is available, the user is prompted to list the available transfer lines at the current station.
Input validation has been improved to handle various edge cases and provide meaningful error messages.

With these additions, the game now **accurately simulates the experience of navigating the NYC subway system**,
allowing players to get from `point A` to `point B` infinitely many ways.

#### Small Cheat Code for Testers/Graders

Take a look for my `handleUserInput()` function in `main.cpp`  
1. Command: `Cmd/Ctrl` + `Shift` + `F`
2. Copy/Paste: 
```text
bool handleUserInput(Train &train, const Station &destinationStation) {
```
3. See the secret input you can give at each station. 

_Hint if you can't find it:_ `e^(iπ) + 1 = __`

Example Output:
```text
------------------------------------------------------------------
Inwood-207 St                      (11 stops away)
    |
Dyckman St                         (10 stops away)
    |
190 St                             (9 stops away)
    |
181 St                             (8 stops away)
    |
175 St                             (7 stops away)
    |
168 St                             (6 stops away)
    |
145 St                             (5 stops away)
    |
125 St                             (4 stops away)
    |
59 St-Columbus Circle              (3 stops away)
    |
42 St-Port Authority Bus Terminal  (2 stops away)
    |
34 St-Penn Station                 (Next Stop)
    |
14 St (8th Av)                  **  Current Station  **
    |
    ↑
------------------------------------------------------------------
```

#### Start Development for the Challenge Class
The `Challenge` class will allow me to create custom hard-coded `starting stations` and `destination stations`,
each categorized based on difficulty.

****

## Video Demonstrations

### [Input Validation](https://www.youtube.com/watch?v=8oJfOjqpsMM)
> **Note:** I set hard coded values to make the demonstration as simple and understandable as possible. In the provided code, the two `Station` Objects are chosen at random.

****

### [Transferring Lines (Run)](https://youtu.be/w70_YOdGSuk)

In this example, the user is placed at `Rector St`
on the `1 Line`.  
**Goal**: Find our way to `Times Square 42nd St`


1. User selects to start traveling Uptown (`Bronxbound`).
2. User requests to advance 2 `Stations`.
3. User arrives at `Chambers St`.

> `Chambers St` has other lines that stop there (`2`,`3`). The user is asked if they would like to transfer.

5. User selects yes.
6. User selects to switch to the `2 Line`, since the `2 Line` can get to `Times Square` in fewer stops.
```text
     1 Line:                     2 Line:
                   Uptown
       ʌ                           ʌ
       |                           |
   Times Sq  ------------------ Times Sq
       |                           |
     34 St --------------------- 34 St
       |                           |
     28 St                         |
       |                           |
     23 St                         |
       |                           |
     18 St                         |
       |                           |
     14 St --------------------  14 St
       |                           |
  Christopher St                   |
       |                           |
   Houston St                      |
       |                           |
    Canal St                       |
       |                           |
   Franklin St                     |
       |                           |
   Chambers St -------------- Chambers St
       |                           |
       v                           v
                  Downtown
```

> The user is now on a train running on the `2 Line`, at `Chambers St`.

> **Note:** the user will always be asked again if they would like to transfer (in case they made a mistake).

9. User selects to board on the Uptown platform, since we still want to be going uptown.

>The user is now on a `Bronxbound 2 Train`.

10. User selects to advance 3 `Stations` (after referring to the map).

The user now reached `Times Square`, the destination station. The game now ends.

****

### [Transferring Lines (Debugger)](https://www.youtube.com/watch?v=O2yxH51k6xI)

In this demonstration video,
I step through the CLion debugger
showing how all the fields we need to update in a Train object to perform a successful transfer.
1. I set up some code in `main.cpp` to test the transfer to the `TWO_TRAIN` at 14th St
2. `transferToLine()` is called with the requested transfers' `LineName` and the Train's `currentStation`
3. `validTransfer()` returns `true`, as it finds the `TWO_LINE` in 14th st's vector of `LineName`s.
4. `updateScheduledStops()` is called and builds a `SubwayMap` to be passed into the `SubwayMap` class (for `Station` file handling).
5. `updateStopsForLine()` is called in `SubwayMap` and uses the requested `LineName` enum to build the path to the correct csv file
   (that holds the station data to that line). 

The standard pattern for the file names is: `{LineName(str)}_stations.csv`

6. `transferToLine()` returns `true` in main, and we can see that the current Train objects' `scheduledStops<Station>` has been updated with all of the `TWO_TRAIN` station data, and we are at the same station still.


```c++
bool transferToLine(LineName newLine, Station currentStation) {
    if (validTransfer(newLine,currentStation)) {        // if the transfer is valid, proceed with the transfer
        updateScheduledStops(newLine);                  // update the Train's Station vector
        setCurrentStation(currentStation.getName());    // update the Train's currentStation
        currentLine = newLine;                          // update the Train's currentLine
        return true;
    }

    return false;  // not a valid requested transfer
}
```

****

### [Subway Adventure: Navigating to Times Square 42nd St](https://youtu.be/Za8aYLOiGR8)  

`Starting Point`: Brooklyn Bridge-City Hall  
`Destination Station`: Times Sq-42 St

**1. Initial Setup**  
  User chooses to wait for the `Bronx-bound` `4 Train` at `Brooklyn Bridge-City Hall (4 5 6 J Z)`.

**2. First Move**  
  User advances `1` station and arrives at `14 St-Union Sq`.

**3. Continuing the Journey**  
  User decides to advance another station, and reaches `Grand Central-42 St (4 5 6 7 S)`.

**4. Checking the Destination**  
  User decides to review the `destination station` and confirms they're heading towards `Times Sq-42 St`.

**5. Transfer Opportunity**  
  Realizing that `Times Square` is more accessible from a different line, the user selects to `transfer`.

**6. Selecting the New Line**  
  After selecting to switch to the `Times Sq-bound` `S Train`, the user proceeds from `Grand Central-42 St`.

**7. Final Leg**  
The `S Train` travels back and forth between `Grand Central` and `Times Square`,
so the user advances `1` station and arrives at the correct `destination station`.


### Visual Diagram of The Journey

```text
             4 Line     (starting line)
           Bronx-bound  (starting direction) 
               ...
                ʌ
                |
                |
42nd St    Grand Central  ––––– (S Line) –––––>  Times Sq-42 St   (destination station)
                |   (transfer)
                |
                |
                |
         14 St-Union Sq
                |
                |
                |
                |
                |
    Brooklyn Bridge-City Hall (starting station)
                |
                |
               ...
```

****