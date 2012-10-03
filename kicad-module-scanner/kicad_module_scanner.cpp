#include <QtXmlPatterns/QXmlQuery>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <qevent.h>
#include <QFileDialog>
#include <QDate>
#include <qlist.h>
#include <ModView.h>
#include "main.h"
#include <math.h>
#include "kicad_module_scanner.h"

#define MAX_CBO_SETTINGS 20
#define MAX_LST_SETTINGS 20

//TODO warn when checked fp already exists in target library

void kicad_module_scanner::onScriptLocationChanged(){
	bool warn = checkScriptsExist();
	if (warn){
		ui.tabFolderScanning->setEnabled(false);
		ui.tabFileScanning->setEnabled(false);
		ui.tabFindingCopying->setEnabled(false);
		ui.tabViewer->setEnabled(false);
	}
	else{
		ui.tabFolderScanning->setEnabled(true);
		ui.tabFileScanning->setEnabled(true);
		ui.tabFindingCopying->setEnabled(true);
		ui.tabViewer->setEnabled(true);
	}
}

/**
 * Checks whether scripts exist. Missing scripts are set to red text; existing scripts are set to standard colour text.
 * @return True if all scripts exist, false otherwise
 */
bool kicad_module_scanner::checkScriptsExist(){
	bool warn = false;
	QList<QLineEdit*> scripts;
	scripts << ui.leShellWorkerScript << ui.leAwkScript << ui.leCopierScript << ui.leExtractorScript;
	QPalette missingPalette;
	missingPalette.setBrush(QPalette::Text, Qt::red);
	for (int i = 0; i < scripts.count(); i++){
		if (!QFile::exists(scripts.at(i)->text())){
			scripts.at(i)->setPalette(missingPalette);
			warn = true;
		}
		else{
			scripts.at(i)->setPalette(palette());
		}
	}
	return warn;
}

kicad_module_scanner::kicad_module_scanner(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.tabWidget->setCurrentIndex(3); //Selecting/Copying tab
	ui.treeSearchResults->sortByColumn(0,Qt::AscendingOrder);
	viewerIsRunning = false;

	//setup General Setup tab
	ui.leShellWorkerScript->setText(settings->value("leShellWorkerScript","scripts/kicad-module-scanner.sh").toString());
	ui.leAwkScript->setText(settings->value("leAwkScript","scripts/kicad-module-scanner.awk").toString());
	ui.leCopierScript->setText(settings->value("leCopierScript","scripts/kicad-copy-module.sh").toString());
	ui.leExtractorScript->setText(settings->value("leExtractorScript","scripts/kicad-extract-module.awk").toString());
	bool warn = checkScriptsExist();
	if (warn){
		QString msg("One or more script files cannot be found.");
		msg += "\nThis may mean the application is running from an incorrect directory.";
		QMessageBox::warning(this,qAppName(),msg,QMessageBox::Cancel,QMessageBox::Cancel);
		ui.tabWidget->setCurrentIndex(0); //setup page TODO check files exist when fields change; remove red text set above
		ui.tabFolderScanning->setEnabled(false);
		ui.tabFileScanning->setEnabled(false);
		ui.tabFindingCopying->setEnabled(false);
		ui.tabViewer->setEnabled(false);
	}
	readCboSettings(ui.cboPostscriptViewer);
	readCboSettings(ui.cboViewerTemporaryFile);

	//setup Folder Scanning tab
	readLstSettings(ui.lstFoldersToScan);
	readRdoSettings(ui.rdoFolderScanOutputOverwrite);
	readRdoSettings(ui.rdoFolderScanOutputAppend);
	readChkSettings(ui.chkFolderIncludePostscript);
	readCboSettings(ui.cboOutputFile_FolderScanning);

	//setup File Scanning tab
	readLstSettings(ui.lstFilesToScan);
	readRdoSettings(ui.rdoFileScanOutputOverwrite);
	readRdoSettings(ui.rdoFileScanOutputAppend);
	readChkSettings(ui.chkFileIncludePostscript);
	readCboSettings(ui.cboOutputFile_FileScanning);

	//setup Finding/Copying tab
	readCboSettings(ui.cboDatabaseFile);
	bool OK;
	ui.spinBoxNumPins->setValue(settings->value(ui.spinBoxNumPins->objectName(),2).toInt(&OK));
	readCboSettings(ui.cboFootprintName);
	readCboSettings(ui.cboKeywords);
	readCboSettings(ui.cboDescription);
	readChkSettings(ui.chkPins);
	readChkSettings(ui.chkFootprintName);
	readChkSettings(ui.chkKeywords);
	readChkSettings(ui.chkDescription);
	ui.treeSearchResults->clear(); //trash design time items
	readChkSettings(ui.chkAutoPreview);
//	readChkSettings(ui.chkShowPinNumbers);
//	ui.cboScale->setCurrentIndex(settings->value(ui.cboScale->objectName(),1).toInt()); //set to 100% scale
	ui.leCopyToModule->setText(settings->value(ui.leCopyToModule->objectName(),"").toString());
	readCboSettings(ui.cboCopyToLibrary);
	readChkSettings(ui.chkAllowOverwrite);
//	ui.chkAutoDisplay->setChecked(settings->value("chkAutoDisplay", true).toBool());
//	ui.chkFolderIncludePostscript->setChecked(settings->value("chkFolderIncludePostscript", false).toBool());
//	ui.chkFileIncludePostscript->setChecked(settings->value("chkFileIncludePostscript", false).toBool());
	readBtnSettings(ui.btnViewingMode);
	readBtnSettings(ui.btnCopyingMode);
	//always true even if settings are false
	qDebug() << "ui.btnViewingMode->isChecked(): " << ui.btnViewingMode->isChecked();
	ui.modViewSmall->setShown(ui.btnViewingMode->isChecked());
	ui.gbCopy->setHidden(ui.btnViewingMode->isChecked());
//	ui.splitter->handle(1)->move()set
}

kicad_module_scanner::~kicad_module_scanner()
{

}
void kicad_module_scanner::readCboSettings(QComboBox *cbo){
	int size = settings->beginReadArray(cbo->objectName());
		if (size){
			cbo->clear(); //trash design time items
			for (int i = 0; i < size; ++i) {
				settings->setArrayIndex(i);
				cbo->addItem(settings->value("file").toString());
				if (settings->value("isCurrent",false).toBool()) cbo->setCurrentIndex(i);
			}
		}
	settings->endArray();
}

void kicad_module_scanner::saveCboSettings(QComboBox *cbo){
	if (cbo->count()>0){
		settings->beginWriteArray(cbo->objectName(),cbo->count());
		for (int i = 0; i < MAX_CBO_SETTINGS && i < cbo->count(); ++i) {
			settings->setArrayIndex(i);
			settings->setValue("file", cbo->itemText(i));
			if (cbo->currentIndex() == i){
				settings->setValue("isCurrent", true);
			}
			else{
				settings->setValue("isCurrent", false);
			}
		}
		settings->endArray();
	}
}
void kicad_module_scanner::readLstSettings(QListWidget *lst){
	int size = settings->beginReadArray(lst->objectName());
	if (size){
		lst->clear(); //trash design time items
		for (int i = 0; i < size; ++i) {
			settings->setArrayIndex(i);
			QListWidgetItem *qlistwidgetitem = new QListWidgetItem(lst);
			qlistwidgetitem->setText(settings->value("file").toString());
			qlistwidgetitem->setCheckState(settings->value("isChecked").toBool()?Qt::Checked:Qt::Unchecked);
			qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
		}
	}
	settings->endArray();
}

void kicad_module_scanner::saveLstSettings(QListWidget *lst){
	if (lst->count()>0){
		settings->beginWriteArray(lst->objectName(), lst->count());
		for (int i = 0; i < MAX_LST_SETTINGS && i < lst->count(); ++i) {
			settings->setArrayIndex(i);
			settings->setValue("file", lst->item(i)->text()); //eg:1\folder=/usr/share/kicad/modules
			settings->setValue("isChecked", lst->item(i)->checkState()); //eg:1\isChecked=2
		}
		settings->endArray();
	}

}

void kicad_module_scanner::readChkSettings(QCheckBox *chk){
	chk->setChecked(settings->value(chk->objectName(), false).toBool());
}
void kicad_module_scanner::saveChkSettings(QCheckBox *chk){
	settings->setValue(chk->objectName(), chk->isChecked());
}
void kicad_module_scanner::readBtnSettings(QPushButton *btn){
	qDebug() << "readBtnSettings: " << btn->objectName();
	qDebug() << "\t= : " << settings->value(btn->objectName(), false).toBool();

	btn->setChecked(settings->value(btn->objectName(), false).toBool());
}
void kicad_module_scanner::saveBtnSettings(QPushButton *btn){
	settings->setValue(btn->objectName(), btn->isChecked());
}

void kicad_module_scanner::readRdoSettings(QRadioButton *rdo){
	rdo->setChecked(settings->value(rdo->objectName(), false).toBool());
}
void kicad_module_scanner::saveRdoSettings(QRadioButton *rdo){
	settings->setValue(rdo->objectName(), rdo->isChecked());
}

void kicad_module_scanner::setupBtnPreview(){
	//adjust ui.btnPreview
	ui.btnPreview->setEnabled(false);
	if (ui.treeSearchResults->currentItem() == 0) return;
	if (ui.chkAutoPreview->isChecked()) return;
	ui.btnPreview->setEnabled(true);
}

void kicad_module_scanner::closeEvent(QCloseEvent *event)
{
	settings->clear(); //must clear everything first otherwise items deleted in say a cbo box won't get removed

	//save General Setup tab
	settings->setValue("leShellWorkerScript", ui.leShellWorkerScript->text());
	settings->setValue("leAwkScript", ui.leAwkScript->text());
	settings->setValue("leCopierScript", ui.leCopierScript->text());
	settings->setValue("leExtractorScript", ui.leExtractorScript->text());
	addToList(ui.cboPostscriptViewer); //save any user amendments - they don't get saved anywhere else
	saveCboSettings(ui.cboPostscriptViewer);
	addToList(ui.cboViewerTemporaryFile); //save any user amendments - they don't get saved anywhere else
	saveCboSettings(ui.cboViewerTemporaryFile);

	//save Folder Scanning tab
	saveLstSettings(ui.lstFoldersToScan);
	saveRdoSettings(ui.rdoFolderScanOutputOverwrite);
	saveRdoSettings(ui.rdoFolderScanOutputAppend);
	saveChkSettings(ui.chkFolderIncludePostscript);
	addToList(ui.cboOutputFile_FolderScanning);
	saveCboSettings(ui.cboOutputFile_FolderScanning);

	//save File Scanning tab
	saveLstSettings(ui.lstFilesToScan);
	saveRdoSettings(ui.rdoFileScanOutputOverwrite);
	saveRdoSettings(ui.rdoFileScanOutputAppend);
	saveChkSettings(ui.chkFileIncludePostscript);
	addToList(ui.cboOutputFile_FileScanning);
	saveCboSettings(ui.cboOutputFile_FileScanning);

	//save Finding/Copying tab
	saveCboSettings(ui.cboDatabaseFile);
	settings->setValue("spinBoxNumPins", ui.spinBoxNumPins->value());
	addToList(ui.cboFootprintName);
	saveCboSettings(ui.cboFootprintName);
	addToList(ui.cboKeywords);
	saveCboSettings(ui.cboKeywords);
	addToList(ui.cboDescription);
	saveCboSettings(ui.cboDescription);
	saveChkSettings(ui.chkPins);
	saveCboSettings(ui.cboFootprintName);
	saveChkSettings(ui.chkFootprintName);
	saveChkSettings(ui.chkKeywords);
	saveChkSettings(ui.chkDescription);
	saveChkSettings(ui.chkAutoPreview);
//	saveChkSettings(ui.chkShowPinNumbers);
//	settings->setValue(ui.cboScale->objectName(), ui.cboScale->currentIndex());//item list is fixed, do not use saveCbo
	settings->setValue(ui.leCopyToModule->objectName(), ui.leCopyToModule->text());
	addToList(ui.cboCopyToLibrary); //save any user amendments - they don't get saved anywhere else
	saveCboSettings(ui.cboCopyToLibrary);
	saveChkSettings(ui.chkAllowOverwrite);
	saveBtnSettings(ui.btnViewingMode);
	saveBtnSettings(ui.btnCopyingMode);
	settings->sync(); //do not remove
//	if (this->viewerIsRunning == true) {
//		this->viewerProcess->close();
//	}
	event->accept();
}
//void kicad_module_scanner::on_cboDatabaseFile_currentIndexChanged ( int index ){
//	(void) index;
//	ui.treeSearchResults->clear();
//}
//void kicad_module_scanner::on_cboDatabaseFile_editTextChanged ( const QString & text ){
//	(void) text;
//	ui.treeSearchResults->clear();
//}
void kicad_module_scanner::on_btnRemoveFolderToScan_clicked(){
//	ui.lstFoldersToScan->removeItemWidget(ui.lstFoldersToScan->currentItem()); //doesn't work
	delete ui.lstFoldersToScan->currentItem(); //works - and is kosher!
	QApplication::processEvents();
	ui.btnRemoveFolderToScan->setEnabled(ui.lstFoldersToScan->count() > 0);
}

void kicad_module_scanner::on_btnAddFolderToScan_clicked(){
	//    QString directory = QFileDialog::getExistingDirectory(this,
	//                                "Select a Folder to Scan (must contain one or more .mod files)");
	QString directory;
	QFileDialog dialog(this, "Select a Folder to Scan (must contain one or more .mod files)");
	dialog.setFileMode(QFileDialog::Directory);
//	dialog.setOption()//| QFileDialog::ExistingFile
	//dialog.setOption(QFileDialog::ShowDirsOnly);
	dialog.setViewMode(QFileDialog::Detail);
//	QStringList fileNames;
	if (dialog.exec()){
		for (int i = 0; i < dialog.selectedFiles().count(); i++){ //wasted! can't select > 1 folder!?
			QString directory = dialog.selectedFiles().at(i);
			if (!directory.isEmpty()){
				QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui.lstFoldersToScan);
				__qlistwidgetitem->setText(directory);
				__qlistwidgetitem->setCheckState(Qt::Checked);
				__qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
				ui.btnRemoveFolderToScan->setEnabled(true);
			}
		}
	}
}
void kicad_module_scanner::on_btnSelectFootprintDatabase_clicked(){
	QString fileName = QFileDialog::getOpenFileName(this,
			"Select the Footprint Database",
			"",
			"Footprint Databases (*.kms);;xml files (*.xml);;All files (*)");
	if (fileName.isNull()) return;
	addToList(ui.cboDatabaseFile, fileName);
}

void kicad_module_scanner::on_btnSelectCopyToLibrary_clicked(){
	QString fileName = QFileDialog::getSaveFileName(this,
			"Select a Footprint Library to copy Module(s) to",
			"",
			"Footprint Libraries (*.mod);;All files (*)");
	if (fileName.isNull()) return;
	addToList(ui.cboCopyToLibrary, fileName);
}

void kicad_module_scanner::on_btnSelectPostscriptViewer_clicked(){
	QString fileName = QFileDialog::getOpenFileName(this,
			"Select a Postscript Viewer",
			"",
			"All files (*)");
	if (fileName.isNull()) return;
	addToList(ui.cboPostscriptViewer, fileName);
}

void kicad_module_scanner::on_btnAddFileToScan_clicked(){
	QStringList fileNames = QFileDialog::getOpenFileNames(this,
			"Select one or more Footprint libraries (.mod) to Scan",
			"",
			"Footprint Libraries (*.mod);;All files (*)"); /*,
			"*.mod",
			QFileDialog::ReadOnly);*/
	QList<QListWidgetItem *> itemsFound;
	for (int i = 0; i < fileNames.count(); i++){ //can select > 1 file
		QString fileName = fileNames.at(i);
		itemsFound =  ui.lstFilesToScan->findItems(fileName,Qt::MatchFixedString | Qt::MatchCaseSensitive);
		if (itemsFound.count() == 0){ //only add files if not in list already
			QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(ui.lstFilesToScan);
			__qlistwidgetitem->setText(fileName);
			__qlistwidgetitem->setCheckState(Qt::Checked);
			__qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
			ui.btnRemoveFileToScan->setEnabled(true);
		}
	}
}
void kicad_module_scanner::on_btnRemoveFileToScan_clicked(){
	delete ui.lstFilesToScan->currentItem(); //works - and is kosher!
	QApplication::processEvents();
	ui.btnRemoveFileToScan->setEnabled(ui.lstFilesToScan->count() > 0);
}

void kicad_module_scanner::on_btnStopScanCheckedFolders_clicked(){ //disabled unless shellProcess is running
	if (! shellProcess){
		shellProcess->kill(); //does this fire onShellProcessFinished? TODO
	}
}

void kicad_module_scanner::on_btnStopScanCheckedFiles_clicked(){ //disabled unless shellProcess is running
	if (! shellProcess){
		shellProcess->kill(); //does this fire onShellProcessFinished? TODO
	}
}

/**
 * If the combobox's itemList contains an item whose text equals text that item is
 * set current and nothing else happens.
 * If the combobox's itemList does not contain an item whose text equals text
 * then it is added. If text is not given the cbo's currentText is used. Use this
 * to add an item added by the user, this will then be saved in closeEvent.
 * In particular, use this to add a scan output file to the viewer database file list
 * - see onShellProcessFinishedFolders and onShellProcessFinishedFiles().
 */
void kicad_module_scanner::addToList(QComboBox *cbo, QString text){
	bool found = false;
	QString theText;

	if (text.isNull()) theText = cbo->currentText();
	else theText = text;

	for (int i = 0; i < cbo->count(); ++i) {
		if (theText == cbo->itemText(i)){
			cbo->setCurrentIndex(i);
			found = true;
			break;
		}
	}
	if (!found){
		cbo->insertItem(0, theText); //insert at top, item 0
		cbo->setCurrentIndex(0); //set current item
	}
}

void kicad_module_scanner::on_btnScanCheckedFolders_clicked(){
	addToList(ui.cboOutputFile_FolderScanning);
	bool doMsgBox = false;
	if (ui.lstFoldersToScan->count() > 0){
		shellProcess = new QProcess(this);
		QStringList arguments;
		QString program = ui.leShellWorkerScript->text();
		//warning - filenames with spaces may cause problems
//		arguments << QString("--outfile=\"%1\"").arg(ui.cboOutputFile_FileScanning->currentText());
		arguments << QString("--outfile=%1").arg(ui.cboOutputFile_FolderScanning->currentText());
		arguments << "--inputmode=folder";
		arguments << "--outputxml=on";
//		arguments << QString("--awkscript=\"%1\"").arg(ui.leAwkScript->text());
		arguments << QString("--awkscript=%1").arg(ui.leAwkScript->text());
		arguments << QString("--postscript=%1").arg(ui.chkFolderIncludePostscript->isChecked()?"on":"off");
		arguments << QString("--outputmode=%1").arg(ui.rdoFolderScanOutputAppend->isChecked()?"append":"overwrite");
//		if (ui.chkFolderIncludePostscript->isChecked()) arguments << "--postscript=on";
//		else  arguments << "--postscript=off";
//		if (ui.rdoFolderScanOutputAppend->isChecked()){ //default output mode is overwrite
//			arguments << "--outputmode=append";
//		}
		int count = 0;
		for (int i = 0; i < ui.lstFoldersToScan->count(); ++i) {
			if (ui.lstFoldersToScan->item(i)->checkState() == Qt::Checked){
//				arguments << QString("\"%1\"").arg(ui.lstFoldersToScan->item(i)->text()) ;
				arguments << QString("%1").arg(ui.lstFoldersToScan->item(i)->text()) ;
				count++;
			}
		}
		if (count){
			connect(shellProcess, SIGNAL(started()), this, SLOT(onShellProcessStartedFolders()));
			connect(shellProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onShellProcessFinishedFolders(int, QProcess::ExitStatus)));
			connect(shellProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onShellProcessReadyReadStandardOutput()));
			shellProcess->start(program, arguments);
		}
		else{
			doMsgBox = true;
		}
	}
	else{
		doMsgBox = true;
	}
	if (doMsgBox) QMessageBox::information(this,"Info","There are no checked folders to scan");
}

void kicad_module_scanner::on_btnScanCheckedFiles_clicked(){
	//save output file in ui.cboOutputFile_FileScanning->currentText()
	addToList(ui.cboOutputFile_FileScanning);
	if (ui.lstFilesToScan->count() > 0){
		shellProcess = new QProcess(this);
		QStringList arguments;
		QString program = ui.leShellWorkerScript->text();
		//warning - filenames with spaces may cause problems
//		arguments << QString("--outfile=\"%1\"").arg(ui.cboOutputFile_FileScanning->currentText());
		arguments << QString("--outfile=%1").arg(ui.cboOutputFile_FileScanning->currentText());
		arguments << "--inputmode=file";
		arguments << "--outputxml=on";
//		arguments << QString("--awkscript=\"%1\"").arg(ui.leAwkScript->text());
		arguments << QString("--awkscript=%1").arg(ui.leAwkScript->text());
		arguments << QString("--postscript=%1").arg(ui.chkFileIncludePostscript->isChecked()?"on":"off");
		arguments << QString("--outputmode=%1").arg(ui.rdoFileScanOutputAppend->isChecked()?"append":"overwrite");
//		if (ui.chkFileIncludePostscript->isChecked()) arguments << "--postscript=on";
//		else  arguments << "--postscript=off";
//		if (ui.rdoFileScanOutputAppend->isChecked()){ //default output mode is overwrite
//			arguments << "--outputmode=append";
//		}
		for (int i = 0; i < ui.lstFilesToScan->count(); ++i) {
			if (ui.lstFilesToScan->item(i)->checkState() == Qt::Checked){
//				arguments << QString("\"%1\"").arg(ui.lstFilesToScan->item(i)->text()) ;
				arguments << QString("%1").arg(ui.lstFilesToScan->item(i)->text()) ;
			}
		}
		connect(shellProcess, SIGNAL(started()), this, SLOT(onShellProcessStartedFiles()));
		connect(shellProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onShellProcessFinishedFiles(int, QProcess::ExitStatus)));
		connect(shellProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onShellProcessReadyReadStandardOutput()));
		shellProcess->start(program, arguments);
	}
	else{
		QMessageBox::information(this,"Info","There are no checked files to scan");
	}
}
void kicad_module_scanner::runFootprintCopier(){
	shellProcess = new QProcess(this);
	QStringList arguments;
	QString program = ui.leCopierScript->text();
	arguments << QString("--allowoverwrite=%1").arg(ui.chkAllowOverwrite->isChecked()?"true":"false");
	arguments << QString("--frommodule=%1").arg(footprintsToCopy.at(indexOfFootprintBeingCopied)->name);
	//add tomodule if just 1 module is being copied
	if (footprintsToCopy.count() == 1 && ui.leCopyToModule->text().length()>0){
		arguments << QString("--tomodule=%1").arg(ui.leCopyToModule->text()); //1 item to copy so allow module name change
	}
	arguments << QString("--fromfile=%1").arg(footprintsToCopy.at(indexOfFootprintBeingCopied)->file);
	arguments << QString("--tofile=%1").arg(ui.cboCopyToLibrary->currentText());
	connect(shellProcess, SIGNAL(started()), this, SLOT(onShellProcessStartedCopyFootprint()));
	connect(shellProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onShellProcessFinishedCopyFootprint(int, QProcess::ExitStatus)));
	connect(shellProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onShellProcessReadyReadStandardOutput()));
	shellProcess->start(program, arguments);
}
void kicad_module_scanner::updateFootprintsInDestinationLibrary(){
//	footprintsInDestinationLibrary.clear();
	ui.treeFpsInDestLibrary->clear();
	if (ui.cboCopyToLibrary->currentText().length()==0)	return;
	QFile f(ui.cboCopyToLibrary->currentText());
	if (! f.open(QIODevice::ReadOnly | QIODevice::Text)){
		ui.lblFpsInLibrary->setText("Library doesn't exist");
		return;
	}
	ui.lblFpsInLibrary->setText(QString("Fp's in %1").arg(QFileInfo(ui.cboCopyToLibrary->currentText()).fileName()));
	QTextStream ts(&f);
	while (!ts.atEnd()){
		QString line = ts.readLine();
//		qDebug() << line;
		QStringList tokens = line.split(' ');
//		qDebug() << tokens.count() << " tokens: " << tokens;
		if (tokens.at(0) == "$MODULE"){
			if (tokens.count() > 1){
//				footprintsInDestinationLibrary << tokens.at(1);
				QTreeWidgetItem *qtwi = new QTreeWidgetItem(ui.treeFpsInDestLibrary);
				qtwi->setText(0,tokens.at(1));
				ui.treeFpsInDestLibrary->addTopLevelItem(qtwi);
			}
		}
	}
	f.close();
//	qDebug() << footprintsInDestinationLibrary;
}
/**
 * Check to see if copying would fail
 */
bool kicad_module_scanner::oKToCopyFootprints(){
	if (ui.cboCopyToLibrary->currentText().length()==0){
		QMessageBox::warning(this,"Cannot proceed...", "Please specify a library to copy to.");
		ui.cboCopyToLibrary->setFocus();
		return false;
	}
	if (ui.chkAllowOverwrite->isChecked()) return true; //allow overwriting enabled - no problem will occur
	//if we get here module overwriting is not allowed...
	//...so check whether footprint to be copied already exists in destination library
	updateFootprintsInDestinationLibrary();
	QString fpExistingNames;
	int numAlreadyExisting = 0;
	for (int i = 0; i < footprintsToCopy.size(); i++){
//		if (footprintsInDestinationLibrary.contains(footprintsToCopy.at(i)->name,Qt::CaseInsensitive)){
		if (ui.treeFpsInDestLibrary->findItems(footprintsToCopy.at(i)->name, Qt::MatchFixedString, 0).count()){
			fpExistingNames += footprintsToCopy.at(i)->name + "\n";
			numAlreadyExisting++;
		}
	}
	if (numAlreadyExisting == 1){ //"Allow Overwrite" is false and there's just 1 overwrite - has the user specified a different name?
		if (ui.leCopyToModule->text().compare(fpExistingNames.simplified(),Qt::CaseInsensitive)==0){
			QMessageBox::critical(this,"Cannot copy a footprint...",
					QString("Footprint \"%1\" already exists in %2.\nChange the name or check \"Allow Overwrite\" to update it.").arg(fpExistingNames.simplified()).arg(ui.cboCopyToLibrary->currentText())
					);
			ui.leCopyToModule->setFocus();
			return false;
		}
	}
	else if (numAlreadyExisting > 1){
		QMessageBox::critical(this,"Cannot copy some footprints...",
				QString("%1 footprints to be copied already exist in %2\n\
						They would be overwritten but overwriting is disabled.\n\
						You can EITHER check \"Allow Overwrite\" to update these footprints\
OR copy the footprints one at a time to a different name.\
						\nFootprints affected:\n%3").arg(numAlreadyExisting).arg(ui.cboCopyToLibrary->currentText()).arg(fpExistingNames)
				);
		return false;
	}
	return true;
}

void kicad_module_scanner::on_btnCopy_clicked(){ //disabled unless there is at least 1 module to copy
	footprintsToCopy.clear();
	for (int i = 0; i< ui.treeSearchResults->topLevelItemCount(); i++){
		if (ui.treeSearchResults->topLevelItem(i)->checkState(0) == Qt::Checked){
			//fill the target module's name
			footprint *fp = new footprint(ui.treeSearchResults->topLevelItem(i)->text(0),ui.treeSearchResults->topLevelItem(i)->text(4));
			footprintsToCopy.append(fp);
		}
	}
	if ( ! oKToCopyFootprints()){
		return;
	}
	indexOfFootprintBeingCopied=0;
	runFootprintCopier();
}

void kicad_module_scanner::on_cboCopyToLibrary_editTextChanged( const QString & text ){
	(void) text;
	updateFootprintsInDestinationLibrary();
}
void kicad_module_scanner::on_cboCopyToLibrary_currentIndexChanged( const QString & text ){
	(void) text;
	updateFootprintsInDestinationLibrary();
}

void kicad_module_scanner::onShellProcessStartedCopyFootprint(){
	QString msg = QString("Copying module %1").arg(footprintsToCopy[indexOfFootprintBeingCopied]->name);
	ui.statusbar->showMessage(msg,0);
}

void kicad_module_scanner::onShellProcessFinishedCopyFootprint(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitStatus;
	//have we finished?
	//need to deal with errors here TODO
	if (exitCode == 0){
		updateFootprintsInDestinationLibrary(); //could do this when we're finished rather than for each module successfully copied
	}
	qDebug()<< "index= " << indexOfFootprintBeingCopied << " numfps= " << footprintsToCopy.size();
	if (indexOfFootprintBeingCopied == footprintsToCopy.size()-1){
		ui.statusbar->showMessage("Ready",0);
		return;
	}
	//not finished yet, start the next copy operation
	++indexOfFootprintBeingCopied;
	runFootprintCopier();
}
void kicad_module_scanner::onShellProcessStartedRetrieveData(){
	ui.tabFindingCopying->setEnabled(false);
	ui.statusbar->showMessage("Retrieving module data...",0);
}
void kicad_module_scanner::onShellProcessFinishedRetrieveData(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitStatus;
	if (exitCode == 0){
		ui.statusbar->showMessage("Ready",0);
		ui.modView->setData(data);
		ui.modView->parse();
		ui.modViewSmall->setData(data);
		ui.modViewSmall->parse();
	}
	else{
		ui.statusbar->showMessage(QString("An error (%1) occurred when retrieving module data.").arg(exitCode),0); //need more diagnostics TODO
	}
	ui.tabFindingCopying->setEnabled(true);
	shellProcess = 0;
}
void kicad_module_scanner::onShellProcessReadyReadStandardOutputData(){
	data = shellProcess->readAllStandardOutput();
	qDebug() << data;
}

void kicad_module_scanner::onShellProcessStartedRetrievePS(){
	ui.tabFindingCopying->setEnabled(false);
	ui.statusbar->showMessage("Retrieving postscript...",0);
}
void kicad_module_scanner::onShellProcessFinishedRetrievePS(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitStatus;
	if (exitCode == 0){
		ui.statusbar->showMessage("Ready",0);
		if (! viewerIsRunning){
			startViewer();
		}
	}
	else{
		ui.statusbar->showMessage(QString("An error (%1) occurred when retrieving postscript.").arg(exitCode),0); //need more diagnostics TODO
	}
	ui.tabFindingCopying->setEnabled(true);
	shellProcess = 0;
}
void kicad_module_scanner::onShellProcessStartedFiles(){
	ui.btnScanCheckedFiles->setEnabled(false);
	ui.btnStopScanCheckedFiles->setEnabled(true);
	ui.statusbar->showMessage("Working...",0);
}
void kicad_module_scanner::onShellProcessStartedFolders(){
	ui.btnScanCheckedFolders->setEnabled(false);
	ui.btnStopScanCheckedFolders->setEnabled(true);
	ui.statusbar->showMessage("Working...",0);
}
void kicad_module_scanner::onShellProcessReadyReadStandardOutput(){
	qDebug() << shellProcess->readAllStandardOutput();
}

void kicad_module_scanner::onShellProcessFinishedFolders(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitStatus;
	if (exitCode == 0){
		ui.statusbar->showMessage("Ready",0);
		//make sure that folder scanning output file is shown in viewer database file combo
		addToList(ui.cboDatabaseFile, ui.cboOutputFile_FolderScanning->currentText());
	}
	else{
		ui.statusbar->showMessage(QString("An error (%1) occurred during scanning.").arg(exitCode),0); //need more diagnostics TODO
	}
	ui.btnScanCheckedFolders->setEnabled(true);
	ui.btnStopScanCheckedFolders->setEnabled(false);
	shellProcess = 0;
}

void kicad_module_scanner::onShellProcessFinishedFiles(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitStatus;
	if (exitCode == 0){
		ui.statusbar->showMessage("Ready",0);
		//make sure that file scanning output file is shown in viewer database file combo
		addToList(ui.cboDatabaseFile, ui.cboOutputFile_FileScanning->currentText());
	}
	else{
		ui.statusbar->showMessage(QString("An error (%1) occurred during scanning.").arg(exitCode),0); //need more diagnostics TODO
	}
	ui.btnScanCheckedFiles->setEnabled(true);
	ui.btnStopScanCheckedFiles->setEnabled(false);
	shellProcess = 0;
}

void kicad_module_scanner::onViewerStarted(){
	qDebug() << "onViewerStarted() Viewer started" << ui.cboViewerTemporaryFile->currentText();
	viewerIsRunning= true;
	qDebug() << "Viewer started";
}
void kicad_module_scanner::onViewerFinished(int exitCode, QProcess::ExitStatus exitStatus){
	(void) exitCode;
	(void) exitStatus;
	viewerIsRunning=false;
	qDebug() << "Viewer finished";
}

void kicad_module_scanner::startViewer(){
	qDebug() << "startViewer() Starting viewer: " << ui.cboViewerTemporaryFile->currentText();
	viewerProcess = new QProcess(this);
	QString program = ui.cboPostscriptViewer->currentText();
	QStringList arguments(ui.cboViewerTemporaryFile->currentText());
	connect(viewerProcess, SIGNAL(started()), this, SLOT(onViewerStarted()));
	connect(viewerProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onViewerFinished(int, QProcess::ExitStatus)));
	viewerProcess->start(program, arguments);
}

/**
 * Return the number of checked items in treeSearchResults
 */
int kicad_module_scanner::numCheckedFootprints(){
	int numSelectedItems = 0;
	for (int i = 0; i< ui.treeSearchResults->topLevelItemCount(); i++){
		if (ui.treeSearchResults->topLevelItem(i)->checkState(0) == Qt::Checked){
			numSelectedItems++;
		}
	}
	return numSelectedItems;
}
void kicad_module_scanner::previewFootprint(QTreeWidgetItem * item){
	//update modView
//	qDebug() << "previewFootprint: running";
	bool ok;
	int index = item->data(0, Qt::UserRole).toInt(&ok);
	QString theName = item->text(0); //oh for an enum! module name is in column 0
	QString theFile = item->text(4); //oh for an enum! filename is in column 4
	ui.lblFootprintName->setText(QString("%1 in File %2").arg(theName).arg(theFile));
	shellProcess = new QProcess(this);
	QString program = ui.leExtractorScript->text();
	QStringList arguments;
	//kicad-extract-module.awk --assign frommodule=CP_5x6mm  capacitors.mod
	arguments << QString("--assign");
	arguments << QString("frommodule=%1").arg(theName);
	arguments << theFile; //there's no output file so we read output from stdin into data
	connect(shellProcess, SIGNAL(started()), this, SLOT(onShellProcessStartedRetrieveData()));
	connect(shellProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onShellProcessFinishedRetrieveData(int, QProcess::ExitStatus)));
	connect(shellProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onShellProcessReadyReadStandardOutputData()));
	shellProcess->start(program, arguments);
//	ui.modView->setData(data);
//	ui.modView->parse();

}
//void kicad_module_scanner::previewFootprintOld(QTreeWidgetItem * item){
//	//retrieve postscript for this item
//	bool ok;
//	int index = item->data(0, Qt::UserRole).toInt(&ok);
////	qDebug() << index; //unique index
//
//	//const QString psQuery = QString("doc('%1')/kms/module[numpins = %2][%3]/postscript/string()").arg(ui.cboDatabaseFile->currentText()).arg(ui.spinBoxNumPins->text()).arg(index) ;
//	QString psQuery = composeQuery();//eg: doc('libcms.xml')/kms/module[numpins = 6]
//	//specify the selected record
//	psQuery += QString("[%1]/postscript/string()").arg(index); //eg:doc('libcms.xml')/kms/module[numpins = 6][3]/postscript/string()
//	QStringList ps;
//	QXmlQuery query;
//	query.setQuery(psQuery);
//	if (! query.evaluateTo(&ps) ){
//		qDebug() << "Postscript Query failed: " << psQuery;
//		return;
//	}
//	if (ps.at(0).length() < 2){ //even empty queries return a newline at least
//		//we get here because the database file was created with chkFolderIncludePostscript
//		//or chkFileIncludePostscript unchecked and the postscript field is therefore empty
//		qDebug() << QString("Retrieving postscript for %1").arg(item->text(0)); //HERE retrieve ps if ps not included TODO
//		QString theName = item->text(0); //oh for an enum! module name is in column 0
//		QString theFile = item->text(4); //oh for an enum! filename is in column 4
//		shellProcess = new QProcess(this);
//		QString program = ui.leShellWorkerScript->text();
//		QStringList arguments;
//		arguments << QString("--awkscript=%1").arg(ui.leAwkScript->text());
//		arguments << QString("--module=%1").arg(theName);
//		arguments << QString("--outputxml=off");
//		arguments << QString("--postscript=on");
//		arguments << QString("--scale=%1").arg(ui.cboScale->currentText());
//		arguments << QString("--showpinnumbers=%1").arg(ui.chkShowPinNumbers->isChecked()?"on":"off");
//		arguments << QString("--outfile=%1").arg(ui.cboViewerTemporaryFile->currentText());
//		arguments << QString("--inputmode=file");
//		arguments << QString("--outputmode=overwrite");
//		arguments << theFile;
//		connect(shellProcess, SIGNAL(started()), this, SLOT(onShellProcessStartedRetrievePS()));
//		connect(shellProcess, SIGNAL(finished( int, QProcess::ExitStatus)), this, SLOT(onShellProcessFinishedRetrievePS(int, QProcess::ExitStatus)));
//		connect(shellProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(onShellProcessReadyReadStandardOutput()));
//		shellProcess->start(program, arguments);
////			onShellProcessFinishedRetrievePS() will start the viewer
//		return;
//	}
//	else{ //postscript was saved with the database file - write it to temp file
//		QFile data(ui.cboViewerTemporaryFile->currentText());
//		 if (data.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
//			 QTextStream out(&data);
//			 out << ps.at(0);
//			 data.close();
//			//if we get here, the postscript temporary file has been updated
//			//with postcript corresponding to the clicked item
//			if (! viewerIsRunning){
//				startViewer();
//			}
//		 }
//		 else{
//			 (void)QMessageBox::warning(this, QString("kms"),
//					 QString("Failed to open %1 for writing.").arg(ui.cboViewerTemporaryFile->currentText())
//					 );
//			 return;
//		 }
//	}
//}

void kicad_module_scanner::on_treeSearchResults_itemClicked( QTreeWidgetItem * item, int column){
//	qDebug() << "on_treeSearchResults_itemClicked: " << item->text(0);
//	(void) column;
	if (column == 0){ //control gbcopy and leCopyToModule based on how many items are checked
		int numSelectedItems = 0;
		QString rememberCheckedItemName;
		for (int i = 0; i< ui.treeSearchResults->topLevelItemCount(); i++){
			if (ui.treeSearchResults->topLevelItem(i)->checkState(0) == Qt::Checked){
				numSelectedItems++;
				if (numSelectedItems==1){
					ui.leCopyToModule->setText(ui.treeSearchResults->topLevelItem(i)->text(0));//fill the target module's name
				}
			}
		}
		if (numSelectedItems == 0){ //nothing selected; no copying possible
			ui.gbCopy->setEnabled(false);
			ui.gbCopy->setTitle(QString("Copy:"));
			ui.leCopyToModule->setVisible(false);
		}
		else if (numSelectedItems == 1){//1 item selected; can copy to a different module name
			ui.gbCopy->setEnabled(true);
			ui.gbCopy->setTitle(QString("Copy checked footprint to a footprint called:"));
			ui.leCopyToModule->setVisible(true);
		}
		else{//several items selected; can copy but not to a different module name
			ui.gbCopy->setEnabled(true);
			ui.gbCopy->setTitle(QString("Copy %1 checked footprints to:").arg(numSelectedItems));
			ui.leCopyToModule->setVisible(false);
		}
		//warn if any checked items are already contained in target library TODO
	}
	if (! ui.chkAutoPreview->isChecked()) return;
	previewFootprint(item);
}
/**
 * compose an xpath query based on enabled criteria
 * the return value looks something like [numpins = 6][contains(commentdesc,'QFP')] etc.
 */
const QString kicad_module_scanner::composeQuery(){
	QString footprintQuery("");
	QString criteria;
	////.[lower-case(name())='book']
	if(ui.chkPins->isChecked()){
		criteria = QString("[numpins = %1]").arg(ui.spinBoxNumPins->text());
	}
	if (ui.chkFootprintName->isChecked()){
//		criteria += QString("[contains(name,'%1')]").arg(ui.cboFootprintName->currentText());
		criteria += QString("[contains(lower-case(name),'%1')]").arg(ui.cboFootprintName->currentText().toLower()); //case insensitive search
	}
	if (ui.chkKeywords->isChecked()){
//		criteria += QString("[contains(keywords,'%1')]").arg(ui.cboKeywords->currentText());
		criteria += QString("[contains(lower-case(keywords),'%1')]").arg(ui.cboKeywords->currentText().toLower()); //case insensitive search
	}
	if (ui.chkDescription->isChecked()){
//		criteria += QString("[contains(commentdesc,'%1')]").arg(ui.cboDescription->currentText());
		criteria += QString("[contains(lower-case(commentdesc),'%1')]").arg(ui.cboDescription->currentText().toLower()); //case insensitive search
	}

	return QString("doc('%1')/kms/module%2").arg(ui.cboDatabaseFile->currentText()).arg(criteria) ;

}
void kicad_module_scanner::on_btnSearch_clicked(){
	//TODO compose query using active search criteria - must also be used in on_lstResults_itemClicked above
//	const QString footprintQuery  = QString("doc('%1')/kms/module[numpins = %2]/string-join((name, 'Desc:', commentdesc, '#Pins:', numpins, 'File:', file),'\t')").arg(ui.cboDatabaseFile->currentText()).arg(ui.spinBoxNumPins->text()) ;
	//works	const QString footprintQuery  = QString("for $i in doc('/home/root/Projects/kicad-module-scanner-kate/libcms.xml')/kms/module[numpins = %1] return $i/string-join((name, file, refdes, keywords, numpins),' ')").arg(ui.spinBoxNumPins->text()) ;

	QString footprintQuery  = composeQuery();//eg: doc('libcms.xml')/kms/module[numpins = 6]
	//add the format we want a record returned in so we can bash it straight into a listWidgetItem
	//footprintQuery += "/string-join((name, ' #Pins:', numpins, ' Desc:', commentdesc, ' Keys:', keywords, ' File:', file),'')";
	//add the format we want a record returned in so we can bash it straight into a treeWidgetItem
	footprintQuery += "/string-join((name, numpins, commentdesc, keywords, file),'|')";
//	qDebug() << "pwd = " << QDir::currentPath() << "query = " << footprintQuery;
//	ui.lstResults->clear();
	ui.treeSearchResults->clear();
	ui.gBoxSearchResults->setTitle(QString("Searching..."));
	QStringList matchingFootprints;
	QXmlQuery query;
	query.setQuery(footprintQuery);
	if (! query.evaluateTo(&matchingFootprints) ){ //TODO fails on large (150MB) xml files
		qDebug() << "Query failed";
		ui.gBoxSearchResults->setTitle(QString("Search Results"));
		return;
	}
	for (int i = 0; i < matchingFootprints.size(); ++i){
		//populate ui.treeSearchResults
		//field order (0 to 4) in treeWidget and XmlQuery are the same ie: name, numpins, commentdesc, keywords, file
		QStringList fields = matchingFootprints.at(i).split('|');
        TreeWidgetItem *treewidgetitem = new TreeWidgetItem(ui.treeSearchResults);//NOTE: This is a TreeWidgetItem with overloaded operator< for correct numpins sorting
        treewidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        treewidgetitem->setCheckState(0, Qt::Unchecked);
        treewidgetitem->setData(0,Qt::UserRole, i+1); //unique index for retrieval in on_treeSearchResults_itemClicked
        for (int j = 0; j < 5; j++){
        	treewidgetitem->setText(j, fields.at(j));
        }
        ui.treeSearchResults->addTopLevelItem(treewidgetitem);
	}
	ui.treeSearchResults->sortByColumn(ui.treeSearchResults->header()->sortIndicatorSection(),ui.treeSearchResults->header()->sortIndicatorOrder());//TODO sorting is alpha on all columns inc pins
	ui.gBoxSearchResults->setTitle(QString("%1 Search Results").arg(matchingFootprints.size()));
}
void kicad_module_scanner::on_modView_measurementChanged(QPointF pip1, QPointF pip2){
	QPointF diff = pip1 - pip2;
	ui.lblDx->setText(QString("%1").arg(diff.x()));
	ui.lblDy->setText(QString("%1").arg(diff.y()));
	double d = sqrt(pow(diff.x(), 2) + pow(diff.y(), 2));
	ui.lblD->setText(QString("%1").arg(d));

}
