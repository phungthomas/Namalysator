#include "w_structview.h"
#include "ui_w_structview.h"
#include "metsparser.h"
#include "altoparser.h"
#include <sstream>
#include <fstream>
#include "w_screenshoterror.h"
#include <windows.h>
 #include <QSortFilterProxyModel>
#include "gui_utilities.h"
#include "calendarcommons.h"
#include "bookModel.h"
#include "bookColumn.h"

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
	
#include <cstdio>
#include <cstdlib>
#include <QMessageBox>

namespace fs = boost::filesystem;


void w_structview::setQMainWindow(QMainWindow* _qmain){
	qmain=_qmain;

	
	contentsWindow->setAllowedAreas(Qt::TopDockWidgetArea
                                  | Qt::BottomDockWidgetArea);
	    
	contentsWindow->setWidget(bookList);
	contentsWindow->setMinimumHeight(50);
	//contentsWindow->setMaximumHeight(180);
	QWidget *titleBarWidget = new QWidget(0);
	contentsWindow->setTitleBarWidget(titleBarWidget);
	contentsWindow->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    qmain->addDockWidget(Qt::TopDockWidgetArea, contentsWindow);

    menu = qmain->menuBar()->addMenu("Issue Viewer option"); 
	QAction *act = menu->addAction(tr("Sampling View"));
	connect(act,SIGNAL(triggered()),this,SLOT(showListSampling()));

	act = menu->addAction(tr("Calendar View"));;
	connect(act, SIGNAL(triggered()), this, SLOT(viewCalendar()));

	act = menu->addAction(tr("List View"));
	connect(act, SIGNAL(triggered()), this, SLOT(viewList()));

	
}

w_structview::w_structview(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_structview),
	m_colors(),currentWidgetSelected(0)
{
    m_ui->setupUi(this);

	bookList = new w_booklist(db);
	bookList ->init(false);
	contentsWindow = new QDockWidget();

	thumb = 0;
	menu = 0;
	mm = 0;


  
	createActions();
	createConnections();
	changeNewDate = false;
	currentPage=1;
	m_ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_ui->label->setScaledContents(true);
	
	m_ui->scrollArea->setWidget(m_ui->label);
	enableButton(false);	
    currentLevel=1;
    currentItem=0;	
    divImage = 5;
    multiImage =  0.2;  
    currentSelectedArticle =0;
    m_ui->btnStructure->setVisible(false);
	viewCalendar();
};

//! create event / slots
void w_structview::createConnections()
{	
	connect(m_ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(getDate(QDate)));
	connect(m_ui->treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this, SLOT(drawRect(QTreeWidgetItem*,QTreeWidgetItem*)));  
	connect(m_ui->listMets,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(getIdMets(QListWidgetItem*)));
	connect(m_ui->listSampling,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(getIdMets(QListWidgetItem*)));
	connect(m_ui->listErrors,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(showError(QListWidgetItem*)));
	connect(m_ui->btnPrevious,SIGNAL(clicked()),this,SLOT(previous()));
	connect(m_ui->btnNext,SIGNAL(clicked()),this,SLOT(next()));
	connect(m_ui->lblPage,SIGNAL(valueChanged(int)),this,SLOT(showPage(int)));
	connect(m_ui->btnStructure,SIGNAL(clicked()),this,SLOT(structure()));
	connect(m_ui->btnDeleteSelectedItem,SIGNAL(clicked()),this,SLOT(deleteSelectedItem()));
	connect(m_ui->btnError,SIGNAL(clicked()),this,SLOT(openErrorScreen()));
	connect(m_ui->btnClearPainter,SIGNAL(clicked()),this,SLOT(clearPainter()));		
	connect(m_ui->btnViewHtml,SIGNAL(clicked()),this,SLOT(viewHtml()));
	connect(m_ui->btnZoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(m_ui->btnZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
	connect(m_ui->zoomNormal, SIGNAL(clicked()), this, SLOT(zoomNon()));
	connect(m_ui->btnFull, SIGNAL(clicked()), this, SLOT(zoomFull()));
	//connect(m_ui->rbCalendar, SIGNAL(clicked()), this, SLOT(viewCalendar()));
	//connect(m_ui->rbList, SIGNAL(clicked()), this, SLOT(viewList()));
	//connect(m_ui->rbSampling,SIGNAL(clicked()),this,SLOT(showListSampling()));
	connect(m_ui->btnChecked, SIGNAL(clicked()), this, SLOT(checked()));
	connect(m_ui->btnUndo, SIGNAL(clicked()), this, SLOT(undo()));
	connect(m_ui->btnViewMets, SIGNAL(clicked()), this, SLOT(viewMetsFile()));
	connect(m_ui->btnViewDir, SIGNAL(clicked()), this, SLOT(viewMetsDir()));
	connect(bookList, SIGNAL(metsIdSelected(int)), this, SLOT(getIdMetsII(int)));
	connect(bookList, SIGNAL(metsThumb(int)), this, SLOT(showThumb(int)));
	//connect(bookList, SIGNAL(metsThumb(int)), this, SLOT(getIdMetsII(int)));
	
}

void w_structview::deleteSelectedItem(){
	static QMessageBox* qmesg=new QMessageBox();
	if ( currentWidgetSelected == 0 ){
		m_ui->btnDeleteSelectedItem->setEnabled(false);
		return;
	}

	int idItem = currentWidgetSelected ->data(Qt::UserRole).toInt();

	
	StructureError s = db.getStructureErrorId(idItem);

	qmesg->setDetailedText((s.getError()+"-"+s.message).c_str());
	qmesg->setText("Are you sure to delete the selected item?");
	qmesg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);

	qmesg->show();
	int ret = qmesg->exec();

	switch (ret){
	  case QMessageBox::Cancel : break;
	  case QMessageBox::Ok : deleteListItem( idItem );
	}


}

void w_structview::deleteListItem(int item){
	db.deleteStructureErrorId(item);
	this->fillListErrors();
}


void w_structview::showError(QListWidgetItem* qq){
	m_ui ->btnDeleteSelectedItem ->setEnabled(true);
	this->currentWidgetSelected = qq;
}


w_structview::~w_structview()
{
    delete m_ui;
	if (thumb){
		thumb->cancel();
		thumb->close();
		delete thumb;
		thumb=0;
	}
	if (contentsWindow){
		contentsWindow->close();
		delete contentsWindow;
		contentsWindow=0;
	};
	if ( menu ){
		menu->close();
		delete menu;
		menu = 0;
	}

	if ( mm ){
		mm->close();
		delete mm;
		mm = 0;
	}

}

//set detail of the batch
void w_structview::setBatchDetail()
{ 	
	//batch = d; 
	
	db.setDataBaseName(BatchDetail::getBatchDetail().database);  
	m_ui->calendarWidget->setVisible(true);
	m_ui->listMets->setVisible(true);
	//m_ui->rbCalendar->setChecked(true);	
	
	initCalendarWidget(m_ui->calendarWidget,BatchDetail::getBatchDetail());
	fillListSamplingStructure();	

}
 
 
void w_structview::setCurrentMets(MetsFile mets)
{
	m_ui->calendarWidget->setSelectedDate(mets.date);
	getDate(mets.date);
}

//event when click on calendar
void w_structview::getDate(QDate search)
{	
    clear();    
	bool findfirst = false;
	std::vector<MetsFile> *MetsOnDate = BatchDetail::getBatchDetail().getMetsByDate(search);
	if (MetsOnDate)	{
		for (std::vector<MetsFile>::iterator itMets = MetsOnDate->begin(); itMets != MetsOnDate->end(); itMets++)
		{
			lst = new QListWidgetItem(itMets->fileName.c_str(), m_ui->listMets, itMets->idMets);	
			if (findfirst == false)
			{				
				mets = *itMets;
				findfirst = true;
			}
		}
		mapTiffPath = db.getMapLinkedFiles(mets.idMets,"IMGGRP");
		mapAltoPath = db.getMapLinkedFiles(mets.idMets,"ALTOGRP");
		currentPage=1;
		maxPage = mets.pages;
		changeNewDate = false;
		m_ui->lblPageEnd->setNum(maxPage);
		showCurrentPage();	
		metsAltoParser();		
		fillListErrors();
		m_colors.set_colorTable(db.loadColor(mets.docType));
		delete MetsOnDate;
	}	
}

//! event when click on the listItem
void w_structview::getIdMetsII(int i ){
	if (BatchDetail::getBatchDetail().getMetsByID(i, mets)) {
		mapTiffPath = db.getMapLinkedFiles(mets.idMets,"IMGGRP");
		mapAltoPath = db.getMapLinkedFiles(mets.idMets,"ALTOGRP");
		currentPage=1;
		maxPage = mapTiffPath.size();
		changeNewDate = false;
		m_ui->lblPageEnd->setNum(maxPage);
		showCurrentPage();		
		metsAltoParser();	
		fillListErrors();
	} else {
		// TODO ERROR HANDLING
	}
}

void w_structview::showThumb(int i ){

	getIdMetsII(i); // do both thumb plus content

	if ( thumb ) {
		thumb->cancel();
		thumb->close ();
		delete thumb;
	};
	
	std::map<int,LinkedFiles> localMap; 
	if (BatchDetail::getBatchDetail().getMetsByID(i, mets)) {
		localMap = db.getMapLinkedFiles(mets.idMets,"IMGGRP");
	};


	thumb = new w_thumb(BatchDetail::getBatchDetail().path +"/"+ mets.path,localMap);
	thumb -> show();
	thumb -> load();
	connect ( thumb, SIGNAL(selectPage(int)),this,SLOT(showPage(int)));
}


 void w_structview::getIdMets(QListWidgetItem* item )
{
	getIdMetsII(item->type());
}
//! show the current page
void w_structview::showCurrentPage()
{		
	
	if (mapTiffPath.find(currentPage)!= mapTiffPath.end())
	{		
		std::string path = BatchDetail::getBatchDetail().path + mets.path + mapTiffPath.find(currentPage)->second.fileName;
		originalImage.load(path.c_str());	
		
		
		currentAltoFile = mapAltoPath.find(currentPage)->second.fileId;
		resizeImage();

		this->currentPageChange();

		updateTableOfContents(currentAltoFile);	
		enableButton(true);		
	}
}
void w_structview::changeEvent(QEvent *e)
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

void w_structview::previous()
{
	if (currentPage > 1) {
		currentPage--;
		showCurrentPage();	
	
	}
}
void w_structview::next()
{
	if (currentPage < (int) mapTiffPath.size()) {
		currentPage++;
		showCurrentPage();	
	}
}

void w_structview::currentPageChange(){
		m_ui->lblPage->setValue(currentPage);
		m_ui->lblPage->setMaximum(mapTiffPath.size());
}

void w_structview::showPage(int i)
{
	int oldcurrent = currentPage;
	//if ( currentPage == i ) return ; // do nothing if no real change
	if ( i <= (int) mapTiffPath.size() && i >=1 ) {
		currentPage=i;
	}else{
		if ( i <= 1 ) {
			currentPage=1;
		}else{
			currentPage=mapTiffPath.size();
		}
	}
	if ( oldcurrent != currentPage)
	showCurrentPage();	
}

void w_structview::zoomIn()
{
   
   divImage = divImage * 0.8;
   multiImage = multiImage / 0.8;
   resizeImage();
}

 void w_structview::zoomOut()
 {
	divImage = divImage /0.8;
	multiImage = multiImage * 0.8;
	resizeImage();
 }

 void w_structview::zoomNon()
 {
	divImage = 1;
	multiImage = 1;
	resizeImage();
 }

 void w_structview::zoomFull()
 {
	 double height = m_ui->scrollArea->height() *0.995;
	 if ( originalImage.width() > originalImage.height() ){
		divImage = originalImage.width()/height;
	 }else{
		divImage = originalImage.height()/height;
	 }
	multiImage = 1/divImage;
	resizeImage();
 }



 
 void w_structview::resizeImage()
 {
	image = originalImage.scaled(originalImage.width()/divImage,originalImage.height()/divImage);	
	originalPixmap = QPixmap::fromImage(image);		
	m_ui->label->setPixmap(originalPixmap);
	m_ui->label->adjustSize();

	// If the current article is still on the new current page, redraw its rectangles
	if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
		drawRect(currentSelectedArticle, 0);
	};
 }

 void w_structview::clearPainter()
 {
	originalPixmap = QPixmap::fromImage(image);
	QPainter painter(&originalPixmap);		
	m_ui->label->setPixmap(originalPixmap);	
 }

 void w_structview::structure()
 { 
	m_ui->label->adjustSize();
    //paintAllStructure(currentAltoFile);  
 }
 
 //! this method parse the mets and alto files to get the logical for creating the table of
 //! contents and get the block coordiantes for painting on the issue.
void w_structview::metsAltoParser()
{		
	std::string pathMets =  BatchDetail::getBatchDetail().path + "/" + mets.path + "/" + mets.fileName;
    Item itemtree;
	metsParser p(pathMets,&itemtree);	
	ParseDocument(pathMets.c_str(),&p);	
	treeContents = p.getItem();
	
	for(std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
	{
		int dpi = mapTiffPath[it->first].dpi;
		std::string path = BatchDetail::getBatchDetail().path +"/"+ mets.path + it->second.fileName;
		altoparser ap(path,it->second,dpi);	
		if (ParseDocument(path.c_str(),&ap)!=0)	
		{						
			// print error				
		}
		else
		{							
			mapAlto[it->second.fileId]=ap.getAltoBlock();
		}		
	}
	m_colors.set_colorTable(db.loadColor(mets.docType));
    createTree();
    createArticle();
	create_page2toc_entry();
}



void w_structview::createActions()
{
    zoomInAct = new QAction(tr(""), this);
    zoomInAct->setShortcut(tr("+"));
    zoomInAct->setEnabled(true);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    m_ui->btnZoomIn->addAction(zoomInAct);

    zoomOutAct = new QAction(tr(""), this);
    zoomOutAct->setShortcut(tr("-"));
    zoomOutAct->setEnabled(true);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    m_ui->btnZoomOut->addAction(zoomOutAct);

	zoomNextAct = new QAction(tr(""), this);
    zoomNextAct->setShortcut(Qt::Key_Right);
    zoomNextAct->setEnabled(true);
    connect(zoomNextAct, SIGNAL(triggered()), this, SLOT(next()));
	m_ui->btnNext->addAction(zoomNextAct);

	zoomPreviousAct = new QAction(tr(""), this);
	zoomPreviousAct->setShortcut(Qt::Key_Left);
    zoomPreviousAct->setEnabled(true);
    connect(zoomPreviousAct, SIGNAL(triggered()), this, SLOT(previous()));
	m_ui->btnPrevious->addAction(zoomPreviousAct);
}

//! create table of contents
void w_structview::createTree()
{	
	Item *item2 = treeContents;	
	m_ui->treeWidget->clear();
	vectItem.clear();
	if (item2->type == "Newspaper")
	{
		item2 = &item2->children[0];	
	}
		
	QTreeWidgetItem *widget = new QTreeWidgetItem(m_ui->treeWidget,item2->counter);
	widget->setText(0,QString::fromUtf8((item2->label).c_str()));
	counter2TreeItem.clear();
	constructTOCrecursively(item2, widget);
	m_ui->treeWidget->expandAll();		
	m_ui->treeWidget->setColumnWidth(0,800);
}

void w_structview::constructTOCrecursively(Item *item,QTreeWidgetItem *widget)
{	
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];
		// If this is a div type that we want to highlight (e.g. ARTICLE)
		if (m_colors.is_color_set(currentItem->type))
		{
			currentWidget = widget;			
			a = new QTreeWidgetItem(currentItem->counter);	
			if (!currentItem->label.empty()) {
				a->setText(0, QString::fromUtf8((currentItem->label + " (" + currentItem->type + ")").c_str()));
			} else {
				a->setText(0, QString::fromUtf8(currentItem->type.c_str()));
			}
			
			a->setTextColor(0,Qt::black);			
			currentWidget->addChild(a);				
			vectItem.push_back(currentItem);
			
			// Changed the entry in listItem from dmdID to id (because some items may not have a dmdID)
			counter2TreeItem[currentItem->counter] = a;
			constructTOCrecursively(currentItem, a);
		} else {
			constructTOCrecursively(currentItem, widget);
		}
	}
}

void w_structview::construct_page2blocks()
// This uses the treeContents as a starting point, so that has to be initialized before calling this function
{
	m_page2blocks.clear();
	std::vector<std::pair<std::string, Item *> > type_stack;
	std::string topmost_type;
	
	//if (
	//type_stack.push_back(std::make_pair(
}

void w_structview::construct_page2blocks_recursive(const std::string &current_type, Item *item)
{
	size_t i;
	// First add all the blocks that are at the current level
	for (std::vector<typeBlock>::const_iterator it = item->vectTypeBlock.begin(); it != item->vectTypeBlock.end(); ++it) {
		typeBlock b;
		b.alto = it->alto;
		b.block = it->block;
		b.type = current_type;
		m_page2blocks[it->alto].push_back(b);
	}
	// Now call the kids
	for (i = 0; i< item->children.size(); ++i) {
		Item *kid = &item->children[i];
		if (m_colors.is_color_set(kid->type)) {
			construct_page2blocks_recursive(kid->type, kid);
		} else {
			construct_page2blocks_recursive(current_type, kid);
		}
	}
}

void w_structview::updateTableOfContents(std::string currentAlto)
{
	// set format of table of contents
	QFont normalFont( "Arial", 8, QFont::Normal);
	QFont boldFont( "Arial",10, QFont::Bold );
	for (std::map<int, std::set<std::string> >::const_iterator it = m_toc_entry2page.begin(); it != m_toc_entry2page.end(); ++it) {
		// Get the pointer to the QTreeWidgetItem for this counter
		std::map<int ,QTreeWidgetItem*>::const_iterator it_tree = counter2TreeItem.find(it->first);
		if (it_tree != counter2TreeItem.end()) {
			QTreeWidgetItem *p = it_tree->second;
			// Check whether this TOC entry is also on this page or not
			if (it->second.find(currentAlto) != it->second.end()) {
				p->setFont(0, boldFont);
			} else {
				p->setFont(0, normalFont);
			}
		} else {
			// TODO: Raise an error
		}
	}
}

void w_structview::drawRect(QTreeWidgetItem *itemW, QTreeWidgetItem *itemW2)
{
	// itemW2 is not used, so get rid of compiler warning
	itemW2 = 0;
	if (!itemW) {
		// Means the tree is emptied, so no item is selected
		return;
	}
	currentSelectedArticle = itemW;
	int x,y,width,height;
	if (mapArticle.find(itemW->type())!=mapArticle.end())
	{	 
		 Article w = mapArticle[itemW->type()];		 
		 
		 const std::set<std::string> &this_toc2page = m_toc_entry2page[itemW->type()];
		 if (this_toc2page.find(currentAltoFile) == this_toc2page.end()) {
			 // We need to change pages, since the newly selected TOC entry is not on the current page
			 // So we switch to the page where this TOC entry has its first block
			currentAltoFile = w.vectArticle[0].alto;
			// load page			
			for (std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
			{
				if(it->second.fileId == currentAltoFile){
					currentPage = it->first;
				}
			}
			showCurrentPage();
			updateTableOfContents(currentAltoFile);
		
		 } 
		originalPixmap = QPixmap::fromImage(image);
		QPainter painter(&originalPixmap);
		QBrush b1(m_colors.get_color(w.type));
		painter.setBrush( b1 );
		painter.setOpacity(0.25);
	
		 for (size_t i= 0 ; i< w.vectArticle.size();i++)
		 {
			if (mapAlto.find(w.vectArticle[i].alto)!= mapAlto.end())
			{
				if (w.vectArticle[i].alto==currentAltoFile)
				{
					altoblock t = mapAlto[w.vectArticle[i].alto];
					
					if (t.mapalto.find(w.vectArticle[i].block) != t.mapalto.end())
					{
						Block block = t.mapalto[w.vectArticle[i].block];							
						x = block.vpos*multiImage ;
						y = block.hpos*multiImage;
						width = block.width*multiImage;
						height =  block.height*multiImage;												
						painter.drawRect( x,y, width,height);						
					}			
				}	
			}	 
		}	
		m_ui->label->setPixmap(originalPixmap);	
		m_ui->scrollArea->ensureVisible(x, y, m_ui->scrollArea->width()/2, m_ui->scrollArea->height()/2);
	}
}

// Creates the mapArticle data structure which maps
// the internal counter (unique int identifier) to an article with title and 
// a vector of typeBlock, which are triplets of (type, alto, block)
void w_structview::createArticle()
{	
	mapArticle.clear();
	int count =1;
	for (size_t i=0; i< vectItem.size(); i++)
	{	
		Article article;
		findBlockToArticle(vectItem[i], article.vectArticle);
		article.type = vectItem[i]->type;
		article.id = vectItem[i]->dmdId;
		article.title = vectItem[i]->label;		
		article.div = vectItem[i]->id;	
		mapArticle[vectItem[i]->counter] = article;
		count++;
	}
}

// Adds all blocks that are children of the given item to the array "output"
void w_structview::findBlockToArticle(Item *item, std::vector<typeBlock> &output)
{
	if (!item->vectTypeBlock.empty()) {
		for (size_t i = 0; i < item->vectTypeBlock.size(); ++i) {
			output.push_back(item->vectTypeBlock[i]);
		}
	}
	for (size_t i=0; i< item->children.size();i++)
	{		
		findBlockToArticle(&item->children[i], output);			
	}
}

void w_structview::create_page2toc_entry()
// The counter2TreeItem structure created in createTree must already exist
{
	m_page2toc_entry.clear();
	m_toc_entry2page.clear();
	for (std::map<int ,QTreeWidgetItem*>::const_iterator it = counter2TreeItem.begin(); it != counter2TreeItem.end(); it++)
	{
		QTreeWidgetItem *toc_entry = it->second;
		// Check for this TOC Entry in the list of articles
		std::map<int, Article>::const_iterator it_art = mapArticle.find(it->first);
		if (it_art != mapArticle.end()) {
			// Iterate over all the blocks for this article
			for (std::vector<typeBlock>::const_iterator it_block = it_art->second.vectArticle.begin(); 
				it_block != it_art->second.vectArticle.end(); ++it_block)
			{
				// For each block, add a reference to the TOC entry for that ALTO000X identifier in m_page2toc_entry
				m_page2toc_entry[it_block->alto].insert(toc_entry);
				// For each TOC entry, add a reference for each page where this TOC entry appears into m_toc_entry2page
				m_toc_entry2page[toc_entry->type()].insert(it_block->alto);
			}
		} else {
			// Something weird going on, the int identifier used should be the same in both counter2TreeItem and mapArticle
		}
	}	
}

void w_structview::openErrorScreen()
{
	//QPixmap xmap = QPixmap::grabWidget(this,0,35,this->width(),this->height()-160);
	
	QPixmap xmap1 = QPixmap::grabWidget(m_ui->treeWidget);
	QPixmap xmap2 = QPixmap::grabWidget(m_ui->scrollArea);
	
	//QPixmap result ( m_ui->treeWidget->width() + m_ui->scrollArea->width(), m_ui->scrollArea->height());
	QPixmap result ( xmap1.width() + xmap2.width(), xmap2.height());

	QPainter painter(&result);
	painter.drawPixmap(0,0, xmap1);
	painter.drawPixmap(xmap1.width(),0, xmap2);

	w_screenshoterror *ws = new w_screenshoterror();
	//ws->setBatchDetailImage(xmap,mets,this);
	ws->setBatchDetailImage(result,mets,this,mapTiffPath.find(currentPage)->second.fileId,currentPage);
	ws->resize(1200,1000);
	ws->show();	
}

void w_structview::enableButton(bool enable)
{
	m_ui->btnError->setEnabled(enable);
	m_ui->btnViewDir->setEnabled(enable);
	m_ui->btnViewMets->setEnabled(enable);
	m_ui->btnNext->setEnabled(enable);
	m_ui->btnViewHtml->setEnabled(enable);
	m_ui->btnZoomIn->setEnabled(enable);
	m_ui->btnZoomOut->setEnabled(enable);
	m_ui->btnFull->setEnabled(enable);
	m_ui->lblPage->setEnabled(enable);
	m_ui->btnPrevious->setEnabled(enable);
	m_ui->btnClearPainter->setEnabled(enable);
	if ( !enable ) {
		m_ui->btnDeleteSelectedItem->setEnabled(enable);
		currentWidgetSelected = 0;
	}
}

void w_structview::clear()
{
	changeNewDate = false;
	counter2TreeItem.clear();
	m_toc_entry2page.clear();
	m_page2toc_entry.clear();
    mapAltoPath.clear();
    mapAlto.clear();
    mapTiffPath.clear();	
    m_ui->listMets->clear();
    m_ui->treeWidget->clear();	
    m_ui->listErrors->clear();
	currentSelectedArticle=0;	
}

void w_structview::fillListSamplingStructure()
{	
	m_ui->listSampling->clear();
	 vListSampling = db.getListSamplingStructure(BatchDetail::getBatchDetail().idTestSet);
	
	for(size_t i=0;i <vListSampling.size(); i++)
	{		
		lstSampling = new QListWidgetItem(vListSampling[i].Mets.fileName.c_str(),  m_ui->listSampling,vListSampling[i].Mets.idMets);	
		if (vListSampling[i].checked ==1)
		lstSampling->setTextColor("red");	
	}
}

void w_structview::showListSampling()
{
	rbhelperSampling(true);
	rbhelperCalendar(false);
	rbhelperList(false);
}

void w_structview::viewCalendar()
{
	rbhelperCalendar(true);
	rbhelperSampling(false);
	rbhelperList(false);
}
void w_structview::viewList()
{
	rbhelperCalendar(false);
	rbhelperSampling(false);
	rbhelperList(true);
}
void w_structview::rbhelperCalendar(bool b){
	m_ui->calendarWidget->setVisible(b);
	m_ui->listMets->setVisible(b);
}
void w_structview::rbhelperSampling(bool b){
	m_ui->listSampling->setVisible(b);
	m_ui->btnChecked->setVisible(b);
	m_ui->btnUndo->setVisible(b);
	if ( b ) fillListSamplingStructure();
}
void w_structview::rbhelperList(bool b){
	contentsWindow->setVisible(b);

	if ( b ) {
        
		if ( mm == 0 ){
			mm =	qmain->menuBar()->addMenu("List View Option"); 
	       
			QAction* act = mm->addAction(tr("Sampling Selection"));
			connect(act, SIGNAL(triggered()), bookList, SLOT(samplingSelection()));

			act = mm->addAction(tr("All Books Selection"));
			connect(act, SIGNAL(triggered()), bookList, SLOT(allSelection()));
		}
	}else{
		if ( mm  ) {
			mm->close();
			delete mm;
			mm = 0;
		}
	}
}


// checked if the issues was validated
void::w_structview::checked()
{
	int i = m_ui->listSampling->currentRow();
	if ( i < 0 ) return;

	db.updateSamplingStructure(vListSampling[i].id,1);
	m_ui->listSampling->currentItem()->setTextColor("red");
}


void::w_structview::undo()
{
	int i = m_ui->listSampling->currentRow();
	if ( i < 0 ) return;

	db.updateSamplingStructure(vListSampling[i].id,0);
	m_ui->listSampling->currentItem()->setTextColor("black");
}

//! fill list of errors of the current Mets
void w_structview::fillListErrors()
{
	minor=0;
	major=0;
	blocking=0;
	
	//m_ui->btnViewHtml->setEnabled(false);
	m_ui->listErrors->clear();
	m_ui->btnDeleteSelectedItem->setEnabled(false);
	std::vector<StructureError> vListErrors = db.getStructureError(mets.idMets);

	for ( std::vector<StructureError>::iterator it = vListErrors.begin(); it != vListErrors.end(); it++)
	{
		std::stringstream txt;

		if (it->fileid.length() != 0)
			txt << it->fileid <<  ":" ;
		txt << it->errorType.severity.gravity  << ": " << it->getError() << " - " << it->message;
		QListWidgetItem* temp  = new QListWidgetItem(txt.str().c_str(),  m_ui->listErrors);	
		temp->setData(Qt::UserRole,QVariant(it->id));
		//m_ui->btnViewHtml->setEnabled(true);
		
		if (it->errorType.severity.gravity=="MINOR")	minor++;		
		else if (it->errorType.severity.gravity=="MAJOR") major++;
		else if (it->errorType.severity.gravity=="BLOCKING") blocking++;		
	}
	setLabel(minor,major,blocking);
}

void w_structview::setLabel(int minor,int major,int blocking){
	initLabel(m_ui->lbl_blocking,"Blocking :",blocking);
	initLabel(m_ui->lbl_major,"Major :",major);
	initLabel(m_ui->lbl_minor,"Minor :",minor);
}

void w_structview::initLabel(QLabel * lbl,char* mess,int val){
	if ( val == 0 ) {
		lbl->setText(mess);
	}else{
		std::stringstream ss;
		ss << mess << " " << val;
		lbl->setText(ss.str().c_str());
	}
}

//! view the error in html
void w_structview::viewHtml()
{
	FILE *fp;	
	int count=0;
		
	std::string path = BatchDetail::getBatchDetail().getErrorPath()  + "/error.html";	
	path = slash_path(path);	
	DeleteFileA(path.c_str());
	fopen_s(&fp,path.c_str(), "a");
	
	if(!fp)
	{			
		fclose(fp);
	}
	// Write header
	fprintf(fp, "<html>");
	fprintf(fp, "<head>");
	fprintf(fp, "<link rel=\"stylesheet\" href=\"../css/error_style.css\" type=\"text/css\">");
	fprintf(fp, "</head>");
	fprintf(fp, "<body>");
	
	std::map<std::string,std::vector<StructureError> > vStructureError = db.getBatchStructureError(BatchDetail::getBatchDetail().idTestSet);	 
	
	
	for ( std::map<std::string,std::vector<StructureError> >::iterator it = vStructureError.begin(); it != vStructureError.end(); it++)
	{	
		std::vector<StructureError> & ref = it->second;

		

		if ( ref.size() > 0 ) { // skip empty file
			fprintf(fp, "<h3>%s</h3>\n",it->first.c_str());
		
			for ( std::vector<StructureError>::iterator itt = ref.begin(); itt != ref.end(); itt++)
			{	
				fprintf(fp, "<h4>%s  (p.%d)</h4>\n", itt->getError().c_str(),itt->pagenb);
				fprintf(fp, "<img  width=\"600\"  src=\"%s\"/>\n", itt->pathImage.c_str());
				fprintf(fp, "<p>%s</p>\n", itt->message.c_str());	
				fprintf(fp, "<br>\n");
			}
			count += 1;
		}
	}
	// Write footer
	fprintf(fp, "</body>");
	fprintf(fp, "</html>");

	fclose(fp);	

	if ( count != 0) {
		ShellExecuteA(NULL, "open",path.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}else{
		// No export but the file is empty and create
		std::stringstream ss;
		ss << "No structure error to export" <<  std::endl ;
		static QErrorMessage* Qerror= new QErrorMessage();
		Qerror->showMessage(ss.str().c_str());
	}
}

void w_structview::viewMetsFile()
{
	ShellExecuteA(NULL, "open", (BatchDetail::getBatchDetail().path + "/" + mets.path + "/" + mets.fileName).c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void w_structview::viewMetsDir()
{
	ShellExecuteA(NULL, "open", (BatchDetail::getBatchDetail().path + "/" + mets.path ).c_str(), NULL, NULL, SW_SHOWNORMAL);
}