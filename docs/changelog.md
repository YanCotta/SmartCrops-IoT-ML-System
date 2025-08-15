# Changelog

## Day 1 — 2025-08-15

Initial project scaffold and first-commit tasks completed for the SmartCrops IoT + ML system:

- Repository initialization
	- Added `.gitignore`, `LICENSE`, and `README.md`.

- Documentation
	- Added `docs/implementation_plan.md`.
	- Created `docs/changelog.md` (this file) and recorded Day 1 tasks.

- Changelog

## Day 1 — 2025-08-15

Initial project scaffold and first-commit tasks completed for the SmartCrops IoT + ML system:

- Repository initialization
	- Added `.gitignore`, `LICENSE`, and `README.md`.

- Documentation
	- Added `docs/implementation_plan.md`.
	- Created `docs/changelog.md` and recorded Day 1 tasks.

- Edge-node firmware (Ir Além 1)
	- `ir-alem1/gateway-node/main.ino` — initial Arduino sketch for the gateway node.
	- `ir-alem1/sensor-node/main.ino` — initial Arduino sketch for the sensor node.

- Data collection & ML (Ir Além 2)
	- `ir-alem2/collector.py` — Python script to collect/receive sensor readings from the network.
	- `ir-alem2/ml_template.ipynb` — Machine learning analysis notebook. Key contents:
		- All imports in a single reproducible cell (pandas, numpy, matplotlib, seaborn, scikit-learn, joblib).
		- Entrega 1: Crop Yield Analysis
			- Loads `crop_yield.csv`.
			- Exploratory Data Analysis: head, describe, info, missing values.
			- Visualizations: yield distribution histogram and correlation heatmap.
			- Categorical handling: one-hot encoding for `Crop`.
			- Feature scaling with `StandardScaler`.
			- Unsupervised analysis: Elbow method and `KMeans` clustering.
			- Outlier detection with `IsolationForest`.
			- Supervised regression models: Linear Regression, Decision Tree, Random Forest, SVR, KNN (results printed and summarized).
		- Ir Além 2: Sensor Data Classification
			- Loads `sensor_data.csv`.
			- Maps `label` to binary `health` (Healthy=1, Unhealthy=0).
			- Trains a `LogisticRegression` classifier, prints accuracy and confusion matrix.
			- Performs 5-fold cross-validation and saves the trained classifier to `classifier.pkl` for integration with `collector.py`.

-- End of Day 1


