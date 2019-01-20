import sys
import openpyxl

def main():
    if len(sys.argv) < 2:
        sys.exit(1)
    
    wb = openpyxl.Workbook()
    sheet = wb.active

    for i in range(2, len(sys.argv)):
        with open(sys.argv[i], 'r') as file:
            lines = file.readlines()
            for j in range(0, len(lines)):
                sheet.cell(row=j+1, column=i-1).value = lines[j]

    wb.save(sys.argv[1])
        
if __name__ == '__main__':
    main()
