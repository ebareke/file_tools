import csv
import argparse

class FileMerger:
    def __init__(self, files, key_columns, separators):
        self.files = files
        self.key_columns = key_columns
        self.separators = separators
        self.data = {}

    def read_data(self):
        """
        Reads the data from each file into a dictionary, using the key column as the key
        """
        for file, separator, key_column in zip(self.files, self.separators, self.key_columns):
            with open(file, 'r') as f:
                reader = csv.reader(f, delimiter=separator)
                self.data[file] = {row[key_column]: row for row in reader}

    def merge_data(self):
        """
        Merges the data from the dictionaries and returns the merged rows
        """
        keys = set.intersection(*[set(d.keys()) for d in self.data.values()])
        merged_rows = []
        for key in keys:
            merged_row = []
            for file, separator, key_column in zip(self.files, self.separators, self.key_columns):
                row = self.data[file].get(key)
                if row is None:
                    row = ["-" for _ in range(len(separator))]
                merged_row.extend(row)
            merged_rows.append(merged_row)
        return merged_rows

    def write_to_file(self, output_file):
        """
        Writes the merged rows to the specified output file
        """
        with open(output_file, 'w') as f:
            writer = csv.writer(f)
            for row in self.merge_data():
                writer.writerow(row)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('files', nargs='+', help='The files to merge')
    parser.add_argument('--key-columns', nargs='+', type=int, help='The key column(s) in each file')
    parser.add_argument('--separators', nargs='+', help='The separator(s) for each file')
    parser.add_argument('--output-file', required=True, help='The output file')
    args = parser.parse_args()

    merger = FileMerger(args.files, args.key_columns, args.separators)
    merger.read_data()
    merger.write_to_file(args.output_file)
