/********************************************************************************
** Form generated from reading UI file 'kicad_module_scanner.ui'
**
** Created: Sat Sep 29 12:07:28 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KICAD_MODULE_SCANNER_H
#define UI_KICAD_MODULE_SCANNER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "/home/root/Projects/kicad-module-scanner/FootprintWidget/ModView.h"

QT_BEGIN_NAMESPACE

class Ui_kicad_module_scannerClass
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_9;
    QTabWidget *tabWidget;
    QWidget *tabSetup;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leKicadInstallationFolder;
    QPushButton *btnSelectKicadInstallationFolder;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_13;
    QLineEdit *leShellWorkerScript;
    QLabel *label_14;
    QLineEdit *leAwkScript;
    QLabel *label_18;
    QLineEdit *leCopierScript;
    QLabel *label_20;
    QLineEdit *leExtractorScript;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *cboPostscriptViewer;
    QPushButton *btnSelectPostscriptViewer;
    QLabel *label_9;
    QComboBox *cboViewerTemporaryFile;
    QLabel *label_21;
    QSpacerItem *verticalSpacer_9;
    QSpacerItem *verticalSpacer_10;
    QWidget *tabFolderScanning;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QListWidget *lstFoldersToScan;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnAddFolderToScan;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnRemoveFolderToScan;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rdoFolderScanOutputOverwrite;
    QRadioButton *rdoFolderScanOutputAppend;
    QComboBox *cboOutputFile_FolderScanning;
    QCheckBox *chkFolderIncludePostscript;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnScanCheckedFolders;
    QPushButton *btnStopScanCheckedFolders;
    QWidget *tabFileScanning;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_7;
    QListWidget *lstFilesToScan;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_6;
    QPushButton *btnAddFileToScan;
    QSpacerItem *verticalSpacer_7;
    QPushButton *btnRemoveFileToScan;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *rdoFileScanOutputOverwrite;
    QRadioButton *rdoFileScanOutputAppend;
    QComboBox *cboOutputFile_FileScanning;
    QCheckBox *chkFileIncludePostscript;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnScanCheckedFiles;
    QPushButton *btnStopScanCheckedFiles;
    QWidget *tabFindingCopying;
    QGridLayout *gridLayout_6;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_22;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cboDatabaseFile;
    QPushButton *btnSelectFootprintDatabase;
    QGroupBox *gbSearchCriteria;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_16;
    QLabel *label;
    QSpinBox *spinBoxNumPins;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *chkPins;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_15;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_10;
    QComboBox *cboFootprintName;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *chkFootprintName;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_16;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_11;
    QComboBox *cboKeywords;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *chkKeywords;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_17;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_12;
    QComboBox *cboDescription;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_11;
    QCheckBox *chkDescription;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btnSearch;
    QGroupBox *gBoxSearchResults;
    QVBoxLayout *verticalLayout_14;
    QTreeWidget *treeSearchResults;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chkAutoPreview;
    QPushButton *btnPreview;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_21;
    QGroupBox *gbCopy;
    QVBoxLayout *verticalLayout_15;
    QLineEdit *leCopyToModule;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout;
    QComboBox *cboCopyToLibrary;
    QPushButton *btnSelectCopyToLibrary;
    QLabel *lblFpsInLibrary;
    QTreeWidget *treeFpsInDestLibrary;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkAllowOverwrite;
    QPushButton *btnCopy;
    QSpacerItem *horizontalSpacer_12;
    ModView *modViewSmall;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *btnViewingMode;
    QPushButton *btnCopyingMode;
    QWidget *tabViewer;
    QGridLayout *gridLayout_10;
    QLabel *lblFootprintName;
    ModView *modView;
    QVBoxLayout *verticalLayout_23;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_13;
    QSlider *horizontalSlider_2;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_14;
    QCheckBox *checkBox_2;
    QLabel *label_23;
    QRadioButton *rdoGrid10Mil;
    QRadioButton *radioButton_3;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_24;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QGroupBox *gbMeasure;
    QFormLayout *formLayout_2;
    QLabel *label_27;
    QLabel *lblDx;
    QLabel *label_28;
    QLabel *lblDy;
    QLabel *label_29;
    QLabel *lblD;
    QWidget *tabTest;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *kicad_module_scannerClass)
    {
        if (kicad_module_scannerClass->objectName().isEmpty())
            kicad_module_scannerClass->setObjectName(QString::fromUtf8("kicad_module_scannerClass"));
        kicad_module_scannerClass->resize(1058, 718);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kicad_module_scannerClass->sizePolicy().hasHeightForWidth());
        kicad_module_scannerClass->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(kicad_module_scannerClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_9 = new QGridLayout(centralwidget);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabSetup = new QWidget();
        tabSetup->setObjectName(QString::fromUtf8("tabSetup"));
        gridLayout = new QGridLayout(tabSetup);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(tabSetup);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        leKicadInstallationFolder = new QLineEdit(tabSetup);
        leKicadInstallationFolder->setObjectName(QString::fromUtf8("leKicadInstallationFolder"));
        leKicadInstallationFolder->setEnabled(false);

        horizontalLayout_5->addWidget(leKicadInstallationFolder);

        btnSelectKicadInstallationFolder = new QPushButton(tabSetup);
        btnSelectKicadInstallationFolder->setObjectName(QString::fromUtf8("btnSelectKicadInstallationFolder"));
        btnSelectKicadInstallationFolder->setEnabled(false);
        btnSelectKicadInstallationFolder->setMinimumSize(QSize(30, 25));
        btnSelectKicadInstallationFolder->setMaximumSize(QSize(30, 25));

        horizontalLayout_5->addWidget(btnSelectKicadInstallationFolder);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 76, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_13 = new QLabel(tabSetup);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        verticalLayout_2->addWidget(label_13);

        leShellWorkerScript = new QLineEdit(tabSetup);
        leShellWorkerScript->setObjectName(QString::fromUtf8("leShellWorkerScript"));

        verticalLayout_2->addWidget(leShellWorkerScript);

        label_14 = new QLabel(tabSetup);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        verticalLayout_2->addWidget(label_14);

        leAwkScript = new QLineEdit(tabSetup);
        leAwkScript->setObjectName(QString::fromUtf8("leAwkScript"));

        verticalLayout_2->addWidget(leAwkScript);

        label_18 = new QLabel(tabSetup);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_2->addWidget(label_18);

        leCopierScript = new QLineEdit(tabSetup);
        leCopierScript->setObjectName(QString::fromUtf8("leCopierScript"));

        verticalLayout_2->addWidget(leCopierScript);

        label_20 = new QLabel(tabSetup);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        verticalLayout_2->addWidget(label_20);

        leExtractorScript = new QLineEdit(tabSetup);
        leExtractorScript->setObjectName(QString::fromUtf8("leExtractorScript"));

        verticalLayout_2->addWidget(leExtractorScript);


        gridLayout->addLayout(verticalLayout_2, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 76, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(tabSetup);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        cboPostscriptViewer = new QComboBox(tabSetup);
        cboPostscriptViewer->insertItems(0, QStringList()
         << QString::fromUtf8("/usr/bin/okular")
         << QString::fromUtf8("/usr/bin/gs -dSAFER -dNOPAUSE")
        );
        cboPostscriptViewer->setObjectName(QString::fromUtf8("cboPostscriptViewer"));
        cboPostscriptViewer->setEnabled(false);
        cboPostscriptViewer->setEditable(true);

        horizontalLayout_6->addWidget(cboPostscriptViewer);

        btnSelectPostscriptViewer = new QPushButton(tabSetup);
        btnSelectPostscriptViewer->setObjectName(QString::fromUtf8("btnSelectPostscriptViewer"));
        btnSelectPostscriptViewer->setEnabled(true);
        btnSelectPostscriptViewer->setMinimumSize(QSize(30, 25));
        btnSelectPostscriptViewer->setMaximumSize(QSize(30, 25));

        horizontalLayout_6->addWidget(btnSelectPostscriptViewer);


        verticalLayout_3->addLayout(horizontalLayout_6);

        label_9 = new QLabel(tabSetup);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_3->addWidget(label_9);

        cboViewerTemporaryFile = new QComboBox(tabSetup);
        cboViewerTemporaryFile->insertItems(0, QStringList()
         << QString::fromUtf8("kms-temp-file.ps")
        );
        cboViewerTemporaryFile->setObjectName(QString::fromUtf8("cboViewerTemporaryFile"));
        cboViewerTemporaryFile->setEnabled(false);
        cboViewerTemporaryFile->setEditable(true);

        verticalLayout_3->addWidget(cboViewerTemporaryFile);


        gridLayout->addLayout(verticalLayout_3, 7, 0, 1, 1);

        label_21 = new QLabel(tabSetup);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout->addWidget(label_21, 1, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_9, 2, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_10, 0, 0, 1, 1);

        tabWidget->addTab(tabSetup, QString());
        tabFolderScanning = new QWidget();
        tabFolderScanning->setObjectName(QString::fromUtf8("tabFolderScanning"));
        gridLayout_3 = new QGridLayout(tabFolderScanning);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_5 = new QLabel(tabFolderScanning);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_8->addWidget(label_5);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_2 = new QLabel(tabFolderScanning);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_6->addWidget(label_2);

        lstFoldersToScan = new QListWidget(tabFolderScanning);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(lstFoldersToScan);
        __qlistwidgetitem->setText(QString::fromUtf8("/usr/share/kicad/modules"));
        __qlistwidgetitem->setCheckState(Qt::Checked);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(lstFoldersToScan);
        __qlistwidgetitem1->setText(QString::fromUtf8("/usr/share/kicad/converted"));
        __qlistwidgetitem1->setCheckState(Qt::Unchecked);
        __qlistwidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        lstFoldersToScan->setObjectName(QString::fromUtf8("lstFoldersToScan"));

        verticalLayout_6->addWidget(lstFoldersToScan);


        horizontalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        btnAddFolderToScan = new QPushButton(tabFolderScanning);
        btnAddFolderToScan->setObjectName(QString::fromUtf8("btnAddFolderToScan"));

        verticalLayout_7->addWidget(btnAddFolderToScan);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_4);

        btnRemoveFolderToScan = new QPushButton(tabFolderScanning);
        btnRemoveFolderToScan->setObjectName(QString::fromUtf8("btnRemoveFolderToScan"));

        verticalLayout_7->addWidget(btnRemoveFolderToScan);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_5);


        horizontalLayout_9->addLayout(verticalLayout_7);


        verticalLayout_8->addLayout(horizontalLayout_9);

        groupBox = new QGroupBox(tabFolderScanning);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rdoFolderScanOutputOverwrite = new QRadioButton(groupBox);
        rdoFolderScanOutputOverwrite->setObjectName(QString::fromUtf8("rdoFolderScanOutputOverwrite"));
        rdoFolderScanOutputOverwrite->setChecked(true);

        verticalLayout_4->addWidget(rdoFolderScanOutputOverwrite);

        rdoFolderScanOutputAppend = new QRadioButton(groupBox);
        rdoFolderScanOutputAppend->setObjectName(QString::fromUtf8("rdoFolderScanOutputAppend"));

        verticalLayout_4->addWidget(rdoFolderScanOutputAppend);


        horizontalLayout_8->addLayout(verticalLayout_4);

        cboOutputFile_FolderScanning = new QComboBox(groupBox);
        cboOutputFile_FolderScanning->setObjectName(QString::fromUtf8("cboOutputFile_FolderScanning"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cboOutputFile_FolderScanning->sizePolicy().hasHeightForWidth());
        cboOutputFile_FolderScanning->setSizePolicy(sizePolicy1);
        cboOutputFile_FolderScanning->setEditable(true);

        horizontalLayout_8->addWidget(cboOutputFile_FolderScanning);


        verticalLayout_5->addLayout(horizontalLayout_8);

        chkFolderIncludePostscript = new QCheckBox(groupBox);
        chkFolderIncludePostscript->setObjectName(QString::fromUtf8("chkFolderIncludePostscript"));

        verticalLayout_5->addWidget(chkFolderIncludePostscript);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);


        verticalLayout_8->addWidget(groupBox);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        btnScanCheckedFolders = new QPushButton(tabFolderScanning);
        btnScanCheckedFolders->setObjectName(QString::fromUtf8("btnScanCheckedFolders"));

        horizontalLayout_7->addWidget(btnScanCheckedFolders);

        btnStopScanCheckedFolders = new QPushButton(tabFolderScanning);
        btnStopScanCheckedFolders->setObjectName(QString::fromUtf8("btnStopScanCheckedFolders"));
        btnStopScanCheckedFolders->setEnabled(false);

        horizontalLayout_7->addWidget(btnStopScanCheckedFolders);


        verticalLayout_8->addLayout(horizontalLayout_7);


        gridLayout_3->addLayout(verticalLayout_8, 0, 0, 1, 1);

        tabWidget->addTab(tabFolderScanning, QString());
        tabFileScanning = new QWidget();
        tabFileScanning->setObjectName(QString::fromUtf8("tabFileScanning"));
        gridLayout_5 = new QGridLayout(tabFileScanning);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_6 = new QLabel(tabFileScanning);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_13->addWidget(label_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        label_7 = new QLabel(tabFileScanning);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_12->addWidget(label_7);

        lstFilesToScan = new QListWidget(tabFileScanning);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(lstFilesToScan);
        __qlistwidgetitem2->setText(QString::fromUtf8("/home/root/Projects/kicad-module-scanner-kate/40tex-Ell600.mod"));
        __qlistwidgetitem2->setCheckState(Qt::Unchecked);
        __qlistwidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(lstFilesToScan);
        __qlistwidgetitem3->setText(QString::fromUtf8("/home/root/Projects/kicad-module-scanner-kate/PQFP112.mod"));
        __qlistwidgetitem3->setCheckState(Qt::Checked);
        __qlistwidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        lstFilesToScan->setObjectName(QString::fromUtf8("lstFilesToScan"));

        verticalLayout_12->addWidget(lstFilesToScan);


        horizontalLayout_12->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_6);

        btnAddFileToScan = new QPushButton(tabFileScanning);
        btnAddFileToScan->setObjectName(QString::fromUtf8("btnAddFileToScan"));

        verticalLayout_11->addWidget(btnAddFileToScan);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_7);

        btnRemoveFileToScan = new QPushButton(tabFileScanning);
        btnRemoveFileToScan->setObjectName(QString::fromUtf8("btnRemoveFileToScan"));

        verticalLayout_11->addWidget(btnRemoveFileToScan);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_8);


        horizontalLayout_12->addLayout(verticalLayout_11);


        verticalLayout_13->addLayout(horizontalLayout_12);

        groupBox_2 = new QGroupBox(tabFileScanning);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        rdoFileScanOutputOverwrite = new QRadioButton(groupBox_2);
        rdoFileScanOutputOverwrite->setObjectName(QString::fromUtf8("rdoFileScanOutputOverwrite"));
        rdoFileScanOutputOverwrite->setChecked(true);

        verticalLayout_9->addWidget(rdoFileScanOutputOverwrite);

        rdoFileScanOutputAppend = new QRadioButton(groupBox_2);
        rdoFileScanOutputAppend->setObjectName(QString::fromUtf8("rdoFileScanOutputAppend"));

        verticalLayout_9->addWidget(rdoFileScanOutputAppend);


        horizontalLayout_11->addLayout(verticalLayout_9);

        cboOutputFile_FileScanning = new QComboBox(groupBox_2);
        cboOutputFile_FileScanning->insertItems(0, QStringList()
         << QString::fromUtf8("/home/root/Projects/kicad-module-scanner-kate/kms.xml")
        );
        cboOutputFile_FileScanning->setObjectName(QString::fromUtf8("cboOutputFile_FileScanning"));
        sizePolicy1.setHeightForWidth(cboOutputFile_FileScanning->sizePolicy().hasHeightForWidth());
        cboOutputFile_FileScanning->setSizePolicy(sizePolicy1);
        cboOutputFile_FileScanning->setEditable(true);
        cboOutputFile_FileScanning->setInsertPolicy(QComboBox::InsertAtTop);

        horizontalLayout_11->addWidget(cboOutputFile_FileScanning);


        verticalLayout_10->addLayout(horizontalLayout_11);

        chkFileIncludePostscript = new QCheckBox(groupBox_2);
        chkFileIncludePostscript->setObjectName(QString::fromUtf8("chkFileIncludePostscript"));

        verticalLayout_10->addWidget(chkFileIncludePostscript);


        gridLayout_4->addLayout(verticalLayout_10, 0, 0, 1, 1);


        verticalLayout_13->addWidget(groupBox_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        btnScanCheckedFiles = new QPushButton(tabFileScanning);
        btnScanCheckedFiles->setObjectName(QString::fromUtf8("btnScanCheckedFiles"));

        horizontalLayout_10->addWidget(btnScanCheckedFiles);

        btnStopScanCheckedFiles = new QPushButton(tabFileScanning);
        btnStopScanCheckedFiles->setObjectName(QString::fromUtf8("btnStopScanCheckedFiles"));
        btnStopScanCheckedFiles->setEnabled(false);

        horizontalLayout_10->addWidget(btnStopScanCheckedFiles);


        verticalLayout_13->addLayout(horizontalLayout_10);


        gridLayout_5->addLayout(verticalLayout_13, 0, 0, 1, 1);

        tabWidget->addTab(tabFileScanning, QString());
        tabFindingCopying = new QWidget();
        tabFindingCopying->setObjectName(QString::fromUtf8("tabFindingCopying"));
        gridLayout_6 = new QGridLayout(tabFindingCopying);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        splitter = new QSplitter(tabFindingCopying);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_22 = new QVBoxLayout(layoutWidget);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setSpacing(2);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);
        label_8->setMinimumSize(QSize(0, 0));
        label_8->setMaximumSize(QSize(16777215, 14));

        verticalLayout_20->addWidget(label_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cboDatabaseFile = new QComboBox(layoutWidget);
        cboDatabaseFile->insertItems(0, QStringList()
         << QString::fromUtf8("/home/root/Projects/kicad-module-scanner-kate/libcms.xml")
         << QString::fromUtf8("/usr/share/kicad/modules")
        );
        cboDatabaseFile->setObjectName(QString::fromUtf8("cboDatabaseFile"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cboDatabaseFile->sizePolicy().hasHeightForWidth());
        cboDatabaseFile->setSizePolicy(sizePolicy3);
        cboDatabaseFile->setMaximumSize(QSize(16777215, 24));
        cboDatabaseFile->setEditable(true);

        horizontalLayout_3->addWidget(cboDatabaseFile);

        btnSelectFootprintDatabase = new QPushButton(layoutWidget);
        btnSelectFootprintDatabase->setObjectName(QString::fromUtf8("btnSelectFootprintDatabase"));
        btnSelectFootprintDatabase->setMaximumSize(QSize(30, 24));

        horizontalLayout_3->addWidget(btnSelectFootprintDatabase);

        horizontalLayout_3->setStretch(0, 1);

        verticalLayout_20->addLayout(horizontalLayout_3);


        verticalLayout_22->addLayout(verticalLayout_20);

        gbSearchCriteria = new QGroupBox(layoutWidget);
        gbSearchCriteria->setObjectName(QString::fromUtf8("gbSearchCriteria"));
        sizePolicy3.setHeightForWidth(gbSearchCriteria->sizePolicy().hasHeightForWidth());
        gbSearchCriteria->setSizePolicy(sizePolicy3);
        gbSearchCriteria->setMinimumSize(QSize(0, 101));
        gbSearchCriteria->setMaximumSize(QSize(16777215, 101));
        gridLayout_7 = new QGridLayout(gbSearchCriteria);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setVerticalSpacing(0);
        gridLayout_7->setContentsMargins(6, 2, 6, 2);
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(2);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(2);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        label = new QLabel(gbSearchCriteria);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setMinimumSize(QSize(0, 15));
        label->setMaximumSize(QSize(16777215, 15));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label);

        spinBoxNumPins = new QSpinBox(gbSearchCriteria);
        spinBoxNumPins->setObjectName(QString::fromUtf8("spinBoxNumPins"));
        spinBoxNumPins->setEnabled(false);
        spinBoxNumPins->setMaximum(999);
        spinBoxNumPins->setValue(2);

        verticalLayout_16->addWidget(spinBoxNumPins);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_4);

        chkPins = new QCheckBox(gbSearchCriteria);
        chkPins->setObjectName(QString::fromUtf8("chkPins"));
        chkPins->setMaximumSize(QSize(16777215, 14));
        chkPins->setChecked(false);

        horizontalLayout_15->addWidget(chkPins);

        horizontalSpacer_5 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_5);


        verticalLayout_16->addLayout(horizontalLayout_15);


        horizontalLayout_19->addLayout(verticalLayout_16);

        label_15 = new QLabel(gbSearchCriteria);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(label_15);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_10 = new QLabel(gbSearchCriteria);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);
        label_10->setMinimumSize(QSize(0, 15));
        label_10->setMaximumSize(QSize(16777215, 15));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_10);

        cboFootprintName = new QComboBox(gbSearchCriteria);
        cboFootprintName->insertItems(0, QStringList()
         << QString::fromUtf8("QFP")
        );
        cboFootprintName->setObjectName(QString::fromUtf8("cboFootprintName"));
        cboFootprintName->setEnabled(false);
        cboFootprintName->setEditable(true);

        verticalLayout_17->addWidget(cboFootprintName);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_6);

        chkFootprintName = new QCheckBox(gbSearchCriteria);
        chkFootprintName->setObjectName(QString::fromUtf8("chkFootprintName"));
        chkFootprintName->setMaximumSize(QSize(16777215, 14));

        horizontalLayout_16->addWidget(chkFootprintName);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_7);


        verticalLayout_17->addLayout(horizontalLayout_16);


        horizontalLayout_19->addLayout(verticalLayout_17);

        label_16 = new QLabel(gbSearchCriteria);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(label_16);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(2);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        label_11 = new QLabel(gbSearchCriteria);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy3.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy3);
        label_11->setMinimumSize(QSize(0, 15));
        label_11->setMaximumSize(QSize(16777215, 15));
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(label_11);

        cboKeywords = new QComboBox(gbSearchCriteria);
        cboKeywords->setObjectName(QString::fromUtf8("cboKeywords"));
        cboKeywords->setEnabled(false);
        cboKeywords->setEditable(true);

        verticalLayout_18->addWidget(cboKeywords);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_8);

        chkKeywords = new QCheckBox(gbSearchCriteria);
        chkKeywords->setObjectName(QString::fromUtf8("chkKeywords"));
        chkKeywords->setMaximumSize(QSize(16777215, 14));

        horizontalLayout_17->addWidget(chkKeywords);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_9);


        verticalLayout_18->addLayout(horizontalLayout_17);


        horizontalLayout_19->addLayout(verticalLayout_18);

        label_17 = new QLabel(gbSearchCriteria);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(label_17);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(2);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        label_12 = new QLabel(gbSearchCriteria);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);
        label_12->setMinimumSize(QSize(0, 15));
        label_12->setMaximumSize(QSize(16777215, 15));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_19->addWidget(label_12);

        cboDescription = new QComboBox(gbSearchCriteria);
        cboDescription->setObjectName(QString::fromUtf8("cboDescription"));
        cboDescription->setEnabled(false);
        cboDescription->setEditable(true);

        verticalLayout_19->addWidget(cboDescription);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_11);

        chkDescription = new QCheckBox(gbSearchCriteria);
        chkDescription->setObjectName(QString::fromUtf8("chkDescription"));
        chkDescription->setMaximumSize(QSize(16777215, 14));

        horizontalLayout_18->addWidget(chkDescription);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_10);

        btnSearch = new QPushButton(gbSearchCriteria);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnSearch->sizePolicy().hasHeightForWidth());
        btnSearch->setSizePolicy(sizePolicy4);
        btnSearch->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_18->addWidget(btnSearch);


        verticalLayout_19->addLayout(horizontalLayout_18);


        horizontalLayout_19->addLayout(verticalLayout_19);

        horizontalLayout_19->setStretch(2, 1);
        horizontalLayout_19->setStretch(4, 1);
        horizontalLayout_19->setStretch(6, 1);

        gridLayout_7->addLayout(horizontalLayout_19, 0, 0, 1, 1);


        verticalLayout_22->addWidget(gbSearchCriteria);

        gBoxSearchResults = new QGroupBox(layoutWidget);
        gBoxSearchResults->setObjectName(QString::fromUtf8("gBoxSearchResults"));
        verticalLayout_14 = new QVBoxLayout(gBoxSearchResults);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        treeSearchResults = new QTreeWidget(gBoxSearchResults);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Name"));
        treeSearchResults->setHeaderItem(__qtreewidgetitem);
        new QTreeWidgetItem(treeSearchResults);
        new QTreeWidgetItem(treeSearchResults);
        treeSearchResults->setObjectName(QString::fromUtf8("treeSearchResults"));
        treeSearchResults->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeSearchResults->setProperty("showDropIndicator", QVariant(false));
        treeSearchResults->setRootIsDecorated(false);
        treeSearchResults->setItemsExpandable(false);
        treeSearchResults->setSortingEnabled(true);
        treeSearchResults->setExpandsOnDoubleClick(false);
        treeSearchResults->setColumnCount(5);

        verticalLayout_14->addWidget(treeSearchResults);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        chkAutoPreview = new QCheckBox(gBoxSearchResults);
        chkAutoPreview->setObjectName(QString::fromUtf8("chkAutoPreview"));
        chkAutoPreview->setLayoutDirection(Qt::RightToLeft);
        chkAutoPreview->setChecked(true);

        horizontalLayout_4->addWidget(chkAutoPreview);

        btnPreview = new QPushButton(gBoxSearchResults);
        btnPreview->setObjectName(QString::fromUtf8("btnPreview"));
        btnPreview->setEnabled(false);

        horizontalLayout_4->addWidget(btnPreview);


        verticalLayout_14->addLayout(horizontalLayout_4);


        verticalLayout_22->addWidget(gBoxSearchResults);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout_21 = new QVBoxLayout(layoutWidget1);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        gbCopy = new QGroupBox(layoutWidget1);
        gbCopy->setObjectName(QString::fromUtf8("gbCopy"));
        gbCopy->setEnabled(false);
        sizePolicy3.setHeightForWidth(gbCopy->sizePolicy().hasHeightForWidth());
        gbCopy->setSizePolicy(sizePolicy3);
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(105, 107, 103, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        gbCopy->setPalette(palette);
        verticalLayout_15 = new QVBoxLayout(gbCopy);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        leCopyToModule = new QLineEdit(gbCopy);
        leCopyToModule->setObjectName(QString::fromUtf8("leCopyToModule"));

        verticalLayout_15->addWidget(leCopyToModule);

        label_19 = new QLabel(gbCopy);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy2.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy2);
        label_19->setMinimumSize(QSize(0, 26));
        label_19->setMaximumSize(QSize(16777215, 26));
        label_19->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_15->addWidget(label_19);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cboCopyToLibrary = new QComboBox(gbCopy);
        cboCopyToLibrary->insertItems(0, QStringList()
         << QString::fromUtf8("/home/root/Projects/kicad-module-scanner-kate/test.mod")
        );
        cboCopyToLibrary->setObjectName(QString::fromUtf8("cboCopyToLibrary"));
        cboCopyToLibrary->setMinimumSize(QSize(0, 26));
        cboCopyToLibrary->setMaximumSize(QSize(16777215, 26));
        cboCopyToLibrary->setEditable(true);
        cboCopyToLibrary->setInsertPolicy(QComboBox::InsertAtTop);

        horizontalLayout->addWidget(cboCopyToLibrary);

        btnSelectCopyToLibrary = new QPushButton(gbCopy);
        btnSelectCopyToLibrary->setObjectName(QString::fromUtf8("btnSelectCopyToLibrary"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(btnSelectCopyToLibrary->sizePolicy().hasHeightForWidth());
        btnSelectCopyToLibrary->setSizePolicy(sizePolicy5);
        btnSelectCopyToLibrary->setMaximumSize(QSize(30, 26));

        horizontalLayout->addWidget(btnSelectCopyToLibrary);

        horizontalLayout->setStretch(0, 1);

        verticalLayout_15->addLayout(horizontalLayout);

        lblFpsInLibrary = new QLabel(gbCopy);
        lblFpsInLibrary->setObjectName(QString::fromUtf8("lblFpsInLibrary"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblFpsInLibrary->setPalette(palette1);
        lblFpsInLibrary->setAutoFillBackground(true);
        lblFpsInLibrary->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(lblFpsInLibrary);

        treeFpsInDestLibrary = new QTreeWidget(gbCopy);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeFpsInDestLibrary);
        __qtreewidgetitem1->setText(0, QString::fromUtf8("Footprint1"));
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeFpsInDestLibrary);
        __qtreewidgetitem2->setText(0, QString::fromUtf8("Footprint2"));
        treeFpsInDestLibrary->setObjectName(QString::fromUtf8("treeFpsInDestLibrary"));
        treeFpsInDestLibrary->setEnabled(false);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        treeFpsInDestLibrary->setPalette(palette2);
        treeFpsInDestLibrary->setLineWidth(3);
        treeFpsInDestLibrary->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeFpsInDestLibrary->setProperty("showDropIndicator", QVariant(false));
        treeFpsInDestLibrary->setSelectionMode(QAbstractItemView::NoSelection);
        treeFpsInDestLibrary->setRootIsDecorated(false);
        treeFpsInDestLibrary->setItemsExpandable(false);
        treeFpsInDestLibrary->setExpandsOnDoubleClick(false);
        treeFpsInDestLibrary->header()->setVisible(false);

        verticalLayout_15->addWidget(treeFpsInDestLibrary);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chkAllowOverwrite = new QCheckBox(gbCopy);
        chkAllowOverwrite->setObjectName(QString::fromUtf8("chkAllowOverwrite"));
        sizePolicy5.setHeightForWidth(chkAllowOverwrite->sizePolicy().hasHeightForWidth());
        chkAllowOverwrite->setSizePolicy(sizePolicy5);
        chkAllowOverwrite->setMinimumSize(QSize(0, 26));
        chkAllowOverwrite->setMaximumSize(QSize(87, 26));
        chkAllowOverwrite->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_2->addWidget(chkAllowOverwrite);

        btnCopy = new QPushButton(gbCopy);
        btnCopy->setObjectName(QString::fromUtf8("btnCopy"));
        btnCopy->setMinimumSize(QSize(0, 26));
        btnCopy->setMaximumSize(QSize(44, 26));

        horizontalLayout_2->addWidget(btnCopy);


        horizontalLayout_13->addLayout(horizontalLayout_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);


        verticalLayout_15->addLayout(horizontalLayout_13);


        verticalLayout_21->addWidget(gbCopy);

        modViewSmall = new ModView(layoutWidget1);
        modViewSmall->setObjectName(QString::fromUtf8("modViewSmall"));
        modViewSmall->setMinimumSize(QSize(0, 150));

        verticalLayout_21->addWidget(modViewSmall);

        groupBox_3 = new QGroupBox(layoutWidget1);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_14 = new QHBoxLayout(groupBox_3);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        btnViewingMode = new QPushButton(groupBox_3);
        btnViewingMode->setObjectName(QString::fromUtf8("btnViewingMode"));
        btnViewingMode->setCheckable(true);
        btnViewingMode->setChecked(true);
        btnViewingMode->setAutoExclusive(true);

        horizontalLayout_14->addWidget(btnViewingMode);

        btnCopyingMode = new QPushButton(groupBox_3);
        btnCopyingMode->setObjectName(QString::fromUtf8("btnCopyingMode"));
        btnCopyingMode->setCheckable(true);
        btnCopyingMode->setAutoExclusive(true);

        horizontalLayout_14->addWidget(btnCopyingMode);


        verticalLayout_21->addWidget(groupBox_3);

        verticalLayout_21->setStretch(1, 1);
        splitter->addWidget(layoutWidget1);

        gridLayout_6->addWidget(splitter, 0, 0, 1, 1);

        tabWidget->addTab(tabFindingCopying, QString());
        tabViewer = new QWidget();
        tabViewer->setObjectName(QString::fromUtf8("tabViewer"));
        gridLayout_10 = new QGridLayout(tabViewer);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        lblFootprintName = new QLabel(tabViewer);
        lblFootprintName->setObjectName(QString::fromUtf8("lblFootprintName"));

        gridLayout_10->addWidget(lblFootprintName, 0, 0, 1, 2);

        modView = new ModView(tabViewer);
        modView->setObjectName(QString::fromUtf8("modView"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(modView->sizePolicy().hasHeightForWidth());
        modView->setSizePolicy(sizePolicy6);
        modView->setMinimumSize(QSize(200, 200));

        gridLayout_10->addWidget(modView, 1, 0, 1, 1);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setSpacing(2);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        groupBox_6 = new QGroupBox(tabViewer);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(0, 40));
        gridLayout_13 = new QGridLayout(groupBox_6);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setVerticalSpacing(2);
        gridLayout_13->setContentsMargins(-1, 2, -1, 2);
        horizontalSlider_2 = new QSlider(groupBox_6);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        sizePolicy5.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy5);
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setValue(100);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout_13->addWidget(horizontalSlider_2, 0, 0, 1, 1);


        verticalLayout_23->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(tabViewer);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox_7->sizePolicy().hasHeightForWidth());
        groupBox_7->setSizePolicy(sizePolicy7);
        gridLayout_14 = new QGridLayout(groupBox_7);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_14->setVerticalSpacing(1);
        gridLayout_14->setContentsMargins(9, 2, 9, 2);
        checkBox_2 = new QCheckBox(groupBox_7);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout_14->addWidget(checkBox_2, 0, 0, 1, 1);

        label_23 = new QLabel(groupBox_7);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy7.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy7);

        gridLayout_14->addWidget(label_23, 1, 0, 1, 1);

        rdoGrid10Mil = new QRadioButton(groupBox_7);
        rdoGrid10Mil->setObjectName(QString::fromUtf8("rdoGrid10Mil"));
        rdoGrid10Mil->setChecked(true);

        gridLayout_14->addWidget(rdoGrid10Mil, 2, 0, 1, 2);

        radioButton_3 = new QRadioButton(groupBox_7);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        gridLayout_14->addWidget(radioButton_3, 3, 0, 1, 2);


        verticalLayout_23->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(tabViewer);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        sizePolicy7.setHeightForWidth(groupBox_8->sizePolicy().hasHeightForWidth());
        groupBox_8->setSizePolicy(sizePolicy7);
        verticalLayout_24 = new QVBoxLayout(groupBox_8);
        verticalLayout_24->setSpacing(2);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(-1, 2, -1, 2);
        pushButton_5 = new QPushButton(groupBox_8);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_24->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(groupBox_8);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout_24->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(groupBox_8);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        verticalLayout_24->addWidget(pushButton_7);

        pushButton_8 = new QPushButton(groupBox_8);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        verticalLayout_24->addWidget(pushButton_8);


        verticalLayout_23->addWidget(groupBox_8);

        gbMeasure = new QGroupBox(tabViewer);
        gbMeasure->setObjectName(QString::fromUtf8("gbMeasure"));
        sizePolicy3.setHeightForWidth(gbMeasure->sizePolicy().hasHeightForWidth());
        gbMeasure->setSizePolicy(sizePolicy3);
        gbMeasure->setMinimumSize(QSize(0, 80));
        formLayout_2 = new QFormLayout(gbMeasure);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label_27 = new QLabel(gbMeasure);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMinimumSize(QSize(22, 0));
        label_27->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_27);

        lblDx = new QLabel(gbMeasure);
        lblDx->setObjectName(QString::fromUtf8("lblDx"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lblDx);

        label_28 = new QLabel(gbMeasure);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMinimumSize(QSize(22, 0));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_28);

        lblDy = new QLabel(gbMeasure);
        lblDy->setObjectName(QString::fromUtf8("lblDy"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lblDy);

        label_29 = new QLabel(gbMeasure);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMinimumSize(QSize(22, 0));
        label_29->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_29);

        lblD = new QLabel(gbMeasure);
        lblD->setObjectName(QString::fromUtf8("lblD"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lblD);


        verticalLayout_23->addWidget(gbMeasure);


        gridLayout_10->addLayout(verticalLayout_23, 1, 1, 1, 1);

        tabWidget->addTab(tabViewer, QString());
        tabTest = new QWidget();
        tabTest->setObjectName(QString::fromUtf8("tabTest"));
        tabWidget->addTab(tabTest, QString());

        gridLayout_9->addWidget(tabWidget, 0, 0, 1, 1);

        kicad_module_scannerClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(kicad_module_scannerClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1058, 23));
        kicad_module_scannerClass->setMenuBar(menubar);
        statusbar = new QStatusBar(kicad_module_scannerClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        kicad_module_scannerClass->setStatusBar(statusbar);

        retranslateUi(kicad_module_scannerClass);
        QObject::connect(chkPins, SIGNAL(toggled(bool)), spinBoxNumPins, SLOT(setEnabled(bool)));
        QObject::connect(chkFootprintName, SIGNAL(toggled(bool)), cboFootprintName, SLOT(setEnabled(bool)));
        QObject::connect(chkKeywords, SIGNAL(toggled(bool)), cboKeywords, SLOT(setEnabled(bool)));
        QObject::connect(chkDescription, SIGNAL(toggled(bool)), cboDescription, SLOT(setEnabled(bool)));
        QObject::connect(horizontalSlider_2, SIGNAL(valueChanged(int)), modView, SLOT(setPadOpacity(int)));
        QObject::connect(checkBox_2, SIGNAL(toggled(bool)), modView, SLOT(toggleShowGrid(bool)));
        QObject::connect(rdoGrid10Mil, SIGNAL(toggled(bool)), modView, SLOT(gridUnitsInMil(bool)));
        QObject::connect(pushButton_5, SIGNAL(clicked()), modView, SLOT(zoomIn()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), modView, SLOT(zoomOut()));
        QObject::connect(pushButton_7, SIGNAL(clicked()), modView, SLOT(zoomToFit()));
        QObject::connect(pushButton_8, SIGNAL(clicked()), modView, SLOT(zoomReset()));
        QObject::connect(btnViewingMode, SIGNAL(toggled(bool)), gbCopy, SLOT(setHidden(bool)));
        QObject::connect(btnViewingMode, SIGNAL(toggled(bool)), modViewSmall, SLOT(setShown(bool)));
        QObject::connect(leShellWorkerScript, SIGNAL(textEdited(QString)), kicad_module_scannerClass, SLOT(onScriptLocationChanged()));
        QObject::connect(leAwkScript, SIGNAL(textEdited(QString)), kicad_module_scannerClass, SLOT(onScriptLocationChanged()));
        QObject::connect(leCopierScript, SIGNAL(textEdited(QString)), kicad_module_scannerClass, SLOT(onScriptLocationChanged()));
        QObject::connect(leExtractorScript, SIGNAL(textEdited(QString)), kicad_module_scannerClass, SLOT(onScriptLocationChanged()));

        tabWidget->setCurrentIndex(0);
        cboKeywords->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(kicad_module_scannerClass);
    } // setupUi

    void retranslateUi(QMainWindow *kicad_module_scannerClass)
    {
        kicad_module_scannerClass->setWindowTitle(QApplication::translate("kicad_module_scannerClass", "Kicad Footprint Viewer \342\206\204\342\203\235 MMXII Tin Tray Productions", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("kicad_module_scannerClass", "Kicad Installation Folder", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        leKicadInstallationFolder->setToolTip(QApplication::translate("kicad_module_scannerClass", "The Kicad Installation Folder is not used yet.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        leKicadInstallationFolder->setText(QApplication::translate("kicad_module_scannerClass", "/usr/share/kicad/", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnSelectKicadInstallationFolder->setToolTip(QApplication::translate("kicad_module_scannerClass", "Not implemented yet", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSelectKicadInstallationFolder->setText(QApplication::translate("kicad_module_scannerClass", "...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("kicad_module_scannerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Scanner Script (kicad-module-scanner.sh)</p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        leShellWorkerScript->setText(QApplication::translate("kicad_module_scannerClass", "scripts/kicad-module-scanner.sh", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("kicad_module_scannerClass", "Awk Scanner Script", 0, QApplication::UnicodeUTF8));
        leAwkScript->setText(QApplication::translate("kicad_module_scannerClass", "scripts/kicad-module-scanner.awk", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("kicad_module_scannerClass", "Footprint Copier Script", 0, QApplication::UnicodeUTF8));
        leCopierScript->setText(QApplication::translate("kicad_module_scannerClass", "scripts/kicad-copy-module.sh", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("kicad_module_scannerClass", "Module Extractor Script", 0, QApplication::UnicodeUTF8));
        leExtractorScript->setText(QApplication::translate("kicad_module_scannerClass", "scripts/kicad-extract-module.awk", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("kicad_module_scannerClass", "Postscript Viewer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboPostscriptViewer->setToolTip(QApplication::translate("kicad_module_scannerClass", "Footprints are shown with an external viewer which can be specified here. Okular is a good choice as it automatically detects when the file it is displaying changes. It also has good zoom abilities.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnSelectPostscriptViewer->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        btnSelectPostscriptViewer->setText(QApplication::translate("kicad_module_scannerClass", "...", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("kicad_module_scannerClass", "Viewer Temporary File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboViewerTemporaryFile->setToolTip(QApplication::translate("kicad_module_scannerClass", "You can specify any file name here which can be written to by this application and read by the Postscript Viewer above.\n"
"It is overwritten when the viewed footprint changes.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_21->setText(QApplication::translate("kicad_module_scannerClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Script and Program Locations (items in <span style=\" font-weight:600; color:#ff0000;\">red</span> do not exist and must be fixed before other pages are available)</p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSetup), QApplication::translate("kicad_module_scannerClass", "General Setup", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("kicad_module_scannerClass", "Use this page to scan footprint libraries (*.mod) in one or more folders.", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("kicad_module_scannerClass", "Folders to Scan", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = lstFoldersToScan->isSortingEnabled();
        lstFoldersToScan->setSortingEnabled(false);
        lstFoldersToScan->setSortingEnabled(__sortingEnabled);

        btnAddFolderToScan->setText(QApplication::translate("kicad_module_scannerClass", "Add...", 0, QApplication::UnicodeUTF8));
        btnRemoveFolderToScan->setText(QApplication::translate("kicad_module_scannerClass", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("kicad_module_scannerClass", "Output to Database File", 0, QApplication::UnicodeUTF8));
        rdoFolderScanOutputOverwrite->setText(QApplication::translate("kicad_module_scannerClass", "Overwrite", 0, QApplication::UnicodeUTF8));
        rdoFolderScanOutputAppend->setText(QApplication::translate("kicad_module_scannerClass", "Append output to", 0, QApplication::UnicodeUTF8));
        cboOutputFile_FolderScanning->clear();
        cboOutputFile_FolderScanning->insertItems(0, QStringList()
         << QApplication::translate("kicad_module_scannerClass", "/home/root/Projects/kicad-module-scanner-kate/kms.xml", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cboOutputFile_FolderScanning->setToolTip(QApplication::translate("kicad_module_scannerClass", "When you scan a folder (or several folders), all the footprints found in the .mod files contained in those folders will be written to one xml database file which you can specify here. Obviously, this can potentially produce a large file but it makes it easy to search/view the results on the Viewing page. For finer control use the File Scanning page.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkFolderIncludePostscript->setToolTip(QApplication::translate("kicad_module_scannerClass", "If checked, the Database file will include Postscript for drawing the footprints. This makes viewing footprints slightly quicker but canproduce huge files if many libraries are scanned which may result in memory problems on smaller computers.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkFolderIncludePostscript->setText(QApplication::translate("kicad_module_scannerClass", "Include Postscript", 0, QApplication::UnicodeUTF8));
        btnScanCheckedFolders->setText(QApplication::translate("kicad_module_scannerClass", "Scan Checked Folders", 0, QApplication::UnicodeUTF8));
        btnStopScanCheckedFolders->setText(QApplication::translate("kicad_module_scannerClass", "Stop Scanning", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFolderScanning), QApplication::translate("kicad_module_scannerClass", "Folder Scanning", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("kicad_module_scannerClass", "Use this page to scan footprint libraries (*.mod) in one or more files.", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("kicad_module_scannerClass", "Files to Scan", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = lstFilesToScan->isSortingEnabled();
        lstFilesToScan->setSortingEnabled(false);
        lstFilesToScan->setSortingEnabled(__sortingEnabled1);

        btnAddFileToScan->setText(QApplication::translate("kicad_module_scannerClass", "Add...", 0, QApplication::UnicodeUTF8));
        btnRemoveFileToScan->setText(QApplication::translate("kicad_module_scannerClass", "Remove", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("kicad_module_scannerClass", "Output to Database File", 0, QApplication::UnicodeUTF8));
        rdoFileScanOutputOverwrite->setText(QApplication::translate("kicad_module_scannerClass", "Overwrite", 0, QApplication::UnicodeUTF8));
        rdoFileScanOutputAppend->setText(QApplication::translate("kicad_module_scannerClass", "Append output to", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboOutputFile_FileScanning->setToolTip(QApplication::translate("kicad_module_scannerClass", "The footprints found in the .mod files checked above will be written to a single xml database file which you can specify here. To quickly scan all .mod libraries in a folder use the Folder Scanning page.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkFileIncludePostscript->setToolTip(QApplication::translate("kicad_module_scannerClass", "If checked, the Database file will include Postscript for drawing the footprints. This makes viewing footprints slightly quicker but canproduce huge files if many libraries are scanned which may result in memory problems on smaller computers.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkFileIncludePostscript->setText(QApplication::translate("kicad_module_scannerClass", "Include Postscript", 0, QApplication::UnicodeUTF8));
        btnScanCheckedFiles->setText(QApplication::translate("kicad_module_scannerClass", "Scan Checked Files", 0, QApplication::UnicodeUTF8));
        btnStopScanCheckedFiles->setText(QApplication::translate("kicad_module_scannerClass", "Stop Scanning", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFileScanning), QApplication::translate("kicad_module_scannerClass", "File Scanning", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("kicad_module_scannerClass", "Footprint Database", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboDatabaseFile->setToolTip(QApplication::translate("kicad_module_scannerClass", "Select a database file that you have previously made on the Folder Scanning or File Scanning tabs.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSelectFootprintDatabase->setText(QApplication::translate("kicad_module_scannerClass", "...", 0, QApplication::UnicodeUTF8));
        gbSearchCriteria->setTitle(QApplication::translate("kicad_module_scannerClass", "Search Criteria (all criteria are \"anded\")", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("kicad_module_scannerClass", "# Pins", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        chkPins->setToolTip(QApplication::translate("kicad_module_scannerClass", "Check to search on number of pins", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkPins->setText(QString());
        label_15->setText(QApplication::translate("kicad_module_scannerClass", "&", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("kicad_module_scannerClass", "Name Contains", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboFootprintName->setToolTip(QApplication::translate("kicad_module_scannerClass", "Enter a single term (eg:QFP) to find in the footprint's name.\n"
"(Lists of terms are not supported.)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkFootprintName->setToolTip(QApplication::translate("kicad_module_scannerClass", "Check to search on Footprint Name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkFootprintName->setText(QString());
        label_16->setText(QApplication::translate("kicad_module_scannerClass", "&", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("kicad_module_scannerClass", "Keywords Contain", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboKeywords->setToolTip(QApplication::translate("kicad_module_scannerClass", "Enter a single term (eg:SMD) to find in the footprint's keywords.\n"
"(Lists of terms are not supported.)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkKeywords->setToolTip(QApplication::translate("kicad_module_scannerClass", "Check to search on Keywords", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkKeywords->setText(QString());
        label_17->setText(QApplication::translate("kicad_module_scannerClass", "&", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("kicad_module_scannerClass", "Description Contains", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cboDescription->setToolTip(QApplication::translate("kicad_module_scannerClass", "Enter a single term to find in the footprint's description..\n"
"(Lists of terms are not supported.)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkDescription->setToolTip(QApplication::translate("kicad_module_scannerClass", "Check to search on Description", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkDescription->setText(QString());
        btnSearch->setText(QApplication::translate("kicad_module_scannerClass", "Search", 0, QApplication::UnicodeUTF8));
        gBoxSearchResults->setTitle(QApplication::translate("kicad_module_scannerClass", "Search Results", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeSearchResults->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("kicad_module_scannerClass", "In File", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(3, QApplication::translate("kicad_module_scannerClass", "Keys", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("kicad_module_scannerClass", "Desc", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("kicad_module_scannerClass", "Pins", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = treeSearchResults->isSortingEnabled();
        treeSearchResults->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeSearchResults->topLevelItem(0);
        ___qtreewidgetitem1->setText(4, QApplication::translate("kicad_module_scannerClass", "file2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(3, QApplication::translate("kicad_module_scannerClass", "k2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(2, QApplication::translate("kicad_module_scannerClass", "d2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(1, QApplication::translate("kicad_module_scannerClass", "2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("kicad_module_scannerClass", "dummy", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = treeSearchResults->topLevelItem(1);
        ___qtreewidgetitem2->setText(4, QApplication::translate("kicad_module_scannerClass", "/home/root/Projects/kicad-module-scanner-kate/40tex-Ell600.mod", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(3, QApplication::translate("kicad_module_scannerClass", "Keys", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(2, QApplication::translate("kicad_module_scannerClass", "A description", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(1, QApplication::translate("kicad_module_scannerClass", "40", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("kicad_module_scannerClass", "40Tex-Ell600", 0, QApplication::UnicodeUTF8));
        treeSearchResults->setSortingEnabled(__sortingEnabled2);

#ifndef QT_NO_TOOLTIP
        chkAutoPreview->setToolTip(QApplication::translate("kicad_module_scannerClass", "Automatically display footprint when selected.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkAutoPreview->setText(QApplication::translate("kicad_module_scannerClass", "Auto Preview", 0, QApplication::UnicodeUTF8));
        btnPreview->setText(QApplication::translate("kicad_module_scannerClass", "Preview", 0, QApplication::UnicodeUTF8));
        gbCopy->setTitle(QApplication::translate("kicad_module_scannerClass", "Copy", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("kicad_module_scannerClass", "in library", 0, QApplication::UnicodeUTF8));
        btnSelectCopyToLibrary->setText(QApplication::translate("kicad_module_scannerClass", "...", 0, QApplication::UnicodeUTF8));
        lblFpsInLibrary->setText(QApplication::translate("kicad_module_scannerClass", "Footprints in Destination Library", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = treeFpsInDestLibrary->headerItem();
        ___qtreewidgetitem3->setText(0, QApplication::translate("kicad_module_scannerClass", "Name", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled3 = treeFpsInDestLibrary->isSortingEnabled();
        treeFpsInDestLibrary->setSortingEnabled(false);
        treeFpsInDestLibrary->setSortingEnabled(__sortingEnabled3);

#ifndef QT_NO_TOOLTIP
        chkAllowOverwrite->setToolTip(QApplication::translate("kicad_module_scannerClass", "If a footprint to be copied exists in the destination\n"
"library, allow it to be overwritten (updated).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chkAllowOverwrite->setText(QApplication::translate("kicad_module_scannerClass", "Allow\n"
"Overwrite", 0, QApplication::UnicodeUTF8));
        btnCopy->setText(QApplication::translate("kicad_module_scannerClass", "Copy", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("kicad_module_scannerClass", "Mode", 0, QApplication::UnicodeUTF8));
        btnViewingMode->setText(QApplication::translate("kicad_module_scannerClass", "Viewing", 0, QApplication::UnicodeUTF8));
        btnCopyingMode->setText(QApplication::translate("kicad_module_scannerClass", "Copying", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFindingCopying), QApplication::translate("kicad_module_scannerClass", "Finding/Copying", 0, QApplication::UnicodeUTF8));
        lblFootprintName->setText(QApplication::translate("kicad_module_scannerClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("kicad_module_scannerClass", "Pad Opacity", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("kicad_module_scannerClass", "Grid", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("kicad_module_scannerClass", "Show", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("kicad_module_scannerClass", "Divisions", 0, QApplication::UnicodeUTF8));
        rdoGrid10Mil->setText(QApplication::translate("kicad_module_scannerClass", "10 mil", 0, QApplication::UnicodeUTF8));
        radioButton_3->setText(QApplication::translate("kicad_module_scannerClass", "0.5mm", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("kicad_module_scannerClass", "Zoom", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("kicad_module_scannerClass", "In", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("kicad_module_scannerClass", "Out", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("kicad_module_scannerClass", "To Fit", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("kicad_module_scannerClass", "Reset", 0, QApplication::UnicodeUTF8));
        gbMeasure->setTitle(QApplication::translate("kicad_module_scannerClass", "Measure (mil)", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("kicad_module_scannerClass", "dX:", 0, QApplication::UnicodeUTF8));
        lblDx->setText(QApplication::translate("kicad_module_scannerClass", "0", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("kicad_module_scannerClass", "dY:", 0, QApplication::UnicodeUTF8));
        lblDy->setText(QApplication::translate("kicad_module_scannerClass", "0", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("kicad_module_scannerClass", "d:", 0, QApplication::UnicodeUTF8));
        lblD->setText(QApplication::translate("kicad_module_scannerClass", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabViewer), QApplication::translate("kicad_module_scannerClass", "Viewer", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabTest), QApplication::translate("kicad_module_scannerClass", "test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class kicad_module_scannerClass: public Ui_kicad_module_scannerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KICAD_MODULE_SCANNER_H
