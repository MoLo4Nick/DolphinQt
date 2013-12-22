#include <QTabWidget>
#include <QPushButton>

class QButtonGroup;
class QCheckBox;
class QComboBox;
class QListWidget;
class DControlStateManager;

class DConfigMainGeneralTab : public QTabWidget
{
	Q_OBJECT

public:
	DConfigMainGeneralTab(QWidget* p = NULL);

signals:
	void IsoPathsChanged();

public slots:
	void Reset();
	void Apply();

	void OnAddIsoPath();
	void OnRemoveIsoPath();
	void OnClearIsoPathList();

	void OnPathListChanged();
	void OnSelectionChanged();

private:
	QWidget* CreateCoreTabWidget(QWidget* p);
	QWidget* CreatePathsTabWidget(QWidget* p);

	// Core
	QCheckBox* cbDualCore,* cbIdleSkipping,* cbCheats;

	QComboBox* chFramelimit;
	QButtonGroup* rbCPUEngine;

	QCheckBox* cbFPSLimit,* cbConfirmOnStop,* cbRenderToMain;

	// Paths
	QListWidget* pathList;
	QCheckBox* cbRecurse;
	QPushButton* addPath,* removePath, *clearPathList;
	bool paths_changed;

	DControlStateManager* ctrlManager;
};
