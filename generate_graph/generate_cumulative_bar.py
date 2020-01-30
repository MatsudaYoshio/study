import numpy as np
import matplotlib
import matplotlib.colors as colors
import matplotlib.pyplot as plt
from matplotlib import rc
from matplotlib.ticker import FormatStrFormatter

def main():
    dimensions = ['JR西日本', '在阪5私鉄', '公営・中小私鉄']

    data = [[44.1,44.5,44.6,44.6,44.5,44.6,44.5], [41.1,40.8,40.8,40.8,40.7,40.8,40.8], [14.8,14.7,14.6,14.6,14.8,14.6,14.7]]

    fig, ax = plt.subplots(figsize=(20, 13), dpi=100)
    x = np.arange(len(data[0]))

    rc('font', weight='bold')

    bar_width = 0.5

    ax.yaxis.labelpad = 15
    ax.tick_params(bottom=False)

    ax3 = ax.bar(x, data[0], width=bar_width, bottom=(np.array(data[1])+np.array(data[2])).tolist(), label=dimensions[0])
    ax2 = ax.bar(x, data[1], width=bar_width, bottom=data[2], label=dimensions[1])
    ax1 = ax.bar(x, data[2], width=bar_width, label=dimensions[2])

    for r1, r2, r3 in zip(ax1, ax2, ax3):
        h1 = r1.get_height()
        h2 = r2.get_height()
        h3 = r3.get_height()
        plt.text(r1.get_x() + r1.get_width() / 2., h1 / 2., "%.1f" % h1, ha="center", va="center", color="white", fontsize=32, fontweight="bold")
        plt.text(r2.get_x() + r2.get_width() / 2., h1 + h2 / 2., "%.1f" % h2, ha="center", va="center", color="white", fontsize=32, fontweight="bold")
        plt.text(r3.get_x() + r3.get_width() / 2., h1 + h2 + h3 / 2., "%.1f" % h3, ha="center", va="center", color="white", fontsize=32, fontweight="bold")

    ax.legend(bbox_to_anchor=(0.08, 1.1), loc='upper left', borderaxespad=0, fontsize=32, ncol=3)

    plt.rcParams['font.family'] = 'arial'
    plt.gca().yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
    plt.ylim([0,100])
    plt.ylabel('近畿圏のシェア(%)', fontsize=42, weight='bold')
    plt.yticks([0.0, 20.0, 40.0, 60.0, 80.0, 100.0], fontsize=32)
    ax.set_xticklabels(['', '2011', '2012', '2013', '2014', '2015', '2016', '2017'], weight='bold', fontsize=32, family='arial')

    plt.savefig('kinki_share.png', bbox_inches='tight', pad_inches=0.05)

if __name__ == '__main__':
    main()