import os
import csv


# Function to reverse CSV file contents
def reverse_csv_file(file_path):
    with open(file_path, 'r', newline='') as csvfile:
        reader = csv.reader(csvfile)
        data = list(reader)

    with open(file_path, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(reversed(data))


# List all CSV files in the current directory
csv_files = [file for file in os.listdir() if file.endswith('csv')]

# Pattern of files to reverse
pattern = [
    'c_train_stations.csv', 'e_train_stations.csv'
    'b_train_stations.csv', 'd_train_stations.csv', 'f_train_stations.csv', 'm_train_stations.csv',
    'n_train_stations.csv', 'q_train_stations.csv', 'r_train_stations.csv', 'w_train_stations.csv',
    'j_train_stations.csv', 'z_train_stations.csv',
    'g_train_stations.csv',
    'l_train_stations.csv'
]

# Filter out files following the specified pattern
target_files = [file for file in csv_files if file.lower() in pattern]

# Reverse contents of each target file
for file in target_files:
    reverse_csv_file(file)
    print(f"Reversed contents of {file}")

print("All target CSV files reversed successfully.")
