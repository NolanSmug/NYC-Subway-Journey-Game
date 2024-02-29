import csv

# Dictionary to store stations for each train line
train_stations = {
    "1": [],
    "2": [],
    "3": [],
    "4": [],
    "5": [],
    "6": [],
    "7": [],
    "A": [],
    "B": [],
    "C": [],
    "D": [],
    "E": [],
    "F": [],
    "G": [],
    "J": [],
    "L": [],
    "M": [],
    "N": [],
    "Q": [],
    "R": [],
    "S": [],
    "Z": [],
}

# Read the provided data and organize stations by train line
with open('./csv/all_stations.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        stop_id = row['stop_id']
        transfers = row['transfers'].split(',')
        for line in transfers:
            for char in line.split():
                train_stations[char].append(row)

# Write stations for each train line to separate CSV files
for line, stations in train_stations.items():
    with open(f'{line}_train_stations.csv', mode='w', newline='') as csvfile:
        fieldnames = ['stop_id', 'stop_name', 'transfers', 'borough']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for station in stations:
            writer.writerow(station)
