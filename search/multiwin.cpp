#include "multiwin.h"


Multiwin::Multiwin(std::string config_file) : QWidget(NULL){
  get_config_inputs(config_file, config_inputs);
  myIndexFileName = config_inputs["INDEX_FILE"];


  //make a search engine and parse all the files
  parser = new MDPageParser;
  searchEngine = new SearchEng;
  searchEngine->add_parse_from_index_file(myIndexFileName, parser);

  QHBoxLayout* mainLayout = new QHBoxLayout();
  setLayout(mainLayout);
  setWindowTitle("Emanuel's Google");
  resize(600, 340);

  andRButtonIsClicked = false;
  orRButtonIsClicked = false;
  singleWordRButtonIsClicked = false;


/****************************************************************************************************************/
  //right side of main window, search words input and search button and radio buttons for search type
  QVBoxLayout* rightSideMainLayout = new QVBoxLayout;
  mainLayout->addLayout(rightSideMainLayout);//add the right side to the overall layout

  //make label above search box/line
  searchInputLabel = new QLabel("Enter Words to Search Below");
  rightSideMainLayout->addWidget(searchInputLabel);

  //add line edit widgit for search words entry
  searchWordsInput = new QLineEdit();
  QObject::connect(searchWordsInput, SIGNAL(returnPressed()), this, SLOT(searchButtonClicked()));
  rightSideMainLayout->addWidget(searchWordsInput);

  //add the three radio buttons
  //add AND Radio Button
  andRButton = new QRadioButton("&AND");
  rightSideMainLayout->addWidget(andRButton);
  QObject::connect(andRButton, SIGNAL(clicked()), this, SLOT(andRButtonClicked()));
  //add OR Radio Button 
  QRadioButton* orRButton = new QRadioButton("O&R");
  rightSideMainLayout->addWidget(orRButton);
  QObject::connect(orRButton, SIGNAL(clicked()), this, SLOT(orRButtonClicked()));
  //add Single Word Radio Button
  QRadioButton* singleWordRButton = new QRadioButton("Single &Word");
  singleWordRButton->setChecked(true);
  singleWordRButtonIsClicked = true;// :( i didn't use the isChecked property
  rightSideMainLayout->addWidget(singleWordRButton);
  QObject::connect(singleWordRButton, SIGNAL(clicked()), this, SLOT(singleWordRButtonClicked()));

  //make the search button
  searchButton = new QPushButton("&Search");
  rightSideMainLayout->addWidget(searchButton);
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));

  //make the Quit button
  quitButton = new QPushButton("&quit");
  rightSideMainLayout->addWidget(quitButton);
  QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButtonClicked()));


  //**********************************************************************************************

  //left side of main window, contains listbox of filenames from search and the 3 search types
  QVBoxLayout* leftSideMainLayout = new QVBoxLayout;

  //labels for incoming and outgoing
  linkNumLabel = new QHBoxLayout();
  filenameLabel = new QLabel("Filename                 #In         #Out");

  linkNumLabel->addWidget(filenameLabel);

  leftSideMainLayout->addLayout(linkNumLabel);

  //add list box containing filenames of the search result
  filenamesList = new QListWidget();
  leftSideMainLayout->addWidget(filenamesList);
  QObject::connect(filenamesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(filesnameListItemDblClicked(QListWidgetItem*) ) );

  //adding sorting buttons
  sortByPageRankButton = new QPushButton("Sort By &PageRank");
  leftSideMainLayout->addWidget(sortByPageRankButton);
  QObject::connect(sortByPageRankButton, SIGNAL(clicked()), this, SLOT(sortByPageRankButtonClicked() ) );

  sortByNameButton = new QPushButton("Sort By &FileName");
  leftSideMainLayout->addWidget(sortByNameButton);
  QObject::connect(sortByNameButton, SIGNAL(clicked()), this, SLOT(sortByNameButtonClicked()));

  sortByIncomingButton = new QPushButton("Sort By Number of &Incoming Links");
  leftSideMainLayout->addWidget(sortByIncomingButton);
  QObject::connect(sortByIncomingButton, SIGNAL(clicked()), this, SLOT(sortByIncomingButtonClicked()));

  sortByOutgoingButton = new QPushButton("Sort By Number of &Outgoing Links");
  leftSideMainLayout->addWidget(sortByOutgoingButton);
  QObject::connect(sortByOutgoingButton, SIGNAL(clicked()), this, SLOT(sortByOutgoingButtonClicked()));

  //add left layout to main layout
  mainLayout->addLayout(leftSideMainLayout);

  //**********************************************************************

  //this is the WEBPAGE POP UP WINDOW

  displayWin = new QWidget;
  displayLayout = new QVBoxLayout;
  displayWin->setLayout(displayLayout); //puts the displayLayout on the pop up window
  displayWin->resize(720,680);
  displayWinLabel = new QLabel();
  linkLists = new QHBoxLayout();

  webpageContentsText = new QTextEdit();
  webpageContentsText->setReadOnly(true);

  linksLabelLayout = new QHBoxLayout();
  outLinksLabel = new QLabel("Outgoing Links:");
  inLinksLabel = new QLabel("Incoming Links:");

  displayLayout->addWidget(displayWinLabel);// add wp label and the contents in QTextEdit
  displayLayout->addWidget(webpageContentsText);

  displayLayout->addLayout(linksLabelLayout);
  displayLayout->addLayout(linkLists);

  outgoingLinkList = new QListWidget();
  QObject::connect(outgoingLinkList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(filesnameListItemDblClicked(QListWidgetItem*) ) );
  
  incomingLinkList = new QListWidget();
  QObject::connect(incomingLinkList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(filesnameListItemDblClicked(QListWidgetItem*) ) );

  linksLabelLayout->addWidget(inLinksLabel);
  linksLabelLayout->addWidget(outLinksLabel);
  linkLists->addWidget(incomingLinkList);
  linkLists->addWidget(outgoingLinkList);

  /// add three new sort buttons here 
  sortNameButton = new QPushButton("Sort By &Name");
  displayLayout->addWidget(sortNameButton);
  QObject::connect(sortNameButton, SIGNAL(clicked()), this, SLOT(sortNameButtonClicked()));

  sortIncomingButton = new QPushButton("Sort By &Incoming");
  displayLayout->addWidget(sortIncomingButton);
  QObject::connect(sortIncomingButton, SIGNAL(clicked()), this, SLOT(sortIncomingButtonClicked()));

  sortOutgoingButton = new QPushButton("Sort By &Outgoing");
  displayLayout->addWidget(sortOutgoingButton);
  QObject::connect(sortOutgoingButton, SIGNAL(clicked()), this, SLOT(sortOutgoingButtonClicked()));

  exitButton = new QPushButton("&close");
  displayLayout->addWidget(exitButton);
  QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(exitButtonClicked()));

}

Multiwin::~Multiwin(){

  delete parser;
  delete searchEngine;

}

void Multiwin::searchButtonClicked()
{
  //clear ListWidget
  filenamesList->clear();
  fileNames.clear();//clear vector containing filenames before adding to it

  if(!andRButtonIsClicked && !orRButtonIsClicked && !singleWordRButtonIsClicked){//no RButton pressed
    return;
  }

  //get the words from the search input 
  if(andRButtonIsClicked){ /// AND SEARCH ***************************************************

    //clear ListWidget
    filenamesList->clear();
    fileNames.clear();//clear vector containing filenames before adding to it

    if(searchWordsInput->text().isEmpty()){// didn't enter words to search for
      return;
    }

    std::string inputLineStr = searchWordsInput->text().toStdString(); 
    //convert input line into vector of the separate words and pass it into AND_command
    std::vector<std::string> inputWordsVect = get_words_to_search(inputLineStr); 
    std::set<WebPage*> search_result = searchEngine->AND_command(inputWordsVect);

    std::set<WebPage*>::iterator it;
    std::stringstream inOutSize;
    for(it = search_result.begin(); it !=search_result.end(); ++it){
      inOutSize << (*it)->incoming_links().size() << "                 " << (*it)->outgoing_links().size();
      filenamesList->addItem( QString::fromStdString( (*it)->filename() + "      " + inOutSize.str() ) );//convert QString
      fileNames.push_back( (*it)->filename() + "   " + inOutSize.str() );
      inOutSize.str(std::string() );//clear string
    }

  }
  else if(orRButtonIsClicked){ /// OR SEARCH ************************************************

    //clear ListWidget
    filenamesList->clear();
    fileNames.clear();//clear vector containing filenames before adding to it

    if(searchWordsInput->text().isEmpty()){// didn't enter words to search for
      return;
    }

    std::string inputLineStr = searchWordsInput->text().toStdString(); 
    //convert input line into vector of the separate words and pass it into AND_command
    std::vector<std::string> inputWordsVect = get_words_to_search(inputLineStr); 

    std::set<WebPage*> search_result = searchEngine->OR_command(inputWordsVect);

    std::set<WebPage*>::iterator it;
    std::stringstream inOutSize;
    for(it = search_result.begin(); it !=search_result.end(); ++it){
      inOutSize << (*it)->incoming_links().size() << "                 " << (*it)->outgoing_links().size();
      filenamesList->addItem( QString::fromStdString( (*it)->filename() + "      " + inOutSize.str() ) );//convert QString
      fileNames.push_back( (*it)->filename() + "   " + inOutSize.str() );
      inOutSize.str(std::string() );//clear string
    }
  }
  else if(singleWordRButtonIsClicked){ /// SINGLE WORD SEARCH *******************************
    //clear ListWidget
    filenamesList->clear();
    fileNames.clear();//clear vector containing filenames before adding to it

    if(searchWordsInput->text().isEmpty()){// didn't enter words to search for
      return;
    }

    std::string inputLineStr = searchWordsInput->text().toStdString(); 
    //convert input line into vector of the separate words and pass it into AND_command
    std::vector<std::string> inputWordsVect = get_words_to_search(inputLineStr);
    if(inputWordsVect.size() > 1){ // multiple words entered for single word search
      return;
    } 

    std::set<WebPage*> search_result = searchEngine->one_word_search(inputWordsVect[0]);

    std::set<WebPage*>::iterator it;
    std::stringstream inOutSize;// to display in and out links size, not working right now
    for(it = search_result.begin(); it !=search_result.end(); ++it){
      inOutSize << (*it)->incoming_links().size() << "                 " << (*it)->outgoing_links().size();
      filenamesList->addItem( QString::fromStdString( (*it)->filename() + "      " + inOutSize.str() ) );//convert QString
      fileNames.push_back( (*it)->filename() + "   " + inOutSize.str() );
      inOutSize.str(std::string() );//clear string
    }

  }
  sortByPageRankButtonClicked(); // default is by pagerank
}

void Multiwin::exitButtonClicked(){
  displayWin->hide();
}

void Multiwin::quitButtonClicked(){
  displayWin->hide();
  close();
}

void Multiwin::andRButtonClicked(){
  andRButtonIsClicked = true;
  orRButtonIsClicked = false;
  singleWordRButtonIsClicked = false;
}

void Multiwin::orRButtonClicked(){
  orRButtonIsClicked = true;
  andRButtonIsClicked = false;
  singleWordRButtonIsClicked = false; 
}

void Multiwin::singleWordRButtonClicked(){
  singleWordRButtonIsClicked = true;
  orRButtonIsClicked = false;
  andRButtonIsClicked = false;  
}

void Multiwin::sortByPageRankButtonClicked(){
  //calculate PageRank of all webpages in our candidate set

  //calculate initial pagerank for t = 0
  std::map<WebPage*, double> mapPageRankOf;
  int n = fileNames.size();//num of webpages
  double initPageRank = 1.0/(double)n;

  for(unsigned int i = 0; i < fileNames.size(); i++){
    mapPageRankOf.insert( std::make_pair(searchEngine->get_webpage_at(get_filename(fileNames[i])), initPageRank) );
  }

  //calculate pagerank from t = 1 -> t = STEP_NUMBER
  int t = 0;
  double E = 0.0;
  std::stringstream ss;
  ss << config_inputs["STEP_NUMBER"];
  ss >> t;
  const char* E_cstr = config_inputs["RESTART_PROBABILITY"].c_str();
  E = atof(E_cstr);

  int i = 1;
  double Sum = 0;
  std::map<WebPage*, double> newPageRank;
  while(i <= t){

    std::map<WebPage*, double>::iterator it;
    for(it = mapPageRankOf.begin(); it != mapPageRankOf.end(); ++it){//update P() of each webpage
      //std::cout << "Calculating P("<< (it->first)->filename() << ", " << i << " + 1)" << std::endl;

      double PR = 0;//used to hold pagerank of each webpage. will put calculated value in this

      MySet<WebPage*>::iterator u;
      Sum = 0;

      MySet<WebPage*> inSet = (it->first)->incoming_links();
      for(u = inSet.begin(); u != inSet.end(); ++u){//SUM of pageranks of incoming pages/their out_degree 

         if(mapPageRankOf.count(*u) ){//incoming link is in the candidate set
           //std::cout << " In Site: " << (*u)->filename() << std::endl;
           MySet<WebPage*> tempOutSet = (*u)->outgoing_links();
           MySet<WebPage*>::iterator c;
           int du = 0;
           for(c = tempOutSet.begin(); c != tempOutSet.end(); ++c){
            if(mapPageRankOf.count(*c) ){
               du++;
            }
           }

           // std::cout << "  du+ before adding self: " << du << std::endl;
           if( !(*u)->outgoing_links().count(*u) ){//add self loop if it doesnt have one already
            // std::cout << "       added self loop for out of u." << std::endl;
            du++;// add 1 to out degree
           }

           // std::cout << "  du+ after adding self: " << du << std::endl;
           // std::cout << "  Sum before update: " << Sum << std::endl;
           Sum += mapPageRankOf[ *u ] / (double)( du );
           // std::cout << "  SUM += PG/du+: " << mapPageRankOf[ *u ] << " / " << (double)( du ) << std::endl;
           // std::cout << "  Sum after update: " << Sum << std::endl;

         }
      }

      //calculate how much value "it" gets from linking to itself

      //calculate out degree of "it"
      if(!(it->first)->outgoing_links().count(it->first) ){   // if self loop doesnt already exist, add one
         int dv = 0;
         MySet<WebPage*>::iterator it6;
         MySet<WebPage*> calcOutSet = (it->first)->outgoing_links();
         for(it6 = calcOutSet.begin(); it6 != calcOutSet.end(); ++it6 ){
            if(mapPageRankOf.count(*it6) ){
               dv++;
            }
         }
         if(!mapPageRankOf.count(*it6) ){//add self loop
               dv++;// add 1 to out degree
         }
         Sum += mapPageRankOf[it->first] / ( (double) dv );
         // std::cout << " calculating page rank recieved from self loop: " << mapPageRankOf[it->first] / ( (double) dv ) << std::endl;
         // std::cout << "  PG/outDeg(v): " << mapPageRankOf[it->first] << " / " <<( (double) dv ) << std::endl;
      }

      //std::cout << "SIGMA for calculation: " << Sum << std::endl;
      PR = (1-E)*Sum;
      PR += E/(double)n;
      newPageRank.insert(std::make_pair(it->first, PR));
      //std::cout << "P("<< (it->first)->filename() << ", " << i << " + 1): " << PR << std::endl << std::endl;

    }

    mapPageRankOf = newPageRank;
    newPageRank.clear();

    i++;
  }

  // sort by PageRank
  // 1)convert map to a vector of pairs
  std::vector<std::pair<WebPage*, double> > vectPageRank;
  std::map<WebPage*, double>::iterator it4;
  for(it4 = mapPageRankOf.begin(); it4 != mapPageRankOf.end(); ++it4){
   vectPageRank.push_back(*it4);
  } 

  // 2) sort vector of pairs by pagerank
  pageRankComp comparePageRank;
  useMergeSort(vectPageRank, comparePageRank);

  //prints out webpages and their page ranks in descending order
  std::cout << std::endl << "vector of pages sorted by rank: " << std::endl;
  double SUMPGs = 0.0;
  for(unsigned int j = 0; j < vectPageRank.size(); j++){//print vector out for testing
   std::cout << (vectPageRank[j].first)->filename() << "  , "  << vectPageRank[j].second << std::endl;
   SUMPGs += vectPageRank[j].second;
  } 
  std::cout << "SUM: " << SUMPGs <<std::endl;

  // 3) update QListWidget
  std::vector<WebPage*> webpagesVect;
  for(unsigned int j = 0; j < vectPageRank.size(); j++){//print vector out for testing
   webpagesVect.push_back( vectPageRank[j].first );
  }

  //clear ListWidget
  fileNames.clear();
  filenamesList->clear();

  //fill ListWidget up with correctly ordered filenames
  std::stringstream inOutSize;// to display in and out links size
  for(unsigned int i = 0; i < webpagesVect.size(); ++i){
    inOutSize << webpagesVect[i]->incoming_links().size() << "                 " << webpagesVect[i]->outgoing_links().size();
    fileNames.push_back( webpagesVect[i]->filename() + "      " + inOutSize.str() );
    inOutSize.str(std::string() );//clear string
  }
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    filenamesList->addItem( QString::fromStdString( fileNames[i] ) );
  }

}

void Multiwin::sortByNameButtonClicked(){

  //put all the webpages that have filenames in the list into a vector of webpages 
  std::vector<WebPage*> webpagesVect;
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    webpagesVect.push_back(searchEngine->get_webpage_at( get_filename( fileNames[i] ) ) );
  }

  //make the comparator for this sort type
  filenameComp compareFilenames;
  useMergeSort(webpagesVect, compareFilenames);

  //clear ListWidget
  fileNames.clear();
  filenamesList->clear();

  //fill ListWidget up with correctly ordered filenames
  std::stringstream inOutSize;// to display in and out links size
  for(unsigned int i = 0; i < webpagesVect.size(); ++i){
    inOutSize << webpagesVect[i]->incoming_links().size() << "                 " << webpagesVect[i]->outgoing_links().size();
    fileNames.push_back( webpagesVect[i]->filename() + "      " + inOutSize.str() );
    inOutSize.str(std::string() );//clear string
  }
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    filenamesList->addItem( QString::fromStdString( fileNames[i] ) );
  }

}

void Multiwin::sortByIncomingButtonClicked(){

  //put all the webpages that have filenames in the list into a vector of webpages 
  std::vector<WebPage*> webpagesVect;
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    webpagesVect.push_back(searchEngine->get_webpage_at( get_filename( fileNames[i] ) ) );
  }

  //make the constuctor for this sort type
  incLinkSizeComp compareIncLinkSize;
  useMergeSort(webpagesVect, compareIncLinkSize);

  //clear ListWidget
  fileNames.clear();
  filenamesList->clear();

  //fill ListWidget up with correctly ordered filenames
  std::stringstream inOutSize;// to display in and out links size
  for(unsigned int i = 0; i < webpagesVect.size(); ++i){
    inOutSize << webpagesVect[i]->incoming_links().size() << "                 " << webpagesVect[i]->outgoing_links().size();
    fileNames.push_back( webpagesVect[i]->filename() + "      " + inOutSize.str() );
    inOutSize.str(std::string() );//clear string
  }
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    filenamesList->addItem( QString::fromStdString( fileNames[i] ) );
  } 
}

void Multiwin::sortByOutgoingButtonClicked(){

  //put all the webpages that have filenames in the list into a vector of webpages 
  std::vector<WebPage*> webpagesVect;
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    webpagesVect.push_back(searchEngine->get_webpage_at( get_filename( fileNames[i] ) ) );
  }

  //make the constuctor for this sort type
  outgLinkSizeComp compareOutgLinkSize;
  useMergeSort(webpagesVect, compareOutgLinkSize);

  //clear ListWidget
  fileNames.clear();
  filenamesList->clear();

  //fill ListWidget up with correctly ordered filenames
  std::stringstream inOutSize;
  for(unsigned int i = 0; i < webpagesVect.size(); ++i){
    inOutSize << webpagesVect[i]->incoming_links().size() << "                 " << webpagesVect[i]->outgoing_links().size();
    fileNames.push_back( webpagesVect[i]->filename() + "      " + inOutSize.str() );
    inOutSize.str(std::string() );//clear string
  }
  for(unsigned int i = 0; i < fileNames.size(); ++i){
    filenamesList->addItem( QString::fromStdString( fileNames[i] ) );
  }
}

void Multiwin::filesnameListItemDblClicked(QListWidgetItem* filenameItem){

  displayWin->setWindowTitle("Webpage: " + QString::fromStdString( get_filename( filenameItem->text().toStdString() ) ) );

  displayWinLabel->setText( QString::fromStdString( get_filename( filenameItem->text().toStdString() ) ) + ":\n" );

  std::string filename = get_filename( filenameItem->text().toStdString() );

  //stream contents of webpage into string stream and then get a string from the stream
  //to store in the textbox
  std::stringstream webpageContents;
  webpageContents << *(searchEngine->get_webpage_at(filename) );
  webpageContentsText->setPlainText( QString::fromStdString(webpageContents.str() ) );

//***********************************************************************************************************

    //   POPULATE LIST WIDGETS WITH INCOMING AND OUTGING LINKS SORTED BY FILENAME

  //clear list widgets
  outgoingLinkList->clear();
  incomingLinkList->clear();
  wpIncomingLinks.clear();
  wpOutgoingLinks.clear();

  //get string vectors of links
  std::set<WebPage*> incoming_links_set = (searchEngine->get_webpage_at(filename) )->incoming_links();
  std::set<WebPage*> outgoing_links_set = (searchEngine->get_webpage_at(filename) )->outgoing_links();

  std::set<WebPage*>::iterator it;
  for(it = incoming_links_set.begin(); it != incoming_links_set.end(); ++it){
    wpIncomingLinks.push_back( (*it) );
  }
  for(it = outgoing_links_set.begin(); it != outgoing_links_set.end(); ++it){
    wpOutgoingLinks.push_back( (*it) );
  }

  //sort vectors by filename
  filenameComp compareFilename;
  useMergeSort(wpIncomingLinks, compareFilename);
  useMergeSort(wpOutgoingLinks, compareFilename);

  //iterate through sorted vectors and add them to their respective ListWidget
  for(unsigned int i = 0; i < wpIncomingLinks.size(); i++){
    incomingLinkList->addItem( QString::fromStdString(wpIncomingLinks[i]->filename() ) );
  }
  for(unsigned int i = 0; i < wpOutgoingLinks.size(); i++){
    outgoingLinkList->addItem( QString::fromStdString(wpOutgoingLinks[i]->filename() ) );
  }

//***********************************************************************************************************
  
  displayWin->show();
}

void Multiwin::sortNameButtonClicked(){
  //   POPULATE LIST WIDGETS WITH INCOMING AND OUTGING LINKS SORTED BY FILENAME

  //clear list widgets
  outgoingLinkList->clear();
  incomingLinkList->clear();

  //sort vectors by filename
  filenameComp compareFilename;
  useMergeSort(wpIncomingLinks, compareFilename);
  useMergeSort(wpOutgoingLinks, compareFilename);

  //iterate through sorted vectors and add them to their respective ListWidget
  for(unsigned int i = 0; i < wpIncomingLinks.size(); i++){
    incomingLinkList->addItem( QString::fromStdString(wpIncomingLinks[i]->filename() ) );
  }
  for(unsigned int i = 0; i < wpOutgoingLinks.size(); i++){
    outgoingLinkList->addItem( QString::fromStdString(wpOutgoingLinks[i]->filename() ) );
  }

}

void Multiwin::sortIncomingButtonClicked(){

  //   POPULATE LIST WIDGETS WITH INCOMING AND OUTGING LINKS SORTED BY FILENAME

  //clear list widgets
  outgoingLinkList->clear();
  incomingLinkList->clear();

  //sort vectors by filename
  incLinkSizeComp compareIncoming;
  useMergeSort(wpIncomingLinks, compareIncoming);
  useMergeSort(wpOutgoingLinks, compareIncoming);

  //iterate through sorted vectors and add them to their respective ListWidget
  for(unsigned int i = 0; i < wpIncomingLinks.size(); i++){
    incomingLinkList->addItem( QString::fromStdString(wpIncomingLinks[i]->filename() ) );
  }
  for(unsigned int i = 0; i < wpOutgoingLinks.size(); i++){
    outgoingLinkList->addItem( QString::fromStdString(wpOutgoingLinks[i]->filename() ) );
  }
}

void Multiwin::sortOutgoingButtonClicked(){
      //   POPULATE LIST WIDGETS WITH INCOMING AND OUTGING LINKS SORTED BY FILENAME

  //clear list widgets
  outgoingLinkList->clear();
  incomingLinkList->clear();

  //sort vectors by filename
  outgLinkSizeComp compareOutgoing;
  useMergeSort(wpIncomingLinks, compareOutgoing);
  useMergeSort(wpOutgoingLinks, compareOutgoing);

  //iterate through sorted vectors and add them to their respective ListWidget
  for(unsigned int i = 0; i < wpIncomingLinks.size(); i++){
    incomingLinkList->addItem( QString::fromStdString(wpIncomingLinks[i]->filename() ) );
  }
  for(unsigned int i = 0; i < wpOutgoingLinks.size(); i++){
    outgoingLinkList->addItem( QString::fromStdString(wpOutgoingLinks[i]->filename() ) );
  }

}

//returns a vector of all words the user enters. The vector returned contains all lowercase words
std::vector<std::string> Multiwin::get_words_to_search(std::string inputLine){
  
  std::stringstream ss;
  std::vector<std::string> words_to_search;
  std::string temp_word;

  ss << inputLine; // convert input string line into a stream

  while(!ss.fail()){
    ss >> temp_word;
    if(!ss.fail()){ 
      str_to_lower(temp_word);
      words_to_search.push_back(temp_word);
    }
  }

  return words_to_search;
}

//convert a string to all lowercase, for non case sensitive funtionality
void Multiwin::str_to_lower(std::string& word){
  for(unsigned int i = 0; i < word.size(); i++){
    if(isalpha(word[i])){
      word[i] = char_to_lower(word[i]);
    }
  }
}

char Multiwin::char_to_lower(char c){
  if(c < 'a'){
    c += 32;
  }
  return c;
}

//override event for x button so I can hide second window before closing
void Multiwin::closeEvent(QCloseEvent *event)
{
  event = event;// doesn't do anything, used to get ride of unused variable event warning
  quitButtonClicked();
}

// takes a string containnig the filename, incoming size, outgoing size and returns just the filename
std::string Multiwin::get_filename(std::string itemString){
  std::string result;
  std::stringstream ss;
  ss << itemString;
  ss >> result;
  return result;
}

// void Multiwin::get_config_inputs(std::string config_file_str, std::map<std::string, std::string>& config_inputs){
//   std::ifstream config_file(config_file_str.c_str() );

//   if(config_file.fail()){
//     std::cout << std::endl<< "ERROR: Couldn't open configuration file." << std::endl << std::endl;
//   }

//   std::string line;
//   std::string param;
//   std::string val;
//   unsigned int i = 0;
//   while(!config_file.eof() && !config_file.fail() ){
//     getline(config_file, line);

//     if(config_file.fail()){ break;} // just finished last line of file

//     if(line.empty()){ continue;} // go to next line if empty
    
//     if(line[0] == '#'){ continue;} // skip line if comment #
    

//     i = 0;
//     // get parameter
//     while( line[i] != ' ' && line[i] != '='){// not a space and or =
//       param += line[i];
//       i++;
//     }
    
//     while(line[i] == ' ' || line[i] == '='){// skip all the spaces and = before value
//       i++;
//     }

//     //get val
//     while( line[i] != ' ' && line[i] != '#' && i < line.size() ){
//       val += line[i];
//       i++;
//     }

//     config_inputs.insert(make_pair(param, val));
//     param.clear();
//     val.clear();

//   }
// } 