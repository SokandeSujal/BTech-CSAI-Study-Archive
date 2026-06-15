import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report, ConfusionMatrixDisplay
from ucimlrepo import fetch_ucirepo
from fpdf import FPDF
from PIL import Image
import os
import warnings
warnings.filterwarnings('ignore')

OUTPUT_DIR = "lab6_output"
os.makedirs(OUTPUT_DIR, exist_ok=True)

heart_disease = fetch_ucirepo(id=45)
X = heart_disease.data.features
y = heart_disease.data.targets
df = pd.concat([X, y], axis=1)

df['target'] = (df['num'] > 0).astype(int)
df.drop('num', axis=1, inplace=True)

print("Missing values before cleaning:\n", df.isnull().sum())
df = df.dropna()
print(f"\nAfter dropping missing values: {len(df)} samples remain")

plt.style.use('seaborn-v0_8-darkgrid')
bg_color = '#0D1117'
card_color = '#161B22'
text_color = '#E6EDF3'
muted = '#8B949E'

plt.rcParams.update({
    'figure.facecolor': bg_color,
    'axes.facecolor': card_color,
    'axes.edgecolor': '#30363D',
    'axes.labelcolor': text_color,
    'xtick.color': muted,
    'ytick.color': muted,
    'text.color': text_color,
    'grid.color': '#21262D',
    'grid.linestyle': '--',
    'grid.linewidth': 0.5,
})

fig1, axes = plt.subplots(2, 2, figsize=(12, 8))
ax = axes[0, 0]
df['target'].value_counts().plot(kind='bar', color=['#2EA043', '#F78166'], ax=ax)
ax.set_title('Target Distribution (0=No Disease, 1=Disease)', fontsize=12)
ax.set_xlabel('Target')
ax.set_ylabel('Count')
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() + p.get_width()/2, p.get_height()), ha='center', va='bottom')

ax = axes[0, 1]
df['age'].hist(bins=20, color='#388BFD', edgecolor='white', ax=ax)
ax.set_title('Age Distribution')
ax.set_xlabel('Age')
ax.set_ylabel('Frequency')

ax = axes[1, 0]
num_cols = ['age', 'trestbps', 'chol', 'thalach', 'oldpeak']
corr = df[num_cols].corr()
sns.heatmap(corr, annot=True, cmap='coolwarm', ax=ax, cbar_kws={'shrink': 0.8})
ax.set_title('Correlation Heatmap (Numerical Features)')

ax = axes[1, 1]
categorical_cols = ['cp', 'restecg', 'slope', 'ca', 'thal']
df[categorical_cols].nunique().plot(kind='bar', color='#F39C12', ax=ax)
ax.set_title('Unique Values in Categorical Features')
ax.set_ylabel('Number of categories')
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'eda_overview.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()

fig2, axes = plt.subplots(2, 3, figsize=(12, 8))
axes = axes.flatten()
for i, col in enumerate(categorical_cols):
    df[col].value_counts().sort_index().plot(kind='bar', ax=axes[i], color='#2EA043')
    axes[i].set_title(f'Distribution of {col}')
    axes[i].set_xlabel(col)
    axes[i].set_ylabel('Count')
for j in range(len(categorical_cols), len(axes)):
    axes[j].axis('off')
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'categorical_distributions.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()

feature_cols = [col for col in df.columns if col != 'target']
X = df[feature_cols]
y = df['target']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

clf = DecisionTreeClassifier(random_state=42, max_depth=5, min_samples_split=10, min_samples_leaf=5)
clf.fit(X_train, y_train)

y_pred = clf.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f"Test Accuracy: {accuracy:.4f}")
print("\nClassification Report:\n", classification_report(y_test, y_pred))

cm = confusion_matrix(y_test, y_pred)
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=['No Disease', 'Disease'])
fig_cm, ax_cm = plt.subplots(figsize=(5, 4))
disp.plot(ax=ax_cm, cmap='Greens', values_format='d')
ax_cm.set_facecolor(card_color)
fig_cm.patch.set_facecolor(bg_color)
plt.title('Confusion Matrix', color=text_color)
plt.savefig(os.path.join(OUTPUT_DIR, 'confusion_matrix.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()

plt.figure(figsize=(12, 8))
plot_tree(clf, feature_names=feature_cols, class_names=['No Disease', 'Disease'], filled=True, rounded=True, fontsize=8)
plt.title('Decision Tree Visualization', fontsize=14, color=text_color)
plt.savefig(os.path.join(OUTPUT_DIR, 'decision_tree.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()

importances = clf.feature_importances_
indices = np.argsort(importances)[::-1]
plt.figure(figsize=(8, 5))
plt.barh(range(len(indices)), importances[indices], color='#2EA043')
plt.yticks(range(len(indices)), [feature_cols[i] for i in indices])
plt.xlabel('Feature Importance')
plt.title('Feature Importance from Decision Tree')
plt.gca().invert_yaxis()
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'feature_importance.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()

def add_image_safe(pdf, img_path, x, y, w):
    img = Image.open(img_path)
    img.thumbnail((w*4, 300), Image.Resampling.LANCZOS)
    temp_path = os.path.join(OUTPUT_DIR, "temp_resized.png")
    img.save(temp_path, "PNG")
    pdf.image(temp_path, x=x, y=y, w=w)
    os.remove(temp_path)

pdf = FPDF()
pdf.add_page()
pdf.set_font("Arial", "B", 16)
pdf.cell(0, 10, "Lab 6: Heart Disease Classification Report", ln=True, align='C')
pdf.ln(5)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 8, "Dataset: Heart Disease (UCI ID 45). Binary classification task: predict presence of heart disease (target > 0) vs no disease (target = 0).")
pdf.ln(4)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Exploratory Data Analysis", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 6, f"Total samples after cleaning: {len(df)}\nFeatures used: {len(feature_cols)}\nDisease prevalence: {y.mean()*100:.1f}%")
pdf.image(os.path.join(OUTPUT_DIR, 'eda_overview.png'), x=10, y=None, w=180)
pdf.ln(85)
pdf.image(os.path.join(OUTPUT_DIR, 'categorical_distributions.png'), x=10, y=None, w=180)
pdf.ln(85)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Model Training & Evaluation", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 6, f"Algorithm: Decision Tree (max_depth=5, min_samples_split=10, min_samples_leaf=5)\nTrain/Test split: 80/20\nAccuracy: {accuracy:.4f}")
pdf.ln(4)
pdf.cell(0, 10, "Classification Report:", ln=True)
report_lines = classification_report(y_test, y_pred, output_dict=False).split('\n')
for line in report_lines:
    pdf.set_font("Courier", "", 9)
    pdf.cell(0, 5, line, ln=True)
pdf.ln(5)
pdf.image(os.path.join(OUTPUT_DIR, 'confusion_matrix.png'), x=10, y=None, w=100)
pdf.ln(60)
pdf.image(os.path.join(OUTPUT_DIR, 'feature_importance.png'), x=10, y=None, w=100)
pdf.ln(65)
add_image_safe(pdf, os.path.join(OUTPUT_DIR, 'decision_tree.png'), x=10, y=None, w=180)
pdf.ln(10)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Generated Images", ln=True)
pdf.set_font("Arial", "", 12)
images_list = ["eda_overview.png", "categorical_distributions.png", "confusion_matrix.png", "feature_importance.png", "decision_tree.png"]
for img in images_list:
    pdf.cell(0, 6, f"- {img}", ln=True)
pdf.output(os.path.join(OUTPUT_DIR, "classification_report.pdf"))
print(f"\nAll outputs saved in '{OUTPUT_DIR}' folder.")
print("PDF report generated: lab6_output/classification_report.pdf")