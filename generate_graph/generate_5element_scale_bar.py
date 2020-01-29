import numpy as np
import matplotlib
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from matplotlib import rc
import csv
import subprocess

category_names = ['strongly disagree', 'disagree', 'neither agree nor disagree', 'agree', 'strongly agree']
category_num = len(category_names)
methods = ['optimized', 'fixed']
method_num = len(methods)

def main():
    # スコア1が10人，スコア2が15人，．．．という感じ
    data = [[10, 15, 17, 32, 26], [26, 22, 29, 10, 13]]

    np_data = np.array(data)
    data_cum = np_data.cumsum(axis=1)
    category_colors = plt.get_cmap('RdYlGn')(np.linspace(0.15, 0.85, np_data.shape[1]))

    fig, ax = plt.subplots(figsize=(10, 5), dpi=300)
    
    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')
    ax.invert_yaxis()
    ax.xaxis.set_visible(False)
    ax.set_xlim(0, np.sum(np_data, axis=1).max())
    ax.set_yticklabels(methods, weight='bold', fontsize=16, family='arial')

    for i, (colname, color) in enumerate(zip(category_names, category_colors)):
        widths = np_data[:, i]
        starts = data_cum[:, i] - widths
        ax.barh(methods, widths, left=starts, height=0.5, label=colname, color=color)
        xcenters = starts + widths / 2

        r, g, b, _ = color
        for y, (x, c) in enumerate(zip(xcenters, widths)):
            if(c != 0):
                ax.text(x, y, str(int(c)), ha='center', va='center', color='black', weight='bold', fontsize=15, name='arial')
    
    ax.legend(ncol=len(category_names), bbox_to_anchor=(0, 1), loc='lower left', fontsize=9.45)

    output_file_name = 'questionnaire_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.05)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()