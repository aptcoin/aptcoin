// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "miningpage.h"
#include "ui_miningpage.h"

#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>

extern int nCurrentNFactor;
extern int nBestHeight;
extern CWallet* pwalletMain;
extern void GenerateBitcoins(bool fGenerate, CWallet* pwallet);
extern bool SoftSetBoolArg(const std::string& strArg, bool fValue);

class MPExecutor : public QThread
{
     Q_OBJECT

  public:
    void setThreadRunning(int state)
    {
        threadRunning = state;
    }

    void cleanup()
    {
        threadRunning = 0;
        exit();
    }

  public slots:
     void run()
     {
         while(threadRunning != 0)
         {
             QString result = "Current NFactor: " + QString::number(nCurrentNFactor+1) +
                 "\nCurrent Block Height: " + QString::number(nBestHeight);
             emit resultReady(result);
             msleep(800);
         }
     }

  signals:
     void resultReady(const QString &result);

  private:
     int threadRunning;
};
#include "miningpage.moc"


MiningPage::MiningPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiningPage),
    clientModel(0),
    walletModel(0)
{
    ui->setupUi(this);
    mpe = new MPExecutor();
    connect(mpe, SIGNAL(resultReady(QString)), this, SLOT(refreshMiningData(QString)));
}

MiningPage::~MiningPage()
{
    mpe->cleanup();
    mpe->wait(1000);
    delete ui;
    delete mpe;
}

void MiningPage::setClientModel(ClientModel *model)
{
    this->clientModel = model;
}

void MiningPage::setWalletModel(WalletModel *model)
{
    this->walletModel = model;
}

void MiningPage::startMining()
{
    if (pwalletMain)
    {
        bool status = true;
        SoftSetBoolArg("-gen", status);
        GenerateBitcoins(status, pwalletMain);

        QPixmap image(":/images/mining_active");
        ui->miningStatus->setPixmap(image);
        ui->miningStatus->repaint();
        ui->miningStart->setEnabled(false);
        ui->miningStop->setEnabled(true);

        ui->miningData->setText("Aptcoin Miner\nMining is active.");
        mpe->setThreadRunning(1);
        mpe->start();
    }
    else
    {
        QMessageBox::information(NULL, "Mining Status Error", "Failed to start the internal miner.  Possible wallet error detected.");
    }
}

void MiningPage::stopMining()
{
    if (pwalletMain)
    {
        bool status = false;
        SoftSetBoolArg("-gen", status);
        GenerateBitcoins(status, pwalletMain);

        QPixmap image(":/images/mining_inactive");
        ui->miningStatus->setPixmap(image);
        ui->miningStatus->repaint();
        ui->miningStart->setEnabled(true);
        ui->miningStop->setEnabled(false);

        ui->miningData->setText("Aptcoin Miner\nMining is not active.");
        mpe->setThreadRunning(0);
        ui->miningInfo->setText("");
    }
    else
    {
        QMessageBox::information(NULL, "Mining Status Error", "Failed to stop the internal miner.  Possible wallet error detected.");
    }
}

void MiningPage::refreshMiningData(const QString& data)
{
    ui->miningInfo->setText(data);
}
