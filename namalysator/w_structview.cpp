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
namespace fs = boost::filesystem;

w_structview::w_structview(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_structview),
	m_colors()
{
    m_ui->setupUi(this);
  
	createActions();
	createConnections();
	changeNewDate = false;
	currentPage=1;
	m_ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_ui->label->setScaledContents(true);
	m_ui->btnViewHtml->setEnabled(false);
	m_ui->scrollArea->setWidget(m_ui->label);
	enableButton(false);	
    currentLevel=1;
    currentItem=0;	
    divImage = 5;
    multiImage =  0.2;  
    currentSelectedArticle =0;
    m_ui->btnStructure->setVisible(false);
	viewCalendar();

	bookList = new w_booklist(db);
	m_ui->bookW->setWidget(bookList);
	m_ui->bookW->setWidgetResizable(true);
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
	connect(m_ui->btnError,SIGNAL(clicked()),this,SLOT(openErrorScreen()));
	connect(m_ui->btnClearPainter,SIGNAL(clicked()),this,SLOT(clearPainter()));
//	connect(m_ui->btnShowSampling,SIGNAL(clicked()),this,SLOT(showListSampling()));		
	connect(m_ui->btnViewHtml,SIGNAL(clicked()),this,SLOT(viewHtml()));
	connect(m_ui->btnZoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(m_ui->btnZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
	connect(m_ui->zoomNormal, SIGNAL(clicked()), this, SLOT(zoomNon()));
	connect(m_ui->rbCalendar, SIGNAL(clicked()), this, SLOT(viewCalendar()));
	connect(m_ui->rbList, SIGNAL(clicked()), this, SLOT(viewList()));
	connect(m_ui->rbSampling,SIGNAL(clicked()),this,SLOT(showListSampling()));
	connect(m_ui->btnChecked, SIGNAL(clicked()), this, SLOT(checked()));
	connect(m_ui->btnUndo, SIGNAL(clicked()), this, SLOT(undo()));
	connect(m_ui->btnViewMets, SIGNAL(clicked()), this, SLOT(viewMetsFile()));
}

w_structview::~w_structview()
{
    delete m_ui;
}

//set detail of the batch
void w_structview::setBatchDetail()
{ 	
	//batch = d; 
	db.setDataBaseName(BatchDetail::getBatchDetail().database);  
	m_ui->calendarWidget->setVisible(true);
	m_ui->listMets->setVisible(true);
	m_ui->rbCalendar->setChecked(true);	
	
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
		m_colors.set_schema(mets.docType);
		delete MetsOnDate;
	}	
}

//! event when click on the listItem
 void w_structview::getIdMets(QListWidgetItem* item )
{
	if (BatchDetail::getBatchDetail().getMetsByID(item->type(), mets)) {
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
//! show the current page
void w_structview::showCurrentPage()
{		
	
	if (mapTiffPath.find(currentPage)!= mapTiffPath.end())
	{		
		std::string path = BatchDetail::getBatchDetail().path + mets.path + mapTiffPath.find(currentPage)->second.fileName;
		originalImage.load(path.c_str());			
		image = originalImage.scaled(originalImage.width()/divImage,originalImage.height()/divImage);
		originalPixmap = QPixmap::fromImage(image);		
		m_ui->label->setPixmap(originalPixmap);
		scaleFactor = 1.0;
		m_ui->label->adjustSize();	
		currentAltoFile = mapAltoPath.find(currentPage)->second.fileId;
		m_ui->lblPage->setValue(currentPage);
		m_ui->lblPage->setMaximum(mapTiffPath.size());
		updateTableOfContents(currentAltoFile);	
		// TODO : Add call to drawRect
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
		// If the current article is still on the new current page, redraw its rectangles
		if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
			drawRect(currentSelectedArticle, 0);
		}
	}
}
void w_structview::next()
{
	if (currentPage < mapTiffPath.size()) {
		currentPage++;
		showCurrentPage();
		// If the current article is still on the new current page, redraw its rectangles
		if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
			drawRect(currentSelectedArticle, 0);
		}
	}
}

void w_structview::showPage(int i)
{
	if ( i <= mapTiffPath.size() && i >=1 ) {
		currentPage=i;
	}else{
		if ( i <= 1 ) {
			currentPage=1;
		}else{
			currentPage=mapTiffPath.size();
		}
	}
		showCurrentPage();
		// If the current article is still on the new current page, redraw its rectangles
		if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
			drawRect(currentSelectedArticle, 0);
		}
	
}

void w_structview::zoomIn()
{
   scaleImage(1.25);
   divImage = divImage * 0.8;
   multiImage = multiImage / 0.8;
   resizeImage();

   if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
		drawRect(currentSelectedArticle, 0);
	}
}

 void w_structview::zoomOut()
 {
	divImage = divImage /0.8;
	multiImage = multiImage * 0.8;
	resizeImage();
    scaleImage(0.8);

	if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
		drawRect(currentSelectedArticle, 0);
	}
 }

 void w_structview::zoomNon()
 {
	divImage = 1;
	multiImage = 1;
	scaleFactor = 1;
	resizeImage();
    scaleImage(1);

	if (currentSelectedArticle && (m_toc_entry2page[currentSelectedArticle->type()].find(currentAltoFile) != m_toc_entry2page[currentSelectedArticle->type()].end())) {
		drawRect(currentSelectedArticle, 0);
	}
 }



 
 void w_structview::resizeImage()
 {
 	std::string file;
	file = mets.fileName.substr(0, mets.fileName.length()-9);
	image = originalImage.scaled(originalImage.width()/divImage,originalImage.height()/divImage);	
	originalPixmap = QPixmap::fromImage(image);		
	m_ui->label->setPixmap(originalPixmap);
 }

 void w_structview::clearPainter()
 {
	originalPixmap = QPixmap::fromImage(image);
	QPainter painter(&originalPixmap);		
	m_ui->label->setPixmap(originalPixmap);	
 }
 
 //scale the image
 void w_structview::scaleImage(double factor)
 { 
     scaleFactor *= factor;
     m_ui->label->resize(scaleFactor *m_ui->label->pixmap()->size());
     adjustScrollBar(m_ui->scrollArea->horizontalScrollBar(), factor);
     adjustScrollBar(m_ui->scrollArea->verticalScrollBar(), factor);
 }
//adjust scrollbar from scaling
 void w_structview::adjustScrollBar(QScrollBar *scrollBar, double factor)
 {
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
 }

 void w_structview::structure()
 { 
	m_ui->label->adjustSize();
    paintAllStructure(currentAltoFile);  
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
		altoparser ap(path,it->second,&mapAlto,dpi);	
		if (ParseDocument(path.c_str(),&ap)!=0)	
		{						
			// print error				
		}
		else
		{							
			mapAlto[it->second.fileId]=ap.getAltoBlock();
		}		
	}
	m_colors.set_schema(mets.docType);
    createTree();
    createArticle();
	create_page2toc_entry();
}


void w_structview::paintAllStructure(std::string altoFile)
// This function should paint the current page with the different lowest-level colors, including headings and captions in yellow
// It remains to be implemented
{
	int x,y,width,height;

	originalPixmap = QPixmap::fromImage(image);
	QPainter painter(&originalPixmap);
	
/*	for (std::set<std::pair<std::string,std::string>>::iterator it = blockAltoDmd.begin(); it != blockAltoDmd.end(); it++)
	{	
		if (it->second !="Newspaper")
		if (it->second.find("MODSMD_ISSUE") != std::string::npos)
		if (it->second != "MODSMD_PRINT MODSMD_ELEC")
		if( it->first == altoFile)
		{
			for (std::map<int,Article>::iterator itArticle = mapArticle.begin(); itArticle != mapArticle.end(); itArticle++)
			{
				if (itArticle->second.id == it->second)
				{
					for (size_t i=0;i< itArticle->second.vectArticle.size();i++)
					{
						altoblock t = mapAlto[altoFile];
						typeBlock ab = itArticle->second.vectArticle[i];
						
						Block block = t.mapalto[ab.block];						
						x = block.vpos*multiImage ;
						y = block.hpos*multiImage;
						width = block.width*multiImage;
						height =  block.height*multiImage;	
						
						if (ab.type=="HEADING")
						{
							QBrush b1( Qt::yellow );						
							painter.setBrush( b1 );
							painter.setOpacity(0.25);
							painter.drawRect( x,y, width,height);	
							
						}
						else if (ab.type=="PARAGRAPH")
						{
							QBrush b1( Qt::green);							
							painter.setBrush( b1 );
							painter.setBrush(Qt::NoBrush);
							painter.setOpacity(1);						
							painter.setPen(Qt::green);			
						}
						else
						{
							QBrush b1( Qt::blue );
							painter.setBrush( b1 );
							painter.setOpacity(0.25);													
						}
						painter.drawLine( x, y, x, y+height ) ;	
						painter.drawLine( x+ width, y, x+ width, y+height ) ;			
					}					
				}			
			}		
		}
		m_ui->label->setPixmap(originalPixmap);
		m_ui->scrollArea->setWidget(m_ui->label);			
	}*/
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
	widget->setText(0,item2->label.c_str());
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
				if(it->second.fileId == currentAltoFile)
					currentPage = it->first;				
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
	QPixmap xmap = QPixmap::grabWidget(this,0,35,this->width(),this->height()-160);
	w_screenshoterror *ws = new w_screenshoterror();
	ws->setBatchDetailImage(xmap,mets,this);
	ws->resize(1200,910);
	ws->show();	
}

void w_structview::enableButton(bool enable)
{
	m_ui->btnError->setEnabled(enable);
	m_ui->btnNext->setEnabled(enable);
	m_ui->btnZoomIn->setEnabled(enable);
	m_ui->btnZoomOut->setEnabled(enable);
	m_ui->btnNext->setEnabled(enable);
	m_ui->btnPrevious->setEnabled(enable);
	m_ui->btnClearPainter->setEnabled(enable);	
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
    m_ui->btnViewHtml->setEnabled(false);
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
	m_ui->bookW->setVisible(b);
}


// checked if the issues was validated
void::w_structview::checked()
{
	db.updateSamplingStructure(vListSampling[m_ui->listSampling->currentRow()].id,1);
	m_ui->listSampling->currentItem()->setTextColor("red");
}


void::w_structview::undo()
{
	db.updateSamplingStructure(vListSampling[m_ui->listSampling->currentRow()].id,0);
	m_ui->listSampling->currentItem()->setTextColor("black");
}

//! fill list of errors of the current Mets
void w_structview::fillListErrors()
{
	int minor=0;
	int major=0;
	int blocking=0;
	
	m_ui->btnViewHtml->setEnabled(false);
	m_ui->listErrors->clear();
	std::map<int,StructureError> vListErrors = db.getStructureError(mets.idMets);
	for ( std::map<int,StructureError>::iterator it = vListErrors.begin(); it != vListErrors.end(); it++)
	{
		std::string txt;
		txt =it->second.errorType.severity.gravity  + ": " + it->second.errorType.error + " - " + it->second.message;
		new QListWidgetItem(txt.c_str(),  m_ui->listErrors,mets.idMets);	
		m_ui->btnViewHtml->setEnabled(true);
		
		if (it->second.errorType.severity.gravity=="MINOR")	minor++;		
		else if (it->second.errorType.severity.gravity=="MAJOR") major++;
		else if (it->second.errorType.severity.gravity=="BLOCKING") blocking++;		
	}
	QString ss;
//	m_ui->lbMinor->setText(ss.setNum(minor));
//	m_ui->lbMajor->setText(ss.setNum(major));
//	m_ui->lbBlocking->setText(ss.setNum(blocking));
}

//! view the error in html
void w_structview::viewHtml()
{
	FILE *fp;	
	
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream errorImgPath;		
	errorImgPath << CurrentPath << "/ErrorImg/" ; 	
	std::string path = errorImgPath.str() + "error.html";	
	path = slash_path(path);	
	DeleteFileA(path.c_str());
	fopen_s(&fp,path.c_str(), "a");
	
	if(!fp)
	{			
		fclose(fp);		
	}	
	vStructureError = db.getStructureError(mets.idMets);	 
	
	for ( std::map<int,StructureError>::iterator it = vStructureError.begin(); it != vStructureError.end(); it++)
	{	
		fprintf(fp, "<h1>");	
		fprintf(fp,it->second.errorType.error.c_str());
		fprintf(fp, "</h1>");	
		fprintf(fp, "<h3>");	
		fprintf(fp, it->second.message.c_str());
		fprintf(fp, "<h3>");	
		//fprintf(fp, "<img =\"500px\" height=\"500px\"    src=\"");		
		fprintf(fp, "<img    src=\"");
		fprintf(fp, it->second.pathImage.c_str());
		fprintf(fp, "\"/>");
		fprintf(fp, "<br>");			
	}	
	fclose(fp);	
	ShellExecuteA(NULL, "open",path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void w_structview::viewMetsFile()
{
	ShellExecuteA(NULL, "open", (BatchDetail::getBatchDetail().path + "/" + mets.path + "/" + mets.fileName).c_str(), NULL, NULL, SW_SHOWNORMAL);
}