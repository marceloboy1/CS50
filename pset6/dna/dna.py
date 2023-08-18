import csv
import sys


def main():

    # check arguments
    if len(sys.argv) != 3:
        print('Usage python dna.py data.csv sequence.txt')
        return

    # loads files in memory
    csvfile = open(sys.argv[1], newline='')
    file = open(sys.argv[2])
    reader = csv.DictReader(csvfile)

    # make a dict to keep track of sequences
    dict = {}
    for key in reader.fieldnames[1:]:
        dict[key] = 1

    # iterate trugh all sequence
    for line in file:

        # for each STR in database file
        for sequence in reader.fieldnames[1:]:
            max = 1
            i = 0
            while i < len(line):

                # cheks if current str matches with next. If it does, increment counter
                first = line[i:i+len(sequence)]
                second = line[i+len(sequence):i+len(sequence)*2]
                if (first == sequence) and (second == sequence):
                    max += 1
                    i = i + len(sequence)

                # if desnt, reset counter and icrement i, and add max to dict if is higher than previus value
                else:
                    i += 1
                    if dict[sequence] < max:
                        dict[sequence] = max
                        max = 1

    # check if the values matches with anybody in database
    found = False
    for row in reader:
        match = True
        for key in dict:
            if int(row[key]) != dict[key]:
                match = False
        # if it does, print matching name
        if match:
            found = True
            print(row['name'])

    # if it doesnt, send no match massage
    if not found:
        print("No match.")


main()