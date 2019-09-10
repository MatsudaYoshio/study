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
operator_questions_num = 5
bystander_questions_num = 3
all_questions_num = operator_questions_num+bystander_questions_num
dimensions = ['comfort', 'fun', 'ease of use', 'efficiency', 'low\ninterference', 'benefit', 'advertisement', 'attraction']

def get_data(data, yerr):
    raw_data = [[[] for i in range(all_questions_num)] for j in range(method_num)]

    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # ヘッダーを読み飛ばす

        for row in reader:
            for i in range(method_num):
                for j in range(operator_questions_num):
                    raw_data[i][j].append(row[41+i*operator_questions_num+j])

                for j in range(bystander_questions_num):
                    raw_data[i][operator_questions_num+j].append(row[56+i*bystander_questions_num+j])

    # 平均値とエラーバーに使う標準誤差を計算
    for i in range(method_num):
        for q in raw_data[i]:
            q_data = [int(x) for x in q]
            data[i].append(statistics.mean(q_data))
            yerr[i].append(statistics.pstdev(q_data)/math.sqrt(len(q_data)))

def add_anotation(ax, x1, x2, label):
    y1 = -0.5
    y2 = -0.8

    ax.plot([x1, x1, x2, x2], [y1, y2, y2, y1], 'k', clip_on=False)

    center = (x1 + x2) / 2
    ax.text(center+0.05, y2 - 0.1, label, fontsize=50, ha='center', va='top')

def add_asterisk(n, s, t, x, bar_width, data, yerr, dh=.05, asterisk='*'):
    lx, ly = x[n], data[s][n]
    rx, ry = x[n]+t*bar_width, data[t][n]

    ly += yerr[s][n]
    ry += yerr[t][n]
  
    ax_y0, ax_y1 = plt.gca().get_ylim()
    barh =.05
    dh *= (ax_y1 - ax_y0)
    barh *= (ax_y1 - ax_y0)
  
    y = max(ly, ry) + dh
  
    barx = [lx, lx, rx, rx]
    bary = [y-0.1, y+barh-0.1, y+barh-0.1, y-0.1]
    mid = ((lx+rx)/2, y+barh-0.2)
  
    plt.plot(barx, bary, c='black')
  
    kwargs = dict(ha='center', va='bottom')
    kwargs['fontsize'] = 42
  
    plt.text(*mid, asterisk, **kwargs)

def main():
    data = [[] for i in range(method_num)]
    yerr = [[] for i in range(method_num)]
    get_data(data, yerr)

    fig, ax = plt.subplots(figsize=(33, 10), dpi=330)
    bar_width = 0.2
    x = np.arange(all_questions_num)  # numpyで横軸を設定

    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')
    
    ax.grid(True, 'major', 'y', ls='--', lw=.5, c='k', alpha=.3)
    ax.tick_params(bottom=False)

    bar_colors = [colors.cnames['hotpink'], colors.cnames['deepskyblue'], colors.cnames['cornflowerblue']]
    bar_labels = ['optimized', 'fixed1', 'fixed2']

    for i in range(method_num):
        ax.bar(x+i*bar_width, data[i], bar_width, color=bar_colors[i], label=bar_labels[i], capsize=6, yerr=yerr[i])
        
    ax.set_ylabel('Mean ratings', weight='bold', fontsize=50, family='arial')
    ax.set_ylim([1,5])
    ax.set_yticklabels([1,2,3,4,5], weight='bold', fontsize=42, family='arial')
    ax.tick_params(axis='y', labelsize=42)
    
    ax.set_xticks(x + bar_width)
    ax.set_xticklabels(dimensions, weight='bold', fontsize=42, rotation=30, family='arial')
    
    ax.legend(bbox_to_anchor=(0.77, 1.15), loc='upper', borderaxespad=0, fontsize=42, ncol=3)

    # 有意差のアスタリスクをつける
    add_asterisk(0, 0, 1, x, bar_width, data, yerr)
    add_asterisk(0, 0, 2, x, bar_width, data, yerr, dh=0.15, asterisk='**')

    add_asterisk(3, 0, 1, x, bar_width, data, yerr)
    add_asterisk(3, 0, 2, x, bar_width, data, yerr, dh=0.15)

    add_asterisk(4, 0, 1, x, bar_width, data, yerr, asterisk='**')
    add_asterisk(4, 0, 2, x, bar_width, data, yerr, dh=0.15, asterisk='***')

    # axes外に注釈をつける
    xticks = ax.get_xticks()
    add_anotation(ax, xticks[0], xticks[4], 'main user')
    add_anotation(ax, xticks[5], xticks[7], 'bystander')
   
    output_file_name = 'questionnaire_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.05)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()