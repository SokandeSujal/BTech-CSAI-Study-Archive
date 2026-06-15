import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import seaborn as sns
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import apriori, association_rules
import warnings
warnings.filterwarnings('ignore')

CSV_PATH = r"C:\Users\sujal\OneDrive\Desktop\Study\Btech\Sem 4\DETL\Exp 5\Groceries_dataset.csv"

df = pd.read_csv(CSV_PATH)
df.columns = df.columns.str.strip()
df['Date']      = pd.to_datetime(df['Date'], dayfirst=True, infer_datetime_format=True)
df['Month']     = df['Date'].dt.strftime('%b')
df['Month_num'] = df['Date'].dt.month
df['Quarter']   = df['Date'].dt.quarter.map({1:'Q1', 2:'Q2', 3:'Q3', 4:'Q4'})

baskets = df.groupby('Member_number')['itemDescription'].apply(list).tolist()

te       = TransactionEncoder()
te_array = te.fit_transform(baskets)
basket_df = pd.DataFrame(te_array, columns=te.columns_)

frequent_itemsets = apriori(basket_df, min_support=0.01, use_colnames=True)
rules_df          = association_rules(frequent_itemsets, metric='confidence', min_threshold=0.3)
rules_df['antecedents'] = rules_df['antecedents'].apply(lambda x: ', '.join(sorted(x)))
rules_df['consequents'] = rules_df['consequents'].apply(lambda x: ', '.join(sorted(x)))

BG    = '#0D1117'
CARD  = '#161B22'
WHITE = '#E6EDF3'
MUTED = '#8B949E'

month_order = ['Jan','Feb','Mar','Apr','May','Jun',
               'Jul','Aug','Sep','Oct','Nov','Dec']

plt.rcParams.update({
    'figure.facecolor': BG,        'axes.facecolor':    CARD,
    'axes.edgecolor':  '#30363D',  'axes.labelcolor':   WHITE,
    'xtick.color':     MUTED,      'ytick.color':       MUTED,
    'text.color':      WHITE,      'grid.color':        '#21262D',
    'grid.linestyle':  '--',       'grid.linewidth':    0.5,
    'font.family':     'DejaVu Sans',
    'axes.spines.top': False,      'axes.spines.right': False,
})

fig1 = plt.figure(figsize=(20, 14), facecolor=BG)
fig1.suptitle('🛒  Grocery Store — Exploratory Analysis Dashboard',
              fontsize=22, fontweight='bold', color=WHITE, y=0.98)
gs1 = gridspec.GridSpec(2, 2, figure=fig1, hspace=0.48, wspace=0.35,
                        left=0.06, right=0.97, top=0.92, bottom=0.07)

# 1A: Top 15 items
ax1 = fig1.add_subplot(gs1[0, 0])
top15  = df['itemDescription'].value_counts().head(15).sort_values(ascending=True)
colors = sns.color_palette('mako', len(top15))
bars   = ax1.barh(top15.index, top15.values, color=colors, height=0.65, edgecolor='none')
for bar, v in zip(bars, top15.values):
    ax1.text(bar.get_width() + top15.max() * 0.01,
             bar.get_y() + bar.get_height() / 2,
             f'{v:,}', va='center', fontsize=9, fontweight='bold', color=WHITE)
ax1.set_xlim(0, top15.max() * 1.14)
ax1.set_xlabel('Transaction Count', fontsize=10)
ax1.set_title('Top 15 Most Purchased Items', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax1.set_yticklabels(top15.index, fontsize=8.5)
ax1.grid(axis='x', alpha=0.4)
ax1.set_axisbelow(True)

# 1B: Monthly trend 
ax2 = fig1.add_subplot(gs1[0, 1])
monthly = (df.groupby(['Month_num', 'Month']).size()
             .reset_index(name='count')
             .sort_values('Month_num'))
present = monthly['Month'].tolist()
ax2.plot(present, monthly['count'], color='#2EA043',
         linewidth=2.5, marker='o', markersize=9,
         markerfacecolor='#F78166', markeredgecolor=BG, markeredgewidth=1.5, zorder=3)
ax2.fill_between(range(len(present)), monthly['count'], alpha=0.12, color='#2EA043')
for _, row in monthly.iterrows():
    ax2.annotate(f"{int(row['count']):,}",
                 (row['Month'], row['count']),
                 textcoords='offset points', xytext=(0, 9),
                 ha='center', fontsize=8.5, color=WHITE, fontweight='bold')
ax2.set_xticks(range(len(present)))
ax2.set_xticklabels(present, fontsize=9)
ax2.set_ylabel('Transactions', fontsize=10)
ax2.set_title('Monthly Transaction Volume', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax2.grid(axis='y', alpha=0.4)
ax2.set_axisbelow(True)

# 1C: Seaborn countplot top 10 
ax3 = fig1.add_subplot(gs1[1, 0])
order10 = df['itemDescription'].value_counts().head(10).index.tolist()
sns.countplot(data=df[df['itemDescription'].isin(order10)],
              y='itemDescription', order=order10,
              palette='plasma', ax=ax3, edgecolor='none')
ax3.set_title('Top 10 Items — Seaborn Count Plot', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax3.set_xlabel('Count', fontsize=10)
ax3.set_ylabel('', fontsize=10)
for p in ax3.patches:
    ax3.text(p.get_width() + 1, p.get_y() + p.get_height() / 2,
             f'{int(p.get_width()):,}', va='center', fontsize=9, color=WHITE)
ax3.tick_params(labelsize=9)
ax3.grid(axis='x', alpha=0.4)
ax3.set_axisbelow(True)

# 1D: Quarterly breakdown 
ax4 = fig1.add_subplot(gs1[1, 1])
q_counts = df['Quarter'].value_counts().sort_index()
q_colors = sns.color_palette('cool', len(q_counts))
b = ax4.bar(q_counts.index, q_counts.values, color=q_colors,
            edgecolor='none', width=0.55)
for bar, v in zip(b, q_counts.values):
    ax4.text(bar.get_x() + bar.get_width() / 2,
             bar.get_height() + q_counts.max() * 0.01,
             f'{v:,}', ha='center', fontsize=10, fontweight='bold', color=WHITE)
ax4.set_xlabel('Quarter', fontsize=10)
ax4.set_ylabel('Transactions', fontsize=10)
ax4.set_title('Transactions by Quarter', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax4.grid(axis='y', alpha=0.4)
ax4.set_axisbelow(True)

plt.savefig('fig1_exploratory.png', dpi=150, bbox_inches='tight', facecolor=BG)
plt.show()
print("✓ Figure 1 done")


fig2 = plt.figure(figsize=(20, 12), facecolor=BG)
fig2.suptitle('📊  Seaborn Deep Dives',
              fontsize=22, fontweight='bold', color=WHITE, y=0.98)
gs2 = gridspec.GridSpec(1, 2, figure=fig2, wspace=0.35,
                        left=0.06, right=0.97, top=0.90, bottom=0.08)

# 2A: Heatmap Item × Month (top 12 items) 
ax5 = fig2.add_subplot(gs2[0, 0])
top12 = df['itemDescription'].value_counts().head(12).index.tolist()
pivot = (df[df['itemDescription'].isin(top12)]
         .pivot_table(index='itemDescription', columns='Month',
                      values='Member_number', aggfunc='count', fill_value=0))
pivot = pivot.reindex(columns=[m for m in month_order if m in pivot.columns])
sns.heatmap(pivot, ax=ax5, cmap='YlGn', linewidths=0.4, linecolor='#21262D',
            annot=True, fmt='d', annot_kws={'size': 9, 'color': '#0D1117'},
            cbar_kws={'shrink': 0.7})
ax5.set_title('Purchase Heatmap — Top 12 Items × Month', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax5.set_xlabel('Month', fontsize=10)
ax5.set_ylabel('', fontsize=10)
ax5.tick_params(axis='both', labelsize=8.5)
ax5.collections[0].colorbar.ax.tick_params(colors=MUTED, labelsize=8)

# 2B: Item support bar 
ax6 = fig2.add_subplot(gs2[0, 1])
n_members = df['Member_number'].nunique()
item_sup  = (df['itemDescription'].value_counts() / n_members).head(15).sort_values(ascending=True)
colors6   = sns.color_palette('plasma', len(item_sup))
bars6     = ax6.barh(item_sup.index, item_sup.values, color=colors6,
                     height=0.65, edgecolor='none')
for bar, v in zip(bars6, item_sup.values):
    ax6.text(bar.get_width() + 0.001, bar.get_y() + bar.get_height() / 2,
             f'{v:.2%}', va='center', fontsize=9, fontweight='bold', color=WHITE)
ax6.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'{x:.0%}'))
ax6.set_xlabel('Support', fontsize=10)
ax6.set_title('Item Support — Top 15', fontsize=13,
              fontweight='bold', color=WHITE, pad=12)
ax6.set_yticklabels(item_sup.index, fontsize=8.5)
ax6.grid(axis='x', alpha=0.4)
ax6.set_axisbelow(True)

plt.savefig('fig2_seaborn.png', dpi=150, bbox_inches='tight', facecolor=BG)
plt.show()
print("✓ Figure 2 done")

fig3 = plt.figure(figsize=(20, 10), facecolor=BG)
fig3.suptitle('🔗  Apriori — Association Rules  |  min_support=1%  min_confidence=30%',
              fontsize=18, fontweight='bold', color=WHITE, y=0.98)
gs3 = gridspec.GridSpec(1, 3, figure=fig3, wspace=0.40,
                        left=0.06, right=0.97, top=0.88, bottom=0.12)

if len(rules_df) == 0:
    fig3.text(0.5, 0.5,
              'No rules found.\nTry lowering min_support or min_confidence.',
              ha='center', va='center', fontsize=14, color=MUTED)
else:
    # 3A: Top rules by confidence 
    ax7 = fig3.add_subplot(gs3[0, 0])
    top_rules = rules_df.sort_values('confidence', ascending=True).tail(12)
    labels    = [f"{r['antecedents']} → {r['consequents']}"
                 for _, r in top_rules.iterrows()]
    conf_vals = top_rules['confidence'].values
    bar_c     = ['#2EA043' if v >= 0.6 else '#388BFD' if v >= 0.4 else MUTED
                 for v in conf_vals]
    bars7 = ax7.barh(range(len(labels)), conf_vals, color=bar_c,
                     height=0.6, edgecolor='none')
    ax7.set_yticks(range(len(labels)))
    ax7.set_yticklabels(labels, fontsize=8)
    for bar, v in zip(bars7, conf_vals):
        ax7.text(bar.get_width() + 0.005, bar.get_y() + bar.get_height() / 2,
                 f'{v:.0%}', va='center', fontsize=9, color=WHITE, fontweight='bold')
    ax7.set_xlim(0, 1.15)
    ax7.set_xlabel('Confidence', fontsize=10)
    ax7.set_title('Top Rules by Confidence', fontsize=13,
                  fontweight='bold', color=WHITE, pad=12)
    ax7.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'{x:.0%}'))
    ax7.grid(axis='x', alpha=0.4)
    ax7.set_axisbelow(True)

    # 3B: Scatter support vs confidence (size = lift) 
    ax8 = fig3.add_subplot(gs3[0, 1])
    sc = ax8.scatter(rules_df['support'], rules_df['confidence'],
                     s=rules_df['lift'] * 200,
                     c=rules_df['lift'], cmap='RdYlGn',
                     alpha=0.80, edgecolors=WHITE, linewidths=0.4, zorder=3)
    cbar = plt.colorbar(sc, ax=ax8, shrink=0.8, pad=0.02)
    cbar.set_label('Lift', color=MUTED, fontsize=9)
    cbar.ax.tick_params(colors=MUTED, labelsize=8)
    ax8.set_xlabel('Support', fontsize=10)
    ax8.set_ylabel('Confidence', fontsize=10)
    ax8.set_title('Support vs Confidence\n(bubble size = Lift)', fontsize=13,
                  fontweight='bold', color=WHITE, pad=8)
    ax8.xaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'{x:.0%}'))
    ax8.yaxis.set_major_formatter(plt.FuncFormatter(lambda x, _: f'{x:.0%}'))
    ax8.grid(alpha=0.4)
    ax8.set_axisbelow(True)

    # 3C: Rules table 
    ax9 = fig3.add_subplot(gs3[0, 2])
    ax9.axis('off')
    ax9.set_title('Top 10 Rules', fontsize=13, fontweight='bold', color=WHITE, pad=12)
    display = rules_df.sort_values('confidence', ascending=False).head(10)
    col_labels  = ['Antecedent', 'Consequent', 'Sup', 'Conf', 'Lift']
    table_data  = [[r['antecedents'], r['consequents'],
                    f"{r['support']:.3f}", f"{r['confidence']:.2f}", f"{r['lift']:.2f}"]
                   for _, r in display.iterrows()]
    table = ax9.table(cellText=table_data, colLabels=col_labels,
                      loc='center', cellLoc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(8.5)
    table.scale(1.05, 1.9)
    for (row, col), cell in table.get_celld().items():
        cell.set_edgecolor('#30363D')
        if row == 0:
            cell.set_facecolor('#238636')
            cell.set_text_props(color=WHITE, fontweight='bold')
        elif row % 2 == 0:
            cell.set_facecolor('#1C2128')
            cell.set_text_props(color=WHITE)
        else:
            cell.set_facecolor(CARD)
            cell.set_text_props(color=WHITE)

plt.savefig('fig3_apriori.png', dpi=150, bbox_inches='tight', facecolor=BG)
plt.show()
print("✓ Figure 3 done")
print(f"\nTotal rules found: {len(rules_df)}")
print(rules_df.sort_values('confidence', ascending=False).head(10).to_string(index=False))