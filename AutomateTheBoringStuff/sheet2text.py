import sys
import openpyxl

def main():
    if len(sys.argv) != 2:
        sys.exit(1)

    wb = openpyxl.load_workbook(sys.argv[1])
    sheet = wb.active

    for i in range(1, sheet.max_column+1):
        with open("new_text"+str(i)+".txt", 'w') as file:
            for cell in list(sheet.columns)[i-1]:
                file.write(str(cell.value))
                file.write('\n')
                
if __name__ == '__main__':
    main()
