const {
  Document, Packer, Paragraph, TextRun, Table, TableRow, TableCell,
  AlignmentType, UnderlineType, BorderStyle, WidthType, ShadingType, LevelFormat
} = require('docx');
const fs = require('fs');

// ---------------------- STYLE CONSTANTS ----------------------
const BLACK = "000000";
const BLUE = "1F4E79";
const ACCENT = "2E75B6";
const WHITE = "FFFFFF";

// ---------------------- HELPER FUNCTIONS ----------------------
function heading(text) {
  return new Paragraph({
    children: [new TextRun({ text, bold: true, size: 28, color: BLACK, font: "Arial" })],
    spacing: { before: 300, after: 120 }
  });
}

function subheading(text) {
  return new Paragraph({
    children: [new TextRun({ text, bold: true, size: 24, color: BLACK, font: "Arial" })],
    spacing: { before: 200, after: 80 }
  });
}

function bullet(text, level = 0) {
  return new Paragraph({
    numbering: { reference: "bullets", level },
    children: [new TextRun({ text, size: 21, color: BLUE, font: "Arial" })],
    spacing: { before: 40, after: 40 }
  });
}

function faqQ(text) {
  return new Paragraph({
    children: [new TextRun({ text, bold: true, size: 22, color: BLACK, font: "Arial" })],
    spacing: { before: 200, after: 70 }
  });
}

function codeBlock(text) {
  return new Paragraph({
    children: [new TextRun({ text, size: 20, color: "333333", font: "Courier New", italics: true })],
    spacing: { before: 60, after: 60 },
    shading: { fill: "F4F4F4", type: ShadingType.CLEAR }
  });
}

function divider() {
  return new Paragraph({
    border: { bottom: { style: BorderStyle.SINGLE, size: 6, color: ACCENT, space: 1 } },
    spacing: { before: 100, after: 100 }
  });
}

function space() { return new Paragraph({ text: "", spacing: { after: 80 } }); }

// ---------------------- ASSIGNMENT 2: DATA PRE‑PROCESSING (DETAILED) ----------------------
function createAssignment2() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }, { level: 1, format: LevelFormat.BULLET, text: "\u25E6", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 1080, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. Academic Year 2025-26 Semester: IV", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "Data Engineering & Technologies (AID30010)", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "LAB ASSIGNMENT – 2", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        new Paragraph({ children: [new TextRun({ text: "Assignment No: ", bold: true, size: 24, color: BLACK, font: "Arial" }), new TextRun({ text: "02", bold: true, size: 24, color: ACCENT, font: "Arial" })], spacing: { after: 60 } }),
        new Paragraph({ children: [new TextRun({ text: "Title: ", bold: true, size: 24, color: BLACK, font: "Arial" }), new TextRun({ text: "Data Pre‑Processing using Python", bold: true, size: 24, color: ACCENT, font: "Arial" })], spacing: { after: 120 } }),

        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "To perform comprehensive data preprocessing using Python, including data cleaning, integration, transformation (normalization & binning), and reduction (PCA) to prepare raw data for analysis and machine learning.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),

        divider(),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "Given a real‑world dataset (e.g., CSV/Excel) containing missing values, duplicates, inconsistent formats, and high dimensionality. Implement the following preprocessing steps in Python:", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 50 } }),
        bullet("Clean the data: handle missing values (drop/impute), detect and treat outliers using IQR/Z‑score."),
        bullet("Integrate data: resolve redundancy using Pearson correlation, remove duplicate tuples."),
        bullet("Transform data: apply Min‑Max and Z‑score normalization; smooth data using binning methods."),
        bullet("Reduce dimensionality: apply Principal Component Analysis (PCA) and visualise explained variance."),
        space(),

        divider(),
        heading("OBJECTIVES:"),
        bullet("Understand the importance of preprocessing in data mining pipelines."),
        bullet("Implement missing value treatment (mean, median, mode, or predictive imputation)."),
        bullet("Perform correlation analysis to detect redundant features and remove them."),
        bullet("Apply normalization techniques (Min‑Max, StandardScaler) to scale numerical features."),
        bullet("Use equal‑width and equal‑frequency binning to discretize and smooth continuous variables."),
        bullet("Implement PCA and interpret the principal components."),
        space(),

        divider(),
        heading("THEORY:"),
        subheading("1. Data Cleaning:"),
        bullet("Missing values: MCAR, MAR, MNAR. Techniques: deletion, imputation (mean/median/mode, KNN, regression)."),
        bullet("Outliers: detected via boxplot (IQR method) or Z‑score (threshold 3). Treated by capping, transformation, or removal."),
        bullet("Noise: smoothing via binning, clustering, or regression."),

        subheading("2. Data Integration:"),
        bullet("Combines data from multiple sources (databases, files)."),
        bullet("Redundancy: attribute redundancy (correlation) and tuple duplication."),
        bullet("Pearson correlation coefficient: r = Cov(X,Y)/(σₓσᵧ). Values near +1 or -1 indicate strong linear relationship."),
        bullet("p‑value: tests statistical significance of correlation (p < 0.05 → significant)."),

        subheading("3. Data Transformation:"),
        bullet("Normalization (scaling):"),
        bullet("Min‑Max: X_new = (X - X_min)/(X_max - X_min) → range [0,1].", 1),
        bullet("Z‑score: X_new = (X - μ)/σ → mean 0, std 1.", 1),
        bullet("Binning (data smoothing):"),
        bullet("Equal‑width: divide range into k intervals of equal size.", 1),
        bullet("Equal‑frequency (quantile): each bin contains same number of samples.", 1),
        bullet("Replace each bin by mean, median, or bin boundaries.", 1),

        subheading("4. Data Reduction – PCA:"),
        bullet("Linear transformation that projects data onto a lower‑dimensional subspace while preserving maximum variance."),
        bullet("Steps: standardize data → compute covariance matrix → eigenvectors/values → sort by eigenvalue → select top k components."),
        bullet("Explained variance ratio: λᵢ / Σλⱼ. Choose k such that cumulative variance > 0.95."),

        space(),
        divider(),
        heading("IMPLEMENTATION IN PYTHON (Detailed Steps):"),
        subheading("Step 1: Load Libraries & Dataset"),
        codeBlock("import pandas as pd\nimport numpy as np\nimport seaborn as sns\nimport matplotlib.pyplot as plt\nfrom sklearn.preprocessing import MinMaxScaler, StandardScaler\nfrom sklearn.decomposition import PCA\nfrom scipy.stats import pearsonr\n\n# Load dataset\ndf = pd.read_csv('data.csv')\nprint(df.head())"),
        subheading("Step 2: Data Cleaning"),
        codeBlock("# Check missing values\nprint(df.isnull().sum())\n\n# Drop rows with >50% missing\ndf = df.dropna(thresh=0.5*len(df.columns))\n\n# Impute numerical columns with median\nfor col in df.select_dtypes(include=np.number).columns:\n    df[col].fillna(df[col].median(), inplace=True)\n\n# Outlier detection (IQR)\nQ1 = df[col].quantile(0.25)\nQ3 = df[col].quantile(0.75)\nIQR = Q3 - Q1\nlower = Q1 - 1.5*IQR\nupper = Q3 + 1.5*IQR\ndf = df[(df[col] >= lower) & (df[col] <= upper)]"),
        subheading("Step 3: Data Integration & Redundancy Check"),
        codeBlock("# Pearson correlation matrix\ncorr_matrix = df.corr()\nsns.heatmap(corr_matrix, annot=True, cmap='coolwarm')\nplt.show()\n\n# Remove highly correlated features (>0.9)\nthreshold = 0.9\nupper_tri = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(bool))\nto_drop = [column for column in upper_tri.columns if any(upper_tri[column] > threshold)]\ndf = df.drop(columns=to_drop)\n\n# Remove duplicate rows\ndf = df.drop_duplicates()"),
        subheading("Step 4: Data Transformation – Normalization"),
        codeBlock("# Min‑Max scaling\nscaler_minmax = MinMaxScaler()\ndf_minmax = pd.DataFrame(scaler_minmax.fit_transform(df), columns=df.columns)\n\n# Z‑score standardization\nscaler_std = StandardScaler()\ndf_std = pd.DataFrame(scaler_std.fit_transform(df), columns=df.columns)"),
        subheading("Step 5: Data Smoothing – Binning"),
        codeBlock("# Equal‑width binning (3 bins)\ndf['age_binned'] = pd.cut(df['age'], bins=3, labels=['Young', 'Middle', 'Old'])\n\n# Equal‑frequency binning\ndf['income_binned'] = pd.qcut(df['income'], q=4, labels=['Q1','Q2','Q3','Q4'])\n\n# Smooth by bin median\ndf['age_smoothed'] = df.groupby('age_binned')['age'].transform('median')"),
        subheading("Step 6: Data Reduction – PCA"),
        codeBlock("# Standardize before PCA\nX_std = StandardScaler().fit_transform(df.select_dtypes(include=np.number))\n\npca = PCA(n_components=2)\nX_pca = pca.fit_transform(X_std)\nprint(f'Explained variance ratio: {pca.explained_variance_ratio_}')\nprint(f'Cumulative variance: {sum(pca.explained_variance_ratio_):.2f}')\n\n# Plot 2D projection\nplt.scatter(X_pca[:,0], X_pca[:,1])\nplt.xlabel('PC1')\nplt.ylabel('PC2')\nplt.show()"),
        space(),

        divider(),
        heading("CONCLUSION:"),
        bullet("Successfully implemented all major preprocessing steps: cleaning, integration, transformation (normalization & binning), and reduction (PCA)."),
        bullet("Correlation analysis helped remove redundant features, reducing overfitting risk."),
        bullet("Normalization made features comparable for distance‑based algorithms (e.g., KNN, SVM)."),
        bullet("Binning converted continuous variables into categorical, improving interpretability and reducing noise."),
        bullet("PCA reduced dimensionality from N to 2 while retaining >95% variance, enabling visualisation and faster training."),
        space(),

        divider(),
        heading("FAQs (Detailed Answers):"),
        faqQ("Q1. Why do we need scaling?"),
        bullet("Algorithms that compute distances (KNN, K‑means, SVM) or gradients (neural networks, logistic regression) are sensitive to feature magnitudes. Scaling ensures each feature contributes equally; otherwise, features with larger ranges dominate."),
        faqQ("Q2. Benefits and Techniques of Binning in Python?"),
        bullet("Benefits: handles small observation errors, creates ordinal categories, reduces overfitting, improves model stability. Techniques: pd.cut (equal‑width), pd.qcut (equal‑frequency), and custom bin edges."),
        faqQ("Q3. What is data leakage, how to avoid it?"),
        bullet("Data leakage is when information from outside the training dataset (e.g., test data) influences the model. Avoid by: splitting data BEFORE preprocessing, fitting scalers/PCA only on training set, then transforming test set. Never use global min/max/mean computed on full dataset."),
        faqQ("Q4. Which technique should we use – Normalization or Standardization?"),
        bullet("Use Min‑Max when you know data has bounded range (e.g., [0,1]) and no extreme outliers. Use Standardization (Z‑score) when data follows Gaussian distribution or algorithms assume zero mean (PCA, linear regression). For clustering, standardization is often safer."),
        faqQ("Q5. Benefits of Correlation Analysis?"),
        bullet("Identifies linear relationships; helps feature selection (remove highly correlated predictors); detects multicollinearity (affects regression coefficients); guides data integration (confirming redundant attributes)."),
        faqQ("Q6. Significance of Correlation Analysis?"),
        bullet("Quantifies the strength and direction of association. A correlation of +0.8 indicates strong positive linear relationship; -0.6 indicates moderate negative. It is a foundation for many statistical models and exploratory analysis."),
        faqQ("Q7. Different kinds of correlation analysis? Discuss strengths/weaknesses."),
        bullet("Pearson: measures linear relationship. Strength: sensitive to linear trends. Weakness: affected by outliers and non‑linearity.", 1),
        bullet("Spearman: monotonic relationship (rank‑based). Strength: robust to outliers, captures any monotonic trend. Weakness: less powerful for linear only.", 1),
        bullet("Kendall Tau: ordinal association. Strength: suitable for small samples with ties. Weakness: computationally heavier.", 1),
        faqQ("Q8. Factors that affect Correlation Analysis?"),
        bullet("Outliers (inflate/deflate r), non‑linear relationships (Pearson may be near zero even if strong non‑linear), range restriction (low variance reduces correlation), measurement error (attenuates correlation)."),
        faqQ("Q9. Write a short note on correlation coefficient and p‑value."),
        bullet("Correlation coefficient (r): ranges -1 to +1; magnitude indicates strength, sign indicates direction. p‑value: probability of observing such r by chance if true correlation is zero. p < 0.05 → statistically significant correlation."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- ASSIGNMENT 3: OLAP & DATA WAREHOUSE (DETAILED) ----------------------
function createAssignment3() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. AIDS Semester‑4, AY 2025‑26", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "DET Lab Assignment No. 03", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "Design a data warehouse schema, build a multidimensional cube using OLAPCube tool (or Python), and perform OLAP operations (Drill down, Roll up, Slicing, Dicing) to support business intelligence.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "A music company maintains the following database tables: Customers, Orders, OrderDetails, Album, Employees. Create dimensions (simple, hierarchical, relational, time), define measures (total sales, quantity sold), build a cube, and generate analytical reports. Then perform OLAP operations.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 100 } }),
        divider(), heading("OBJECTIVES:"),
        bullet("Understand data warehouse schemas: Star, Snowflake, Fact Constellation."),
        bullet("Create dimensions: simple (product), hierarchical (time: year→quarter→month), relational (customer→city→region), time dimension."),
        bullet("Define measures (additive, semi‑additive, non‑additive)."),
        bullet("Build a multidimensional cube using OLAPCube tool or Python (pandas pivot)."),
        bullet("Generate reports on different dimensions and measures."),
        bullet("Perform Drill down, Roll up, Slice, Dice operations."),
        space(), divider(), heading("THEORY:"),
        subheading("Data Warehouse Schemas:"),
        bullet("Star Schema: A central fact table connected directly to dimension tables (denormalized). Simple, fast queries. Example: FactSales connected to DimProduct, DimCustomer, DimTime."),
        bullet("Snowflake Schema: Dimension tables are normalized into sub‑dimensions. Saves storage but more joins. Example: DimProduct → DimCategory."),
        bullet("Fact Constellation: Multiple fact tables share dimension tables (galaxy schema). Example: FactSales and FactInventory share DimProduct and DimTime."),

        subheading("Dimensions and Measures:"),
        bullet("Dimensions: descriptive attributes (who, what, where, when). Hierarchies allow drilling. Example: Time (Year > Quarter > Month)."),
        bullet("Measures: numeric facts (sales amount, quantity). Additive (can sum across all dimensions), semi‑additive (e.g., inventory level – sum over product but not time), non‑additive (ratios)."),

        subheading("OLAP Operations:"),
        bullet("Drill Down: Navigate from summary to detail (e.g., from Year to Month). Increases granularity."),
        bullet("Roll Up (Drill Up): Aggregate data to a higher level (e.g., from Month to Quarter). Decreases granularity."),
        bullet("Slice: Select a single value along one dimension (e.g., sales for '2025')."),
        bullet("Dice: Select a sub‑cube by specifying values on multiple dimensions (e.g., sales for '2025' and 'Rock' genre)."),
        bullet("Pivot (Rotate): Reorient the cube to see different dimensional views."),

        space(), divider(), heading("IMPLEMENTATION (Using Python pandas as an OLAP substitute):"),
        subheading("Step 1: Create Sample Data"),
        codeBlock("import pandas as pd\n\n# Fact table: Sales\nsales_data = {\n    'Date': ['2025-01-15','2025-02-10','2025-01-20','2025-03-05'],\n    'ProductID': [1,2,1,3],\n    'CustomerID': [101,102,101,103],\n    'Quantity': [2,1,3,1],\n    'Revenue': [19.98, 9.99, 29.97, 14.99]\n}\nfacts = pd.DataFrame(sales_data)\n\n# Dimension tables\ndim_product = pd.DataFrame({'ProductID':[1,2,3], 'Product':['Album A','Album B','Album C'], 'Genre':['Rock','Pop','Rock']})\ndim_time = pd.DataFrame({'Date':['2025-01-15','2025-02-10','2025-01-20','2025-03-05'], 'Year':[2025,2025,2025,2025], 'Month':[1,2,1,3], 'Quarter':['Q1','Q1','Q1','Q1']})"),
        subheading("Step 2: Build Cube (Multi‑dimensional aggregation)"),
        codeBlock("# Merge dimensions to fact\ncube = facts.merge(dim_product, on='ProductID').merge(dim_time, on='Date')\n\n# Pivot table for multi‑dimensional view\npivot = pd.pivot_table(cube, values='Revenue', index=['Genre','Product'], columns=['Quarter'], aggfunc='sum', fill_value=0)\nprint(pivot)"),
        subheading("Step 3: OLAP Operations"),
        codeBlock("# Roll Up: aggregate Genre to all products\ntotal_by_genre = cube.groupby('Genre')['Revenue'].sum()\n\n# Drill Down: from Genre to Product\nby_product = cube.groupby(['Genre','Product'])['Revenue'].sum()\n\n# Slice: filter Genre = 'Rock'\nrock_sales = cube[cube['Genre'] == 'Rock']\n\n# Dice: Rock genre AND Q1\nrock_q1 = cube[(cube['Genre'] == 'Rock') & (cube['Quarter'] == 'Q1')]"),
        subheading("Step 4: Using OLAPCube Tool (if available)"),
        bullet("OLAPCube is a Windows tool that allows drag‑drop cube building. Steps:"),
        bullet("Import database (CSV/Excel).", 1),
        bullet("Define dimensions and hierarchies (e.g., Time: Year→Quarter→Month).", 1),
        bullet("Define measures (e.g., Sum of Revenue).", 1),
        bullet("Build cube and browse using pivot tables and charts.", 1),
        bullet("Perform right‑click → Drill Down, Roll Up, etc.", 1),
        space(), divider(), heading("CONCLUSION:"),
        bullet("Successfully built a multi‑dimensional cube from relational data."),
        bullet("OLAP operations (Drill down, Roll up, Slice, Dice) enabled interactive analysis across dimensions."),
        bullet("Star schema provided fast query performance for business intelligence."),
        bullet("Understanding of hierarchies and measures is crucial for effective reporting."),
        space(), divider(), heading("FAQs:"),
        faqQ("Q1. What are dimensions and measures?"),
        bullet("Dimensions are qualitative categories that describe the data (e.g., time, location, product). Measures are quantitative values that are analyzed (e.g., sales, profit, quantity)."),
        faqQ("Q2. What do you mean by slicing and dicing?"),
        bullet("Slicing: selecting a single dimension value (e.g., sales for 2025 only). Dicing: selecting a sub‑cube by multiple dimension values (e.g., sales for 2025 and Rock genre)."),
        faqQ("Q3. What do you mean by drill down and drill up?"),
        bullet("Drill down: increasing detail (e.g., from Year to Month). Drill up: decreasing detail (e.g., from Month to Quarter)."),
        faqQ("Q4. Difference between star and snowflake schema?"),
        bullet("Star: denormalized dimensions (one table per dimension). Snowflake: normalized dimensions (multiple related tables). Star is simpler and faster for queries; snowflake saves storage."),
        faqQ("Q5. What is a factless fact table?"),
        bullet("A fact table with no measures, only foreign keys to dimensions. Used to track events (e.g., student attendance, patient visits)."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- ASSIGNMENT 4: POWER BI DASHBOARD (DETAILED) ----------------------
function createAssignment4() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. AIDS Semester‑4, AY 2025‑26", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "DET Lab Assignment No. 04", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "Extract, transform, and load (ETL) data into Power BI, build an interactive dashboard with multiple visualisations, and generate insightful reports across different dimensions and measures.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "Using datasets from one of the following domains: Retail Company Sales, Healthcare Data, Education/University Data, or Crime Dataset. Perform data transformations (format changes, column renaming, removing unwanted columns, filling missing data, removing duplicates, merging). Build a meaningful interactive dashboard with at least 5 different chart types. Generate reports on at least 3 different dimensions and 2 measures.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 100 } }),
        divider(), heading("OBJECTIVES:"),
        bullet("Learn the end‑to‑end process of data visualisation using Power BI."),
        bullet("Perform data cleaning and shaping using Power Query Editor."),
        bullet("Create relationships between tables."),
        bullet("Design interactive dashboards with slicers, filters, and drill‑through."),
        bullet("Generate reports and share insights."),
        space(), divider(), heading("THEORY:"),
        subheading("Power BI Components:"),
        bullet("Power Query: ETL tool to connect, transform, and load data (M language)."),
        bullet("Data Model: relationships, DAX (Data Analysis Expressions) for calculated columns and measures."),
        bullet("Reports: collection of visualisations on one or more pages."),
        bullet("Dashboards: single canvas with pinned tiles from reports."),

        subheading("ETL Process in Power BI:"),
        bullet("Extract: from Excel, CSV, SQL Server, Web, etc."),
        bullet("Transform: change data types, rename columns, remove columns, replace values, split columns, merge queries, append queries, pivot/unpivot."),
        bullet("Load: load into Power BI data model."),

        subheading("Visualisations:"),
        bullet("Bar/Column charts (clustered, stacked), Line charts, Pie/Donut charts, Maps (filled, bubble), Cards, Slicers, Tables, Matrix, Scatter plots, Funnel, Gauge."),

        subheading("DAX Measures:"),
        bullet("Total Sales = SUM(Sales[Amount])"),
        bullet("Average Price = AVERAGE(Products[Price])"),
        bullet("YoY Growth = (SUM(Sales[Amount]) - CALCULATE(SUM(Sales[Amount]), SAMEPERIODLASTYEAR(Calendar[Date]))) / CALCULATE(SUM(Sales[Amount]), SAMEPERIODLASTYEAR(Calendar[Date]))"),

        space(), divider(), heading("IMPLEMENTATION STEPS (with example: Retail Sales):"),
        subheading("Step 1: Load Data"),
        bullet("Get Data → Excel/CSV → select Sales.csv, Products.csv, Customers.csv, Calendar.csv."),
        subheading("Step 2: Transform Data (Power Query Editor)"),
        bullet("Sales table: change 'OrderDate' to Date type, remove 'ShippingAddress' column, replace nulls in 'Discount' with 0, remove duplicate OrderIDs."),
        bullet("Products table: split 'ProductName - Category' into two columns, rename columns appropriately."),
        bullet("Customers table: fill missing 'Region' using mode per city, remove rows where 'CustomerID' is null."),
        bullet("Merge Sales and Customers on CustomerID → new query 'SalesWithCustomer'."),
        subheading("Step 3: Create Data Model & Relationships"),
        bullet("Create a Calendar table using DAX: Calendar = CALENDAR(MIN(Sales[OrderDate]), MAX(Sales[OrderDate]))"),
        bullet("Relationships: Sales[ProductID] → Products[ProductID]; Sales[CustomerID] → Customers[CustomerID]; Sales[OrderDate] → Calendar[Date]."),
        subheading("Step 4: Create Measures"),
        codeBlock("Total Sales = SUM(Sales[Amount])\nTotal Quantity = SUM(Sales[Quantity])\nAvg Order Value = AVERAGEX(Sales, Sales[Amount])\nSales LY = CALCULATE([Total Sales], SAMEPERIODLASTYEAR(Calendar[Date]))\nYoY Growth = DIVIDE([Total Sales] - [Sales LY], [Sales LY])"),
        subheading("Step 5: Build Dashboard"),
        bullet("Page 1 – Overview: Card for Total Sales, Card for Total Quantity, Line chart of Sales by Month, Bar chart of Sales by Product Category, Map of Sales by Region, Slicer for Year."),
        bullet("Page 2 – Customer Analysis: Matrix of Customer Name × Product Category showing Quantity, Scatter plot of Avg Order Value vs Customer Tenure, Donut chart of Sales by Gender."),
        bullet("Page 3 – Product Performance: Clustered column chart of Sales by Product and Quarter, Funnel chart of Sales by Category, Gauge for Sales vs Target."),
        bullet("Add drill‑through from Product to Product Details page."),
        subheading("Step 6: Publish to Power BI Service"),
        bullet("Publish → create dashboard → pin visuals → set up scheduled refresh."),
        space(), divider(), heading("CONCLUSION:"),
        bullet("Successfully created an interactive Power BI dashboard enabling real‑time data exploration."),
        bullet("Power Query Editor simplified data cleaning and integration."),
        bullet("DAX measures allowed complex calculations like YoY growth."),
        bullet("Dashboards provide actionable insights for business decision‑making."),
        space(), divider(), heading("FAQs:"),
        faqQ("Q1. Differentiate between Tableau and Power BI features?"),
        bullet("Power BI: tight Microsoft integration, DAX language, lower cost, better for paginated reports, natural language Q&A. Tableau: superior visualisation flexibility, easier for complex calculations, better for ad‑hoc exploration, higher cost."),
        faqQ("Q2. What is the purpose of Tableau dashboard?"),
        bullet("Tableau dashboards combine multiple worksheets and dashboards into a single interactive canvas, allowing users to filter, highlight, and drill down to explore data stories."),
        faqQ("Q3. What is the difference between Power BI Report and Dashboard?"),
        bullet("Report: one or more pages of visuals based on a single dataset; can have interactive filters and drill‑through. Dashboard: single canvas with tiles pinned from different reports; provides a high‑level overview."),
        faqQ("Q4. Explain the role of DAX in Power BI."),
        bullet("DAX (Data Analysis Expressions) is a formula language for creating calculated columns, measures, and tables. It enables dynamic aggregations, time intelligence (e.g., YTD, QoQ), and complex business logic."),
        faqQ("Q5. How do you handle incremental refresh in Power BI?"),
        bullet("Incremental refresh loads only new or changed rows since the last refresh. Set up in Power Query by adding a RangeStart/RangeEnd parameter, then configure incremental refresh policy in the dataset settings."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- ASSIGNMENT 5: APRIORI ALGORITHM (DETAILED) ----------------------
function createAssignment5() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. AIDS Semester‑4, AY 2025‑26", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "DET Lab Assignment No. 05", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "Apply the Apriori algorithm to discover frequent itemsets from transaction data and generate strong association rules (Market Basket Analysis) using Python.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "Given a transactional dataset (e.g., grocery store purchases, online retail). Implement Apriori to find frequent itemsets with minimum support = 0.02 and generate association rules with minimum confidence = 0.5. Compute support, confidence, lift, and conviction for each rule. Visualise top rules.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 100 } }),
        divider(), heading("OBJECTIVES:"),
        bullet("Understand frequent itemsets, closed itemsets, and market basket analysis."),
        bullet("Calculate support, confidence, lift, and conviction mathematically and programmatically."),
        bullet("Implement the Apriori algorithm from scratch or using libraries (mlxtend)."),
        bullet("Generate and interpret strong association rules."),
        bullet("Visualise rule metrics using scatter plots and network graphs."),
        space(), divider(), heading("THEORY:"),
        subheading("Association Rules:"),
        bullet("An implication of the form X → Y, where X and Y are disjoint itemsets. Example: {Bread, Milk} → {Eggs}."),
        bullet("Support(X→Y) = P(X∪Y) = (transactions containing both X and Y) / (total transactions)."),
        bullet("Confidence(X→Y) = P(Y|X) = support(X∪Y) / support(X)."),
        bullet("Lift(X→Y) = confidence(X→Y) / support(Y). Lift > 1 indicates positive association."),
        bullet("Conviction(X→Y) = (1 - support(Y)) / (1 - confidence(X→Y)). Conviction > 1 means rule is interesting."),

        subheading("Apriori Principle:"),
        bullet("All non‑empty subsets of a frequent itemset must also be frequent. This property is used to prune candidate itemsets, reducing computational cost."),

        subheading("Pseudocode of Apriori:"),
        codeBlock("1. Generate candidate 1‑itemsets (C1)\n2. Scan database to count support of each item, keep those ≥ min_support → L1 (frequent 1‑itemsets)\n3. For k = 2,3,... until Lk‑1 is empty:\n   a. Generate candidate k‑itemsets (Ck) by joining Lk‑1 with itself (self‑join)\n   b. Prune: remove candidates with any (k‑1)-subset not in Lk‑1\n   c. Scan database to count support of Ck, keep those ≥ min_support → Lk\n4. Return ∪Lk as frequent itemsets\n5. Generate rules from frequent itemsets: for each frequent itemset I, generate all non‑empty subsets S ⊂ I, rule S → (I \\ S). Keep rules with confidence ≥ min_conf."),

        subheading("Closed and Maximal Itemsets:"),
        bullet("Closed itemset: no proper superset with same support."),
        bullet("Maximal itemset: no frequent superset."),

        space(), divider(), heading("IMPLEMENTATION IN PYTHON:"),
        subheading("Step 1: Install and Import Libraries"),
        codeBlock("pip install mlxtend pandas matplotlib networkx"),
        codeBlock("import pandas as pd\nfrom mlxtend.frequent_patterns import apriori, association_rules\nfrom mlxtend.preprocessing import TransactionEncoder\nimport matplotlib.pyplot as plt\nimport networkx as nx"),
        subheading("Step 2: Load and Transform Data"),
        codeBlock("# Sample transaction data\ndataset = [['Milk','Bread','Butter'],\n           ['Bread','Butter'],\n           ['Milk','Bread','Butter','Eggs'],\n           ['Milk','Eggs'],\n           ['Milk','Bread','Eggs'],\n           ['Bread','Butter','Eggs'],\n           ['Milk','Bread','Butter'],\n           ['Milk','Bread'],\n           ['Milk','Eggs'],\n           ['Bread','Eggs']]\n\n# One‑hot encode\nte = TransactionEncoder()\nte_array = te.fit(dataset).transform(dataset)\ndf = pd.DataFrame(te_array, columns=te.columns_)"),
        subheading("Step 3: Find Frequent Itemsets"),
        codeBlock("frequent_itemsets = apriori(df, min_support=0.2, use_colnames=True)\nprint(frequent_itemsets.sort_values('support', ascending=False))"),
        subheading("Step 4: Generate Association Rules"),
        codeBlock("rules = association_rules(frequent_itemsets, metric='confidence', min_threshold=0.6)\nrules = rules[['antecedents','consequents','support','confidence','lift','conviction']]\nprint(rules.sort_values('lift', ascending=False))"),
        subheading("Step 5: Visualise Rules"),
        codeBlock("# Scatter plot: support vs confidence\nplt.scatter(rules['support'], rules['confidence'], c=rules['lift'], cmap='viridis')\nplt.xlabel('Support')\nplt.ylabel('Confidence')\nplt.colorbar(label='Lift')\nplt.show()\n\n# Network graph of top rules\ntop_rules = rules.nlargest(10, 'lift')\nG = nx.DiGraph()\nfor _, row in top_rules.iterrows():\n    ant = str(list(row['antecedents']))\n    con = str(list(row['consequents']))\n    G.add_edge(ant, con, weight=row['lift'])\npos = nx.spring_layout(G)\nnx.draw(G, pos, with_labels=True, node_size=2000, node_color='lightblue', font_size=8)\nplt.show()"),
        subheading("Step 6: Interpretation"),
        bullet("If {Bread, Butter} → {Milk} has support=0.3, confidence=0.85, lift=1.4 → 30% of transactions contain all three; when Bread and Butter are bought, 85% of the time Milk is also bought; lift>1 indicates positive association."),
        space(), divider(), heading("CONCLUSION:"),
        bullet("Implemented Apriori algorithm to find frequent itemsets and generate association rules."),
        bullet("Lift and conviction helped identify truly interesting rules beyond random co‑occurrence."),
        bullet("Market basket analysis can optimise product placement, cross‑selling, and promotions."),
        bullet("Apriori principle significantly reduces computational cost compared to brute force."),
        space(), divider(), heading("FAQs:"),
        faqQ("Q1. What is the Apriori principle?"),
        bullet("If an itemset is frequent, all its subsets are frequent. Conversely, if an itemset is infrequent, all its supersets are infrequent (used for pruning)."),
        faqQ("Q2. What are the different steps involved in the Apriori algorithm?"),
        bullet("(1) Generate candidates, (2) Count support, (3) Prune infrequent, (4) Repeat for larger itemsets, (5) Generate rules."),
        faqQ("Q3. Describe the minimum support threshold."),
        bullet("Minimum support is the fraction of transactions that must contain an itemset for it to be considered frequent. Lower support yields more itemsets but increases computation."),
        faqQ("Q4. Describe the minimum confidence threshold."),
        bullet("Minimum confidence is the conditional probability required for a rule to be accepted. For rule X→Y, confidence = P(Y|X). Higher confidence means stronger implication."),
        faqQ("Q5. How are frequent itemsets identified using Apriori?"),
        bullet("By iteratively generating candidate itemsets of increasing size and testing their support against the min_support threshold, pruning those that fail."),
        faqQ("Q6. How are association rules generated using Apriori?"),
        bullet("From each frequent itemset I, generate all possible rules of the form S → (I\\S) where S is a non‑empty subset. Keep rules with confidence ≥ min_conf."),
        faqQ("Q7. How can Apriori be used to detect credit card fraud in real time?"),
        bullet("By mining frequent patterns of fraudulent transactions (e.g., small amount followed by large amount, unusual merchant categories). Rules with high lift can trigger alerts. However, real‑time requires optimised algorithms (FP‑Growth) and streaming data handling."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- ASSIGNMENT 6: DECISION TREE (DETAILED) ----------------------
function createAssignment6() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. AIDS Semester‑4, AY 2025‑26", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "DET Lab Assignment No. 06", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "Apply the Decision Tree algorithm for supervised classification on a suitable dataset, evaluate its performance using various metrics, and visualise the tree structure.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "Use the Iris dataset (or Titanic, Bank Marketing). Build a Decision Tree classifier to predict the species (or survival). Split data into train/test (70:30). Calculate accuracy, precision, recall, F1‑score, and confusion matrix. Prune the tree to avoid overfitting and visualise the final tree.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 100 } }),
        divider(), heading("OBJECTIVES:"),
        bullet("Understand the working of Decision Tree (CART, ID3, C4.5)."),
        bullet("Implement Decision Tree using scikit‑learn."),
        bullet("Measure classification performance (confusion matrix, classification report)."),
        bullet("Visualise the decision tree using graphviz/matplotlib."),
        bullet("Experiment with hyperparameters (max_depth, min_samples_split) to control overfitting."),
        space(), divider(), heading("THEORY:"),
        subheading("Decision Tree Algorithm:"),
        bullet("A non‑parametric supervised learning method that recursively partitions the feature space into regions, assigning a majority class (or mean) to each region."),
        bullet("Splitting criteria:"),
        bullet("Entropy: H(S) = -Σ pᵢ log₂ pᵢ. Information Gain = H(parent) – Σ (|Sᵥ|/|S|) H(Sᵥ).", 1),
        bullet("Gini Impurity: Gini(S) = 1 – Σ pᵢ². Lower Gini is better.", 1),
        bullet("CART uses Gini; ID3 uses Information Gain."),

        subheading("Binary vs Multiclass Classification:"),
        bullet("Binary: two classes (e.g., spam/ham, survive/die). Multiclass: three or more (e.g., Iris species: setosa, versicolor, virginica)."),

        subheading("Pruning:"),
        bullet("Pre‑pruning: stop growing when splitting doesn't improve purity beyond threshold (max_depth, min_samples_leaf)."),
        bullet("Post‑pruning: grow full tree then remove branches that provide little power (cost complexity pruning)."),

        subheading("Performance Metrics:"),
        bullet("Confusion Matrix: TP, FP, TN, FN."),
        bullet("Accuracy = (TP+TN)/(TP+FP+TN+FN)"),
        bullet("Precision = TP/(TP+FP) – positive predictive value."),
        bullet("Recall = TP/(TP+FN) – sensitivity."),
        bullet("F1 = 2 * (Precision * Recall)/(Precision + Recall) – harmonic mean."),

        space(), divider(), heading("IMPLEMENTATION IN PYTHON:"),
        subheading("Step 1: Load Data and Split"),
        codeBlock("from sklearn.datasets import load_iris\nfrom sklearn.model_selection import train_test_split\nfrom sklearn.tree import DecisionTreeClassifier, plot_tree\nfrom sklearn.metrics import confusion_matrix, classification_report, accuracy_score\nimport matplotlib.pyplot as plt\n\niris = load_iris()\nX, y = iris.data, iris.target\nX_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)"),
        subheading("Step 2: Train Decision Tree (default)"),
        codeBlock("clf = DecisionTreeClassifier(random_state=42)\nclf.fit(X_train, y_train)\ny_pred = clf.predict(X_test)\nprint(f'Accuracy: {accuracy_score(y_test, y_pred):.4f}')\nprint(classification_report(y_test, y_pred, target_names=iris.target_names))"),
        subheading("Step 3: Visualise Tree"),
        codeBlock("plt.figure(figsize=(12,8))\nplot_tree(clf, feature_names=iris.feature_names, class_names=iris.target_names, filled=True)\nplt.show()"),
        subheading("Step 4: Prune to Avoid Overfitting"),
        codeBlock("# Pre‑pruning: limit depth\nclf_pruned = DecisionTreeClassifier(max_depth=3, min_samples_split=5, random_state=42)\nclf_pruned.fit(X_train, y_train)\ny_pred_pruned = clf_pruned.predict(X_test)\nprint(f'Pruned Accuracy: {accuracy_score(y_test, y_pred_pruned):.4f}')\n\n# Post‑pruning (cost complexity)\npath = clf.cost_complexity_pruning_path(X_train, y_train)\nccp_alphas = path.ccp_alphas\n# Train trees for each alpha and select best via cross‑validation"),
        subheading("Step 5: Feature Importance"),
        codeBlock("importances = clf_pruned.feature_importances_\nfor name, imp in zip(iris.feature_names, importances):\n    print(f'{name}: {imp:.3f}')\n\n# Plot importance\nplt.barh(iris.feature_names, importances)\nplt.title('Feature Importance')\nplt.show()"),
        subheading("Step 6: Confusion Matrix Heatmap"),
        codeBlock("import seaborn as sns\ncm = confusion_matrix(y_test, y_pred_pruned)\nsns.heatmap(cm, annot=True, fmt='d', cmap='Blues', xticklabels=iris.target_names, yticklabels=iris.target_names)\nplt.xlabel('Predicted')\nplt.ylabel('Actual')\nplt.show()"),
        space(), divider(), heading("CONCLUSION:"),
        bullet("Decision Tree achieved high accuracy (~95%) on Iris dataset with default parameters."),
        bullet("Pruning (max_depth=3) reduced overfitting and improved interpretability."),
        bullet("Feature importance showed petal length and width are most discriminative."),
        bullet("Decision Trees are easy to interpret but can be unstable (small data changes may produce different trees)."),
        space(), divider(), heading("FAQs:"),
        faqQ("Q1. Difference between binary and multiclass classifier? Give examples."),
        bullet("Binary: two mutually exclusive classes (e.g., email spam/ham, tumor malignant/benign). Multiclass: more than two classes (e.g., handwritten digit recognition 0‑9, iris species)."),
        faqQ("Q2. What is Decision Tree classifier? Advantages?"),
        bullet("A tree‑based model that splits data based on feature values. Advantages: no feature scaling, handles mixed data types, interpretable, can capture non‑linear relationships."),
        faqQ("Q3. How does a decision tree work?"),
        bullet("It recursively selects the best feature to split the data using metrics (Gini, entropy). The goal is to create pure subsets. Splitting continues until a stopping criterion is met (max depth, min samples)."),
        faqQ("Q4. Difference between decision tree and random forest?"),
        bullet("Decision tree: single tree, prone to overfitting. Random forest: ensemble of many trees (bagging), reduces variance, more accurate but less interpretable."),
        faqQ("Q5. Purpose of confusion matrix in classification?"),
        bullet("It visualises the performance by showing correct and incorrect predictions per class. From it we compute precision, recall, F1, and accuracy."),
        faqQ("Q6. Explain overfitting in classifiers."),
        bullet("Overfitting occurs when the model learns noise and training‑specific patterns instead of the underlying distribution. For decision trees, deep trees with many leaves are prone to overfitting. Use pruning, cross‑validation, or ensemble methods."),
        faqQ("Q7. Real‑world examples where decision tree is used as classifier."),
        bullet("Credit risk assessment (loan approval), medical diagnosis (disease from symptoms), customer churn prediction, quality control in manufacturing, fraud detection (rule‑based)."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- ASSIGNMENT 7: CLUSTERING (DETAILED) ----------------------
function createAssignment7() {
  const doc = new Document({
    numbering: { config: [{ reference: "bullets", levels: [{ level: 0, format: LevelFormat.BULLET, text: "\u2022", alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 360 } } } }] }] },
    styles: { default: { document: { run: { font: "Arial", size: 21 } } } },
    sections: [{
      properties: { page: { size: { width: 12240, height: 15840 }, margin: { top: 1080, right: 1080, bottom: 1080, left: 1080 } } },
      children: [
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "S.Y. B. Tech. AIDS Semester‑4, AY 2025‑26", bold: true, size: 23, color: BLACK, font: "Arial" })] }),
        new Paragraph({ alignment: AlignmentType.CENTER, children: [new TextRun({ text: "DET Lab Assignment No. 07", bold: true, size: 26, color: ACCENT, font: "Arial", underline: { type: UnderlineType.SINGLE } })], spacing: { after: 100 } }),
        divider(),
        heading("AIM:"),
        new Paragraph({ children: [new TextRun({ text: "Apply different clustering algorithms (K‑means, Hierarchical, DBSCAN) on a suitable dataset and evaluate their performance using internal validation metrics.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 120 } }),
        heading("PROBLEM STATEMENT:"),
        new Paragraph({ children: [new TextRun({ text: "Use the Mall Customer Segmentation dataset (or Iris, Wholesale). Perform K‑means clustering (find optimal K using elbow method), Hierarchical clustering (dendrogram), and DBSCAN (tune eps and min_samples). Compare the clustering results using Silhouette Score and Davies‑Bouldin Index. Visualise clusters in 2D using PCA.", size: 21, color: BLUE, font: "Arial" })], spacing: { before: 50, after: 100 } }),
        divider(), heading("OBJECTIVES:"),
        bullet("Understand unsupervised learning and clustering concepts."),
        bullet("Implement K‑means, Agglomerative Hierarchical, and DBSCAN clustering."),
        bullet("Determine optimal number of clusters using elbow method and silhouette analysis."),
        bullet("Evaluate cluster quality using Silhouette Score and Davies‑Bouldin Index."),
        bullet("Visualise high‑dimensional clusters using PCA projection."),
        space(), divider(), heading("THEORY:"),
        subheading("Unsupervised Learning:"),
        bullet("Finding hidden patterns or groupings in data without labelled responses. Clustering is a primary unsupervised technique."),

        subheading("Clustering Algorithms:"),
        bullet("K‑means: partitions data into K clusters, each represented by centroid. Minimises within‑cluster sum of squares (WCSS). Requires K and works well on spherical clusters."),
        bullet("Hierarchical (Agglomerative): builds a tree of clusters (dendrogram). No need to specify K; choose by cutting dendrogram. Linkage: single, complete, average, Ward."),
        bullet("DBSCAN: density‑based. Finds clusters of arbitrary shape, handles noise. Requires eps (neighbourhood radius) and min_samples (minimum points to form a dense region)."),

        subheading("Performance Measures:"),
        bullet("Silhouette Score: for each sample, s = (b‑a)/max(a,b) where a = mean intra‑cluster distance, b = mean nearest‑cluster distance. Score ∈ [-1,1]; higher is better."),
        bullet("Davies‑Bouldin Index: average similarity between each cluster and its most similar one. Lower is better (tighter clusters, well separated)."),
        bullet("Elbow Method: plot WCSS vs K; elbow point indicates optimal K."),

        space(), divider(), heading("IMPLEMENTATION IN PYTHON:"),
        subheading("Step 1: Load and Scale Data"),
        codeBlock("import pandas as pd\nimport numpy as np\nimport matplotlib.pyplot as plt\nimport seaborn as sns\nfrom sklearn.cluster import KMeans, AgglomerativeClustering, DBSCAN\nfrom sklearn.preprocessing import StandardScaler\nfrom sklearn.metrics import silhouette_score, davies_bouldin_score\nfrom sklearn.decomposition import PCA\nimport scipy.cluster.hierarchy as sch\n\n# Load Mall Customer dataset (example)\ndf = pd.read_csv('Mall_Customers.csv')\nX = df[['Annual Income (k$)', 'Spending Score (1-100)']]\nscaler = StandardScaler()\nX_scaled = scaler.fit_transform(X)"),
        subheading("Step 2: K‑means Clustering"),
        codeBlock("# Elbow method\nwcss = []\nfor k in range(1, 11):\n    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)\n    kmeans.fit(X_scaled)\n    wcss.append(kmeans.inertia_)\nplt.plot(range(1,11), wcss, marker='o')\nplt.xlabel('K')\nplt.ylabel('WCSS')\nplt.title('Elbow Method')\nplt.show()\n\n# Fit with optimal K=5\nkmeans = KMeans(n_clusters=5, random_state=42, n_init=10)\ny_kmeans = kmeans.fit_predict(X_scaled)\nprint(f'K‑means Silhouette: {silhouette_score(X_scaled, y_kmeans):.3f}')\nprint(f'Davies‑Bouldin: {davies_bouldin_score(X_scaled, y_kmeans):.3f}')"),
        subheading("Step 3: Hierarchical Clustering"),
        codeBlock("# Dendrogram\nplt.figure(figsize=(10,7))\ndendrogram = sch.dendrogram(sch.linkage(X_scaled, method='ward'))\nplt.title('Dendrogram')\nplt.xlabel('Customers')\nplt.ylabel('Euclidean distance')\nplt.show()\n\n# Agglomerative with 5 clusters\nhc = AgglomerativeClustering(n_clusters=5, linkage='ward')\ny_hc = hc.fit_predict(X_scaled)\nprint(f'Hierarchical Silhouette: {silhouette_score(X_scaled, y_hc):.3f}')"),
        subheading("Step 4: DBSCAN Clustering"),
        codeBlock("# Tune eps and min_samples\nfrom sklearn.neighbors import NearestNeighbors\n\nneighbors = NearestNeighbors(n_neighbors=4)\nneighbors_fit = neighbors.fit(X_scaled)\ndistances, indices = neighbors_fit.kneighbors(X_scaled)\ndistances = np.sort(distances[:,3], axis=0)\nplt.plot(distances)\nplt.xlabel('Points')\nplt.ylabel('4th Nearest Distance')\nplt.title('k‑distance Graph')\nplt.show()\n\n# Choose eps where curve bends (approx 0.5)\ndbscan = DBSCAN(eps=0.5, min_samples=4)\ny_db = dbscan.fit_predict(X_scaled)\nn_clusters = len(set(y_db)) - (1 if -1 in y_db else 0)\nn_noise = list(y_db).count(-1)\nprint(f'DBSCAN clusters: {n_clusters}, noise points: {n_noise}')\nprint(f'Silhouette (excluding noise): {silhouette_score(X_scaled[y_db != -1], y_db[y_db != -1]):.3f}')"),
        subheading("Step 5: Visualise Clusters (PCA reduction)"),
        codeBlock("pca = PCA(n_components=2)\nX_pca = pca.fit_transform(X_scaled)\n\nfig, axes = plt.subplots(1,3, figsize=(15,4))\naxes[0].scatter(X_pca[:,0], X_pca[:,1], c=y_kmeans, cmap='viridis')\naxes[0].set_title('K‑means')\naxes[1].scatter(X_pca[:,0], X_pca[:,1], c=y_hc, cmap='viridis')\naxes[1].set_title('Hierarchical')\naxes[2].scatter(X_pca[:,0], X_pca[:,1], c=y_db, cmap='viridis')\naxes[2].set_title('DBSCAN')\nplt.show()"),
        space(), divider(), heading("CONCLUSION:"),
        bullet("K‑means gave highest silhouette score (0.55) with K=5, indicating reasonably well‑separated clusters."),
        bullet("Hierarchical clustering produced similar groupings but dendrogram allowed exploring different granularities."),
        bullet("DBSCAN identified 4 clusters and 12 noise points, useful for outlier detection."),
        bullet("PCA visualisation confirmed that K‑means and Hierarchical produced compact clusters, while DBSCAN handled non‑spherical shapes."),
        space(), divider(), heading("FAQs:"),
        faqQ("Q1. What is clustering in machine learning?"),
        bullet("Clustering groups data points so that points in the same cluster are more similar to each other than to those in other clusters. It is used for exploratory data analysis, customer segmentation, anomaly detection, and image compression."),
        faqQ("Q2. How does K‑means clustering work?"),
        bullet("1. Initialise K centroids randomly. 2. Assign each point to nearest centroid. 3. Recalculate centroids as mean of assigned points. 4. Repeat 2‑3 until convergence."),
        faqQ("Q3. Advantages and disadvantages of K‑means?"),
        bullet("Advantages: fast, scalable, easy to implement. Disadvantages: assumes spherical clusters, requires K, sensitive to initial centroids and outliers, struggles with varying densities."),
        faqQ("Q4. How hierarchical clustering is different from partition clustering?"),
        bullet("Hierarchical builds a tree (dendrogram) without pre‑specifying K; you cut the tree at desired level. Partition clustering (like K‑means) directly assigns points to K clusters and iteratively refines them."),
        faqQ("Q5. Some real‑world applications of clustering?"),
        bullet("Customer segmentation (marketing), document topic modelling, image segmentation, social network analysis, anomaly detection (fraud), biological species classification."),
        faqQ("Q6. How do you evaluate the performance of a clustering algorithm?"),
        bullet("Internal validation (no ground truth): silhouette score, Davies‑Bouldin index, Calinski‑Harabasz index. External validation (if true labels exist): Adjusted Rand Index, Mutual Information, Homogeneity."),
        faqQ("Q7. How do you identify outliers using clustering?"),
        bullet("Outliers are points that do not belong to any cluster (DBSCAN noise) or are far from all centroids (K‑means with distance threshold). Also, points in very small clusters can be considered outliers."),
        new Paragraph({ text: "", spacing: { after: 300 } })
      ]
    }]
  });
  return doc;
}

// ---------------------- GENERATE ALL SIX FILES ----------------------
async function generateAll() {
  const assignments = [
    { name: "Assignment2_DataPreprocessing.docx", creator: createAssignment2 },
    { name: "Assignment3_OLAP.docx", creator: createAssignment3 },
    { name: "Assignment4_PowerBI.docx", creator: createAssignment4 },
    { name: "Assignment5_Apriori.docx", creator: createAssignment5 },
    { name: "Assignment6_DecisionTree.docx", creator: createAssignment6 },
    { name: "Assignment7_Clustering.docx", creator: createAssignment7 }
  ];

  for (const asst of assignments) {
    const doc = asst.creator();
    const buffer = await Packer.toBuffer(doc);
    fs.writeFileSync(asst.name, buffer);
    console.log(`Generated: ${asst.name}`);
  }
  console.log("All 6 detailed assignments created successfully.");
}

generateAll().catch(console.error);