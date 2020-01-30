import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.colors as colors
import numpy as np
from matplotlib import rc

def main():
    data = [1362, 61, 356, 212]
    label = ['運輸業：1,362億円', '流通業：61億円', '不動産業：356億円', 'その他：212億円']

    plt.style.use('ggplot')
    plt.rcParams.update({'font.size':32})
    rc('font', weight='bold')
    col = [colors.cnames['cornflowerblue'], colors.cnames['hotpink'], colors.cnames['orange'], colors.cnames['green']]

    fig, ax = plt.subplots(figsize=(16, 20), dpi=100)

    ax.set_title('営業利益：1,969億円', y=0.94)
    ax.axis('equal')

    ax.pie(data, colors=col, counterclock=False, startangle=90, autopct=lambda p:'{:.1f}%'.format(p) if p>=5 else '',  textprops={'color': "white", 'weight': "bold", 'size':40})

    ax.legend(label, loc='bottom', fontsize=32, bbox_to_anchor=(0.74, 0.1), borderaxespad=0)
    
    plt.subplots_adjust(left=0, right=0.7, top=0.775)
    plt.savefig('operating_income_west.png', bbox_inches='tight', pad_inches=0.05)

if __name__ == '__main__':
    main()