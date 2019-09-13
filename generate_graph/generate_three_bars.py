import numpy as np
import matplotlib
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter
from matplotlib import rc
import csv
import statistics
import math
import subprocess

def add_asterisk(s, t, x, bar_width, data, yerr):
    lx, ly = x[s], data[s]
    rx, ry = x[s]+(t-s)*bar_width, data[t]

    ly += yerr[s]
    ry += yerr[t]

    ax_y0, ax_y1 = plt.gca().get_ylim()
    dh=.05
    barh =.04
    dh *= (ax_y1 - ax_y0)
    barh *= (ax_y1 - ax_y0)
  
    y = max(ly, ry) + dh
  
    barx = [lx, lx, rx, rx]
    dy = 0.9
    bary = [y-dy, y+barh-dy, y+barh-dy, y-dy]
    mid = ((lx+rx)/2, y+barh-2*dy)
  
    plt.plot(barx, bary, c='black')

    kwargs = dict(ha='center', va='bottom')
    kwargs['fontsize'] = 44
  
    plt.text(*mid, '*', **kwargs)

def main():

    bar_colors = [colors.cnames['hotpink'], colors.cnames['deepskyblue'], colors.cnames['cornflowerblue']]
    bar_labels = ['optimized', 'fixed1', 'fixed2']

    fig = plt.figure(figsize=(30, 10), dpi=220)

    plt.subplots_adjust(wspace=0.4)
    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')

    # 左のグラフの描画
    plt.subplot(1,3,1)

    method_num = 3
    user_num = 2

    raw_data = [[[] for i in range(user_num)] for j in range(method_num)]
    data = [[] for i in range(method_num)]
    yerr = [[] for i in range(method_num)]

    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)

        for row in reader:
            for i in range(method_num):
                for j in range(user_num):
                    raw_data[i][j].append(row[8+i+j*method_num])

        for i in range(method_num):
            for q in raw_data[i]:
                q_data = [int(x) for x in q]
                data[i].append(statistics.mean(q_data))
                yerr[i].append(statistics.pstdev(q_data)/math.sqrt(len(q_data)))

    x = np.arange(user_num)
    bar_width = 0.2

    plt.grid(which='major', axis='y', color='black', linestyle='--', alpha=0.3)
    plt.tick_params(bottom=False)

    for i in range(method_num):
        plt.bar(x+i*bar_width, data[i], color=bar_colors[i], width=bar_width, yerr=yerr[i], capsize=6, label=bar_labels[i], align='center')

    plt.ylim([50,90])
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%.2f'))
    plt.ylabel('Mean accuracy rate [%]', fontsize=44, weight='bold')
    plt.yticks([50.00,60.00,70.00,80.00,90.00], fontsize=44)

    plt.xlabel('(a)', fontsize=44, weight='bold')
    plt.xticks(x+bar_width, ['main user', 'bystander'], fontsize=44)

    plt.legend(bbox_to_anchor=(0.6, 1.2), loc='upper left', borderaxespad=0, fontsize=44, ncol=3)


    # 中央のグラフの描画
    plt.subplot(1,3,2)

    raw_data = [[] for i in range(method_num)]
    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)

        for row in reader:
            for i in range(method_num):
                raw_data[i].append(int(row[14+i])/1000)
            
    data = []
    yerr = []
    for i in range(method_num):
        data.append(statistics.mean(raw_data[i]))
        yerr.append(statistics.pstdev(raw_data[i])/math.sqrt(len(raw_data[i])))

    x = np.arange(method_num)
    bar_width = 1.0

    plt.grid(which='major', axis='y', color='black', linestyle='--', alpha=0.3)
    plt.tick_params(bottom=False)

    plt.bar(x, data, color=bar_colors, width=bar_width, yerr=yerr, capsize = 6, align='center')

    plt.ylim([130,180])
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d'))
    plt.ylabel('Mean time [s]', fontsize=44, weight='bold')
    plt.yticks([130,140,150,160,170,180], fontsize=44)

    dummy = ['a']*method_num
    plt.xlim([-3,5])
    plt.xlabel('(b)', fontsize=44, weight='bold')
    plt.xticks(x, dummy, fontsize=44, color=colors.cnames['white'])


    # 右のグラフの描画
    plt.subplot(1,3,3)

    raw_data = [[] for i in range(method_num)]
    with open('experiment_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)

        for row in reader:
            for i in range(method_num):
                raw_data[i].append(int(row[17+i]))
            
    data = []
    yerr = []
    for i in range(method_num):
        data.append(statistics.mean(raw_data[i]))
        yerr.append(statistics.pstdev(raw_data[i])/math.sqrt(len(raw_data[i])))

    plt.grid(which='major', axis='y', color='black', linestyle='--', alpha=0.3)
    plt.tick_params(bottom=False)

    plt.bar(x, data, color=bar_colors, width=bar_width, yerr=yerr, capsize=6, align='center')
    plt.ylim([10,50])
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%d'))
    plt.ylabel('Mean # of item selections', fontsize=44, weight='bold')
    plt.yticks([10,20,30,40,50], fontsize=44)

    plt.xlim([-3,5])
    plt.xlabel('(c)', fontsize=44, weight='bold')
    plt.xticks(x, dummy, fontsize=44, color=colors.cnames['white'])

    add_asterisk(0, 2, x, bar_width, data, yerr)
    add_asterisk(1, 2, x, bar_width, data, yerr)


    output_file_name = 'task_variables_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.2)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()