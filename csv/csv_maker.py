import csv

train_line_stations = {
    "four_train": [],
    "five_train": [],
    "six_train": [],
    "seven_train": [],
    "a_train": [],
    "b_train": [],
    "c_train": [],
    "d_train": [],
    "e_train": [],
    "f_train": [],
    "g_train": [],
    "j_train": [],
    "l_train": [],
    "m_train": [],
    "n_train": [],
    "q_train": [],
    "r_train": [],
    "s_train": [],
    "z_train": [],
}

# Read the provided data and organize stations by train line
with open('./csv/all_stations.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        stop_id = row['stop_id']
        transfers = row['transfers'].split(',')
        for line in transfers:
            for char in line.split():
                if char in train_line_stations:
                    train_line_stations[char].append(row)

# Write stations for each train line to separate CSV files
for line, stations in train_line_stations.items():
    with open(f'./csv/{line}.csv', mode='w', newline='') as csvfile:
        fieldnames = ['stop_id', 'stop_name', 'transfers', 'borough']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        writer.writeheader()
        for station in stations:
            writer.writerow(station)
