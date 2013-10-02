/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Fri Aug 16 03:00:56 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *s_paramGB;
    QGridLayout *gridLayout;
    QDoubleSpinBox *m_tensionBox;
    QLabel *label_5;
    QDoubleSpinBox *m_isovalue;
    QLabel *label_3;
    QDoubleSpinBox *m_blobRadius;
    QDoubleSpinBox *m_voxelSize;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label;
    QDoubleSpinBox *m_containerSizeZBox;
    QDoubleSpinBox *m_containerSizeYBox;
    QLabel *label_2;
    QDoubleSpinBox *m_containerSizeXBox;
    QLabel *label_4;
    QDoubleSpinBox *m_smoothRadiusBox;
    QDoubleSpinBox *m_gravityXBox;
    QLabel *label_12;
    QDoubleSpinBox *m_obstacleRadiusBox;
    QDoubleSpinBox *m_gravityYBox;
    QDoubleSpinBox *m_gravityZBox;
    QLabel *label_8;
    QDoubleSpinBox *m_viscosityBox;
    QPushButton *m_runButton;
    QPushButton *m_stopButton;
    QPushButton *m_resetButton;
    QSpacerItem *verticalSpacer;
    QSpinBox *m_numParticlesBox;
    QLabel *label_15;
    QDoubleSpinBox *m_elasticityBox;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_14;
    QSpacerItem *verticalSpacer_4;
    QDoubleSpinBox *m_obstacleXBox;
    QDoubleSpinBox *m_obstacleYBox;
    QDoubleSpinBox *m_obstacleZBox;
    QLabel *label_17;
    QLabel *label_18;
    QPushButton *m_addObstacleButton;
    QPushButton *m_deleteObstaclesButton;
    QLabel *label_6;
    QDoubleSpinBox *m_restDensityBox;
    QLabel *label_10;
    QDoubleSpinBox *m_gasKBox;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_7;
    QLabel *label_16;
    QComboBox *m_drawBox;
    QLabel *label_13;
    QComboBox *m_isosurface;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 735);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setObjectName(QString::fromUtf8("s_mainWindowGridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        s_paramGB = new QGroupBox(centralwidget);
        s_paramGB->setObjectName(QString::fromUtf8("s_paramGB"));
        gridLayout = new QGridLayout(s_paramGB);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_tensionBox = new QDoubleSpinBox(s_paramGB);
        m_tensionBox->setObjectName(QString::fromUtf8("m_tensionBox"));
        m_tensionBox->setDecimals(4);
        m_tensionBox->setMaximum(50);
        m_tensionBox->setValue(0.0728);

        gridLayout->addWidget(m_tensionBox, 18, 0, 1, 1);

        label_5 = new QLabel(s_paramGB);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 31, 2, 1, 1);

        m_isovalue = new QDoubleSpinBox(s_paramGB);
        m_isovalue->setObjectName(QString::fromUtf8("m_isovalue"));
        m_isovalue->setDecimals(4);
        m_isovalue->setMinimum(-2);
        m_isovalue->setMaximum(2);
        m_isovalue->setSingleStep(0.1);

        gridLayout->addWidget(m_isovalue, 32, 0, 1, 1);

        label_3 = new QLabel(s_paramGB);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 31, 1, 1, 1);

        m_blobRadius = new QDoubleSpinBox(s_paramGB);
        m_blobRadius->setObjectName(QString::fromUtf8("m_blobRadius"));
        m_blobRadius->setDecimals(4);
        m_blobRadius->setMaximum(0.5);
        m_blobRadius->setSingleStep(0.01);

        gridLayout->addWidget(m_blobRadius, 32, 2, 1, 1);

        m_voxelSize = new QDoubleSpinBox(s_paramGB);
        m_voxelSize->setObjectName(QString::fromUtf8("m_voxelSize"));
        m_voxelSize->setDecimals(4);
        m_voxelSize->setMaximum(1);
        m_voxelSize->setSingleStep(0.01);

        gridLayout->addWidget(m_voxelSize, 32, 1, 1, 1);

        label_11 = new QLabel(s_paramGB);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 31, 0, 1, 1);

        label_9 = new QLabel(s_paramGB);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 6, 2, 1, 1);

        label = new QLabel(s_paramGB);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        m_containerSizeZBox = new QDoubleSpinBox(s_paramGB);
        m_containerSizeZBox->setObjectName(QString::fromUtf8("m_containerSizeZBox"));
        m_containerSizeZBox->setMaximum(5);
        m_containerSizeZBox->setSingleStep(0.5);
        m_containerSizeZBox->setValue(2);

        gridLayout->addWidget(m_containerSizeZBox, 5, 2, 1, 1);

        m_containerSizeYBox = new QDoubleSpinBox(s_paramGB);
        m_containerSizeYBox->setObjectName(QString::fromUtf8("m_containerSizeYBox"));
        m_containerSizeYBox->setMaximum(5);
        m_containerSizeYBox->setSingleStep(0.5);
        m_containerSizeYBox->setValue(2);

        gridLayout->addWidget(m_containerSizeYBox, 5, 1, 1, 1);

        label_2 = new QLabel(s_paramGB);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        m_containerSizeXBox = new QDoubleSpinBox(s_paramGB);
        m_containerSizeXBox->setObjectName(QString::fromUtf8("m_containerSizeXBox"));
        m_containerSizeXBox->setMaximum(5);
        m_containerSizeXBox->setSingleStep(0.5);
        m_containerSizeXBox->setValue(2);

        gridLayout->addWidget(m_containerSizeXBox, 5, 0, 1, 1);

        label_4 = new QLabel(s_paramGB);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 6, 1, 1, 1);

        m_smoothRadiusBox = new QDoubleSpinBox(s_paramGB);
        m_smoothRadiusBox->setObjectName(QString::fromUtf8("m_smoothRadiusBox"));
        m_smoothRadiusBox->setDecimals(4);
        m_smoothRadiusBox->setMaximum(1);
        m_smoothRadiusBox->setSingleStep(0.01);
        m_smoothRadiusBox->setValue(0.1);

        gridLayout->addWidget(m_smoothRadiusBox, 7, 1, 1, 1);

        m_gravityXBox = new QDoubleSpinBox(s_paramGB);
        m_gravityXBox->setObjectName(QString::fromUtf8("m_gravityXBox"));
        m_gravityXBox->setMinimum(-99.99);

        gridLayout->addWidget(m_gravityXBox, 22, 0, 1, 1);

        label_12 = new QLabel(s_paramGB);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 21, 0, 1, 1);

        m_obstacleRadiusBox = new QDoubleSpinBox(s_paramGB);
        m_obstacleRadiusBox->setObjectName(QString::fromUtf8("m_obstacleRadiusBox"));
        m_obstacleRadiusBox->setMaximum(5);
        m_obstacleRadiusBox->setSingleStep(0.1);
        m_obstacleRadiusBox->setValue(0.4);

        gridLayout->addWidget(m_obstacleRadiusBox, 29, 0, 1, 1);

        m_gravityYBox = new QDoubleSpinBox(s_paramGB);
        m_gravityYBox->setObjectName(QString::fromUtf8("m_gravityYBox"));
        m_gravityYBox->setMinimum(-99.99);
        m_gravityYBox->setValue(-9.8);

        gridLayout->addWidget(m_gravityYBox, 22, 1, 1, 1);

        m_gravityZBox = new QDoubleSpinBox(s_paramGB);
        m_gravityZBox->setObjectName(QString::fromUtf8("m_gravityZBox"));
        m_gravityZBox->setMinimum(-99.99);

        gridLayout->addWidget(m_gravityZBox, 22, 2, 1, 1);

        label_8 = new QLabel(s_paramGB);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 17, 1, 1, 1);

        m_viscosityBox = new QDoubleSpinBox(s_paramGB);
        m_viscosityBox->setObjectName(QString::fromUtf8("m_viscosityBox"));
        m_viscosityBox->setDecimals(4);
        m_viscosityBox->setValue(3.5);

        gridLayout->addWidget(m_viscosityBox, 18, 1, 1, 1);

        m_runButton = new QPushButton(s_paramGB);
        m_runButton->setObjectName(QString::fromUtf8("m_runButton"));

        gridLayout->addWidget(m_runButton, 34, 0, 1, 1);

        m_stopButton = new QPushButton(s_paramGB);
        m_stopButton->setObjectName(QString::fromUtf8("m_stopButton"));

        gridLayout->addWidget(m_stopButton, 34, 1, 1, 1);

        m_resetButton = new QPushButton(s_paramGB);
        m_resetButton->setObjectName(QString::fromUtf8("m_resetButton"));

        gridLayout->addWidget(m_resetButton, 34, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 33, 0, 1, 1);

        m_numParticlesBox = new QSpinBox(s_paramGB);
        m_numParticlesBox->setObjectName(QString::fromUtf8("m_numParticlesBox"));
        m_numParticlesBox->setMaximum(10000);
        m_numParticlesBox->setValue(1000);

        gridLayout->addWidget(m_numParticlesBox, 2, 0, 1, 1);

        label_15 = new QLabel(s_paramGB);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 17, 2, 1, 1);

        m_elasticityBox = new QDoubleSpinBox(s_paramGB);
        m_elasticityBox->setObjectName(QString::fromUtf8("m_elasticityBox"));
        m_elasticityBox->setMaximum(1);
        m_elasticityBox->setSingleStep(0.1);
        m_elasticityBox->setValue(0.2);

        gridLayout->addWidget(m_elasticityBox, 18, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_3, 8, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 35, 1, 1, 1);

        label_14 = new QLabel(s_paramGB);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(7);
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_14, 35, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_4, 23, 0, 1, 1);

        m_obstacleXBox = new QDoubleSpinBox(s_paramGB);
        m_obstacleXBox->setObjectName(QString::fromUtf8("m_obstacleXBox"));
        m_obstacleXBox->setMinimum(-10);
        m_obstacleXBox->setMaximum(10);
        m_obstacleXBox->setSingleStep(0.1);

        gridLayout->addWidget(m_obstacleXBox, 27, 0, 1, 1);

        m_obstacleYBox = new QDoubleSpinBox(s_paramGB);
        m_obstacleYBox->setObjectName(QString::fromUtf8("m_obstacleYBox"));
        m_obstacleYBox->setMinimum(-10);
        m_obstacleYBox->setMaximum(10);
        m_obstacleYBox->setSingleStep(0.1);

        gridLayout->addWidget(m_obstacleYBox, 27, 1, 1, 1);

        m_obstacleZBox = new QDoubleSpinBox(s_paramGB);
        m_obstacleZBox->setObjectName(QString::fromUtf8("m_obstacleZBox"));
        m_obstacleZBox->setMinimum(-10);
        m_obstacleZBox->setMaximum(10);
        m_obstacleZBox->setSingleStep(0.1);

        gridLayout->addWidget(m_obstacleZBox, 27, 2, 1, 1);

        label_17 = new QLabel(s_paramGB);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout->addWidget(label_17, 26, 0, 1, 2);

        label_18 = new QLabel(s_paramGB);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 28, 0, 1, 1);

        m_addObstacleButton = new QPushButton(s_paramGB);
        m_addObstacleButton->setObjectName(QString::fromUtf8("m_addObstacleButton"));

        gridLayout->addWidget(m_addObstacleButton, 29, 1, 1, 1);

        m_deleteObstaclesButton = new QPushButton(s_paramGB);
        m_deleteObstaclesButton->setObjectName(QString::fromUtf8("m_deleteObstaclesButton"));

        gridLayout->addWidget(m_deleteObstaclesButton, 29, 2, 1, 1);

        label_6 = new QLabel(s_paramGB);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        m_restDensityBox = new QDoubleSpinBox(s_paramGB);
        m_restDensityBox->setObjectName(QString::fromUtf8("m_restDensityBox"));
        m_restDensityBox->setMaximum(1500);
        m_restDensityBox->setValue(50);

        gridLayout->addWidget(m_restDensityBox, 7, 0, 1, 1);

        label_10 = new QLabel(s_paramGB);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 17, 0, 1, 1);

        m_gasKBox = new QDoubleSpinBox(s_paramGB);
        m_gasKBox->setObjectName(QString::fromUtf8("m_gasKBox"));
        m_gasKBox->setDecimals(4);
        m_gasKBox->setValue(3.5);

        gridLayout->addWidget(m_gasKBox, 7, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(10, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 30, 2, 1, 1);

        label_7 = new QLabel(s_paramGB);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 30, 0, 1, 1);

        label_16 = new QLabel(s_paramGB);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_16, 36, 0, 1, 1);

        m_drawBox = new QComboBox(s_paramGB);
        m_drawBox->setObjectName(QString::fromUtf8("m_drawBox"));

        gridLayout->addWidget(m_drawBox, 37, 0, 1, 1);

        label_13 = new QLabel(s_paramGB);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 36, 2, 1, 1);

        m_isosurface = new QComboBox(s_paramGB);
        m_isosurface->setObjectName(QString::fromUtf8("m_isosurface"));

        gridLayout->addWidget(m_isosurface, 37, 2, 1, 1);


        s_mainWindowGridLayout->addWidget(s_paramGB, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        m_drawBox->setCurrentIndex(4);
        m_isosurface->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SPH Fluid Sim", 0, QApplication::UnicodeUTF8));
        s_paramGB->setTitle(QApplication::translate("MainWindow", "Simulation Parameters", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Blobby Radius", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Voxel Size", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Isovalue", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Stiffness", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Number of Particles ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Container Size", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Smoothing Radius", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Gravity", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Viscosity", 0, QApplication::UnicodeUTF8));
        m_runButton->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
        m_stopButton->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        m_resetButton->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Collision Elasticity", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "*Reset to see changes*", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Create Sphere Obstacle: Position", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "Sphere Radius", 0, QApplication::UnicodeUTF8));
        m_addObstacleButton->setText(QApplication::translate("MainWindow", "Add Obstacle", 0, QApplication::UnicodeUTF8));
        m_deleteObstaclesButton->setText(QApplication::translate("MainWindow", "Clear Obstacles", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Rest Density", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "SurfaceTension", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Marching Cubes", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Draw Mode", 0, QApplication::UnicodeUTF8));
        m_drawBox->clear();
        m_drawBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Points", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Density", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Surface", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Marching Cubes", 0, QApplication::UnicodeUTF8)
        );
        label_13->setText(QApplication::translate("MainWindow", "Isosurface", 0, QApplication::UnicodeUTF8));
        m_isosurface->clear();
        m_isosurface->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Averaged Centers", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Metaballs", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
