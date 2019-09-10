import numpy as np
import matplotlib
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from matplotlib import rc
import csv
import statistics
import math
import subprocess


method_num = 2
questions_num = 7
dimensions = ["comfort", "fun", "low physical\nfatigue", "low mental\nfatigue", "ease of use", "efficiency", "low\ninterference"]

def get_data(data, yerr):
    raw_data = [[[] for i in range(questions_num)] for j in range(method_num)]

    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # ヘッダーを読み飛ばす

        for row in reader:
            for i in range(method_num):
                for j in range(questions_num):
                    raw_data[i][j].append(row[12+i*questions_num+j])

    # 平均値とエラーバーに使う標準誤差を計算
    for i in range(method_num):
        for q in raw_data[i]:
            q_data = [int(x) for x in q]
            data[i].append(statistics.mean(q_data))
            yerr[i].append(statistics.pstdev(q_data)/math.sqrt(len(q_data)))

def add_asterisk(n, x, bar_width, data, yerr, s=0, t=1, asterisk='*'):
    lx, ly = x[n], data[s][n]
    rx, ry = x[n]+t*bar_width, data[t][n]

    ly += yerr[s][n]
    ry += yerr[t][n]
  
    ax_y0, ax_y1 = plt.gca().get_ylim()
    dh =.05
    barh =.05
    dh *= (ax_y1 - ax_y0)
    barh *= (ax_y1 - ax_y0)
  
    y = max(ly, ry) + dh
  
    barx = [lx, lx, rx, rx]
    bary = [y-0.1, y+barh-0.1, y+barh-0.1, y-0.1]
    mid = ((lx+rx)/2, y+barh-0.15)
  
    plt.plot(barx, bary, c='black')

    kwargs = dict(ha='center', va='bottom')
    kwargs['fontsize'] = 42
  
    plt.text(*mid, asterisk, **kwargs)

def main():
    data = [[] for i in range(method_num)]
    yerr = [[] for i in range(method_num)]
    get_data(data, yerr)
    
    fig, ax = plt.subplots(figsize=(25, 13), dpi=300)
    bar_width = 0.3
    x = np.arange(questions_num)  # numpyで横軸を設定

    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')

    ax.grid(True, 'major', 'y', ls='--', lw=.5, c='k', alpha=.3)
    ax.tick_params(bottom=False)

    bar_colors = [colors.cnames['hotpink'], colors.cnames['deepskyblue']]
    bar_labels = ['optimized', 'fixed']

    for i in range(method_num):
        ax.bar(x+i*bar_width, data[i], bar_width, color=bar_colors[i], label=bar_labels[i], capsize=6, yerr=yerr[i], align='center')

    ax.set_ylabel('Mean ratings', weight='bold', fontsize=42, family='arial')
    ax.set_ylim([1,5])
    plt.yticks([1,2,3,4,5], weight='bold', fontsize=32, family='arial')

    ax.xaxis.labelpad = 15
    ax.set_xlabel('questionnaire', fontsize=42, weight='bold', family='arial')
    ax.set_xticks(x + bar_width/2)
    ax.set_xticklabels(dimensions, weight='bold', fontsize=32, family='arial')
    
    ax.legend(loc='best', fontsize=32, ncol=2)

    # 有意差のアスタリスクをつける
    add_asterisk(0, x, bar_width, data, yerr)
    add_asterisk(1, x, bar_width, data, yerr, asterisk='**')
    add_asterisk(3, x, bar_width, data, yerr, asterisk='**')
    add_asterisk(5, x, bar_width, data, yerr)
    add_asterisk(6, x, bar_width, data, yerr, asterisk='**')

    output_file_name = 'questionnaire_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.05)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()