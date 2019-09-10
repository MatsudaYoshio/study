import numpy as np
import matplotlib
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from matplotlib import rc
import csv
import statistics
import math
import subprocess

method_num = 3
questions_num = 6
dimensions = ['mental\ndemand', 'physical\ndemand', 'temporal\ndemand', 'performance', 'effort', 'frustration']

def get_data(data, yerr):
    raw_data = [[[] for i in range(questions_num)] for j in range(method_num)]

    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # ヘッダーを読み飛ばす

        for row in reader:
            for i in range(method_num):
                for j in range(questions_num):
                    raw_data[i][j].append(row[23+i*questions_num+j])

    # 平均値とエラーバーに使う標準誤差を計算
    for i in range(method_num):
        for q in raw_data[i]:
            q_data = [int(x)*5 for x in q] # NASA-TLXで100点満点にするため5倍する
            data[i].append(statistics.mean(q_data))
            yerr[i].append(statistics.pstdev(q_data)/math.sqrt(len(q_data)))

def add_asterisk(n, s, t, x, bar_width, data, yerr, dh=.05, asterisk='*'):
    lx, ly = x[n], data[s][n]
    rx, ry = x[n]+t*bar_width, data[t][n]

    ly += yerr[s][n]
    ry += yerr[t][n]
  
    ax_y0, ax_y1 = plt.gca().get_ylim()
    barh =.04
    dh *= (ax_y1 - ax_y0)
    barh *= (ax_y1 - ax_y0)
  
    y = max(ly, ry) + dh
  
    barx = [lx, lx, rx, rx]
    dy = 2.0
    bary = [y-dy, y+barh-dy, y+barh-dy, y-dy]
    mid = ((lx+rx)/2, y+barh-2*dy)
  
    plt.plot(barx, bary, c='black')

    kwargs = dict(ha='center', va='bottom')
    kwargs['fontsize'] = 34
  
    plt.text(*mid, asterisk, **kwargs)

def main():
    data = [[] for i in range(method_num)]
    yerr = [[] for i in range(method_num)]
    get_data(data, yerr)
    
    fig, ax = plt.subplots(figsize=(23, 12), dpi=240)
    bar_width = 0.2
    x = np.arange(questions_num)  # numpyで横軸を設定

    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')

    ax.grid(True, 'major', 'y', ls='--', lw=.5, c='k', alpha=.3)
    ax.tick_params(bottom=False)

    bar_colors = [colors.cnames['hotpink'], colors.cnames['deepskyblue'], colors.cnames['cornflowerblue']]
    bar_labels = ['optimized', 'fixed1', 'fixed2']

    for i in range(method_num):
        ax.bar(x+i*bar_width, data[i], bar_width, color=bar_colors[i], label=bar_labels[i], capsize=6, yerr=yerr[i])

    ax.set_ylabel('Mean ratings', weight='bold', fontsize=42, family='arial')
    ax.set_ylim([0,90])
    ax.set_yticklabels([0,10,20,30,40,50,60,70,80,90], weight='bold', fontsize=34, family='arial')

    ax.set_xticks(x + bar_width)
    ax.set_xticklabels(dimensions, weight='bold', fontsize=34, family='arial')

    ax.legend(bbox_to_anchor=(0.8, 1.1025), loc='upper', borderaxespad=0, fontsize=34, ncol=3)

    # 有意差のアスタリスクをつける
    add_asterisk(2, 0, 1, x, bar_width, data, yerr)
    add_asterisk(2, 0, 2, x, bar_width, data, yerr, dh=0.15)

    add_asterisk(5, 0, 1, x, bar_width, data, yerr)
    add_asterisk(5, 0, 2, x, bar_width, data, yerr, dh=0.1, asterisk='**')

    output_file_name = 'NASA_TLX_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.05)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()