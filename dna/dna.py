import csv
import sys


def main():

    # TODO: Check for command-line usage
    # If the arguments are less than 2 or more than 2
    # print(Usage: Database.CSV Sequences.txt)
    if (len(sys.argv) != 3):
        print ("Usage: Database.CSV Sequences.txt")


    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1]) as file:
        dbreader = csv.DictReader(file)
        for row in dbreader:
           data.append(row)


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        seqreader = csv.reader(file)
        sequence = next(seqreader)[0]



    # TODO: Find longest match of each STR in DNA sequence

    # Go to the first row
        # Go through each column
            # Increase the STR count until an empty cell reached
            # Go to the first STR and copy that text, store that in a variable STR#num in its Type field
            # Put that as the substring for the longest_match function
            # With the retruned value from the langest_match, move down the column to each row
            # Keep moving until empty cell reached
                # Check if same as longest_match returned value
                # If yes, navigate to the first column of that row, Store that name into a variable called STR_Match%candaiate, where candiate 1
                # Keep checking, If one more found, store that name into the variable called STR_Match%candidate, whire candidate is now 2
                # so on..
        # Go to the next column


    # We need to check for the sequence for all possible STRs on the sequence file
    # We need to go one by one through each column to first get that STR, then run the longest_match function on it, get a number, then store that value against that STR, then repeat until column is empty
    STR_data = {}
    for key in list(row.keys())[1:]:
        STR_data[key] = longest_match(sequence, key)
        # print(f"{STR_data[key]}")

    # TODO: Check database for matching profiles
    # Compare each row of data on the dbreader and data on the STR_data file
    # If found comletely true, go to the first row on dbreader file and store the name on a variable
    # Return all the names that match

    total_match = 0

    for row in data:
        positive_matches = 0

        for key in STR_data:
            list(row.keys())[1:]
            # print(f"{STR_data[key]}  ", end = "")
            # print(f"{row[key]}")

            if STR_data[key] != int(row[key]):
                # positive_matches += 1
                match_found = False
                break

            elif STR_data[key] == int(row[key]):
                match_found = True

        # matched_name = row["name"]
        if match_found == True:
            print(f"{row["name"]}")
            total_match += 1
        # print(f"Match: {positive_matches}")
        positive_matches = 0
        
    if match_found == False and total_match == 0:
        print("No Match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

