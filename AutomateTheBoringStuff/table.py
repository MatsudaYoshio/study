def print_table(table):
    max_len = [max([len(x) for x in table[i]])+1 for i in range(len(table))]
    max_len[0] = max_len[0]-1
    
    for i in range(len(table[0])):
        for j in range(len(table)):
            print(table[j][i].rjust(max_len[j]), end="")
        print("")
    
def main():
    table_data = [["apple", "orange", "cherries", "banana"],
                  ["Alice", "Bob", "Carol", "David"],
                  ["dogs", "cats", "moose", "goose"]]
    print_table(table_data)
    
if __name__ == '__main__':
    main()
