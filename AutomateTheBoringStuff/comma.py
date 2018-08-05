def show_list(list):
    for item in list[:-1]:
        print(item + ", ", end="")
    print("and " + list[-1])
    
def main():
    input_list = ["apples", "bananas", "tofu", "cats", "fish", "orange"]

    show_list(input_list)
    
if __name__ == '__main__':
    main()
