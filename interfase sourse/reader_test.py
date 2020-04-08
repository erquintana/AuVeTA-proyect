import csv
with open('activity_data.csv', 'r') as file:
    reader = csv.reader(file, delimiter = ',')
    for row in reader:
        print(row)