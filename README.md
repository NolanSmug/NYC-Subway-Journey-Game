
# Nolan Cyr
## Subway Shuffle: A Randomized NYC Journey

## Summary of Program

This is a game where a player is placed into a random NYC subway station,
and the goal is to reach another randomly given station.

Upon starting the game, the player is given a random `current station` and a random `destination station`.
They are then prompted to choose a train `Line` to board from the available transfer options at the `current station`.
After selecting a `Line`,
the player is asked to choose a `Direction` (e.g., `Queens-bound` or `Brooklyn-bound`) to start traveling.

At each station stop, the program displays the following information:
- `Current Line` and `Direction`
- `Current Station`
- Available `Transfer Lines` at the `Current Station`

And the user is then given **4 options**:
1. Enter a number to advance that many stations (or leave blank to advance one station)
2. Enter 't' to transfer to a different line
3. Enter 'c' to change the direction of travel (e.g., from Queens-bound to Brooklyn-bound, or vice versa)
4. Enter 'd' to display the Destination Station information again

> No worries! There is no "losing" in this game, as the program runs until the player reaches the `destination station`.

If the player types `t` to transfer lines,
they are prompted to select a new line from the available transfer options at the current station
and choose a new direction.
(Input validation is implemented here too)

After a valid input is given, the player is notified of the station they have arrived at,
and the process repeats until the player reaches the `destination station`.

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
| `LineName getName()`                                            | Gets the current line of the Train.                                    |
| `void setName(LineName newLineName)`                            | Sets the current line of the Train.                                    |
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

#### Friend Overloaded Operator:  
| Operator                                             | Description                                               |
|------------------------------------------------------|-----------------------------------------------------------|
| `ostream& operator<<(ostream& str, Station station)` | Overloaded insertion operator (toString() for a Station). |

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

### Main

Acts as the "Driver" for the game.
Includes input validation for all questions, which has been extensively tested.

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
    string input;
    cout << "Enter 't' to transfer | 'c' to change direction | a number to advance that many stations (nothing advances 1 station)  ";
    getline(cin, input);

    if (input.empty()) { // advance 1 station
        return handleAdvanceOneStation(train);
    } 
    else if (tolower(input[0]) == 't' && input.length() == 1) {  // transfer
        return handleTransfer(train, uptownLabel, downtownLabel); 
    } 
    else if (tolower(input[0]) == 'c' && input.length() == 1) {  // flip directions
        return handleChangeDirection(train);
    } 
    else {  // advance (int)input stations
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
   {
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
The `SubwayMap` class now includes the `updateStopsForLine()` method builds the scheduled stops for a given subway line
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

#### Start Development for the Challenge Class
The `Challenge` class will allow me to create custom hard-coded `starting stations` and `destination stations`,
each categorized based on difficulty.

****

## Video Demonstrations

**[Input Validation](https://www.youtube.com/watch?v=8oJfOjqpsMM)**
> **Note:** I set hard coded values to make the demonstration as simple and understandable as possible. In the provided code, the two `Station` Objects are chosen at random.

****

**[Transferring Lines (Run)](https://youtu.be/w70_YOdGSuk)**

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

**[Transferring Lines (Debugger)](https://www.youtube.com/watch?v=O2yxH51k6xI)**

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
