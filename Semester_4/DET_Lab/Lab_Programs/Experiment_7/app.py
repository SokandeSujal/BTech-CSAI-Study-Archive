import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, DBSCAN
from sklearn.metrics import silhouette_score, davies_bouldin_score, calinski_harabasz_score
from sklearn.decomposition import PCA
from scipy.cluster.hierarchy import dendrogram, linkage, fcluster
from fpdf import FPDF
from PIL import Image
from tqdm import tqdm
import os
import warnings
warnings.filterwarnings('ignore')

OUTPUT_DIR = "lab7_output"
os.makedirs(OUTPUT_DIR, exist_ok=True)

print("="*60)
print("LAB 7: CLUSTERING - STARTING...")
print("="*60)

# ------------------------- DATASET LOADING (PRIORITY ORDER) -------------------------
local_csv = "customer_segmentation_data.csv"
url_csv = "https://raw.githubusercontent.com/selva86/datasets/master/Customer%20Segmentation.csv"

df = None

if os.path.exists(local_csv):
    df = pd.read_csv(local_csv)
    print(f"✓ Loaded local dataset: {local_csv}")
else:
    try:
        df = pd.read_csv(url_csv)
        print("✓ Loaded dataset from GitHub URL.")
    except:
        print("⚠ URL fetch failed. Generating synthetic dataset locally...")
        data_dict = {
            'CustomerID': range(1, 201),
            'Gender': np.random.choice(['Male', 'Female'], 200),
            'Age': np.random.randint(18, 70, 200),
            'Annual Income (k$)': np.random.randint(15, 140, 200),
            'Spending Score (1-100)': np.random.randint(1, 100, 200)
        }
        df = pd.DataFrame(data_dict)
        print("✓ Synthetic dataset generated.")

print(f"Dataset shape: {df.shape}")
print("Missing values:\n", df.isnull().sum())

# ------------------------- LIGHT THEME FOR PLOTS -------------------------
plt.style.use('seaborn-v0_8-whitegrid')
bg_color = 'white'
card_color = '#f8f9fa'
text_color = '#212529'
muted = '#6c757d'

plt.rcParams.update({
    'figure.facecolor': bg_color,
    'axes.facecolor': bg_color,
    'axes.edgecolor': '#dee2e6',
    'axes.labelcolor': text_color,
    'xtick.color': text_color,
    'ytick.color': text_color,
    'text.color': text_color,
    'grid.color': '#e9ecef',
    'grid.linestyle': '--',
    'grid.linewidth': 0.5,
})

# ------------------------- EDA PLOTS -------------------------
print("\n[1/7] Generating EDA plots...")
fig1, axes = plt.subplots(2, 2, figsize=(12, 8))
ax = axes[0, 0]
df['Gender'].value_counts().plot(kind='bar', color=['#2ea043', '#f78166'], ax=ax)
ax.set_title('Gender Distribution')
ax.set_xlabel('Gender')
ax.set_ylabel('Count')
for p in ax.patches:
    ax.annotate(str(p.get_height()), (p.get_x() + p.get_width()/2, p.get_height()), ha='center', va='bottom')

ax = axes[0, 1]
df['Age'].hist(bins=20, color='#388bfd', edgecolor='black', ax=ax)
ax.set_title('Age Distribution')
ax.set_xlabel('Age')
ax.set_ylabel('Frequency')

ax = axes[1, 0]
num_cols = ['Age', 'Annual Income (k$)', 'Spending Score (1-100)']
corr = df[num_cols].corr()
sns.heatmap(corr, annot=True, cmap='coolwarm', ax=ax, cbar_kws={'shrink': 0.8})
ax.set_title('Correlation Heatmap')

ax = axes[1, 1]
df['Spending Score (1-100)'].hist(bins=20, color='#f39c12', edgecolor='black', ax=ax)
ax.set_title('Spending Score Distribution')
ax.set_xlabel('Spending Score')
ax.set_ylabel('Frequency')
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'eda_overview.png'), dpi=100, bbox_inches='tight', facecolor=bg_color)
plt.close()
print("✓ EDA plots saved.")

# ------------------------- PREPROCESSING -------------------------
X = df[['Age', 'Annual Income (k$)', 'Spending Score (1-100)']].copy()
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# ------------------------- ELBOW METHOD (K-MEANS) -------------------------
print("\n[2/7] Computing Elbow Method (K-Means)...")
wcss = []
for i in tqdm(range(1, 11), desc="K-Means iterations"):
    kmeans = KMeans(n_clusters=i, init='k-means++', max_iter=300, n_init=10, random_state=42)
    kmeans.fit(X_scaled)
    wcss.append(kmeans.inertia_)

plt.figure(figsize=(8, 5))
plt.plot(range(1, 11), wcss, marker='o', color='#2ea043', linewidth=2)
plt.title('Elbow Method for Optimal K')
plt.xlabel('Number of clusters')
plt.ylabel('WCSS')
plt.grid(alpha=0.3)
plt.savefig(os.path.join(OUTPUT_DIR, 'elbow_method.png'), dpi=100, bbox_inches='tight')
plt.close()
print("✓ Elbow plot saved.")

optimal_k = 5
print(f"Using optimal k = {optimal_k}")

print("\n[3/7] Training K-Means...")
kmeans = KMeans(n_clusters=optimal_k, init='k-means++', max_iter=300, n_init=10, random_state=42)
kmeans_labels = kmeans.fit_predict(X_scaled)

kmeans_silhouette = silhouette_score(X_scaled, kmeans_labels)
kmeans_db = davies_bouldin_score(X_scaled, kmeans_labels)
kmeans_ch = calinski_harabasz_score(X_scaled, kmeans_labels)
print(f"✓ K-Means done. Silhouette: {kmeans_silhouette:.4f}")

# ------------------------- HIERARCHICAL CLUSTERING -------------------------
print("\n[4/7] Performing Hierarchical Clustering (linkage)...")
print("   Computing linkage matrix (this may take a moment)...")
linkage_matrix = linkage(X_scaled, method='ward')
print("   Generating dendrogram...")
plt.figure(figsize=(12, 6))
dendrogram(linkage_matrix, truncate_mode='level', p=5, color_threshold=0.7*max(linkage_matrix[:,2]))
plt.title('Hierarchical Clustering Dendrogram')
plt.xlabel('Data Points')
plt.ylabel('Distance')
plt.savefig(os.path.join(OUTPUT_DIR, 'dendrogram.png'), dpi=100, bbox_inches='tight')
plt.close()

hier_labels = fcluster(linkage_matrix, t=optimal_k, criterion='maxclust')
hier_silhouette = silhouette_score(X_scaled, hier_labels)
hier_db = davies_bouldin_score(X_scaled, hier_labels)
hier_ch = calinski_harabasz_score(X_scaled, hier_labels)
print(f"✓ Hierarchical done. Silhouette: {hier_silhouette:.4f}")

# ------------------------- DBSCAN -------------------------
print("\n[5/7] Tuning DBSCAN (epsilon search)...")
eps_values = np.linspace(0.1, 1.5, 10)
silhouette_scores = []
best_eps = 0.5
best_score = -1
for eps in tqdm(eps_values, desc="DBSCAN eps tuning"):
    dbscan = DBSCAN(eps=eps, min_samples=5)
    labels = dbscan.fit_predict(X_scaled)
    if len(set(labels)) > 1 and len(set(labels)) < len(X_scaled):
        score = silhouette_score(X_scaled, labels)
        silhouette_scores.append(score)
        if score > best_score:
            best_score = score
            best_eps = eps
    else:
        silhouette_scores.append(-1)

plt.figure(figsize=(8, 5))
plt.plot(eps_values, silhouette_scores, marker='o', color='#2ea043')
plt.title('DBSCAN Silhouette Score vs Epsilon')
plt.xlabel('Epsilon')
plt.ylabel('Silhouette Score')
plt.grid(alpha=0.3)
plt.savefig(os.path.join(OUTPUT_DIR, 'dbscan_eps_tuning.png'), dpi=100, bbox_inches='tight')
plt.close()
print(f"✓ Best eps = {best_eps:.2f}")

print("   Running final DBSCAN...")
dbscan = DBSCAN(eps=best_eps, min_samples=5)
dbscan_labels = dbscan.fit_predict(X_scaled)
n_clusters_db = len(set(dbscan_labels)) - (1 if -1 in dbscan_labels else 0)
n_noise = list(dbscan_labels).count(-1)
print(f"   DBSCAN found {n_clusters_db} clusters and {n_noise} noise points.")

if n_clusters_db > 1:
    dbscan_silhouette = silhouette_score(X_scaled[dbscan_labels != -1], dbscan_labels[dbscan_labels != -1])
    dbscan_db = davies_bouldin_score(X_scaled[dbscan_labels != -1], dbscan_labels[dbscan_labels != -1])
    dbscan_ch = calinski_harabasz_score(X_scaled[dbscan_labels != -1], dbscan_labels[dbscan_labels != -1])
else:
    dbscan_silhouette = -1
    dbscan_db = -1
    dbscan_ch = -1
    print("   ⚠ DBSCAN produced too few clusters for valid metrics.")

# ------------------------- PCA VISUALIZATION -------------------------
print("\n[6/7] Creating PCA visualizations...")
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_scaled)

fig, axes = plt.subplots(1, 3, figsize=(15, 5))
scatter1 = axes[0].scatter(X_pca[:, 0], X_pca[:, 1], c=kmeans_labels, cmap='tab10', alpha=0.7)
axes[0].set_title(f'K-Means Clustering (k={optimal_k})')
axes[0].set_xlabel('PC1')
axes[0].set_ylabel('PC2')
plt.colorbar(scatter1, ax=axes[0])

scatter2 = axes[1].scatter(X_pca[:, 0], X_pca[:, 1], c=hier_labels, cmap='tab10', alpha=0.7)
axes[1].set_title(f'Hierarchical Clustering (k={optimal_k})')
axes[1].set_xlabel('PC1')
axes[1].set_ylabel('PC2')
plt.colorbar(scatter2, ax=axes[1])

scatter3 = axes[2].scatter(X_pca[:, 0], X_pca[:, 1], c=dbscan_labels, cmap='tab10', alpha=0.7)
axes[2].set_title(f'DBSCAN Clustering (eps={best_eps:.2f})')
axes[2].set_xlabel('PC1')
axes[2].set_ylabel('PC2')
plt.colorbar(scatter3, ax=axes[2])
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'clustering_comparison.png'), dpi=100, bbox_inches='tight')
plt.close()
print("✓ PCA comparison plot saved.")

# ------------------------- CLUSTER PROFILES -------------------------
kmeans_df = df.copy()
kmeans_df['Cluster'] = kmeans_labels
kmeans_profile = kmeans_df.groupby('Cluster')[['Age', 'Annual Income (k$)', 'Spending Score (1-100)']].mean()

fig, axes = plt.subplots(1, 3, figsize=(15, 4))
for i, col in enumerate(['Age', 'Annual Income (k$)', 'Spending Score (1-100)']):
    kmeans_profile[col].plot(kind='bar', ax=axes[i], color='#2ea043')
    axes[i].set_title(f'K-Means: {col} by Cluster')
    axes[i].set_xlabel('Cluster')
    axes[i].set_ylabel(col)
plt.tight_layout()
plt.savefig(os.path.join(OUTPUT_DIR, 'cluster_profiles.png'), dpi=100, bbox_inches='tight')
plt.close()
print("✓ Cluster profiles saved.")

# ------------------------- METRICS TABLE -------------------------
metrics_df = pd.DataFrame({
    'Algorithm': ['K-Means', 'Hierarchical', 'DBSCAN'],
    'Silhouette Score': [kmeans_silhouette, hier_silhouette, dbscan_silhouette],
    'Davies-Bouldin Index': [kmeans_db, hier_db, dbscan_db],
    'Calinski-Harabasz Index': [kmeans_ch, hier_ch, dbscan_ch]
})

fig, ax = plt.subplots(figsize=(8, 4))
ax.axis('tight')
ax.axis('off')
table = ax.table(cellText=metrics_df.round(4).values, colLabels=metrics_df.columns, loc='center', cellLoc='center')
table.auto_set_font_size(False)
table.set_fontsize(10)
table.scale(1.2, 1.5)
for (row, col), cell in table.get_celld().items():
    if row == 0:
        cell.set_facecolor('#238636')
        cell.set_text_props(color='white', fontweight='bold')
    else:
        cell.set_facecolor('#f8f9fa' if row % 2 == 0 else '#e9ecef')
        cell.set_text_props(color='black')
plt.title('Clustering Performance Metrics', fontsize=14, pad=20)
plt.savefig(os.path.join(OUTPUT_DIR, 'metrics_table.png'), dpi=100, bbox_inches='tight')
plt.close()
print("✓ Metrics table saved.")

# ------------------------- PDF REPORT -------------------------
print("\n[7/7] Generating PDF report...")
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
pdf.cell(0, 10, "Lab 7: Customer Segmentation using Clustering Techniques", ln=True, align='C')
pdf.ln(5)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 8, "Dataset: Customer Segmentation Dataset (Mall Customers). Unsupervised learning task: group customers based on age, annual income, and spending behavior.")
pdf.ln(4)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Exploratory Data Analysis", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 6, f"Total samples: {len(df)}\nFeatures used: Age, Annual Income, Spending Score\nGender distribution: {df['Gender'].value_counts().to_dict()}")
pdf.image(os.path.join(OUTPUT_DIR, 'eda_overview.png'), x=10, y=None, w=180)
pdf.ln(85)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Clustering Implementation", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 6, f"Algorithms Implemented: K-Means, Hierarchical (Agglomerative), DBSCAN\nOptimal number of clusters (K-Means & Hierarchical): {optimal_k}\nDBSCAN Parameters: eps={best_eps:.2f}, min_samples=5\nNoise points detected by DBSCAN: {n_noise}")
pdf.image(os.path.join(OUTPUT_DIR, 'elbow_method.png'), x=10, y=None, w=100)
pdf.image(os.path.join(OUTPUT_DIR, 'dendrogram.png'), x=120, y=None, w=80)
pdf.ln(70)
pdf.image(os.path.join(OUTPUT_DIR, 'dbscan_eps_tuning.png'), x=10, y=None, w=100)
pdf.image(os.path.join(OUTPUT_DIR, 'cluster_profiles.png'), x=120, y=None, w=80)
pdf.ln(70)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Performance Evaluation", ln=True)
pdf.set_font("Arial", "", 12)
pdf.multi_cell(0, 6, "Performance Metrics:")
pdf.image(os.path.join(OUTPUT_DIR, 'metrics_table.png'), x=10, y=None, w=180)
pdf.ln(50)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Cluster Visualization (PCA Projection)", ln=True)
pdf.image(os.path.join(OUTPUT_DIR, 'clustering_comparison.png'), x=10, y=None, w=180)
pdf.ln(60)
pdf.set_font("Arial", "B", 14)
pdf.cell(0, 10, "Generated Images", ln=True)
pdf.set_font("Arial", "", 12)
images_list = ["eda_overview.png", "elbow_method.png", "dendrogram.png", "dbscan_eps_tuning.png", "cluster_profiles.png", "metrics_table.png", "clustering_comparison.png"]
for img in images_list:
    pdf.cell(0, 6, f"- {img}", ln=True)
pdf.output(os.path.join(OUTPUT_DIR, "clustering_report.pdf"))
print("✓ PDF report generated.")

# ------------------------- CONSOLE OUTPUT -------------------------
print(f"\n{'='*50}")
print("EXPERIMENT 7: CLUSTERING - COMPLETE")
print(f"{'='*50}")
print(f"Dataset loaded: {len(df)} samples, {len(df.columns)} features")
print(f"Optimal number of clusters (K-Means & Hierarchical): {optimal_k}")
print(f"DBSCAN parameters: eps={best_eps:.2f}, min_samples=5")
print(f"DBSCAN noise points detected: {n_noise}")
print(f"\nPerformance Metrics:")
print(f"{'='*60}")
print(f"{'Algorithm':<15} {'Silhouette':<12} {'Davies-Bouldin':<15} {'Calinski-Harabasz':<18}")
print(f"{'-'*60}")
print(f"{'K-Means':<15} {kmeans_silhouette:<12.4f} {kmeans_db:<15.4f} {kmeans_ch:<18.2f}")
print(f"{'Hierarchical':<15} {hier_silhouette:<12.4f} {hier_db:<15.4f} {hier_ch:<18.2f}")
if dbscan_silhouette > 0:
    print(f"{'DBSCAN':<15} {dbscan_silhouette:<12.4f} {dbscan_db:<15.4f} {dbscan_ch:<18.2f}")
else:
    print(f"{'DBSCAN':<15} {'N/A (too few clusters)':<12} {'N/A':<15} {'N/A':<18}")
print(f"{'='*60}")
print(f"\nAll outputs saved in '{OUTPUT_DIR}' folder.")
print(f"PDF report: {OUTPUT_DIR}/clustering_report.pdf")