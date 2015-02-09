#include "w_selectbatch.h"
#include "ui_w_selectbatch.h"
#include <vector>
#include <string>
#include "w_main.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include "gui_utilities.h"
//#include "w_inventaire.h"
#include "w_stat.h"
#include "parammodel.h"

w_selectBatch::w_selectBatch(QWidget *parent) :batch(BatchDetail::getBatchDetail()),
    QWidget(parent),
    m_ui(new Ui::w_selectBatch)
{
    m_ui->setupUi(this);    	
	setWindowTitle("Namalysator");		
	createConnections();
}

w_selectBatch::~w_selectBatch()
{
    delete m_ui;
}

void w_selectBatch::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
 //! create slots / signals
void w_selectBatch::createConnections()
{
	connect(m_ui->cbBatchName, SIGNAL(currentIndexChanged(QString)),this, SLOT(getListDate(QString)));
	connect(m_ui->listDateTestset,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(getMets(QListWidgetItem*)));
	connect(m_ui->btnAnalyze,SIGNAL(clicked()),this,SLOT(valider()));
	connect(m_ui->btnCancel,SIGNAL(clicked()),this,SLOT(exit()));
	connect(m_ui->btnBrowseDb,SIGNAL(clicked()),this,SLOT(browseDb()));
	connect(m_ui->btnPath, SIGNAL(clicked()),this, SLOT(browsePath()));		
}

//! fill Batch combobox
void w_selectBatch::fillItemBatchName()
{	
	m_ui->cbBatchName->clear();
	db.setDataBaseName(m_ui->lineEditSql->text().toStdString());
	//get all Testsets from batch
	std::vector<std::string> vTestSet  =   db.getvTestSet(); 
	for (size_t i =0; i< vTestSet.size();i++)
	{
		m_ui->cbBatchName->addItem(vTestSet[i].c_str());	
	}	
}

//! fill Inventaire combobox
/*
void w_selectBatch::fillItemInventaire()
{	
	m_ui->cbInventaire->clear();
	dbInventaire.setDataBaseName(m_ui->lineEditInventaire->text().toStdString());	
	vInventaire  =   dbInventaire.getNameInventaire(); 
	for (size_t i =0; i< vInventaire.size();i++)
	{
		m_ui->cbInventaire->addItem(vInventaire[i].name.c_str());	
	}	
}
*/
void w_selectBatch::getMets(QListWidgetItem* item)
{	
	db.getBatch(BatchDetail::getBatchDetail(),item->type());	
	fillBatchDetail();
}

//! browse explorer for select a database
void w_selectBatch::browseDb()
{
 QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"),"",tr("Database Files (*.db)"));
     if (!fileName.isEmpty()) 
     {	  	
	    std::string message = fileName.toStdString();		
        m_ui->lineEditSql->setText(slash_path(message).c_str());  
        batch.database = message;       
        fillItemBatchName();   
		loadParametersCompareBatch();       
     }     	
}

/*
void w_selectBatch::browsePathInventaire()
{

 QString fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open File"),"",tr("Database Files (*.db)"));
     if (!fileName.isEmpty()) 
     {	 	
	    std::string message = fileName.toStdString();		
        m_ui->lineEditInventaire->setText(slash_path(message).c_str());        
       // dbInventaire.setDataBaseName(message);
        fillItemInventaire();
     }     	
}
*/


void w_selectBatch::getListDate(QString name)
{		
	clearBatchDetail();
	std::vector<std::pair<int,std::string>> v =  db.getvDateTestset(name.toStdString()); 	
	
	for (size_t i =0; i< v.size();i++)
	{	
		QListWidgetItem *lst;
		lst =new QListWidgetItem(v[i].second.c_str(),  m_ui->listDateTestset,v[i].first);
		db.getBatch(BatchDetail::getBatchDetail(),v[i].first);
		fillBatchDetail();
		m_ui->listDateTestset->setItemSelected(lst,true);
	}		
	
	loadParametersCompareBatch();
}

void w_selectBatch::valider()
{
	batch.path =   m_ui->lineEdit->text().toStdString ();
	batch.database = m_ui->lineEditSql->text().toStdString ();
	// TODO : Check whether I still need the whole DB in memory
//	batch.mapMets = db.getmMets(batch.idTestSet);
//	batch.mapMetsDate = db.getmMetsDate(batch.idTestSet);
//	batch.mapYearCount  = db.getSumMetsYear(batch.idTestSet);
	//batch.databaseInv = m_ui->lineEditInventaire->text().toStdString ();
	/*
	if (vInventaire.size() >0)
	{
		batch.inventaire = vInventaire[m_ui->cbInventaire->currentIndex()];
	}
	*/
	if (inputDisk() == true)
	{		
		emit validated(batch.testDate);	
	}
}
//! verify if path of the disk corresponds to the data in the database
bool w_selectBatch::inputDisk()
{
	ifstream myfile;
	std::string path = batch.path  + db.getFirstMetsFilename(batch.idTestSet);
	myfile.open(path.c_str());
	
	if(myfile.fail())
	{		
		QMessageBox::information(this, tr("Wrong path"),
                                   tr("Wrong path for disk analyze"));	
		myfile.close(); 
		return false;
	}
	return true;
}
//! browsePath to disk
void w_selectBatch::browsePath()
{	
	QString fileName = QFileDialog::getExistingDirectory(this,tr("Open File"),"C:/");    
    if (!fileName.isEmpty()) 
    {		
		 std::string message = fileName.toStdString();
         m_ui->lineEdit->setText(slash_path(message).c_str());    
    }     	
}

void w_selectBatch::exit()
{
	emit exited();
}

void w_selectBatch::clearBatchDetail()
{	
	m_ui->listDateTestset->clear();
	m_ui->lbBatchName->setText("");	
	m_ui->lbYear->setText("");	
	m_ui->lbNumberMets->setText("");	
	m_ui->groupButton->setEnabled(false);
}


void w_selectBatch::fillBatchDetail()
{
	std::string date;
	QString count; 
	count.setNum(batch.count);
	m_ui->groupButton->setEnabled(true);
	QPalette pal = m_ui->btnAnalyze->palette();
    pal.setColor(QPalette::Button, QColor(Qt::blue));
    m_ui->btnAnalyze->setAutoFillBackground(true);
    m_ui->btnAnalyze->setPalette(pal);
    m_ui->btnAnalyze->update();
	date = batch.minDate + " / " + batch.maxDate ;
	m_ui->lbBatchName->setText(batch.batchName.c_str());	
	m_ui->lbYear->setText(date.c_str());	
	m_ui->lbNumberMets->setText(count);	
	loadParameters(batch.idTestSet);
}

 void w_selectBatch::loadParameters(int id)
 {
	Parameters param = db.getParameterVerifiers(id);
	//m_ui->lbschema->setText("Yes"); // always yes no more choice 
	std::map<std::string,std::string>map=db.key2Label(param.mapFilter());

	paramModel* modelParam = new paramModel();
	modelParam->init(map);
	m_ui->paramView->setModel(modelParam);
	m_ui->paramView->verticalHeader()->hide();
	//m_ui->paramView->horizontalHeader()->hide();
	m_ui->paramView->setAlternatingRowColors(true);

}

 void w_selectBatch::loadParametersCompareBatch()
 {
	std::vector<std::pair<int,std::string>> vDate =  db.getvDateTestset(batch.batchName); 	
	QString ss;	
	QTableWidgetItem *newItem;
	QStringList labels;
	labels   << tr("Error");	
	int rowCount =0;
	set<int> setError;
	for (size_t i =0; i< vDate.size();i++)
	{
		std::vector<ErrorSummary> vEs = db.getvErrorSummary(vDate[i].first);
		std::vector<ErrorSummary> vEsDate = db.getvErrorDate(vDate[i].first);	
		labels   << tr(vDate[i].second.c_str());
		
		for ( size_t k =0;k < vEs.size(); k++)
		{
			if (setError.find(vEs[k].errorType.id) == setError.end())
			{
				setError.insert(vEs[k].errorType.id);
			}
		}
		for ( size_t k =0;k < vEsDate.size(); k++)
		{
			if (setError.find(vEsDate[k].errorType.id) == setError.end())
			{
				setError.insert(vEsDate[k].errorType.id);
			}
		}
	}	
	rowCount =setError.size();
	m_ui->tableSummary->setColumnCount(vDate.size()+1);
	m_ui->tableSummary->setRowCount(rowCount);   
	m_ui->tableSummary->setHorizontalHeaderLabels(labels);	
	m_ui->tableSummary->setShowGrid(true);
	m_ui->tableSummary->verticalHeader()->hide();		
	for (int i=0;i<m_ui->tableSummary->rowCount();i++)
	{
		m_ui->tableSummary->setRowHeight(i,18);
	}

	int countRow=0;
	bool addRow = false;
	std::vector<ErrorType> vErrorType = db.getErrorType();
	for (size_t iError =0 ; iError < vErrorType.size(); iError ++)
	{ 		
		if (addRow == true)
		{	
			countRow++;
		}
		addRow =false;
		
		for(size_t j=0; j < vDate.size();j++)
		{
			int count = db.getErrorTypeCountWithTestset(vErrorType[iError].id,vDate[j].first);			
			if (count==0 )
			{
			
			}
			else
			{
				newItem = new QTableWidgetItem(vErrorType[iError].error.c_str(),0);		
				newItem->setTextAlignment(Qt::AlignCenter);
				m_ui->tableSummary->setItem(countRow, 0, newItem);
				newItem = new QTableWidgetItem(ss.setNum(count),1);		
				newItem->setTextAlignment(Qt::AlignCenter);
				m_ui->tableSummary->setItem(countRow, j+1, newItem);										
				addRow = true;								
			}	
		}	
	}
	for (size_t iError =0 ; iError < vErrorType.size(); iError ++)
	{ 		
		if (addRow == true)
		{	
			countRow++;
		}
		addRow =false;
		
		for(size_t j=0; j < vDate.size();j++)
		{
			int count = db.getErrorTypeCountWithTestsetDates(vErrorType[iError].id,vDate[j].first);			
			if (count==0 )
			{			
			}
			else
			{
				newItem = new QTableWidgetItem(vErrorType[iError].error.c_str(),0);		
				newItem->setTextAlignment(Qt::AlignCenter);
				m_ui->tableSummary->setItem(countRow, 0, newItem);
				newItem = new QTableWidgetItem(ss.setNum(count),1);		
				newItem->setTextAlignment(Qt::AlignCenter);
				m_ui->tableSummary->setItem(countRow, j+1, newItem);										
				addRow = true;								
			}	
		}	
	}	
	int sum =0 ;
	for (size_t i =0;i < vDate.size();i ++)
	{	
		if (i< 3)
		sum = sum + 120;	
	}
	m_ui->tableSummary->resizeColumnsToContents();
	m_ui->tableSummary->resize(m_ui->tableSummary->columnWidth(0)+ sum ,m_ui->tableSummary->height());
}