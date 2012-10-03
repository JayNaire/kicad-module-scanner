#ifndef KICAD_MODULE_SCANNER_H
#define KICAD_MODULE_SCANNER_H

#include <QtGui>
#include <QProcess>

#include "ui_kicad_module_scanner.h"

/**
 * Class TreeWidgetItem
 * Overrides operator< to get correct numeric sorting for NumPins in treeSearchResults
 */
class TreeWidgetItem : public QTreeWidgetItem {
public:
	TreeWidgetItem(QTreeWidget* parent):QTreeWidgetItem(parent){}
private:
	bool operator<(const QTreeWidgetItem &other)const {
		int column = treeWidget()->sortColumn();
		bool OK;
		if (column == 1){ //if column is numpins
			return this->text(1).toInt(&OK) < other.text(1).toInt(&OK);
		}
		return QTreeWidgetItem::operator<( other);
	}
};
/**
 * Class footprint
 * Just used to record footprints thet are to be copied
 * @see QList<footprint *>	footprintsToCopy
 */
class footprint{
public:
	footprint();
	footprint(QString name, QString file) : name(name), file(file) {};
	~footprint();
	QString name;
	QString file;
};

class kicad_module_scanner : public QMainWindow
{
    Q_OBJECT

public:
    kicad_module_scanner(QWidget *parent = 0);
    ~kicad_module_scanner();

private slots:
	//General setup tab
	void onScriptLocationChanged();
	void on_btnSelectPostscriptViewer_clicked();

	//Folder Scanning tab
	void on_btnAddFolderToScan_clicked();
	void on_btnRemoveFolderToScan_clicked();
	void on_btnScanCheckedFolders_clicked();
	void on_btnStopScanCheckedFolders_clicked();

	//File Scanning tab
	void on_btnAddFileToScan_clicked();
	void on_btnRemoveFileToScan_clicked();
	void on_btnScanCheckedFiles_clicked();
	void on_btnStopScanCheckedFiles_clicked();

	//Viewing tab
	void on_cboDatabaseFile_currentIndexChanged ( int index ){(void) index; ui.treeSearchResults->clear();};
	void on_cboDatabaseFile_editTextChanged ( const QString & text ){(void) text; ui.treeSearchResults->clear();};
	void on_btnSelectFootprintDatabase_clicked();
	void on_btnSearch_clicked();
	void on_cboCopyToLibrary_editTextChanged ( const QString & text );
	void on_cboCopyToLibrary_currentIndexChanged ( const QString & text );
	void on_chkDescription_toggled( bool checked ){(void) checked; ui.treeSearchResults->clear();};
	void on_chkFootprintName_toggled( bool checked ){(void) checked; ui.treeSearchResults->clear();};
	void on_chkKeywords_toggled( bool checked ){(void) checked; ui.treeSearchResults->clear();};
	void on_chkPins_toggled( bool checked ){(void) checked; ui.treeSearchResults->clear();};
	void on_treeSearchResults_itemClicked( QTreeWidgetItem * item, int column);
	void on_treeSearchResults_currentItemChanged( QTreeWidgetItem *, QTreeWidgetItem *){setupBtnPreview();};
	void on_chkAutoPreview_toggled( bool checked){(void) checked; setupBtnPreview();};
	void on_btnPreview_clicked(){previewFootprint(ui.treeSearchResults->currentItem());};
	void on_btnSelectCopyToLibrary_clicked();
	void on_btnCopy_clicked();
	void on_modView_measurementChanged(QPointF pip1, QPointF pip2);
	void on_rdoGrid10Mil_toggled(bool b){ui.gbMeasure->setTitle(QString("Measure (%1)").arg(b?"mil":"mm"));};

	//callbacks
	void onShellProcessReadyReadStandardOutput();
	void onShellProcessReadyReadStandardOutputData();

	void onShellProcessStartedFolders();
	void onShellProcessFinishedFolders(int, QProcess::ExitStatus);

	void onShellProcessStartedFiles();
	void onShellProcessFinishedFiles(int, QProcess::ExitStatus);

	void onShellProcessStartedRetrievePS();
	void onShellProcessFinishedRetrievePS(int, QProcess::ExitStatus);

	void onShellProcessStartedRetrieveData();
	void onShellProcessFinishedRetrieveData(int, QProcess::ExitStatus);

	void onShellProcessStartedCopyFootprint();
	void onShellProcessFinishedCopyFootprint(int, QProcess::ExitStatus);

	void onViewerStarted();
	void onViewerFinished(int, QProcess::ExitStatus);


private:
    Ui::kicad_module_scannerClass ui;
    bool checkScriptsExist();
    void runFootprintCopier();
	void addToList(QComboBox *cbo, QString text = QString());
	void readRdoSettings(QRadioButton *rdo);
	void saveRdoSettings(QRadioButton *rdo);
	void readCboSettings(QComboBox *cbo);
	void saveCboSettings(QComboBox *cbo);
	void readChkSettings(QCheckBox *chk);
	void saveChkSettings(QCheckBox *chk);
	void readBtnSettings(QPushButton *btn);
	void saveBtnSettings(QPushButton *btn);
	void readLstSettings(QListWidget *lst);
	void saveLstSettings(QListWidget *lst);
	void startViewer();
	const QString composeQuery();
	int numCheckedFootprints();
	bool oKToCopyFootprints();
	void updateFootprintsInDestinationLibrary();
	void setupBtnPreview();
	void previewFootprintOld(QTreeWidgetItem * item);
	void previewFootprint(QTreeWidgetItem * item);
	int indexOfFootprintBeingCopied;
	bool viewerIsRunning;
    QProcess *viewerProcess;
	QProcess *shellProcess;
	QList<footprint *>	footprintsToCopy;
	QString data; //! see onShellProcessReadyReadStandardOutputData()
protected:
	void closeEvent(QCloseEvent *event);
};

#endif // KICAD_MODULE_SCANNER_H
