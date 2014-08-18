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

extern CWallet* pwalletMain;
extern void GenerateBitcoins(bool fGenerate, CWallet* pwallet);
extern bool SoftSetBoolArg(const std::string& strArg, bool fValue);

class MPExecutor : public QObject
{
    Q_OBJECT

public slots:
signals:
};
#include "miningpage.moc"


MiningPage::MiningPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiningPage),
    clientModel(0),
    walletModel(0)
{
    ui->setupUi(this);
}

MiningPage::~MiningPage()
{
    delete ui;
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
    }
    else
    {
        QMessageBox::information(NULL, "Mining Status Error", "Failed to stop the internal miner.  Possible wallet error detected.");
    }
}
