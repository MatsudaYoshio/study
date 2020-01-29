import numpy as np
import matplotlib
import matplotlib.colors as mcolors
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
method_colors = [mcolors.cnames['hotpink'], mcolors.cnames['deepskyblue'], mcolors.cnames['cornflowerblue']]
method_labels = ['optimized', 'fixed1', 'fixed2']

def get_data(data):
    with open('experiment2_data.csv', 'r') as f:
        reader = csv.reader(f)
        next(reader)  # ヘッダーを読み飛ばす

        for row in reader:
            for i in range(method_num):
                for j in range(operator_questions_num):
                    data[i][j].append(int(row[41+i*operator_questions_num+j]))

                for j in range(bystander_questions_num):
                    data[i][operator_questions_num+j].append(int(row[56+i*bystander_questions_num+j]))

def add_anotation(ax, x1, x2, label):
    y1 = -0.5-0.9
    y2 = -0.8-0.9

    ax.plot([x1, x1, x2, x2], [y1, y2, y2, y1], 'k', clip_on=False)

    center = (x1 + x2) / 2
    ax.text(center+0.05, y2 - 0.1, label, fontsize=50, ha='center', va='top')

def add_asterisk(n, s, x, widths, dh=.05, asterisk='*'):
    lx, ly = x[n], 5
    rx, ry = x[n]+s*widths, 5
  
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
    data = [[[] for i in range(all_questions_num)] for j in range(method_num)]
    get_data(data)

    fig, ax = plt.subplots(figsize=(33, 10), dpi=100)
    widths = 0.2
    x = np.arange(all_questions_num)  # numpyで横軸を設定

    plt.rcParams['font.family'] = 'arial'
    rc('font', weight='bold')

    ax.tick_params(bottom=False)

    positions = [x, list(map(lambda x: x+widths, x)), list(map(lambda x: x+2*widths, x))]

    box_colors = [[x]*all_questions_num for x in method_colors]
    black_color = [mcolors.cnames['black']]*all_questions_num*2

    for i in range(method_num):
        bp = ax.boxplot(data[i], positions=positions[i], patch_artist=True, showfliers=True, widths=widths)

        # 箱の設定
        for b, c in zip(bp['boxes'], box_colors[i]):
            b.set(color=mcolors.cnames['black'], linewidth=0)  # boxの外枠の色
            b.set_facecolor(c) # boxの色

        # 中央値の線の設定
        for b, c in zip(bp['medians'], black_color):
            b.set(color=c, linewidth=3.5)

        # ヒゲの線の設定
        for b, c in zip(bp['whiskers'], black_color):
            b.set(color=c, linewidth=2)

        # ヒゲの先端の線の設定
        for b, c in zip(bp['caps'], black_color):
            b.set(color=c, linewidth=2)

        # 外れ値の設定
        for b, c in zip(bp['fliers'], box_colors[i]):
            b.set(markerfacecolor=c, markeredgecolor=mcolors.cnames['black'], marker='o', markersize=10, linestyle='none')

    ax.tick_params(axis='y', labelsize=42)
    ax.set_ylabel('Likert Scale Scores', weight='bold', fontsize=50, family='arial')
    ax.set_ylim([0.75, 6.5])

    plt.yticks([1, 2, 3, 4, 5], ['1', '2', '3', '4', '5'], fontweight='bold', family='arial')

    ax.set_xticks(x + widths)
    ax.set_xticklabels(dimensions, weight='bold', fontsize=42, rotation=30, family='arial')

    # 凡例をつけるためにダミーのプロットをする
    dummy = [plt.bar([1], 1, color=x)[0] for x in method_colors]
    plt.legend(tuple(dummy), tuple(method_labels), bbox_to_anchor=(0.77, 1.15), loc='upper', borderaxespad=0, fontsize=42, ncol=3) #レジェンドの表示
    for d in dummy:
        d.set_visible(False)

    # 有意差のアスタリスクをつける
    add_asterisk(0, 1, x, widths)
    add_asterisk(0, 2, x, widths, dh=0.15, asterisk='**')

    add_asterisk(3, 1, x, widths)
    add_asterisk(3, 2, x, widths, dh=0.15)

    add_asterisk(4, 1, x, widths, asterisk='**')
    add_asterisk(4, 2, x, widths, dh=0.15, asterisk='***')

    # axes外に注釈をつける
    xticks = ax.get_xticks()
    add_anotation(ax, xticks[0], xticks[4], 'main user')
    add_anotation(ax, xticks[5], xticks[7], 'bystander')

    output_file_name = 'experiment2_questionnaire_all_result.eps'
    plt.savefig(output_file_name, bbox_inches='tight', pad_inches=0.05)

    # latexでのずれを防ぐため，一度pdfにしてepsに戻すスクリプトを実行
    subprocess.run(['./epsbound.sh', output_file_name])

if __name__ == '__main__':
    main()