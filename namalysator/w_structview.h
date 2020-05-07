#ifndef W_STRUCTVIEW_H
#define W_STRUCTVIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include "structgui.h"
#include <fstream>
#include <set>
#include "dbrequest.h"
#include "logstruct_colors.h"
#include "bookModel.h"
#include "w_booklist.h"
#include "w_thumb.h"
#include <QSortFilterProxyModel>


namespace Ui {
    class w_structview;
}

class w_structview : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_structview)
public:
    explicit w_structview(QWidget *parent = 0);
    virtual ~w_structview();
	
	 void setBatchDetail();
	 void fillListErrors();

	 void setCurrentMets(MetsFile mets);
	void setQMainWindow(QMainWindow*);
protected:
    virtual void changeEvent(QEvent *e);

private:
	
	int minor;
	int major;
	int blocking;
	QMenu* menu;
	QMenu* mm ;
	QDockWidget*    contentsWindow;
	QMainWindow* qmain;
    Ui::w_structview *m_ui;
	logstruct_colors	m_colors;
    std::map<int,MetsFile> mapMets;
    QListWidgetItem *lst;	   
    //BatchDetail batch;
    dbrequest db;
    int currentPage;
    int maxPage;
    MetsFile mets;
    void showCurrentPage(); 
	void setLabel(int,int,int);
	void initLabel(QLabel * lbl,char* mess,int val);
    Item *treeContents;
    bool changeNewDate;
	w_booklist * bookList;
    
    QAction *zoomInAct;   
    QAction *zoomOutAct;
	QAction *zoomNextAct;   
    QAction *zoomPreviousAct;

	w_thumb *thumb ;
    
    /*********** functions  *********/
    
		//resize image
		void resizeImage();
		void createActions();
		void createArticle();
		void findBlockToArticle(Item *item, std::vector<typeBlock> &output);
		void create_page2toc_entry();
		
	/******* déclarations **********/   
    QImage image,originalImage;
    
    // Maps the page number (starting from 1) to the corresponding TIFFID and ALTOID
    std::map<int,LinkedFiles> mapAltoPath;
    std::map<int,LinkedFiles> mapTiffPath;     
    // maps alto blocks tro the current id
    std::map<std::string,altoblock> mapAlto;
    
    Item *rootItem;
    int currentLevel;
	Item *currentItem;
	QTreeWidgetItem *currentWidget;
	QListWidgetItem *currentWidgetSelected;
    void metsAltoParser();
    void createTree();
    void fillComboBoxError();
    void constructTOCrecursively(Item *item,QTreeWidgetItem *widget);     
    QTreeWidgetItem *a;

    QPainter painter;
    QPixmap originalPixmap;
    std::string currentAltoFile;
    std::vector<Item*> vectItem;
  
	// map which maps the page (ALTO0000X) to a set of Items in the table of contents
	std::map<std::string, std::set<QTreeWidgetItem *> > m_page2toc_entry;
	// Do the inverse, map the TOC entries (using the internal counter) to the set of ALTO identifier (ALTO0000X)
	// of the pages where the TOC entry has blocks
	std::map<int, std::set<std::string> > m_toc_entry2page;
    std::map<int,StructureError> vStructureError;
    double divImage,multiImage;    
    
    //maps an unique int with the article
	std::map<int,Article> mapArticle;
	
	//Set up a container for all the qtreeWidgetItem so that we can update the table of contents
	// It maps the internal counter (unique ID, also used for the mapArticle) to the QTreeWidgetItem*
	std::map<int ,QTreeWidgetItem*> counter2TreeItem;

	// a map which maps the current page (ALTO0000X) to an array of typeBlock, which tells paintAllStructure which type
	// of block each ALTO block on that page is. The types of blocks are calculated based the types defined in m_colors.
	// If a type is in m_colors (e.g. ARTICLE), then all its children will be ARTICLE, unless the children are themselves
	// in m_colors (e.g. ILLUSTRATION), in which case the color for the child overrides the color for the parent
	std::map<std::string, std::vector<typeBlock> > m_page2blocks;
	
	//update table of contents
	void updateTableOfContents(std::string currentAlto);
	void enableButton(bool enable);
	QTreeWidgetItem *currentSelectedArticle;
	void fillListSamplingStructure();	
	void clear();
	std::vector<Sampling_Structure> vListSampling;
	void createConnections();
	QListWidgetItem *lstSampling;
	
	void construct_page2blocks();
	void construct_page2blocks_recursive(const std::string &current_type, Item *item);
	void currentPageChange();

private slots :	
	void getDate(QDate);  
	void getIdMetsII(int);
	void showThumb(int);
	void getIdMets(QListWidgetItem*);
	void showError(QListWidgetItem*);
	void previous();
	void next();
	void showPage(int);
	void zoomIn();
    void zoomOut();
	void zoomNon();
	void zoomFull();
	void structure();
	void clearPainter();	
	void drawRect(QTreeWidgetItem *item,QTreeWidgetItem *item2);
	void openErrorScreen();
	void showListSampling();
	void viewCalendar();
	void viewList();
	void checked();
	void undo();
	void viewHtml();
	void viewMetsFile();
	void viewMetsDir();
	void deleteSelectedItem();
	void deleteListItem(int item);

	void rbhelperCalendar(bool);
	void rbhelperSampling(bool);
	void rbhelperList(bool);
};

#endif // W_STRUCTVIEW_H
